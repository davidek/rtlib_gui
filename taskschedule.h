#ifndef TASKSCHEDULE_H
#define TASKSCHEDULE_H


#include <list>

#include "traceview.h"

#define     COLORS_NUM              6
#define     STD_TASK_TEXTY_OFFSET   15
#define     STD_CPU_HEIGHT          STD_VERTLINE_HEIGHT

namespace Ui {
class TaskSchedule;
}

/**
    Taks schedule trace view. It represents the scheduling of a task over the available CPUs (y-axis)
    and time (x-axis)

    @see TraceView

    @author Casini Daniel
*/
class TaskSchedule : public TraceView
{
    Q_OBJECT

public:
    /**
     * @brief TaskSchedule
     * @param parent        Parent widget
     * @param taskName      Task name, that is displayed on the left
     * @param y             Y coordinate of the timeline in the widget reference frame
     * @param nProc         Number of processor
     * @param maxTime       Maximum time, i.e., number of intervals along the x axis
     * @param execList      Task execution list, read from traceParser
     * @param simpleEvents  simpleEvent (arrival, deadline miss, ...) - time correspondence
     * @param taskNameLen   Length of the task name
     */
    explicit TaskSchedule(QWidget *parent, QString taskName, unsigned int y, unsigned int nProc, unsigned int maxTime, std::list<ExecutionGUIObject*> execList, std::map<unsigned int, SimpleTaskEvent> simpleEvents, int taskNameLen = 6);

    ~TaskSchedule();

    unsigned int getCpuHeight() const;
    void setCpuHeight(unsigned int value);

    unsigned int getLineXPosStart() const;
    void setLineXPosStart(unsigned int value);

    unsigned int getLineYPos() const;
    void setLineYPos(unsigned int value);

    unsigned int getTickLength() const;
    void setTickLength(unsigned int value);

protected:

    /**
     * @brief   paintEvent
     *          Redefinted from QTWidget, paint event
     * @param   event
     */
    void paintEvent(QPaintEvent *event); // This is re-implemented from QWidget

    /**
     * @brief   drawExecution
     *          Draw an execution rectangle for the given task from tStart to tEnd on the
     *          specified CPU
     * @param   tStart
     * @param   tEnd
     * @param   cpu
     */
    void drawExecution(unsigned int tStart, unsigned int tEnd, unsigned int cpu);

    /**
     * @brief   drawSimpleEvents
     *          Draws the simple events (arrival, deadline miss, ...) specified in the constructor
     */
    void drawSimpleEvents();
private:

    Ui::TaskSchedule *ui;

    /// Task schedule objects instance counter
    static unsigned int instanceCounter;

    /// Static array for the task schedule color
    static QColor taskScheduleColors[COLORS_NUM];

    /// Execution event list
    std::list<ExecutionGUIObject*> _execList;

    /// Time - simple event correspondence
    std::map<unsigned int, SimpleTaskEvent> _simpleEvents;

    /// Task name
    QString taskName;

};

#endif // TASKSCHEDULE_H
