#ifndef TASKALLOCATIONMODEWINDOW_H
#define TASKALLOCATIONMODEWINDOW_H

#include <QWidget>
#include <QScrollArea>


#include "guicontext.h"
#include "QMessageBox"

#include <QDesktopWidget>

#include "gui_types.h"

#include "partionedautompsimexecutor.h"
#include "taskallocationwindow.h"


using namespace RTSim;

namespace Ui {
class taskAllocationModeWindow;
}


/**
    QTWidget used to display the windows that allows to select manual or automatic allocation mode
    for Partioned MultiProcessor Scheduling. It allows also to run a simulation with automatic
    allocation (and to select the task allocation algorithm and some other things)

    @see PartionedAutoMPSIMExecutor

    @author Casini Daniel
*/
class TaskAllocationModeWindow : public QWidget
{
    Q_OBJECT

public:

    explicit TaskAllocationModeWindow(QWidget *parent = 0);

    ~TaskAllocationModeWindow();

    /**
     * @brief   updateWindow
     *          Updates all the elements of the window
     */
    void updateWindow();

private slots:

    /**
     * @brief   on_modeCbox_currentIndexChanged
     *          Enables or disables the text edit field for the automatic allocation depending
     *          on the value of the combo box
     * @param   index
     */
    void on_modeCbox_currentIndexChanged(int index);

    /**
     * @brief   on_next_run_Button_clicked
     *          If the selected allocation mode is automatic, runs the simulation ;
     *          Otherwise open the window for manual allocation
     */
    void on_next_run_Button_clicked();

private:

    /// GUI Object
    Ui::taskAllocationModeWindow *ui;

    /// Manual Task Allocation window
    TaskAllocationWindow allocationWin;

    /**
     * @brief   extractEditFieldData
     *          Exctracts and validates the simulation data inserted in the text edits
     * @param   nCPU          number of available CPUs
     * @param   simulTime     maximum simulation time
     */
    void extractEditFieldData(unsigned int &nCPU, int &simulTime);

    /**
     * @brief   runAutomatic
     *          Runs a Partioned MultiProcessor Simulation with automatic task allocation
     */
    void runAutomatic();

    /// Partioned MultiProcessor Simulation with automatic task allocation executor
    PartionedAutoMPSimExecutor simulator;

    /**
     * @brief   getSchedulerFactoryType
     * @return  the scheduler factory type
     */
    schedulerTypes getSchedulerFactoryType();

    /**
     * @brief   getAllocationStrategy
     * @return  the task allocation strategy
     */
    allocationStrategies getAllocationStrategy();
};

#endif // TASKALLOCATIONMODEWINDOW_H
