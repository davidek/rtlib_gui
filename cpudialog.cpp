#include "cpudialog.h"
#include "ui_cpudialog.h"


CPUDialog::CPUDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPUDialog)
{
    ui->setupUi(this);
    ui->nCPUEdit->setText(QString::number(GUI_CONTEXT.getNCPU()));
}

CPUDialog::~CPUDialog()
{
    delete ui;
}

void CPUDialog::on_buttonBox_accepted()
{
    GUI_CONTEXT.setNCPU(ui->nCPUEdit->text().toUInt());
}
