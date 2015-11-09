#include "removetask.h"
#include "ui_removetask.h"

#include "taskset.h"


RemoveTask::RemoveTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveTask)
{
    ui->setupUi(this);
    loadTaskList();
}

RemoveTask::~RemoveTask()
{
    delete ui;
}

void RemoveTask::on_buttonBox_accepted()
{
    int i = ui->taskComboBox->currentIndex();
    QString name = ui->taskComboBox->currentText();
    GUI_CONTEXT.removePeriodicTaskData(name);
    taskSet->updateTaskTableContent();
}

void RemoveTask::setTaskSet(TaskSet *value)
{
    taskSet = value;
}

void RemoveTask::loadTaskList()
{
    map<QString, PeriodicTaskData*> tasksData = TASKS_DATA;
    map<QString, PeriodicTaskData*>::iterator it;

    PeriodicTaskData *temp;

    ui->taskComboBox->clear();

    for (it=tasksData.begin(); it != tasksData.end(); it++){
        temp = it->second;
        ui->taskComboBox->addItem(temp->name());
    }
}

