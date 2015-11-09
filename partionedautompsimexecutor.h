#ifndef PARTIONEDAUTOMPSIMEXECUTOR_H
#define PARTIONEDAUTOMPSIMEXECUTOR_H

#include "mpsimexecutor.h"
#include "taskallocationviewer.h"

using namespace RTSim;

/**
    Partioned Scheduling MultiProcessor (with automatic task allocation) Simulation class

    @see GlobalMPSIMExecutor, MPSimExecutor, RTSimulationExecutor

    @author Casini Daniel
*/
class PartionedAutoMPSimExecutor : public MPSimExecutor
{
public:
    PartionedAutoMPSimExecutor();

    /**
     * @brief   simulate
     *          Runs the simulation
     */
    void simulate();

    /**
     * @brief   setSchedType
     *          Sets the scheduler type
     * @param   schedType
     */
    void setSchedType(const schedulerTypes &schedType);

    /**
     * @brief   setAllocationStrategyType
     *          Sets the task allocation strategy
     * @param   allocationStrategyType
     */
    void setAllocationStrategyType(const allocationStrategies &allocationStrategyType);

private:

    /// Scheduler factory
    AbsSchedulerFactory     *_schedFactory;

    /// Task Allocation algorithm
    AbsTaskAllocation       *_taskAllocationStrategy;

    /// Scheduler type
    schedulerTypes          _schedType;

    /// Task Allocation type
    allocationStrategies    _allocationStrategyType;

    /// Windows which shows the task allocation (automatic)
    TaskAllocationViewer    _allocationViewer;

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
    void addVMs2Kernel(MRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace);

    /**
     * @brief   createSchedulerFactory
     * @return  A scheduler factory object of type _allocationStrategyType
     */
    AbsSchedulerFactory     *createSchedulerFactory();

    /**
     * @brief   createAllocationStrategy
     * @return  A task allocation algorithm object of type _schedType
     */
    AbsTaskAllocation       *createAllocationStrategy();
};

#endif // PARTIONEDAUTOMPSIMEXECUTOR_H
