#include "scrollschedulewindow.h"

ScrollScheduleWindow::ScrollScheduleWindow(QString pathname) : scheduleWindow(pathname)
{
    scrollArea.setWidget(&scheduleWindow);
    scrollArea.resize(scheduleWindow.getWidth(), scheduleWindow.getHeight());
}

void ScrollScheduleWindow::show(){

    QRect rec = QApplication::desktop()->screenGeometry();

    unsigned int    desktopHeight = rec.height();
    unsigned int    desktopWidth = rec.width();

    if(scheduleWindow.getWidth() > desktopWidth ||
       scheduleWindow.getHeight() > desktopHeight)
            scrollArea.showMaximized();
    else
            scrollArea.show();
}

ScrollScheduleWindow::~ScrollScheduleWindow(){
}
