#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <map>
#include <vector>
#include "taskschedule.h"
#include "budgetstatusview.h"
#include "gui_types.h"
#include "traceparser.h"
#include <QPainter>
#include <QColor>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QSize>


#define TASKSCH_Y_OFFSET    80
#define ServerData  VMData

namespace Ui {
class Schedule;
}

/**
    QTWidget that represent a schedule (as a set of task schedule and budget status view, if any)

    @author Casini Daniel
*/
class Schedule : public QWidget
{
    Q_OBJECT

public:
    ~Schedule();

    /**
     * @brief Schedule
     * @param pathname  Pathname of the trace file
     * @param parent    Parent widget pointer
     */
    Schedule(QString pathname, QWidget *parent = 0);

    unsigned int getWidth() const;
    void setWidth(unsigned int value);

    unsigned int getHeight() const;
    void setHeight(unsigned int value);

private:

    /// GUI Object
    Ui::Schedule *ui;

    /// Maximum time in which an event happens
    unsigned int maxTime;

    /// Number of processors in the schedule
    unsigned int nProc;

    /// Schedule window width
    unsigned int width;

    /// Schedule window height
    unsigned int height;

    unsigned int nTasks;
    unsigned int nServers;
    unsigned int maxBudget;

    TraceParser *parser;
    ArchitectureParameter arch;

    void createServerBudgetViews();
    void createTaskSchedules();
};

#endif // SCHEDULE_H
