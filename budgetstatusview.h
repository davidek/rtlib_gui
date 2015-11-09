#ifndef BUDGETSTATUSVIEW_H
#define BUDGETSTATUSVIEW_H

#include "traceview.h"
#include "serverbudgetguiobj.h"
#include <list>

using namespace std;

#define BUDGET_TEXTY_OFFSET     20

namespace Ui {
class BudgetStatusView;
}

/**
    QTWidget used to display the budget status of a periodic server.

    @see TraceView, ServerBudgetGUIObj

    @author Casini Daniel
*/
class BudgetStatusView : public TraceView
{
    Q_OBJECT

public:
    ~BudgetStatusView();

    /**
     * @brief BudgetStatusView
     * @param parent        Parent widget
     * @param serverName    Server Name
     * @param y             Y coordinate of the timeline in the widget reference frame
     * @param maxBudget     Maximum budget of the server
     * @param maxTime       Maximum time, i.e., number of intervals along the x axis
     * @param budgetList    list of budget status object that contains the information to be displayed
     * @param serverNameLen Server name length
     */
    BudgetStatusView(QWidget *parent, QString serverName, unsigned int y, unsigned int maxBudget, unsigned int maxTime, list<ServerBudgetGUIObj*> budgetList, int serverNameLen);

protected:

    /**
     * @brief   paintEvent
     *          Redefinted from QTWidget, paint event
     * @param   event
     */
    void paintEvent(QPaintEvent *event);

private:

    /// GUI Object
    Ui::BudgetStatusView *ui;

    /// Budget status object list
    list<ServerBudgetGUIObj*> _budgetList;
};

#endif // BUDGETSTATUSVIEW_H
