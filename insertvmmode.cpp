#include "insertvmmode.h"
#include "ui_insertvmmode.h"

InsertVMMode::InsertVMMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::insertVMMode)
{
    ui->setupUi(this);
}

InsertVMMode::~InsertVMMode()
{
    qpWindow.close();
    delete ui;
}

void InsertVMMode::on_next_run_Button_clicked()
{
    this->close();
    if(!editWindow){
        qpWindow.updateVMDefaultNameEdit();
        qpWindow.setTaskSet(taskSet);
        qpWindow.show();
    }
}

void InsertVMMode::setEditWindow(bool value)
{
    editWindow = value;
}

void InsertVMMode::setTaskSet(TaskSet *value)
{
    taskSet = value;
}




