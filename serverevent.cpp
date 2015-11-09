#include "serverevent.h"

ServerEvent::ServerEvent()
{}

ServerEvent::ServerEvent(QString serverName, QString eventType, int time, int budget, int currentBudget, int period) :
     _serverName(serverName),
     _time(time),
     _eventType(eventType),
     _budget(budget),
     _currentBudget(currentBudget),
     _period(period)
{}

QString ServerEvent::eventType() const
{
    return _eventType;
}

void ServerEvent::setEventType(const QString &eventType)
{
    _eventType = eventType;
}

QString ServerEvent::serverName() const
{
    return _serverName;
}

void ServerEvent::setServerName(const QString &serverName)
{
    _serverName = serverName;
}

int ServerEvent::budget() const
{
    return _budget;
}

void ServerEvent::setBudget(int budget)
{
    _budget = budget;
}

int ServerEvent::currentBudget() const
{
    return _currentBudget;
}

void ServerEvent::setCurrentBudget(int currentBudget)
{
    _currentBudget = currentBudget;
}

int ServerEvent::period() const
{
    return _period;
}

void ServerEvent::setPeriod(int period)
{
    _period = period;
}

int ServerEvent::time() const
{
    return _time;
}

void ServerEvent::setTime(int time)
{
    _time = time;
}

