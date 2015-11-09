#include "inserttask.h"
#include "ui_inserttask.h"
#include "taskset.h"
#include "guiexception.h"

using namespace RTSim;

InsertTask::InsertTask(QWidget *parent, bool editWindow) :
    QDialog(parent),
    ui(new Ui::insertTask)
{
    this->editWindow = editWindow;
    if(editWindow)
        ui->taskNameEdit->setReadOnly(true);
    ui->setupUi(this);
    ui->taskNameEdit->setText("Task " + QString::number(GUI_CONTEXT.getTaskCount()));
    loadKernels();
}

InsertTask::~InsertTask()
{
    delete ui;
}

void InsertTask::extractTaskData(){

    bool isInteger, isInteger2, isInteger3, isInteger4;

    taskData.setName(ui->taskNameEdit->text());
    taskData.setPhase(ui->phaseEdit->text().toUInt(&isInteger));
    taskData.setCi(ui->ciEdit->text().toUInt(&isInteger2));
    taskData.setTi(ui->tiEdit->text().toUInt(&isInteger3));
    taskData.setDi(ui->diEdit->text().toUInt(&isInteger4));
    taskData.setKernel(ui->kernelsCBox->currentText());

    if( !isInteger || !isInteger2 || !isInteger3 || !isInteger4 ||
        taskData.phase() < 0  ||  taskData.ci() < 0 ||
        taskData.ti() < 0     ||  taskData.di() < 0 ||
        taskData.name().length() == 0)
            throw InputDataFormatException("Not valid data format");

}

void InsertTask::setData(QString taskName){

    PeriodicTaskData *data = GUI_CONTEXT.getTaskData(taskName);
    ui->taskNameEdit->setText(taskName);
    ui->ciEdit->setText(QString::number(data->ci()));
    ui->tiEdit->setText(QString::number(data->ti()));
    ui->diEdit->setText(QString::number(data->di()));
    ui->phaseEdit->setText(QString::number(data->phase()));
    ui->kernelsCBox->setCurrentText(data->kernel());
}

void InsertTask::on_buttonBox_accepted()
{

   try{
       extractTaskData();
   }
   catch(InputDataFormatException &e){
       GUI_CONTEXT.showMessageBox(e.what());
       return;
   }

   /* The order of the following operation is important :
    * addPeriodicTask changes the name of the task, adding _1,
    * if there exists another task set with the same name */  
   if(!GUI_CONTEXT.getTasksData().isPresent(taskData.name()))
        GUI_CONTEXT.addPeriodicTaskData(taskData.name(), taskData.phase(), taskData.ci(), taskData.ti(), taskData.di(), taskData.kernel());
   else{
       PeriodicTaskData *temp = GUI_CONTEXT.getTasksData().getElement(taskData.name());
       temp->setCi(taskData.ci());
       temp->setDi(taskData.di());
       temp->setTi(taskData.ti());
       temp->setKernel(taskData.kernel());
       temp->setPhase(taskData.phase());
   }
   taskSet->updateTaskTableContent();

}

void InsertTask::setTaskSet(TaskSet *value)
{
    taskSet = value;
}

void InsertTask::loadKernels()
{
    map<QString, VMData *> &vmData = VMS_DATA;
    map<QString, VMData *>::iterator it;

    ui->kernelsCBox->clear();

    ui->kernelsCBox->addItem("MainKernel");
    for (it=vmData.begin(); it != vmData.end(); it++){
        ui->kernelsCBox->addItem(it->first);
    }
}

void InsertTask::setEditWindow()
{
    editWindow = true;
    ui->taskNameEdit->setReadOnly(true);
    ui->taskNameEdit->setEnabled(false);
}
