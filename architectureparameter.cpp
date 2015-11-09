#include "architectureparameter.h"

ArchitectureParameter::ArchitectureParameter(){}


ArchitectureParameter::ArchitectureParameter(int nCPU, int nTask, int maxTime) :
    _nCPU(nCPU),_nTask(nTask), _maxTime(maxTime){}

int ArchitectureParameter::nTask() const
{
    return _nTask;
}

void ArchitectureParameter::setNTask(int nTask)
{
    _nTask = nTask;
}

int ArchitectureParameter::maxTime() const
{
    return _maxTime;
}

void ArchitectureParameter::setMaxTime(int maxTime)
{
    _maxTime = maxTime;
}

int ArchitectureParameter::nCPU() const
{
    return _nCPU;
}

void ArchitectureParameter::setNCPU(int nCPU)
{
    _nCPU = nCPU;
}
