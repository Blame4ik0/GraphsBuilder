#ifndef NODEEDITOR_H
#define NODEEDITOR_H

#include <QDialog>
#include "graphwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NodeEditor; }
QT_END_NAMESPACE

class NodeEditor : public QDialog
{
    Q_OBJECT
public:
    explicit NodeEditor (const Node &node, QWidget *parent = nullptr);
    ~NodeEditor ();

    QString label () const;

private:
    Ui::NodeEditor *ui;
};

#endif // NODEEDITOR_H
