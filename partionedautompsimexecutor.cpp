#include "partionedautompsimexecutor.h"

PartionedAutoMPSimExecutor::PartionedAutoMPSimExecutor()
{}


void PartionedAutoMPSimExecutor::simulate(){

    _schedFactory = createSchedulerFactory();
    _taskAllocationStrategy = createAllocationStrategy();

    try {

        PartionedMRTKernel kern(_nCPU, "PartionedKern", _schedFactory, _taskAllocationStrategy);

        TextTrace ttrace("run_log.txt");
        JSONTrace jtrace("run_trace.json");

        GUI_CONTEXT.addPeriodicTasks();
        GUI_CONTEXT.addVMs();

        addVMs2Kernel(kern, jtrace, ttrace);
        addTasks2Kernel(kern, jtrace, ttrace);

        kern.allocateTask();

        _allocationViewer.updateWindow(kern.getTaskAllocator()->getCpuTaskAllocation(),
                                       kern.getTaskAllocator()->getAllocatedTasks());

        SIMUL.run(_simulTime + 1);


    } catch (BaseExc &e) {
        GUI_CONTEXT.showMessageBox(e.what());
        GUI_CONTEXT.erasePeriodicTask();
        GUI_CONTEXT.erasePeriodicServerVM();
        return;
    }

    showResult();

    _allocationViewer.show();

    GUI_CONTEXT.erasePeriodicTask();
    GUI_CONTEXT.erasePeriodicServerVM();
}

void PartionedAutoMPSimExecutor::setSchedType(const schedulerTypes &schedType)
{
    _schedType = schedType;
}

void PartionedAutoMPSimExecutor::setAllocationStrategyType(const allocationStrategies &allocationStrategyType)
{
    _allocationStrategyType = allocationStrategyType;
}

void PartionedAutoMPSimExecutor::addTasks2Kernel(PartionedMRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace)
{
    map<QString, PeriodicTask*> &tasks = TASKS;
    map<QString, PeriodicTask*>::iterator it;

    PeriodicTask *task;

    for (it=tasks.begin(); it!=tasks.end(); it++){

        task = it->second;

        ttrace.attachToTask(task);
        jtrace.attachToTask(task);
        if(GUI_CONTEXT.getTaskKernel(task->getName()) == "MainKernel")
            kern.addTask(*task, "");
        else{

            Server *kernel = GUI_CONTEXT.getKernel(task->getName());
            kernel->addTask(*task, "");
        }
    }
}

void PartionedAutoMPSimExecutor::addVMs2Kernel(MRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace)//, JSONTrace &jtrace, TextTrace &ttrace)
{
    map<QString, PeriodicServerVM*> &PeriodicVMs = VMs;
    map<QString, PeriodicServerVM*>::iterator it;

    PeriodicServerVM* vm;

    for (it=PeriodicVMs.begin(); it != PeriodicVMs.end(); it++){
        vm = it->second;
        kern.addVM(*vm);

        ttrace.attachToPeriodicServerVM(vm);
        jtrace.attachToPeriodicServerVM(vm);
    }
}

AbsSchedulerFactory *PartionedAutoMPSimExecutor::createSchedulerFactory(){
    switch(_schedType){
        case EDF:   return new EDFSchedulerFactory();
        case RM:    return new RMSchedulerFactory();
    }
}

AbsTaskAllocation *PartionedAutoMPSimExecutor::createAllocationStrategy(){
    switch(_allocationStrategyType){
        case NEXT_FIT:          return new NextFitTaskAllocation();
        case BEST_FIT:          return new BestFitTaskAllocation();
        case WORST_FIT:         return new WorstFitTaskAllocation();
        case FIRST_FIT:         return new FirstFitTaskAllocation();
        case FIRST_FIT_DECR:    return new FirstFitDecreasingTaskAllocation();
    }
}
