#ifndef GLOBALMRTWINDOW_H
#define GLOBALMRTWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include "taskset.h"
#include "schedule.h"
#include "rttask.hpp"
#include "task.hpp"

#include "globalmpsimexecutor.h"
#include <QDesktopWidget>
#include <QMessageBox>


namespace Ui {
class GlobalMRTWindow;
}

/**
    QTWidget used to display the windows that allows to run a global multiprocessor
    real time simulation

    @see GlobalMPSIMExecutor

    @author Casini Daniel
*/
class GlobalMRTWindow : public QWidget
{
    Q_OBJECT

public:

    explicit GlobalMRTWindow(QWidget *parent = 0);

    ~GlobalMRTWindow();

    /**
     * @brief   updateWindow
     *          Updates all the elements of the window
     */
    void updateWindow();

private slots:

    /**
     * @brief   on_runButton_clicked
     *          Runs the simulation (button handler)
     */
    void on_runButton_clicked();

private:

    /// GUI Object
    Ui::GlobalMRTWindow *ui;

    /// Simulation executor object
    GlobalMPSIMExecutor simulator;

    /**
     * @brief   extractSimTimeEditFieldData
     *          Private function that extracts the simulation time from its text field and
     *          check whether it is a valid positive integer
     *
     * @return  maximum simulation time
     */
    int extractSimTimeEditFieldData();


    /**
     * @brief   getSchedulerType
     * @return  an enumerate that represents the selected scheduler type (EDF, RM, ...)
     */
    schedulerTypes getSchedulerType();
};

#endif // GLOBALMRTWINDOW_H
