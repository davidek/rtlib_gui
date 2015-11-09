#ifndef RTSIMULATIONEXECUTOR_H
#define RTSIMULATIONEXECUTOR_H

class ScrollScheduleWindow;

/**
    Abstract Real Time Simulation class, base class for all the classes that run a RT SIM Simulation

    @see GlobalMPSIMExecutor, PartionedAutoMPSimExecutor, PartionedManualMPSimExecutor, MPExecutor

    @author Casini Daniel
*/
class RTSimulationExecutor
{
public:
    RTSimulationExecutor();
    ~RTSimulationExecutor();

protected:

    /// Schedule window (with scroll), to show the result of the simulation
    ScrollScheduleWindow *scheduleWin;

    /// Shows the schedule that consist in the result of the simulation
    void showResult();

    /// Abstract method to run the simulation
    virtual void simulate() = 0;

private:

    /// Saves the result of the simulation in a JSON trace file, after having asked the destination path
    void saveResult();
};

#endif // RTSIMULATIONEXECUTOR_H
