#include "qp_vmwindow.h"
#include "ui_qp_vmwindow.h"


#include "taskset.h"

QP_VMWindow::QP_VMWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QP_VMWindow)
{
    ui->setupUi(this);

}

void QP_VMWindow::updateVMDefaultNameEdit(){
    ui->vmNameEdit->setText("VM " + QString::number(GUI_CONTEXT.getVMCounter()));
}

QP_VMWindow::~QP_VMWindow()
{
    delete ui;
}

void QP_VMWindow::extractServerData(){

    bool isInteger, isInteger2;

    serverData.setName(ui->vmNameEdit->text());
    serverData.setBudget(ui->budgetEdit->text().toUInt(&isInteger));
    serverData.setPeriod(ui->periodEdit->text().toUInt(&isInteger2));

    if( !isInteger || !isInteger2 ||
        serverData.period() < 0  ||  serverData.budget() < 0 || serverData.name().length() == 0)
            throw InputDataFormatException("Not valid data format");

}

void QP_VMWindow::setTaskSet(TaskSet *value)
{
    taskSet = value;
}

void QP_VMWindow::setData(QString vmName){

    VMData *data = GUI_CONTEXT.getVMData(vmName);
    ui->vmNameEdit->setText(vmName);
    ui->budgetEdit->setText(QString::number(data->budget()));
    ui->periodEdit->setText(QString::number(data->period()));
}


void QP_VMWindow::on_buttonBox_accepted()
{
    try{
        extractServerData();
    }
    catch(InputDataFormatException &e){
        GUI_CONTEXT.showMessageBox(e.what());
        return;
    }

    if(!GUI_CONTEXT.getVmData().isPresent(serverData.name()))
        GUI_CONTEXT.addVMData(serverData.name(), serverData.budget(), serverData.period());
    else{
        VMData *temp = GUI_CONTEXT.getVmData().getElement(serverData.name());
        temp->setBudget(serverData.budget());
        temp->setPeriod(serverData.period());
    }


    taskSet->updateVMTableContent();
}

void QP_VMWindow::setEditWindow(bool value)
{
    editWindow = true;
    ui->vmNameEdit->setReadOnly(true);
    ui->vmNameEdit->setEnabled(false);

}
