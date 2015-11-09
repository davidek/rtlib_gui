#include "executionguiobject.h"

ExecutionGUIObject::ExecutionGUIObject(unsigned int tStart, unsigned int tEnd, unsigned int cpu)
{
    this->tStart = tStart;
    this->tEnd = tEnd;
    this->cpu = cpu;
}

unsigned int ExecutionGUIObject::getTStart() const
{
    return tStart;
}

void ExecutionGUIObject::setTStart(unsigned int value)
{
    tStart = value;
}
unsigned int ExecutionGUIObject::getTEnd() const
{
    return tEnd;
}

void ExecutionGUIObject::setTEnd(unsigned int value)
{
    tEnd = value;
}
unsigned int ExecutionGUIObject::getCpu() const
{
    return cpu;
}

void ExecutionGUIObject::setCpu(unsigned int value)
{
    cpu = value;
}

