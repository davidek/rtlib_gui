#ifndef PARTIONEDMANUALMPSIMEXECUTOR_H
#define PARTIONEDMANUALMPSIMEXECUTOR_H

#include "mpsimexecutor.h"

/**
    Partioned Scheduling MultiProcessor (with manual task allocation) Simulation class

    @see GlobalMPSIMExecutor, MPSimExecutor, RTSimulationExecutor

    @author Casini Daniel
*/
class PartionedManualMPSimExecutor : public MPSimExecutor
{
public:
    PartionedManualMPSimExecutor();
    ~PartionedManualMPSimExecutor();

    /**
     * @brief   simulate
     *          Runs the simulation
     */
    void simulate();

    /**
     * @brief setTaskCPUMap
     * @param value taskName-cpuIndex correspondence
     */
    void setTaskCPUMap(const map<string, unsigned int> &value);

    /**
     * @brief setCPUSchedulerMap
     * @param value cpuIndex-schedulerType correspondence
     */
    void setCPUSchedulerMap(const map<unsigned int, schedulerTypes> &value);

private:
    /// cpuIndex - cpuObject correspondence
    map<unsigned int, CPU*> CPUs;

    /// cpuIndex - schedulerType correspondence
    map<unsigned int, schedulerTypes>   CPUSchedulerMap;

    /// taskName - cpuIndex correspondence
    map<string, unsigned int>           TaskCPUMap;

    /// CPU - Scheduler correspondence
    map<CPU*, Scheduler*>               kernelCPUSchedulerMap;

    /// taskName - CPU correspondence
    map<string, CPU*>                   kernelTaskCPUMap;

    /**
     * @brief   addCPUs2Kernel
     *          Adds the CPUs to the given kernel
     * @param   kern
     */
    void addCPUs2Kernel(PartionedMRTKernel &kern);

    /**
     * @brief   addTasks2Kernel
     *          Adds each task to its kernel (MainKernel or a VM)
     * @param   kern
     * @param   jtrace    JSON trace object
     * @param   ttrace    Text trace object
     */
    void addTasks2Kernel(PartionedMRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace);

    /**
     * @brief   addVMs2Kernel
     *          adds a VM to the kernel
     * @param   kern
     * @param   jtrace    JSON trace object
     * @param   ttrace    Text trace object
     */
    void addVMs2Kernel(PartionedMRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace);

    /**
     * @brief   createScheduler
     *          Creates a scheduler of the proper type
     * @param   cpuIndex
     * @return  scheduler
     */
    Scheduler *createScheduler(unsigned int cpuIndex);

    /**
     * @brief   getTaskCPU
     * @param   taskName
     * @return  the cpu of the given task
     */
    CPU *getTaskCPU(QString taskName);

    /**
     * @brief   createSimCPUScheduler
     *          Initializes the kernelCPUSchedulerMap data structure
     */
    void createSimCPUScheduler();

    /**
     * @brief   createSimCPUScheduler
     *          Initializes the kernelTaskCPUMap data structure with the task-cpu correspondence
     */
    void createSimTaskCPU();

    /**
     * @brief   createSimVMCPU
     *          Initializes the kernelTaskCPUMap data structure with the vm-cpu correspondence
     */
    void createSimVMCPU();

    /**
     * @brief   cleanCPUs
     *          Deletes the CPUs
     */
    void cleanCPUs();

    /**
     * @brief   cleanSchedulers
     *          Deletes the schedulers
     */
    void cleanSchedulers();

    /**
     * @brief   cleanExecutionData
     *          Cleans the data structures
     */
    void cleanExecutionData();
};

#endif // PARTIONEDMANUALMPSIMEXECUTOR_H
