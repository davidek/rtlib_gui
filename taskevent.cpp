#include "taskevent.h"

TaskEvent::TaskEvent(){}

unsigned int TaskEvent::time() const
{
    return _time;
}

void TaskEvent::setTime(unsigned int time)
{
    _time = time;
}
QString TaskEvent::eventType() const
{
    return _eventType;
}

void TaskEvent::setEventType(const QString &eventType)
{
    _eventType = eventType;
}
QString TaskEvent::taskName() const
{
    return _taskName;
}

void TaskEvent::setTaskName(const QString &taskName)
{
    _taskName = taskName;
}
unsigned int TaskEvent::arrival() const
{
    return _arrival;
}

void TaskEvent::setArrival(unsigned int arrival)
{
    _arrival = arrival;
}
unsigned int TaskEvent::cpu() const
{
    return _cpu;
}

void TaskEvent::setCpu(unsigned int cpu)
{
    _cpu = cpu;
}

bool TaskEvent::isServer() const
{
    return _server;
}

void TaskEvent::setServer(const bool &server)
{
    _server = server;
}




