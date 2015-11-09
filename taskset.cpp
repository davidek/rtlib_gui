#include "taskset.h"
#include "ui_taskset.h"

#include "guiexception.h"
#include "filedialogmanager.h"

#include "gui_types.h"
#include "selecttaskwindow.h"


using namespace std;


TaskSet::TaskSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskSet)
{
    ui->setupUi(this);

    currentRowTaskTable = 0;
    ui->taskTable->setRowCount(0);
    ui->taskTable->setColumnCount(6);
    QStringList m_taskTableHeader;
    m_taskTableHeader<<"Name"<<"Phase"<<"Ci"<<"Ti"<<"Di"<<"Kernel";
    ui->taskTable->setHorizontalHeaderLabels(m_taskTableHeader);

    currentRowVMTable = 0;
    ui->vmTable->setRowCount(0);
    ui->vmTable->setColumnCount(3);
    QStringList m_vmTableHeader;
    m_vmTableHeader<<"Name"<<"Budget"<<"Period";
    ui->vmTable->setHorizontalHeaderLabels(m_vmTableHeader);
    createMenu();

    updateTaskTableContent();
    ui->taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->taskTable->resizeColumnsToContents();


    ui->vmTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vmTable->resizeColumnsToContents();

    setFixedSize(this->size());
}

void TaskSet::createMenu(){
    menuBar = new QMenuBar(this);
    fileMenu = new QMenu("File");
    taskMenu = new QMenu("Tasks");
    vmMenu = new QMenu("VMs");

    read = fileMenu->addAction("Read JSON");
    write = fileMenu->addAction("Write JSON");

    addTask = taskMenu->addAction("Add Task");
    editTask = taskMenu->addAction("Edit Task");
    removeTask = taskMenu->addAction("Remove Task");
    eraseTasks = taskMenu->addAction("Erase Tasks");

    addVM = vmMenu->addAction("Add VM");
    editVM = vmMenu->addAction("Edit VM");
    removeVM = vmMenu->addAction("Remove VM");
    eraseVM = vmMenu->addAction("Erase VM");

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(taskMenu);
    menuBar->addMenu(vmMenu);

    connect(read, SIGNAL(triggered()),this,SLOT(on_readFile()));
    connect(write, SIGNAL(triggered()),this,SLOT(on_writeFile()));
    connect(addTask, SIGNAL(triggered()),this,SLOT(on_addTask()));
    connect(removeTask, SIGNAL(triggered()),this,SLOT(on_removeTask()));
    connect(eraseTasks, SIGNAL(triggered()),this,SLOT(on_eraseTasks()));
    connect(editTask, SIGNAL(triggered()),this,SLOT(on_editTask()));
    connect(addVM, SIGNAL(triggered()),this,SLOT(on_addVM()));
    connect(removeVM, SIGNAL(triggered()),this,SLOT(on_removeVM()));
    connect(eraseVM, SIGNAL(triggered()),this,SLOT(on_eraseVM()));
    connect(editVM, SIGNAL(triggered()),this,SLOT(on_editVM()));
}

void TaskSet::deleteMenu(){
    delete read;
    delete write;

    delete addTask;
    delete removeTask;
    delete eraseTasks;
    delete editTask;

    delete addVM;
    delete removeVM;
    delete eraseVM;

    delete fileMenu;
    delete taskMenu;
    delete vmMenu;

    delete menuBar;
}

void TaskSet::addElement(QTableWidget *table, QString text, unsigned int row, unsigned int col){
    QTableWidgetItem* newItem = new QTableWidgetItem();
    newItem->setText(text);
    table->setItem(row, col, newItem);
}

void TaskSet::addTask2Table(QString name, int phase, int ci, int ti, int di, QString kernel){

    ui->taskTable->setRowCount(ui->taskTable->rowCount() + 1);

    addElement(ui->taskTable, name, currentRowTaskTable, 0);
    addElement(ui->taskTable, QString::number(phase), currentRowTaskTable, 1);
    addElement(ui->taskTable, QString::number(ci), currentRowTaskTable, 2);
    addElement(ui->taskTable, QString::number(ti), currentRowTaskTable, 3);
    addElement(ui->taskTable, QString::number(di), currentRowTaskTable, 4);
    addElement(ui->taskTable, kernel, currentRowTaskTable, 5);

    currentRowTaskTable++;

    ui->taskTable->update();
    ui->taskTable->resizeColumnsToContents();
}

void TaskSet::addVM2Table(QString name, int budget, int period){

    ui->vmTable->setRowCount(ui->vmTable->rowCount() + 1);

    addElement(ui->vmTable, name, currentRowVMTable, 0);
    addElement(ui->vmTable, QString::number(budget), currentRowVMTable, 1);
    addElement(ui->vmTable, QString::number(period), currentRowVMTable, 2);

    currentRowVMTable++;

    ui->vmTable->update();
    ui->vmTable->resizeColumnsToContents();
}


TaskSet::~TaskSet()
{
    insertVMWindow.close();
    removeTaskWindow.close();
    removeVMWindow.close();
    deleteMenu();
    delete ui;
}

void TaskSet::on_addVM()
{
    insertVMWindow.setTaskSet(this);
    insertVMWindow.show();
}

void TaskSet::on_addTask()
{

    insertTaskWindow.setTaskSet(this);
    insertTaskWindow.loadKernels();
    insertTaskWindow.show();
}


void TaskSet::updateTaskTableContent(){
    currentRowTaskTable = 0;
    ui->taskTable->setRowCount(0);
    map<QString, PeriodicTaskData*> &tasksData = TASKS_DATA;
    map<QString, PeriodicTaskData*>::iterator it;
    PeriodicTaskData *temp;
    for (it=tasksData.begin(); it != tasksData.end(); it++){
        temp = it->second;
        addTask2Table(temp->name(), temp->phase(),  temp->ci(), temp->ti(), temp->di(), temp->kernel());
    }
}

void TaskSet::updateVMTableContent(){
    currentRowVMTable = 0;
    ui->vmTable->setRowCount(0);
    map<QString, VMData*> &vmData = VMS_DATA;
    map<QString, VMData*>::iterator it;
    VMData *temp;
    for (it=vmData.begin(); it != vmData.end(); it++){
        temp = it->second;
        addVM2Table(temp->name(), temp->budget(), temp->period());
    }
}

void TaskSet::on_readFile()
{

    QString pathname;
    pathname = FileDialogManager::getInstance().openJSONLoadFileDialog();
    if(!pathname.isEmpty()){
        TaskSetLoader taskLoader(pathname);
        try{
            taskLoader.readJson();
        } catch (NotValidTaskSetJSONFormatException &e) {
            GUI_CONTEXT.showMessageBox(e.what());
            return;
        }
        updateTaskTableContent();
        updateVMTableContent();
    }
}

void TaskSet::on_writeFile()
{
    QString pathname;
    pathname = FileDialogManager::getInstance().openJSONSaveFileDialog();
    TaskSetWriter taskWriter(pathname + ".json");
    taskWriter.writeJSON();
}

void TaskSet::on_eraseTasks()
{
    GUI_CONTEXT.erasePeriodicTaskData();
    ui->taskTable->setRowCount(0);
    currentRowTaskTable = 0; //Set to 0 the current row in the table
}

void TaskSet::on_removeVM()
{
    removeVMWindow.setTaskSet(this);
    removeVMWindow.loadVMList();
    removeVMWindow.show();
}

void TaskSet::on_editVM()
{
    modifyVMWindow.loadVMList();
    modifyVMWindow.setTaskSet(this);
    modifyVMWindow.show();
}

void TaskSet::on_eraseVM()
{
    confirmEraseVMs();
}

void TaskSet::on_removeTask()
{
    removeTaskWindow.setTaskSet(this);
    removeTaskWindow.loadTaskList();
    removeTaskWindow.show();
}

void TaskSet::on_editTask()
{
    modifyTaskWindow.loadTaskList();
    modifyTaskWindow.setTaskSet(this);
    modifyTaskWindow.show();
}

void TaskSet::on_okButton_clicked()
{
    this->close();
}

void TaskSet::confirmEraseVMs(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0, "Erase VMs", "Are you sure to erase all the VMs? \r\n All the tasks assigned to the VMs will be deleted",
                                        QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        GUI_CONTEXT.eraseVMData();

        ui->vmTable->setRowCount(0);
        currentRowVMTable = 0;

        updateTaskTableContent();
    }
}

