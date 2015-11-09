#ifndef SCROLLSCHEDULEWINDOW_H
#define SCROLLSCHEDULEWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QScrollArea>

#include "schedule.h"


/**
    Scroll window that adds the scrollbar to a schedule window

    @author Casini Daniel
*/
class ScrollScheduleWindow
{
public:

    /**
     * @brief ScrollScheduleWindow
     * @param pathname  pathname of the trace file
     */
    ScrollScheduleWindow(QString pathname);

    ~ScrollScheduleWindow();

    /**
     * @brief show  shows the scroll schedule window
     */
    void show();

private:

    ///QT ScrollArea object
    QScrollArea scrollArea;

    ///Schedule window object
    Schedule scheduleWindow;

};

#endif // SCROLLSCHEDULEWINDOW_H
