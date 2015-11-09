#ifndef ARCHITECTUREPARAMETER_H
#define ARCHITECTUREPARAMETER_H

/**
    Class used to represents a computer architecture, in which
    a task set is scheduled.
    A typical application is to contain the informations
    extracted from the trace file of a real time simulation

    @see TraceParser

    @author Casini Daniel
*/
class ArchitectureParameter
{
public:

    ArchitectureParameter();

    /**
     * @brief ArchitectureParameter
     * @param nCPU      number of CPUs
     * @param nTask     number of tasks
     * @param maxTime   maximum simulation time
     */
    ArchitectureParameter(int nCPU, int nTask, int maxTime);

    int nCPU() const;
    void setNCPU(int nCPU);

    int nTask() const;
    void setNTask(int nTask);

    int maxTime() const;
    void setMaxTime(int maxTime);

private:

    /// Number of CPU
    int _nCPU;

    /// Number of tasks
    int _nTask;

    /// Highest time in which an event happens
    int _maxTime;
};

#endif // ARCHITECTUREPARAMETER_H
