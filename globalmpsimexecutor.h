#ifndef GLOBALMPSIMEXECUTOR_H
#define GLOBALMPSIMEXECUTOR_H

#include "mpsimexecutor.h"

using namespace RTSim;

/**
    Global Scheduling MultiProcessor Simulation class

    @see GlobalMPSIMExecutor, MPSimExecutor, RTSimulationExecutor

    @author Casini Daniel
*/
class GlobalMPSIMExecutor : public MPSimExecutor
{
public:
    GlobalMPSIMExecutor();

    schedulerTypes schedType() const;
    void setSchedType(const schedulerTypes &schedType);

    /// Executes the simulation
    void simulate();

    /**
     * @brief   createScheduler
     * @return  Creates a scheduler of type _schedType
     */
    Scheduler *createScheduler();

private:

    /// Scheduler object
    Scheduler       *_sched;

    /// Scheduler type
    schedulerTypes  _schedType;

    /**
     * @brief   addTasks2Kernel
     *          Adds each task to its kernel (MainKernel or a VM)
     * @param   kern
     * @param   jtrace    JSON trace object
     * @param   ttrace    Text trace object
     */
    void addTasks2Kernel(MRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace);

    /**
     * @brief   addVMs2Kernel
     *          adds a VM to the kernel
     * @param   kern
     * @param   jtrace    JSON trace object
     * @param   ttrace    Text trace object
     */
    void addVMs2Kernel(MRTKernel &kern, JSONTrace &jtrace, TextTrace &ttrace);

};



#endif // GLOBALMPSIMEXECUTOR_H
