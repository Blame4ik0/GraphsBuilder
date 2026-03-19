/********************************************************************************
** Form generated from reading UI file 'nodeeditor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEEDITOR_H
#define UI_NODEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NodeEditor
{
public:
    QFormLayout *formLayout;
    QLabel *labelLbl;
    QLineEdit *labelEdit;
    QDialogButtonBox *buttons;

    void setupUi(QDialog *NodeEditor)
    {
        if (NodeEditor->objectName().isEmpty())
            NodeEditor->setObjectName("NodeEditor");
        NodeEditor->resize(300, 100);
        formLayout = new QFormLayout(NodeEditor);
        formLayout->setObjectName("formLayout");
        labelLbl = new QLabel(NodeEditor);
        labelLbl->setObjectName("labelLbl");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelLbl);

        labelEdit = new QLineEdit(NodeEditor);
        labelEdit->setObjectName("labelEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, labelEdit);

        buttons = new QDialogButtonBox(NodeEditor);
        buttons->setObjectName("buttons");
        buttons->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

        formLayout->setWidget(1, QFormLayout::ItemRole::SpanningRole, buttons);


        retranslateUi(NodeEditor);
        QObject::connect(buttons, &QDialogButtonBox::accepted, NodeEditor, qOverload<>(&QDialog::accept));
        QObject::connect(buttons, &QDialogButtonBox::rejected, NodeEditor, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(NodeEditor);
    } // setupUi

    void retranslateUi(QDialog *NodeEditor)
    {
        NodeEditor->setWindowTitle(QCoreApplication::translate("NodeEditor", "Edit Vertex", nullptr));
        labelLbl->setText(QCoreApplication::translate("NodeEditor", "Label:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NodeEditor: public Ui_NodeEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEEDITOR_H
