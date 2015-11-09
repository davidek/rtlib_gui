#include "taskallocationwindow.h"
#include "ui_taskallocationwindow.h"

#include "guiexception.h"
#include "filedialogmanager.h"


#include "scrollschedulewindow.h"
using namespace RTSim;

TaskAllocationWindow::TaskAllocationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskAllocationWindow)
{
    ui->setupUi(this);
    createMenu();

    // Sets the number of rows and columns in the tables
    ui->taskTable->setRowCount(0);
    ui->cpuTable->setRowCount(0);
    ui->taskTable->setColumnCount(2);
    ui->cpuTable->setColumnCount(2);

    // Makes the table not editable
    ui->taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cpuTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updateWindow();

    setFixedSize(this->size());
}


void TaskAllocationWindow::updateWindow(){

    ui->taskTable->setRowCount(0);
    ui->cpuTable->setRowCount(0);

    fillCPUTable();
    fillTaskTable();

    //Computes hyperperiod
    unsigned int time = GUI_CONTEXT.getHyperPeriod();

    //Default text for the simulation time edit
    ui->simulTimeEdit->setText(QString::number(time));

}

void TaskAllocationWindow::createMenu(){

    menuBar = new QMenuBar(this);
    fileMenu = new QMenu("File");

    read = fileMenu->addAction("Read JSON");
    write = fileMenu->addAction("Write JSON");

    menuBar->addMenu(fileMenu);

    connect(read, SIGNAL(triggered()),this,SLOT(on_readFile()));
    connect(write, SIGNAL(triggered()),this,SLOT(on_writeFile()));
}

void TaskAllocationWindow::deleteMenu(){
    delete read;
    delete write;
    delete fileMenu;
    delete menuBar;
}

void TaskAllocationWindow::getTaskCPUMap(map<QString, unsigned int> &taskCPUMap){

    map<QString, QComboBox*>::iterator it;

    QString name;
    QComboBox *box;

    for (it=taskBoxMap.begin(); it != taskBoxMap.end(); it++){
        box = it->second;
        name = it->first;
        taskCPUMap[name] = box->currentIndex();
    }
}

void TaskAllocationWindow::getCPUSchedulerMap(map<unsigned int, QString> &cpuSchedulerMap){

    unsigned int i;
    QComboBox *box;

    unsigned int nCPU = GUI_CONTEXT.getNCPU();

    for(i=0; i<nCPU; i++){
        box = this->cpuBoxMap[i];
        cpuSchedulerMap[i] = box->currentText();
    }

}

void TaskAllocationWindow::on_writeFile(){

    map<QString, unsigned int> taskCPUMap;
    map<unsigned int, QString> cpuSchedulerMap;

    getTaskCPUMap(taskCPUMap);
    getCPUSchedulerMap(cpuSchedulerMap);

    QString pathname;
    pathname = FileDialogManager::getInstance().openJSONSaveFileDialog();

    ArchitectureWriter archWriter(pathname + ".json");
    archWriter.writeJSON(taskCPUMap, cpuSchedulerMap);

}


void TaskAllocationWindow::on_readFile(){

    map<QString, unsigned int> taskCPUMap;
    map<unsigned int, QString> cpuSchedulerMap;

    QString pathname;
    pathname = FileDialogManager::getInstance().openJSONLoadFileDialog();
    ArchitectureLoader archLoader(pathname);

    try{
       archLoader.readJson(taskCPUMap, cpuSchedulerMap);
    } catch (RTSim::BaseExc &e) {
        GUI_CONTEXT.showMessageBox(e.what());
        return;
    }

    GUI_CONTEXT.setNCPU(cpuSchedulerMap.size());

    eraseTaskTable();
    eraseCPUTable();

    fillTaskTable();
    fillCPUTable();

    updateCPUTable(cpuSchedulerMap);
    updateTaskTable(taskCPUMap);
}

void TaskAllocationWindow::eraseTaskTable(){

    map<QString, QComboBox*>::iterator it;
    QComboBox *box;

    for (it=taskBoxMap.begin(); it != taskBoxMap.end(); it++){
        box = it->second;
        box->clear();
    }

    ui->taskTable->setRowCount(0);
}

void TaskAllocationWindow::eraseCPUTable(){

    map<unsigned int, QComboBox*>::iterator it;
    QComboBox *box;

    for (it=cpuBoxMap.begin(); it != cpuBoxMap.end(); it++){
        box = it->second;
        box->clear();
    }

    ui->cpuTable->setRowCount(0);
}

void TaskAllocationWindow::fillWithTasks(unsigned int &startIndex){
    map<QString, PeriodicTaskData*> tasksData = TASKS_DATA;
    map<QString, PeriodicTaskData*>::iterator taskIter;
    PeriodicTaskData *task;
    QString name;

    unsigned int i = startIndex;

    for (taskIter=tasksData.begin(); taskIter != tasksData.end(); taskIter++){
        name = taskIter->first;
        task = taskIter->second;
        if(task->kernel() == "MainKernel"){
            addTask2Table(name, i);
            i++;
        }
    }

    startIndex = i;
}

void TaskAllocationWindow::fillWithVMs(unsigned int &startIndex){
    map<QString, VMData*> vmData = VMS_DATA;
    map<QString, VMData*>::iterator vmIter;

    QString name;
    unsigned int i = startIndex;

    for (vmIter=vmData.begin(); vmIter != vmData.end(); vmIter++){
        name = vmIter->first;
        addTask2Table(name, i);
        i++;
    }

    startIndex = i;
}

void TaskAllocationWindow::fillTaskTable(){

    QStringList m_TableHeader;
    m_TableHeader<<"Task"<<"CPU";

    ui->taskTable->setHorizontalHeaderLabels(m_TableHeader);
    unsigned int startIndex = 0;

    fillWithTasks(startIndex);
    fillWithVMs(startIndex);

}

void TaskAllocationWindow::fillCPUTable(){

    QStringList m_TableHeader;
    m_TableHeader<<"CPU"<<"Scheduler";
    ui->cpuTable->setHorizontalHeaderLabels(m_TableHeader);

    unsigned int nCPU = GUI_CONTEXT.getNCPU();
    int i = 0;

    for(i=0; i<nCPU; i++){
        addCPU2Table(i);
    }
}

void TaskAllocationWindow::updateCPUTable(map<unsigned int, QString> cpuSchedulerMap){

    unsigned int    nCPU = cpuSchedulerMap.size();

    QComboBox       *box;
    for(unsigned int i=0; i<nCPU; i++){
        box  = cpuBoxMap[i];
        if(cpuSchedulerMap[i] == "EDF")
            box->setCurrentIndex(0);
        else if(cpuSchedulerMap[i] == "RM")
            box->setCurrentIndex(1);
    }
}

void TaskAllocationWindow::updateTaskTable(map<QString, unsigned int> taskCPUMap){

    QString name;

    map<QString, QComboBox*>::iterator it;
    QComboBox *box;

    for (it=taskBoxMap.begin(); it != taskBoxMap.end(); it++){
        name = it->first;
        box = it->second;
        box->setCurrentIndex(taskCPUMap[name]);
    }

}

void TaskAllocationWindow::addTask2Table(QString name, unsigned int row){

    unsigned int col = 0;

    //Increments the number of rows in the table
    ui->taskTable->setRowCount(ui->taskTable->rowCount() + 1);

    //Creates the table element
    QTableWidgetItem* newItem = new QTableWidgetItem();
    newItem->setText(name);
    ui->taskTable->setItem(row, col, newItem);
    col++;

    //Creates the combo box
    QComboBox *box  = createTaskCPUCBox();
    taskBoxMap[name] = box;

    //Adds the widget to the table
    ui->taskTable->setCellWidget(row, col, box);
    ui->taskTable->update();
    ui->taskTable->resizeColumnsToContents();
}

void TaskAllocationWindow::addCPU2Table(unsigned int index){

    unsigned int col = 0;

    ui->cpuTable->setRowCount(ui->cpuTable->rowCount() + 1);

    QTableWidgetItem* newItem = new QTableWidgetItem();
    newItem->setText(("CPU " + QString::number(index)));
    ui->cpuTable->setItem(index, col, newItem);
    col++;

    QComboBox *box  = createCPUSchedulerCBox();

    cpuBoxMap[index] = box;

    ui->cpuTable->setCellWidget(index, col, box);
    ui->cpuTable->update();
    ui->cpuTable->resizeColumnsToContents();
}

QComboBox *TaskAllocationWindow::createTaskCPUCBox(){
    QComboBox* newItem = new QComboBox;
    unsigned int nCPU = GUI_CONTEXT.getNCPU();
    for(unsigned int i=0; i<nCPU; i++){
        newItem->addItem(("CPU" + QString::number(i)));
    }
    return newItem;
}

QComboBox *TaskAllocationWindow::createCPUSchedulerCBox(){
    QComboBox* newItem = new QComboBox;
    newItem->addItem("EDF");
    newItem->addItem("RM");
    return newItem;
}

template <class key, class type>
void deleteComboBoxMaps(map<key, type> &myMap){
    typename map<key, type>::iterator it;
    for (it=myMap.begin(); it != myMap.end(); it++){
        delete it->second;
    }
    myMap.clear();
}

TaskAllocationWindow::~TaskAllocationWindow()
{
    deleteMenu();
    deleteComboBoxMaps(taskBoxMap);
    deleteComboBoxMaps(cpuBoxMap);
    delete ui;
}



schedulerTypes TaskAllocationWindow::getScheduler(unsigned int cpuIndex){
    QComboBox *box = this->cpuBoxMap[cpuIndex];
    return (schedulerTypes) box->currentIndex();
}



unsigned int TaskAllocationWindow::getTaskCPU(QString taskName){
    QComboBox *box = this->taskBoxMap[taskName];
    return box->currentIndex();
}

void TaskAllocationWindow::extractEditFieldData(int &simulTime){
    bool isInteger;
    simulTime = ui->simulTimeEdit->text().toInt(&isInteger);
    if( !isInteger || simulTime < 0){
        throw InputDataFormatException("Not valid data format");
    }
}




void TaskAllocationWindow::createSimCPUScheduler(map<unsigned int, schedulerTypes> &kernelCPUSchedulerMap){

    unsigned int nCPU = GUI_CONTEXT.getNCPU();

    for(unsigned int i=0; i<nCPU; i++){
        kernelCPUSchedulerMap[i] = getScheduler(i);
    }
}

void TaskAllocationWindow::createSimTaskCPU(map<string, unsigned int> &kernelTaskCPUMap){

    QString taskName;
    string key;
    map<QString, QComboBox*>::iterator it;
    for (it=taskBoxMap.begin(); it != taskBoxMap.end(); it++){
        taskName = it->first;
        key = taskName.toStdString();
        kernelTaskCPUMap[key] = getTaskCPU(taskName);
    }
}


void TaskAllocationWindow::on_runButton_clicked()
{
    int simulTime;

    map<unsigned int, schedulerTypes>       simulatorCPUSchedulerMap;
    map<string , unsigned int>              simulatorTaskCPUMap;

    createSimCPUScheduler(simulatorCPUSchedulerMap);
    createSimTaskCPU(simulatorTaskCPUMap);

    try{
        extractEditFieldData(simulTime);
    }catch(InputDataFormatException &e){
        GUI_CONTEXT.showMessageBox(e.what());
        return;
    }

    simulator.setCPUSchedulerMap(simulatorCPUSchedulerMap);
    simulator.setTaskCPUMap(simulatorTaskCPUMap);
    simulator.setSimulTime(simulTime);
    simulator.simulate();

}
