#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QList>
#include <QVector>

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

    QColor paintColor = QColorConstants::Svg::steelblue;
    void setPaintColor(QColor &color);

    int currentMode = 0; // 0 - vertex, 1 - edge

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    int nodeIndexFinder(QPointF &pos, double distance);
    int edgeIndexFinder(QPointF &pos, double tol);
    double distanceBetweenPointsSqr(QPointF &p1, QPointF &p2);

private:
    QList<Node> nodes;
    int followingIndex = 1;

    const double circleRadius = 20.0f;
    const double clickRadius  = circleRadius + CLICK_CONSTANT;
    const double strokeWidth  = 2.8f;
    const double textWeight   = 11.0f;

    bool antialiasingEnabled = true;

    QVector<QVector<int>> adjMatrix;

    void matrixAddNode();
    void matrixRemoveNode(int i);

    int     edgeFirstNodeIdx = -1;
    QPointF rubberBandEnd;

    bool isTooClose(QPointF &p1, QPointF &p2, double minDist);
    QPointF circleEdgePoint(Node &node, QPointF &target);

    void drawNode(Node &node, QPainter &painter);
    void drawEdge(const QPointF &from, const QPointF &to, QPainter &painter);

    QPalette pal = palette();
};

#endif // GRAPHWIDGET_H
