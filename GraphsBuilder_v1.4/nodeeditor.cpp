#include "nodeeditor.h"
#include "ui_nodeeditor.h"

NodeEditor::NodeEditor (const Node &node, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NodeEditor)
{
    ui->setupUi(this);
    setWindowTitle(QString("Edit vertex %1").arg(node.index));
    ui->labelEdit->setText(node.label);
}

NodeEditor::~NodeEditor ()
{
    delete ui;
}

QString NodeEditor::label () const
{
    return ui->labelEdit->text();
}
