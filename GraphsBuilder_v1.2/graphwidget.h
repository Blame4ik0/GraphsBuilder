#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QList>

#define BG_R 18
#define BG_G 18
#define BG_B 22

#define CLICK_CONSTANT 3.0f
#define PLACEMENT_CONSTANT 5.0f

struct Node
{
    QPointF position;
    int     index;
};

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = nullptr);

    QColor paintColor = Qt::darkBlue;

    void setPaintColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void updateWindowStats();

    int nodeIndexFinder(QPointF &pos, double distance);
    double distanceBetweenPointsSqr(QPointF &p1, QPointF &p2);

private:
    QList<Node> nodes;
    int followingIndex = 1;

    const double circleRadius = 20.0f;
    const double clickRadius = circleRadius + CLICK_CONSTANT;

    const double strokeWidth = 2.8f;
    const double textWeight = 11.0f;

    bool antialiasingEnabled = true;

    void drawNode(Node &node, QPainter& painter);

    bool isTooClose(QPointF &p1, QPointF &p2, double minDist);

    QPalette pal = palette();
};

#endif // GRAPHWIDGET_H
