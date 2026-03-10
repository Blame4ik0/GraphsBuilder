#include "graphwidget.h"

// ----------------------- INIT -----------------------

GraphWidget::GraphWidget (QWidget *parent) : QWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    pal.setColor(QPalette::Window, QColor(BG_R, BG_G, BG_B));
    setPalette(pal);
    setAutoFillBackground(true);
}

void GraphWidget::setPaintColor (QColor &color)
{
    paintColor = color;
    update();
}

// ----------------------- MATRIX -----------------------

void GraphWidget::matrixAddNode ()
{
    for (auto &row : adjMatrix) row.append(0);
    adjMatrix.append(QVector<int>(adjMatrix.size() + 1, 0));
}

void GraphWidget::matrixRemoveNode (int idx)
{
    adjMatrix.remove(idx);
    for (auto &row : adjMatrix) row.remove(idx);
}

// ----------------------- HELPERS -----------------------

double GraphWidget::distanceBetweenPointsSqr (QPointF &p1, QPointF &p2)
{
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();
    return dx*dx + dy*dy;
}

bool GraphWidget::isTooClose (QPointF &p1, QPointF &p2, double minDist)
{
    return distanceBetweenPointsSqr(p1, p2) < minDist * minDist;
}

QPointF GraphWidget::circleEdgePoint (Node &n, QPointF &target)
{
    double dx  = target.x() - n.position.x();
    double dy  = target.y() - n.position.y();
    double len = std::sqrt(dx*dx + dy*dy);
    return len < 1e-6 ? n.position : n.position + QPointF(dx, dy) / len * circleRadius;
}

int GraphWidget::nodeIndexFinder (QPointF &pos, double dist)
{
    for (int i = 0; i < nodes.size(); i++)
        if (distanceBetweenPointsSqr(pos, nodes[i].position) <= dist*dist) return i;
    return -1;
}

int GraphWidget::edgeIndexFinder (QPointF &p, double tol)
{
    int n = nodes.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (!adjMatrix[i][j]) continue;

            QPointF a  = circleEdgePoint(nodes[i], nodes[j].position);
            QPointF b  = circleEdgePoint(nodes[j], nodes[i].position);
            QPointF ab = b - a;
            QPointF ap = p - a;

            double t = std::max(0.0, std::min(1.0, QPointF::dotProduct(ap, ab) / QPointF::dotProduct(ab, ab)));
            QPointF d = ap - ab * t;

            if (QPointF::dotProduct(d, d) <= tol*tol) return i*n + j;
        }
    }

    return -1;
}

// ----------------------- DRAWING -----------------------

void GraphWidget::drawNode (Node &node, QPainter &p)
{
    p.setPen(QPen(paintColor, strokeWidth));
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(node.position, circleRadius, circleRadius);

    p.setPen(paintColor);
    p.setFont(QFont("Segoe UI", textWeight, QFont::Bold));

    QRectF textRect
        (
            node.position.x() - circleRadius,
            node.position.y() - circleRadius,
            circleRadius * 2,
            circleRadius * 2
            );

    p.drawText(textRect, Qt::AlignCenter, QString::number(node.index));
}

void GraphWidget::drawEdge (const QPointF &a, const QPointF &b, QPainter &p)
{
    p.setPen(QPen(paintColor, strokeWidth, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(a, b);
}

// ----------------------- EVENTS -----------------------

void GraphWidget::mousePressEvent (QMouseEvent *event)
{
    QPointF pos    = event->position();
    int     nodeIdx = nodeIndexFinder(pos, clickRadius);

    if (event->button() == Qt::RightButton)
    {
        if (nodeIdx >= 0)
        {
            matrixRemoveNode(nodeIdx);
            nodes.removeAt(nodeIdx);
            edgeFirstNodeIdx = -1;
        }
        else
        {
            int hit = edgeIndexFinder(pos, clickRadius + PLACEMENT_CONSTANT);

            if (hit >= 0)
            {
                int n = nodes.size();
                int i = hit / n;
                int j = hit % n;
                adjMatrix[i][j] = adjMatrix[j][i] = 0;
            }
        }
    }
    else if (event->button() == Qt::LeftButton)
    {
        if (currentMode == 0)
        {
            bool tooClose = false;

            for (Node &nd : nodes)
            {
                if (isTooClose(pos, nd.position, 2*clickRadius + PLACEMENT_CONSTANT))
                {
                    tooClose = true;
                    break;
                }
            }

            if (!tooClose && edgeIndexFinder(pos, circleRadius + PLACEMENT_CONSTANT) < 0)
            {
                nodes.append({pos, followingIndex++});
                matrixAddNode();
            }
        }
        else if (currentMode == 1 && nodeIdx >= 0)
        {
            if (edgeFirstNodeIdx < 0)
            {
                edgeFirstNodeIdx = nodeIdx;
                rubberBandEnd    = nodes[nodeIdx].position;
            }
            else
            {
                if (nodeIdx != edgeFirstNodeIdx)
                    adjMatrix[edgeFirstNodeIdx][nodeIdx] = adjMatrix[nodeIdx][edgeFirstNodeIdx] = 1;

                edgeFirstNodeIdx = -1;
            }
        }
    }

    update();
}

void GraphWidget::mouseMoveEvent (QMouseEvent *event)
{
    if (currentMode == 1 && edgeFirstNodeIdx >= 0)
    {
        rubberBandEnd = event->position();
        update();
    }
}

void GraphWidget::keyPressEvent (QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_C:
        nodes.clear();
        adjMatrix.clear();
        followingIndex   = 1;
        edgeFirstNodeIdx = -1;
        break;

    case Qt::Key_A:
        antialiasingEnabled = !antialiasingEnabled;
        break;

    case Qt::Key_Escape:
        edgeFirstNodeIdx = -1;
        break;

    default:
        QWidget::keyPressEvent(event);
        break;
    }

    update();
}

void GraphWidget::paintEvent (QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, antialiasingEnabled);

    int n = nodes.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (!adjMatrix[i][j]) continue;

            drawEdge(circleEdgePoint(nodes[i], nodes[j].position),
                     circleEdgePoint(nodes[j], nodes[i].position), painter);
        }
    }

    if (currentMode == 1 && edgeFirstNodeIdx >= 0 && edgeFirstNodeIdx < n)
    {
        painter.setPen(QPen(paintColor, strokeWidth, Qt::DashLine, Qt::RoundCap));
        painter.drawLine(circleEdgePoint(nodes[edgeFirstNodeIdx], rubberBandEnd), rubberBandEnd);
    }

    for (Node &node : nodes) drawNode(node, painter);
}
