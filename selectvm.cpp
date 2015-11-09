#include "selectvm.h"
#include "ui_selectvm.h"

#include "guicontext.h"

SelectVMWindow::SelectVMWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectVM)
{
    ui->setupUi(this);
}

SelectVMWindow::~SelectVMWindow()
{
    delete ui;
}



void SelectVMWindow::setTaskSet(TaskSet *value)
{
    taskSet = value;
}

void SelectVMWindow::loadVMList()
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

void SelectVMWindow::on_buttonBox_accepted()
{
    int i = ui->vmComboBox->currentIndex();
    QString name = ui->vmComboBox->currentText();
    modifyVM.setEditWindow(true);
    modifyVM.setData(name);
    modifyVM.setTaskSet(taskSet);
    modifyVM.show();
}

