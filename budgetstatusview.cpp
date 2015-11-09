#include "budgetstatusview.h"
#include "ui_budgetstatusview.h"

BudgetStatusView::BudgetStatusView(QWidget *parent, QString serverName, unsigned int y, unsigned int n_VertLines, unsigned int maxTime, list<ServerBudgetGUIObj*> budgetList, int serverNameLen) :
    TraceView(0, serverName, y, n_VertLines, maxTime, BUDGET_TEXTY_OFFSET), _budgetList(budgetList),
    ui(new Ui::BudgetStatusView)
{
    ui->setupUi(this);
}

BudgetStatusView::~BudgetStatusView()
{
    delete ui;
}

void BudgetStatusView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(QPen(Qt::black, 2));

    ServerBudgetGUIObj *temp;

    bool    first = true;
    int     prevBudget, prevTime, budget, time;

    for(list<ServerBudgetGUIObj*>::iterator budgetIter = _budgetList.begin();
        budgetIter != _budgetList.end(); budgetIter++)
    {
        temp = *budgetIter;
        if(first){
            prevBudget = temp->currentBudget();
            prevTime = 0;
            first = false;
        }
        budget = temp->currentBudget();
        time = temp->time();

        if(prevBudget < budget){//prevBudget < budget, replenishment event

            p.drawLine(lineXPosStart + prevTime*tickLength, lineYPos - vertLineHeight*prevBudget,
                       lineXPosStart + time*tickLength , lineYPos- vertLineHeight*prevBudget);
            p.drawLine(lineXPosStart + time*tickLength, lineYPos - vertLineHeight*prevBudget,
                       lineXPosStart + time*tickLength , lineYPos- vertLineHeight*budget);
        }
        else
            p.drawLine(lineXPosStart + prevTime*tickLength, lineYPos - vertLineHeight*prevBudget,
                       lineXPosStart + time*tickLength , lineYPos- vertLineHeight*budget);

        prevBudget = budget;
        prevTime = time;
    }

    drawStructure("", nVertLines);
}
