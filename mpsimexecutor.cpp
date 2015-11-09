#include "mpsimexecutor.h"

MPSimExecutor::MPSimExecutor()
{

}

int MPSimExecutor::nCPU() const
{
    return _nCPU;
}

void MPSimExecutor::setNCPU(int nCPU)
{
    _nCPU = nCPU;
}

int MPSimExecutor::simulTime() const
{
    return _simulTime;
}

void MPSimExecutor::setSimulTime(int simulTime)
{
    _simulTime = simulTime;
}
