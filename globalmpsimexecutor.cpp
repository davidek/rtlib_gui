#include "globalmpsimexecutor.h"

GlobalMPSIMExecutor::GlobalMPSIMExecutor() : MPSimExecutor()
{

}

Scheduler *GlobalMPSIMExecutor::createScheduler(){

    switch(_schedType){
        case EDF:   return new EDFScheduler();
        case RM:    return new RMScheduler();
    }
}

void GlobalMPSIMExecutor::simulate(){

    _sched = createScheduler();

    try {

    MRTKernel kern(_sched, _nCPU, "GlobalKern");

    TextTrace ttrace("run_log.txt");
    JSONTrace jtrace("run_trace.json");

    GUI_CONTEXT.addPeriodicTasks();
    GUI_CONTEXT.addVMs();
    addVMs2Kernel(kern, jtrace, ttrace);
    addTasks2Kernel(kern, jtrace, ttrace);

    SIMUL.run(_simulTime + 1);

    } catch (BaseExc &e) {
        GUI_CONTEXT.showMessageBox(e.what());
        GUI_CONTEXT.erasePeriodicTask();
        GUI_CONTEXT.erasePeriodicServerVM();

        return;
    }

    showResult();

    GUI_CONTEXT.erasePeriodicTask();
    GUI_CONTEXT.erasePeriodicServerVM();

}

schedulerTypes GlobalMPSIMExecutor::schedType() const
{
    return _schedType;
}

void GlobalMPSIMExecutor::setSchedType(const schedulerTypes &schedType)
{
    _schedType = schedType;
}

void GlobalMPSIMExecutor::addTasks2Kernel(MRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace)
{
    map<QString, PeriodicTask*> &tasks = TASKS;
    map<QString, PeriodicTask*>::iterator it;

    PeriodicTask *task;
    for (it=tasks.begin(); it != tasks.end(); it++){

        task = it->second;
        ttrace.attachToTask(task);
        jtrace.attachToTask(task);

        if(GUI_CONTEXT.getTaskKernel(task->getName()) == "MainKernel")
            kern.addTask(*task, "");
        else{

            QString taskName = QString::fromStdString(task->getName());
            PeriodicTaskData *taskData = GUI_CONTEXT.getTaskData(taskName);
            PeriodicServerVM *vm = GUI_CONTEXT.getVM(taskData->kernel());
            Server *kernel = vm->getImplementation();
            kernel->addTask(*task, "");

        }
    }
}

void GlobalMPSIMExecutor::addVMs2Kernel(MRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace)
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

