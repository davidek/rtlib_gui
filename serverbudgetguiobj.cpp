#include "serverbudgetguiobj.h"

ServerBudgetGUIObj::ServerBudgetGUIObj()
{}

ServerBudgetGUIObj::ServerBudgetGUIObj(int time, int budget) : _time(time), _currentBudget(budget)
{}

unsigned int ServerBudgetGUIObj::currentBudget() const
{
    return _currentBudget;
}

void ServerBudgetGUIObj::setCurrentBudget(unsigned int currentBudget)
{
    _currentBudget = currentBudget;
}

unsigned int ServerBudgetGUIObj::time() const
{
    return _time;
}

void ServerBudgetGUIObj::setTime(unsigned int time)
{
    _time = time;
}

QString ServerBudgetGUIObj::getName() const
{
    return name;
}

void ServerBudgetGUIObj::setName(const QString &value)
{
    name = value;
}

