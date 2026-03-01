#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);
}

void GraphWidget::updateWindowStats()
{
    QString aaStatus = antialiasingEnabled ? "ON" : "OFF";
    QString title = QString("Graph – Anti-aliasing %1 (A to toggle)").arg(aaStatus);

    window()->setWindowTitle(title);
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    QPointF clickPoint = event->position();

    if (event->button() == Qt::LeftButton)
    {
        nodes.append({clickPoint, followingIndex++});
        update();
    }
    else if (event->button() == Qt::RightButton)
    {
        int idx = nodeIndexFinder(clickPoint);
        if (idx >= 0)
        {
            nodes.removeAt(idx);
            update();
        }
    }
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
        update();
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

    painter.fillRect(rect(), QColor(18, 18, 22));

    for (auto &node : nodes)
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

    updateWindowStats();
}

int GraphWidget::nodeIndexFinder(QPointF &pos)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        Node &p = nodes[i];
        double dx = p.position.x() - pos.x();
        double dy = p.position.y() - pos.y();

        if (qHypot(dx, dy) <= clickRadius) return i;
    }

    return -1;
}
