#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QList>
#include <QtMath>
#include <QElapsedTimer>

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

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void updateWindowStats();

    int nodeIndexFinder(QPointF &pos);

private:
    QList<Node> nodes;
    int followingIndex = 1;

    const double circleRadius = 20.0f;
    const double clickRadius = circleRadius + 3.0f;

    const QColor paintColor = Qt::red;
    const double strokeWidth = 2.8f;
    const double textWeight = 11.0f;

    bool antialiasingEnabled = true;

signals:
};

#endif // GRAPHWIDGET_H
