#include "graphwidget.h"

// ----------------------- INIT PART -----------------------

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);

    pal.setColor(QPalette::Window, QColor(BG_R, BG_G, BG_B));
    setPalette(pal);
    setAutoFillBackground(true);
}

// ----------------------- UPDATES -----------------------

void GraphWidget::updateWindowStats()
{
    QString aaStatus = antialiasingEnabled ? "ON" : "OFF";
    QString title = QString("Graph – Anti-aliasing %1 (A to toggle)").arg(aaStatus);

    window()->setWindowTitle(title);
}

// ----------------------- HELPERS -----------------------

double GraphWidget::distanceBetweenPointsSqr(QPointF &p1, QPointF &p2)
{
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();

    return dx*dx + dy*dy;
}

bool GraphWidget::isTooClose(QPointF &p1, QPointF &p2, double minDist)
{
    return (distanceBetweenPointsSqr(p1, p2) < minDist*minDist);
}

int GraphWidget::nodeIndexFinder(QPointF &pos, double distance)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        Node &p = nodes[i];

        if (distanceBetweenPointsSqr(pos, p.position) <= distance*distance) return i;
    }

    return -1;
}

// ----------------------- DRAWING -----------------------

void GraphWidget::drawNode(Node &node, QPainter& painter)
{
    painter.setPen(QPen(paintColor, strokeWidth));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(node.position, circleRadius, circleRadius);

    QString text = QString::number(node.index);
    painter.setPen(paintColor);
    painter.setFont(QFont("Segoe UI", textWeight, QFont::Bold));

    QRectF textRect
        (
            node.position.x() - circleRadius,
            node.position.y() - circleRadius,
            circleRadius * 2,
            circleRadius * 2
            );

    painter.drawText(textRect, Qt::AlignCenter, text);
}

// ----------------------- EVENTS HANDLING -----------------------

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    QPointF clickPoint = event->position();

    if (event->button() == Qt::LeftButton)
    {
        bool tooClose = false;
        for (Node &node : nodes)
        {
            if (isTooClose(clickPoint, node.position, 2*clickRadius + PLACEMENT_CONSTANT))
            {
                tooClose = true;
                break;
            }
        }

        if (!tooClose)
        {
            nodes.append({clickPoint, followingIndex++});
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        int idx = nodeIndexFinder(clickPoint, clickRadius);
        if (idx >= 0)
        {
            nodes.removeAt(idx);
        }
    }

    update();
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_C:
        nodes.clear();
        followingIndex = 1;
        update();
        break;

    case Qt::Key_A:
        antialiasingEnabled = !antialiasingEnabled;
        updateWindowStats();
        break;

    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, antialiasingEnabled);

    for (Node &node : nodes)
    {
        drawNode(node, painter);
    }
}
