#include "guicontext.h"
#include <QMessageBox>
#include <server.hpp>

using namespace RTSim;

GUIContext *GUIContext::inst = 0;

GUIContext &GUIContext::getInstance(){

    if (inst == 0)
        inst = new GUIContext();

    return *inst;
}

GUIContext::GUIContext() : taskCounter(0), VMCounter(0), nCPU(1)
{

}

MapContainer<QString, VMData *> &GUIContext::getVmData()
{
    return vmData;
}

MapContainer<QString, PeriodicServerVM *> &GUIContext::getPeriodicVMs()
{
    return periodicVMs;
}

MapContainer<QString, PeriodicTaskData *> &GUIContext::getTasksData()
{
    return tasksData;
}

MapContainer<QString, PeriodicTask *> &GUIContext::getTasks()
{
    return tasks;
}

void GUIContext::addTasks2VM(PeriodicServerVM *vm)
{
    map<QString, PeriodicTask *>::iterator it;
    PeriodicTask *task;

    Server *impl = vm->getImplementation();

    for (it=TASKS.begin(); it != TASKS.end(); it++){

        task = it->second;

        if(getTaskKernel(task->getName()) == QString::fromStdString(vm->getName()))
            impl->addTask(*task, "");

    }
}


unsigned int GUIContext::getVMCounter() const
{
    return VMCounter;
}

PeriodicTaskData *GUIContext::getTaskData(QString taskName)
{
    return tasksData.getElement(taskName);
}

PeriodicTask *GUIContext::getTask(QString taskName)
{
    return tasks.getElement(taskName);
}

VMData *GUIContext::getVMData(QString vmName)
{
    return vmData.getElement(vmName);
}

PeriodicServerVM *GUIContext::getVM(QString vmName)
{
    return periodicVMs.getElement(vmName);
}

Server *GUIContext::getKernel(string taskName)
{
    QString             tName = QString::fromStdString(taskName);
    PeriodicTaskData    *taskData = getTaskData(tName);
    PeriodicServerVM    *vm = GUI_CONTEXT.getVM(taskData->kernel());
    Server              *kernel = vm->getImplementation();
    return kernel;
}

void GUIContext::setVMCounter(unsigned int value)
{
    VMCounter = value;
}

unsigned int GUIContext::getNCPU() const
{
    return nCPU;
}

void GUIContext::setNCPU(unsigned int value)
{
    nCPU = value;
}

void GUIContext::addPeriodicTaskData(const QString &name, int phase, int ci, int ti, int di, QString kernel){
    QString name_ = QString(name);
    PeriodicTaskData *temp;

    //avoids two elements with the same key, required also for name uniquely of entity metasim object
    while(tasksData.isPresent(name_)){
        name_ = name_ + "_1";
    }

    temp = new PeriodicTaskData(name_, phase, ci, ti, di, kernel);
    tasksData.addElement(name_, temp);

    taskCounter++;
}

QString GUIContext::getTaskKernel(QString taskName)
{
    PeriodicTaskData *tData = tasksData.getElement(taskName);
    return tData->kernel();
}

QString GUIContext::getTaskKernel(string taskName)
{
    return getTaskKernel(QString::fromStdString(taskName));
}

void GUIContext::addVMData(QString name, int budget, int period)
{
    VMData *temp;

    //avoids two elements with the same key, required also for name uniquely of entity metasim object
    while(vmData.isPresent(name)){
        name = name + "_1";
    }

    temp = new VMData(name, budget, period);
    vmData.addElement(name, temp);

    VMCounter++;
}

void GUIContext::removeVMData(QString name)
{

    vmData.removeElement(name);
    VMCounter--;
}

void GUIContext::eraseVMData()
{
    map<QString, VMData*>::iterator it;
    VMData *temp;
    for (it=VMS_DATA.begin(); it != VMS_DATA.end(); it++){
        temp = it->second;
        GUI_CONTEXT.removeTasksByVM(temp->name());
    }

    vmData.erase();
    VMCounter = 0;
}

PeriodicTask *GUIContext::addPeriodicTask(PeriodicTaskData *taskData)
{
    return addPeriodicTask(taskData->name(),
                           taskData->phase(),
                           taskData->ci(),
                           taskData->ti(),
                           taskData->di());
}

PeriodicTask *GUIContext::addPeriodicTask(const QString &name, int phase, int ci, int ti, int di){

    PeriodicTask *temp;
    temp = createPeriodicTask(name, phase, ci, ti, di);
    tasks.addElement(name, temp);
    return temp;

}

PeriodicTask *GUIContext::createPeriodicTask(const QString &name, int phase, int ci, int ti, int di)
{
    PeriodicTask *task = new PeriodicTask(ti, di, phase, name.toStdString());
    string code;
    code += "fixed("+ to_string(ci) + ");";
    task->insertCode(code);

    return task;
}

PeriodicServerVM *GUIContext::addVM(VMData *vmData)
{
    PeriodicServerVM *VM = new PeriodicServerVM;
    VM->createFromQP(vmData->name().toStdString(), vmData->budget(), vmData->period());

    periodicVMs.addElement(vmData->name(), VM);

    return VM;
}

unsigned int GUIContext::getTaskCount() const{
    return taskCounter;
}

void GUIContext::removePeriodicTaskData(QString name){
    tasksData.removeElement(name);
    taskCounter--;
}

void GUIContext::removePeriodicTask(QString name){
    tasks.removeElement(name);
}

void GUIContext::erasePeriodicTaskData(){

    tasksData.erase();
    taskCounter = 0;

}

bool GUIContext::taskInserted(QString taskName){
    return tasksData.isPresent(taskName);
}

void GUIContext::erasePeriodicTask(){
    tasks.erase();
}

void GUIContext::erasePeriodicServerVM(){
    periodicVMs.erase();
}

void GUIContext::addPeriodicTasks(){

    map<QString, PeriodicTaskData*>::iterator it;
    PeriodicTaskData *taskData;

    for (it=TASKS_DATA.begin(); it != TASKS_DATA.end(); it++){
        taskData = it->second;
        addPeriodicTask(taskData);
    }

}

void GUIContext::addVMs()
{
    map<QString, VMData*>::iterator it;
    VMData *vm;

    for (it=VMS_DATA.begin(); it != VMS_DATA.end(); it++){
        vm = it->second;
        addVM(vm);
    }
}

unsigned int gcd (unsigned int n1, unsigned int n2) {
    return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}

unsigned int lcm(unsigned int a, unsigned int b)
{
    unsigned int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

unsigned int GUIContext::getHyperPeriod(){

    map<QString, PeriodicTaskData*>::iterator it;
    PeriodicTaskData *temp;

    unsigned int hyperperiod = 0;
    bool first = true;

    for (it=TASKS_DATA.begin(); it != TASKS_DATA.end(); it++){
        temp = it->second;
        if(first){
            hyperperiod = (int)temp->ti();
            first = false;
        }
        else
            hyperperiod = lcm(hyperperiod, (int)temp->ti());
    }

    return hyperperiod;
}

void GUIContext::showMessageBox(string message)
{
    QMessageBox *msgBox = new QMessageBox();
    msgBox->setText(QString::fromStdString(message));
    msgBox->exec();
    delete msgBox;
}

void GUIContext::removeTasksByVM(QString vmName){

    PeriodicTaskData    *temp;
    vector<QString>     keysToRemove;

    map<QString, PeriodicTaskData*>::iterator it;

    for (it=TASKS_DATA.begin(); it != TASKS_DATA.end(); it++){
        temp = it->second;

        if(temp->kernel() == vmName){
            keysToRemove.push_back(temp->name());
        }

    }

    vector<QString>::iterator deleteIter;
    QString name;

    for (deleteIter=keysToRemove.begin(); deleteIter != keysToRemove.end(); deleteIter++){
        name = *deleteIter;
        removePeriodicTaskData(name);
    }

}

void GUIContext::moveTasksVM(QString oldVMName, QString VMName){

    PeriodicTaskData *temp;
    map<QString, PeriodicTaskData*>::iterator it;

    for (it=TASKS_DATA.begin(); it != TASKS_DATA.end(); it++){
        temp = it->second;
        if(temp->kernel() == oldVMName)
            temp->setKernel(VMName);
    }

}


