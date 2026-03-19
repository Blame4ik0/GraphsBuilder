#include "edgeeditor.h"
#include "ui_edgeeditor.h"

EdgeEditor::EdgeEditor (const EdgeData &ed, int idxI, int idxJ, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EdgeEditor)
    , nodeI(idxI)
    , nodeJ(idxJ)
{
    ui->setupUi(this);
    setWindowTitle(QString("Edit edge %1 — %2").arg(idxI).arg(idxJ));

    ui->dirCombo->addItem("None",          static_cast<int>(EdgeDir::None));
    ui->dirCombo->addItem(QString("%1 → %2").arg(idxI).arg(idxJ), static_cast<int>(EdgeDir::ItoJ));
    ui->dirCombo->addItem(QString("%1 → %2").arg(idxJ).arg(idxI), static_cast<int>(EdgeDir::JtoI));
    ui->dirCombo->setCurrentIndex(static_cast<int>(ed.dir));

    ui->weightCheck->setChecked(ed.hasWeight);
    ui->weightSpin->setValue(ed.weight);
    ui->weightSpin->setEnabled(ed.hasWeight);

    connect(ui->weightCheck, &QCheckBox::toggled, ui->weightSpin, &QDoubleSpinBox::setEnabled);
}

EdgeEditor::~EdgeEditor ()
{
    delete ui;
}

EdgeData EdgeEditor::result () const
{
    return {
        ui->weightSpin->value(),
        ui->weightCheck->isChecked(),
        static_cast<EdgeDir>(ui->dirCombo->currentData().toInt())
    };
}
