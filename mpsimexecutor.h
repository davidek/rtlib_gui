#ifndef MPSIMEXECUTOR_H
#define MPSIMEXECUTOR_H

#include "rtsimulationexecutor.h"
#include <kernel.hpp>
#include <partionedmrtkernel.hpp>
#include <edfsched.hpp>
#include <rttask.hpp>
#include <cbserver.hpp>
#include <supercbs.hpp>
#include <instr.hpp>
#include <TaskAllocation.hpp>
#include <QString>
#include <QMessageBox>
#include "guicontext.h"

/**
    Abstract Real Time MultiProcessor Simulation class, base class for all the classes that run
    a MultiProcessor RT SIM Simulation

    @see GlobalMPSIMExecutor, PartionedAutoMPSimExecutor, PartionedManualMPSimExecutor, RTSimulationExecutor

    @author Casini Daniel
*/
class MPSimExecutor : public RTSimulationExecutor
{
public:
    MPSimExecutor();

    int nCPU() const;
    void setNCPU(int nCPU);

    int simulTime() const;
    void setSimulTime(int simulTime);

    /**
     * @brief   simulate
     *          Abstract method to run the simulation
     */
    virtual void simulate() = 0;

protected:
    /// Number of CPUs
    int _nCPU;

    /// Maximum simulation time
    int _simulTime;
};

#endif // MPSIMEXECUTOR_H
