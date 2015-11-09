#ifndef SERVERBUDGETGUIOBJ_H
#define SERVERBUDGETGUIOBJ_H

#include <QString>


/**
    Represents the the server budget in an instant of time

    @author Casini Daniel
*/
class ServerBudgetGUIObj
{
public:

    ServerBudgetGUIObj();

    /**
     * @brief ServerBudgetGUIObj
     * @param time
     * @param budget    budget at the given time
     */
    ServerBudgetGUIObj(int time, int budget);

    unsigned int currentBudget() const;

    void setCurrentBudget(unsigned int currentBudget);

    unsigned int time() const;
    void setTime(unsigned int time);

    QString getName() const;

    /**
     * @brief setName
     * @param sets the server name
     */
    void setName(const QString &value);

private:

    /// Time instant in which the budget is equal to _currentBudget
    unsigned int _time;

    /// Current budget at the given time
    unsigned int _currentBudget;

    /// Name of the server that owns the budget
    QString name;
};

#endif // SERVERBUDGETGUIOBJ_H
