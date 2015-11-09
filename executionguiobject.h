#ifndef EXECUTIONGUIOBJECT_H
#define EXECUTIONGUIOBJECT_H

/**
    Represent an "execution slot" of task on a CPU, in the interval [tStart, tEnd].

    @author Casini Daniel
*/
class ExecutionGUIObject
{

public:
    ExecutionGUIObject(){}

    /**
     * @brief ExecutionGUIObject
     * @param tStart    time in which the execution interval begins
     * @param tEnd      time in which the execution interval terminates
     * @param cpu       cpu in which the execution is performed
     */
    ExecutionGUIObject(unsigned int tStart, unsigned int tEnd, unsigned int cpu);

    unsigned int getTStart() const;
    void setTStart(unsigned int value);

    unsigned int getTEnd() const;
    void setTEnd(unsigned int value);

    unsigned int getCpu() const;
    void setCpu(unsigned int value);

private:

    /// time in which the execution begins
    unsigned int tStart;

    /// time in which the execution terminates
    unsigned int tEnd;

    /// cpu in which the execution is performed
    unsigned int cpu;
};

#endif // EXECUTIONGUIOBJECT_H
