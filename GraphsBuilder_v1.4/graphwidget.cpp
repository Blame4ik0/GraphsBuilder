#include "graphwidget.h"
#include "nodeeditor.h"
#include "edgeeditor.h"
#include <cmath>

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
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++)
    {
        adjMatrix[i].append(0);
        edgeData[i].append(EdgeData{});
    }
    adjMatrix.append(QVector<int>(n + 1, 0));
    edgeData.append(QVector<EdgeData>(n + 1, EdgeData{}));
}

void GraphWidget::matrixRemoveNode (int idx)
{
    adjMatrix.remove(idx);
    edgeData.remove(idx);
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        adjMatrix[i].remove(idx);
        edgeData[i].remove(idx);
    }
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
    double dx    = target.x() - n.position.x();
    double dy    = target.y() - n.position.y();
    double len   = std::sqrt(dx*dx + dy*dy);
    double ratio = circleRadius / len;
    return len < 1e-6 ? n.position : QPointF(n.position.x() + dx * ratio,
                                             n.position.y() + dy * ratio);
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

            double abx = b.x() - a.x(),  aby = b.y() - a.y();
            double apx = p.x() - a.x(),  apy = p.y() - a.y();
            double bpx = p.x() - b.x(),  bpy = p.y() - b.y();

            double lenAB = std::sqrt(abx*abx + aby*aby);
            if (lenAB < 1e-6) continue;

            double h     = std::abs(abx * apy - aby * apx) / lenAB;
            double lenAP = std::sqrt(apx*apx + apy*apy);
            double lenBP = std::sqrt(bpx*bpx + bpy*bpy);
            double dist  = (lenAP <= lenAB && lenBP <= lenAB) ? h : std::min(lenAP, lenBP);

            if (dist <= tol) return i*n + j;
        }
    }

    return -1;
}

// ----------------------- DRAWING -----------------------

void GraphWidget::drawArrow (const QPointF &tip, double angle, QPainter &p)
{
    const double len   = 12.0;
    const double spread = 0.4;

    QPolygonF head = {
        tip,
        { tip.x() - len * std::cos(angle - spread), tip.y() - len * std::sin(angle - spread) },
        { tip.x() - len * std::cos(angle + spread), tip.y() - len * std::sin(angle + spread) }
    };

    p.setPen(Qt::NoPen);
    p.setBrush(paintColor);
    p.drawPolygon(head);
    p.setBrush(Qt::NoBrush);
}

void GraphWidget::drawEdge (int i, int j, QPainter &p)
{
    QPointF   a  = circleEdgePoint(nodes[i], nodes[j].position);
    QPointF   b  = circleEdgePoint(nodes[j], nodes[i].position);
    EdgeData &ed = edgeData[i][j];

    p.setPen(QPen(paintColor, strokeWidth, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(a, b);

    if (ed.dir == EdgeDir::ItoJ)
        drawArrow(b, std::atan2(b.y() - a.y(), b.x() - a.x()), p);
    else if (ed.dir == EdgeDir::JtoI)
        drawArrow(a, std::atan2(a.y() - b.y(), a.x() - b.x()), p);

    if (ed.hasWeight)
    {
        p.setPen(paintColor);
        p.setFont(QFont("Segoe UI", 9, QFont::Bold));
        p.drawText((a + b) / 2.0 + QPointF(4, -4), QString::number(ed.weight, 'g', 4));
    }
}

void GraphWidget::drawNode (Node &node, QPainter &p)
{
    p.setPen(QPen(paintColor, strokeWidth));
    p.setBrush(QColor(BG_R, BG_G, BG_B));
    p.drawEllipse(node.position, circleRadius, circleRadius);

    p.setPen(paintColor);
    p.setFont(QFont("Segoe UI", textWeight, QFont::Bold));

    QString label = node.label.isEmpty() ? QString::number(node.index) : node.label;

    QRectF textRect
        (
            node.position.x() - circleRadius,
            node.position.y() - circleRadius,
            circleRadius * 2,
            circleRadius * 2
            );

    p.drawText(textRect, Qt::AlignCenter, label);
}

// ----------------------- DIALOGS -----------------------

void GraphWidget::openNodeEditor (int nodeIdx)
{
    NodeEditor dlg(nodes[nodeIdx], this);

    if (dlg.exec() == QDialog::Accepted)
    {
        nodes[nodeIdx].label = dlg.label();
        update();
    }
}

void GraphWidget::openEdgeEditor (int i, int j)
{
    EdgeEditor dlg(edgeData[i][j], nodes[i].index, nodes[j].index, this);

    if (dlg.exec() == QDialog::Accepted)
    {
        edgeData[i][j] = dlg.result();

        // Mirror to other side; flip direction
        edgeData[j][i].hasWeight = edgeData[i][j].hasWeight;
        edgeData[j][i].weight    = edgeData[i][j].weight;
        edgeData[j][i].dir       = (edgeData[i][j].dir == EdgeDir::ItoJ) ? EdgeDir::JtoI
                             : (edgeData[i][j].dir == EdgeDir::JtoI) ? EdgeDir::ItoJ
                                                                     : EdgeDir::None;

        if (edgeData[i][j].dir != EdgeDir::None) isDirected = true;
        if (edgeData[i][j].hasWeight)            isWeighted = true;

        update();
    }
}

// ----------------------- FILE I/O -----------------------

void GraphWidget::saveToFile (const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    int n = nodes.size();

    out << n << "\n";
    out << (isDirected ? "directed" : "undirected") << " "
        << (isWeighted ? "weighted" : "unweighted") << "\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            out << (!adjMatrix[i][j] ? 0.0 : isWeighted ? edgeData[i][j].weight : 1.0);
            if (adjMatrix[i][j])
                out << ":" << static_cast<int>(edgeData[i][j].dir);
            if (j < n-1) out << " ";
        }
        out << "\n";
    }

    for (int i = 0; i < n; i++)
    {
        out << "vertex" << i << " = "
            << nodes[i].position.x() << ", " << nodes[i].position.y()
            << ", index = " << nodes[i].index
            << ", label = \"" << nodes[i].label << "\";\n";
    }

    file.close();
}

void GraphWidget::loadFromFile (const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    int n = 0;
    in >> n;

    QString dirStr, weightStr;
    in >> dirStr >> weightStr;
    isDirected = (dirStr  == "directed");
    isWeighted = (weightStr == "weighted");

    // Each cell: value or value:dir
    QVector<QVector<double>>  raw(n, QVector<double>(n, 0));
    QVector<QVector<EdgeDir>> rawDir(n, QVector<EdgeDir>(n, EdgeDir::None));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            QString cell;
            in >> cell;
            QStringList parts = cell.split(':');
            raw[i][j]    = parts[0].toDouble();
            rawDir[i][j] = (parts.size() > 1)
                               ? static_cast<EdgeDir>(parts[1].toInt())
                               : EdgeDir::None;
        }
    }

    in.readLine();

    // Parse node lines directly into Node structs
    QList<Node> loaded(n);
    int maxIndex = 0;

    for (int k = 0; k < n; k++)
    {
        QString line = in.readLine().trimmed().remove(';');
        QStringList parts = line.split(',');
        if (parts.size() < 3) continue;

        double x   = parts[0].split('=').last().trimmed().toDouble();
        double y   = parts[1].trimmed().toDouble();
        int    idx = parts[2].split('=').last().trimmed().toInt();

        QString label = "";
        if (parts.size() >= 4)
        {
            label = parts[3].split('=').last().trimmed();
            label.remove('"');
        }

        loaded[k] = { QPointF(x, y), idx, label };
        maxIndex   = std::max(maxIndex, idx);
    }

    file.close();

    nodes.clear();
    adjMatrix.clear();
    edgeData.clear();
    followingIndex = maxIndex + 1;

    for (int k = 0; k < n; k++)
    {
        nodes.append(loaded[k]);
        matrixAddNode();
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (raw[i][j] == 0) continue;
            adjMatrix[i][j]          = 1;
            edgeData[i][j].weight    = raw[i][j];
            edgeData[i][j].hasWeight = isWeighted;
            edgeData[i][j].dir       = rawDir[i][j];
        }
    }

    update();
}

// ----------------------- EVENTS -----------------------

void GraphWidget::mousePressEvent (QMouseEvent *event)
{
    QPointF pos     = event->position();
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
        if (currentMode == 0) // Vertex
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
                nodes.append({pos, followingIndex++, ""});
                matrixAddNode();
            }
        }
        else if (currentMode == 1 && nodeIdx >= 0) // Edge
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
        else if (currentMode == 2 && nodeIdx >= 0) // Move
        {
            dragNodeIdx = nodeIdx;
        }
    }

    update();
}

void GraphWidget::mouseReleaseEvent (QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && currentMode == 2)
        dragNodeIdx = -1;
}

void GraphWidget::mouseDoubleClickEvent (QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;

    QPointF pos     = event->position();
    int     nodeIdx = nodeIndexFinder(pos, clickRadius);

    if (nodeIdx >= 0)
    {
        openNodeEditor(nodeIdx);
        return;
    }

    int hit = edgeIndexFinder(pos, clickRadius + PLACEMENT_CONSTANT);
    if (hit >= 0)
    {
        int n = nodes.size();
        openEdgeEditor(hit / n, hit % n);
    }
}

void GraphWidget::mouseMoveEvent (QMouseEvent *event)
{
    QPointF pos = event->position();

    if (currentMode == 1 && edgeFirstNodeIdx >= 0)
    {
        rubberBandEnd = pos;
        update();
    }
    else if (currentMode == 2 && dragNodeIdx >= 0)
    {
        nodes[dragNodeIdx].position = pos;
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
        edgeData.clear();
        followingIndex   = 1;
        edgeFirstNodeIdx = -1;
        break;

    case Qt::Key_A:
        antialiasingEnabled = !antialiasingEnabled;
        break;

    case Qt::Key_Escape:
        edgeFirstNodeIdx = -1;
        dragNodeIdx      = -1;
        break;

    default:
        QWidget::keyPressEvent(event);
        break;
    }

    update();
}

// ----------------------- PAINT -----------------------

void GraphWidget::paintEvent (QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, antialiasingEnabled);

    int n = nodes.size();

    // Layer 1: edges
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (adjMatrix[i][j]) drawEdge(i, j, painter);

    // Layer 2: rubber-band
    if (currentMode == 1 && edgeFirstNodeIdx >= 0 && edgeFirstNodeIdx < n)
    {
        painter.setPen(QPen(paintColor, strokeWidth, Qt::DashLine, Qt::RoundCap));
        painter.drawLine(circleEdgePoint(nodes[edgeFirstNodeIdx], rubberBandEnd), rubberBandEnd);
    }

    // Layer 3: nodes
    for (Node &node : nodes) drawNode(node, painter);
}
