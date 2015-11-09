#include "gui_types.h"

PeriodicTaskData::PeriodicTaskData()
{}


PeriodicTaskData::PeriodicTaskData(QString name, int phase, int ci, int ti, int di, QString kernel) :
    _name(name), _phase(phase), _ci(ci), _ti(ti), _di(di), _kernel(kernel)
{}

QString PeriodicTaskData::name() const
{
    return _name;
}

void PeriodicTaskData::setName(const QString &name)
{
    _name = name;
}

int PeriodicTaskData::phase() const
{
    return _phase;
}

void PeriodicTaskData::setPhase(int phase)
{
    _phase = phase;
}

int PeriodicTaskData::ci() const
{
    return _ci;
}

void PeriodicTaskData::setCi(int ci)
{
    _ci = ci;
}

int PeriodicTaskData::ti() const
{
    return _ti;
}

void PeriodicTaskData::setTi(int ti)
{
    _ti = ti;
}

int PeriodicTaskData::di() const
{
    return _di;
}
void PeriodicTaskData::setDi(int di)
{
    _di = di;
}
QString PeriodicTaskData::kernel() const
{
    return _kernel;
}

void PeriodicTaskData::setKernel(const QString &kernel)
{
    _kernel = kernel;
}

// VMData class definition

VMData::VMData()
{}

VMData::VMData(QString name, int budget, int period) : _name(name), _budget(budget), _period(period)
{}


int VMData::budget() const
{
    return _budget;
}

void VMData::setBudget(int budget)
{
    _budget = budget;
}
int VMData::period() const
{
    return _period;
}

void VMData::setPeriod(int period)
{
    _period = period;
}

QString VMData::name() const
{
    return _name;
}

void VMData::setName(const QString &name)
{
    _name = name;
}



