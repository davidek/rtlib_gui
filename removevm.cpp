#include "removevm.h"
#include "ui_removevm.h"

#include "guicontext.h"
#include "taskset.h"

RemoveVM::RemoveVM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveVM)
{
    ui->setupUi(this);

    loadVMList();
    loadRemoveList();
}

RemoveVM::~RemoveVM()
{
    delete ui;
}

void RemoveVM::setTaskSet(TaskSet *value)
{
    taskSet = value;
}

void RemoveVM::on_buttonBox_accepted()
{
    QString name = ui->vmComboBox->currentText();

    GUI_CONTEXT.removeVMData(name);

    taskSet->updateVMTableContent();
    updateTasks();
}

void RemoveVM::loadVMList()
{
    map<QString, VMData *> vmData = VMS_DATA;
    map<QString, VMData *>::iterator it;

    VMData *temp;

    ui->vmComboBox->clear();

    for (it=vmData.begin(); it != vmData.end(); it++){

        temp = it->second;
        ui->vmComboBox->addItem(temp->name());

    }
}

void RemoveVM::loadRemoveList()
{
    map<QString, VMData *> vmData = VMS_DATA;
    map<QString, VMData *>::iterator it;

    VMData *temp;

    ui->vmMoveComboBox->clear();
    ui->vmMoveComboBox->addItem("Remove");
    ui->vmMoveComboBox->addItem("MainKernel");

    for (it=vmData.begin(); it != vmData.end(); it++){

        temp = it->second;
        if(temp->name() != ui->vmComboBox->currentText())
            ui->vmMoveComboBox->addItem(temp->name());

    }
}


void RemoveVM::on_vmComboBox_currentTextChanged(const QString &arg1)
{
    loadRemoveList();
}


void RemoveVM::updateTasks(){

    if(ui->vmMoveComboBox->currentText() == "Remove")
        GUI_CONTEXT.removeTasksByVM(ui->vmComboBox->currentText());
    else
        GUI_CONTEXT.moveTasksVM(ui->vmComboBox->currentText(), ui->vmMoveComboBox->currentText());

    taskSet->updateTaskTableContent();

    loadVMList();
    loadRemoveList();
}






