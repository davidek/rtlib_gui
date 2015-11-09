#include "schedule.h"
#include "ui_schedule.h"

#include "guiexception.h"

using namespace std;

void Schedule::createTaskSchedules(){

    QString name;
    TaskSchedule *t;

    for(list<QString>::iterator taskNameIter = parser->getTaskNames().begin();
        taskNameIter != parser->getTaskNames().end(); taskNameIter++)
    {
        name = *taskNameIter;
        nTasks++;

        t = new TaskSchedule(this , name, 20*arch.nCPU(), arch.nCPU(), arch.maxTime(),
                                          parser->getExecList(name), parser->getTaskSimpleEventsMap(name));
        ui->pageLayout->addWidget(t);
    }

}

void Schedule::createServerBudgetViews(){

    BudgetStatusView    *budgetView;
    ServerData          *serv;

    QString name;

    for(list<QString>::iterator serverNameIter = parser->getServerNames().begin();
        serverNameIter != parser->getServerNames().end(); serverNameIter++){

        name = *serverNameIter;
        nServers++;
        serv = parser->getServerData(name);

        if(serv->budget() > maxBudget)
            maxBudget = serv->budget();

        budgetView = new BudgetStatusView(this , name, 20*(serv->budget() + 1),
                                          (serv->budget() + 1),
                                          arch.maxTime(),
                                          parser->getBudgetStatus(name),
                                          name.length());

        ui->pageLayout->addWidget(budgetView);

    }
}

Schedule::Schedule(QString pathname, QWidget *parent) : QWidget(parent), ui(new Ui::Schedule)
{
    ui->setupUi(this);

    parser = new TraceParser(pathname);

    try{
       parser->readJson();
    }
    catch (NotValidTraceJSONFormatException &e) {
        delete ui;
        throw;
        return;
    }

    arch = parser->getArchParam();

    nTasks = 0;
    nServers = 0;
    maxBudget = 0;

    createTaskSchedules();
    createServerBudgetViews();

    width = 2 * STD_LINEXPOS_START + STD_TICK_LENGTH * arch.maxTime();
    height = (nTasks) * (1.2 * TASKSCH_Y_OFFSET + arch.nCPU() * STD_CPU_HEIGHT) +
             (nServers) * (1.5 * TASKSCH_Y_OFFSET + (maxBudget + 1) * STD_CPU_HEIGHT);

    ui->area->resize(width, height);
    ui->area->setMinimumSize(width, height);

    adjustSize();

}

Schedule::~Schedule()
{
    delete ui;
}


unsigned int Schedule::getHeight() const
{
    return height;
}

void Schedule::setHeight(unsigned int value)
{
    height = value;
}

unsigned int Schedule::getWidth() const
{
    return width;
}

void Schedule::setWidth(unsigned int value)
{
    width = value;
}


