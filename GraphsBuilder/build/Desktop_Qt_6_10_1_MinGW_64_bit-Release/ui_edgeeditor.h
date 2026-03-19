/********************************************************************************
** Form generated from reading UI file 'edgeeditor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDGEEDITOR_H
#define UI_EDGEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_EdgeEditor
{
public:
    QFormLayout *formLayout;
    QLabel *dirLbl;
    QComboBox *dirCombo;
    QLabel *weightLbl;
    QCheckBox *weightCheck;
    QLabel *weightValLbl;
    QDoubleSpinBox *weightSpin;
    QDialogButtonBox *buttons;

    void setupUi(QDialog *EdgeEditor)
    {
        if (EdgeEditor->objectName().isEmpty())
            EdgeEditor->setObjectName("EdgeEditor");
        EdgeEditor->resize(300, 150);
        formLayout = new QFormLayout(EdgeEditor);
        formLayout->setObjectName("formLayout");
        dirLbl = new QLabel(EdgeEditor);
        dirLbl->setObjectName("dirLbl");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, dirLbl);

        dirCombo = new QComboBox(EdgeEditor);
        dirCombo->setObjectName("dirCombo");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, dirCombo);

        weightLbl = new QLabel(EdgeEditor);
        weightLbl->setObjectName("weightLbl");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, weightLbl);

        weightCheck = new QCheckBox(EdgeEditor);
        weightCheck->setObjectName("weightCheck");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, weightCheck);

        weightValLbl = new QLabel(EdgeEditor);
        weightValLbl->setObjectName("weightValLbl");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, weightValLbl);

        weightSpin = new QDoubleSpinBox(EdgeEditor);
        weightSpin->setObjectName("weightSpin");
        weightSpin->setMinimum(-1000000.000000000000000);
        weightSpin->setMaximum(1000000.000000000000000);
        weightSpin->setDecimals(4);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, weightSpin);

        buttons = new QDialogButtonBox(EdgeEditor);
        buttons->setObjectName("buttons");
        buttons->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

        formLayout->setWidget(3, QFormLayout::ItemRole::SpanningRole, buttons);


        retranslateUi(EdgeEditor);
        QObject::connect(buttons, &QDialogButtonBox::accepted, EdgeEditor, qOverload<>(&QDialog::accept));
        QObject::connect(buttons, &QDialogButtonBox::rejected, EdgeEditor, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(EdgeEditor);
    } // setupUi

    void retranslateUi(QDialog *EdgeEditor)
    {
        EdgeEditor->setWindowTitle(QCoreApplication::translate("EdgeEditor", "Edit Edge", nullptr));
        dirLbl->setText(QCoreApplication::translate("EdgeEditor", "Direction:", nullptr));
        weightLbl->setText(QCoreApplication::translate("EdgeEditor", "Has weight:", nullptr));
        weightValLbl->setText(QCoreApplication::translate("EdgeEditor", "Weight:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EdgeEditor: public Ui_EdgeEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDGEEDITOR_H
