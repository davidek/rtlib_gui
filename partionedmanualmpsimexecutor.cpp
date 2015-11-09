#include "partionedmanualmpsimexecutor.h"
#include "cpu.hpp"

#define DELETE(x) if(x) delete x;

PartionedManualMPSimExecutor::PartionedManualMPSimExecutor()
{}

PartionedManualMPSimExecutor::~PartionedManualMPSimExecutor()
{
    cleanExecutionData();
}


void PartionedManualMPSimExecutor::addCPUs2Kernel(PartionedMRTKernel &kern){
    map<CPU *, Scheduler *>::iterator it;
    for (it=kernelCPUSchedulerMap.begin(); it != kernelCPUSchedulerMap.end(); it++){
        kern.addCPU(it->first, it->second);        
    }
}


void PartionedManualMPSimExecutor::addTasks2Kernel(PartionedMRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace)
{
    map<QString, PeriodicTask*> &tasks = TASKS;
    map<QString, PeriodicTask*>::iterator it;

    CPU *cpu;
    PeriodicTask *task;

    for (it=tasks.begin(); it != tasks.end(); it++){

        task = it->second;
        ttrace.attachToTask(task);
        jtrace.attachToTask(task);

        if(GUI_CONTEXT.getTaskKernel(task->getName()) == "MainKernel"){

            cpu = kernelTaskCPUMap[task->getName()];
            kern.addTask(*task, "", cpu);

        }
        else{

            Server *kernel = GUI_CONTEXT.getKernel(task->getName());
            kernel->addTask(*task, "");
        }
    }
}

void PartionedManualMPSimExecutor::addVMs2Kernel(PartionedMRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace)//, JSONTrace &jtrace, TextTrace &ttrace)
{
    map<QString, PeriodicServerVM*> &PeriodicVMs = VMs;
    map<QString, PeriodicServerVM*>::iterator it;

    CPU *cpu;
    PeriodicServerVM* vm;

    for (it=PeriodicVMs.begin(); it != PeriodicVMs.end(); it++){

        vm = it->second;
        cpu = kernelTaskCPUMap[vm->getName()];

        kern.addVM(*vm , cpu);

        ttrace.attachToPeriodicServerVM(vm);
        jtrace.attachToPeriodicServerVM(vm);
    }
}

Scheduler *PartionedManualMPSimExecutor::createScheduler(unsigned int cpuIndex){
    schedulerTypes mode = CPUSchedulerMap[cpuIndex];
    switch(mode){
        case EDF:   return new EDFScheduler();
        case RM:    return new RMScheduler();
    }
}

CPU *PartionedManualMPSimExecutor::getTaskCPU(QString taskName){
    unsigned int index = TaskCPUMap[taskName.toStdString()];
    return CPUs[index];
}

void PartionedManualMPSimExecutor::createSimCPUScheduler(){

    unsigned int nCPU = GUI_CONTEXT.getNCPU();
    CPU *newCPU;

    for(unsigned int i=0; i<nCPU; i++){

        newCPU = new CPU();
        newCPU->setIndex(i);

        CPUs[i] = newCPU;
        kernelCPUSchedulerMap[newCPU] = createScheduler(i);

    }
}

void PartionedManualMPSimExecutor::createSimTaskCPU(){

    map<QString, PeriodicTaskData*> &tasksData = TASKS_DATA;
    map<QString, PeriodicTaskData*>::iterator it;

    PeriodicTaskData *temp;

    for (it=tasksData.begin(); it != tasksData.end(); it++){

        temp = it->second;

        if(temp->kernel() == "MainKernel")
            kernelTaskCPUMap[temp->name().toStdString()] = getTaskCPU(temp->name());

    }
}

void PartionedManualMPSimExecutor::createSimVMCPU(){

    map<QString, VMData*> &vmData = VMS_DATA;
    map<QString, VMData*>::iterator it;

    VMData *temp;

    for (it=vmData.begin(); it != vmData.end(); it++){

        temp = it->second;
        kernelTaskCPUMap[temp->name().toStdString()] = getTaskCPU(temp->name());

    }
}

void PartionedManualMPSimExecutor::cleanCPUs()
{
    map<unsigned int, CPU*>::iterator it;
    CPU *toDelete;;

    for (it=CPUs.begin(); it != CPUs.end(); it++){
        toDelete = it->second;
        DELETE(toDelete);
    }
}

void PartionedManualMPSimExecutor::cleanSchedulers()
{
    map<CPU*, Scheduler*>::iterator it;
    Scheduler *toDelete;

    for (it=kernelCPUSchedulerMap.begin(); it != kernelCPUSchedulerMap.end(); it++){

        toDelete = it->second;
        DELETE(toDelete);
    }
}

void PartionedManualMPSimExecutor::cleanExecutionData()
{
    cleanSchedulers();
    cleanCPUs();
    kernelCPUSchedulerMap.clear();
    kernelTaskCPUMap.clear();
    CPUSchedulerMap.clear();
    TaskCPUMap.clear();
    CPUs.clear();
}

void PartionedManualMPSimExecutor::simulate()
{
    try {

        PartionedMRTKernel kern("PartionedKern");
        TextTrace ttrace("run_log.txt");
        JSONTrace jtrace("run_trace.json");

        createSimCPUScheduler();
        createSimTaskCPU();
        createSimVMCPU();

        GUI_CONTEXT.addPeriodicTasks();
        GUI_CONTEXT.addVMs();

        addCPUs2Kernel(kern);
        addVMs2Kernel(kern, jtrace, ttrace);
        addTasks2Kernel(kern, jtrace, ttrace);

        SIMUL.run(_simulTime + 1);

    } catch (BaseExc &e) {

        GUI_CONTEXT.showMessageBox(e.what());
        GUI_CONTEXT.erasePeriodicTask();
        GUI_CONTEXT.erasePeriodicServerVM();

        cleanExecutionData();
        return;
    }

    showResult();

    GUI_CONTEXT.erasePeriodicTask();
    GUI_CONTEXT.erasePeriodicServerVM();
    cleanExecutionData();
}

void PartionedManualMPSimExecutor::setTaskCPUMap(const map<string, unsigned int> &value)
{
    TaskCPUMap = value;
}

void PartionedManualMPSimExecutor::setCPUSchedulerMap(const map<unsigned int, schedulerTypes> &value)
{
    CPUSchedulerMap = value;
}


