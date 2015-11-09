#include "selecttaskwindow.h"
#include "ui_selecttaskwindow.h"

#include "guicontext.h"

#include "inserttask.h"

SelectTaskWindow::SelectTaskWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectTaskWindow)
{
    ui->setupUi(this);
}

SelectTaskWindow::~SelectTaskWindow()
{
    delete ui;
}



void SelectTaskWindow::setTaskSet(TaskSet *value)
{
    taskSet = value;
}

void SelectTaskWindow::loadTaskList()
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

void SelectTaskWindow::on_buttonBox_accepted()
{
    int i = ui->taskComboBox->currentIndex();
    QString name = ui->taskComboBox->currentText();
    modifyTask.setEditWindow();
    modifyTask.setData(name);
    modifyTask.setTaskSet(taskSet);
    modifyTask.loadKernels();
    modifyTask.show();
}

