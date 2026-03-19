#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QList>
#include <QVector>
#include <QFile>
#include <QTextStream>

#define BG_R 18
#define BG_G 18
#define BG_B 22

#define CLICK_CONSTANT     3.0f
#define PLACEMENT_CONSTANT 5.0f

// --- Data types ---

struct Node
{
    QPointF position;
    int     index;
    QString label;
};

enum class EdgeDir { None, ItoJ, JtoI };

struct EdgeData
{
    double  weight    = 1.0;
    bool    hasWeight = false;
    EdgeDir dir       = EdgeDir::None;
};

// --- Widget ---

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget (QWidget *parent = nullptr);

    QColor paintColor = QColorConstants::Svg::steelblue;
    void setPaintColor (QColor &color);

    int currentMode = 0; // 0 - vertex, 1 - edge, 2 - move

    void saveToFile   (const QString &path);
    void loadFromFile (const QString &path);

protected:
    void paintEvent            (QPaintEvent  *event) override;
    void mousePressEvent       (QMouseEvent  *event) override;
    void mouseReleaseEvent     (QMouseEvent  *event) override;
    void mouseMoveEvent        (QMouseEvent  *event) override;
    void mouseDoubleClickEvent (QMouseEvent  *event) override;
    void keyPressEvent         (QKeyEvent    *event) override;

    int    nodeIndexFinder          (QPointF &pos, double dist);
    int    edgeIndexFinder          (QPointF &pos, double tol);
    double distanceBetweenPointsSqr (QPointF &p1,  QPointF &p2);

private:
    QList<Node>                nodes;
    QVector<QVector<int>>      adjMatrix;
    QVector<QVector<EdgeData>> edgeData;
    int followingIndex = 1;

    bool isDirected = false;
    bool isWeighted = false;

    const double circleRadius = 20.0;
    const double clickRadius  = circleRadius + CLICK_CONSTANT;
    const double strokeWidth  = 2.8;
    const double textWeight   = 11.0;

    bool antialiasingEnabled = true;

    int     edgeFirstNodeIdx = -1;
    QPointF rubberBandEnd;
    int     dragNodeIdx = -1;

    bool    isTooClose      (QPointF &p1, QPointF &p2, double minDist);
    QPointF circleEdgePoint (Node &n, QPointF &target);

    void matrixAddNode    ();
    void matrixRemoveNode (int idx);

    void drawNode  (Node &node,                QPainter &p);
    void drawEdge  (int i, int j,              QPainter &p);
    void drawArrow (const QPointF &tip, double angle, QPainter &p);

    void openNodeEditor (int nodeIdx);
    void openEdgeEditor (int i, int j);

    QPalette pal = palette();
};

#endif // GRAPHWIDGET_H
