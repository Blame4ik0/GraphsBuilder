#ifndef EDGEEDITOR_H
#define EDGEEDITOR_H

#include <QDialog>
#include "graphwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EdgeEditor; }
QT_END_NAMESPACE

class EdgeEditor : public QDialog
{
    Q_OBJECT
public:
    explicit EdgeEditor (const EdgeData &ed, int idxI, int idxJ, QWidget *parent = nullptr);
    ~EdgeEditor ();

    EdgeData result () const;

private:
    Ui::EdgeEditor *ui;
    int nodeI, nodeJ;
};

#endif // EDGEEDITOR_H
