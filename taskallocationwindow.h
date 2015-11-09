#ifndef TASKALLOCATIONWINDOW_H
#define TASKALLOCATIONWINDOW_H

#include <QWidget>
#include <QComboBox>
#include <QDesktopWidget>
#include <QScrollArea>
#include "task.hpp"
#include "rttask.hpp"
#include "cpu.hpp"
#include "schedule.h"

#include <map>

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>

#include "partionedmanualmpsimexecutor.h"

#include <string>

#include "guicontext.h"
#include "architecturewriter.h"
#include "architectureloader.h"

#include "gui_types.h"

using namespace std;
using namespace RTSim;

namespace Ui {
class taskAllocationWindow;
}

/**
    QTWidget used to display the windows that allows to select the task-cpu and cpu-scheduler
    correspondences for Partioned MultiProcessor Scheduling and to run the simulation

    @see PartionedAutoMPSIMExecutor

    @author Casini Daniel
*/
class TaskAllocationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TaskAllocationWindow(QWidget *parent = 0);
    ~TaskAllocationWindow();

    /**
     * @brief   fillTaskTable
     *          Fill the Task-CPU correspondence table using the data retrieved from the context class
     */
    void fillTaskTable();

    /**
     * @brief   fillTaskTable
     *          Fill the CPU-Scheduler correspondence table using the data retrieved from the context class
     */
    void fillCPUTable();

    /**
     * @brief addTask2Table Adds a task to the Task-CPU Table
     * @param name  Task name
     * @param row   Table row
     */
    void addTask2Table(QString name, unsigned int row);

    /**
     * @brief addCPU2Table Adds a CPU to the Task-CPU Table
     * @param index CPU index
     */
    void addCPU2Table(unsigned int index);

    /**
     * @brief createTaskCPUCBox
     * @return Combo box with the list of CPUs as possible selections
     */
    QComboBox *createTaskCPUCBox();

    /**
     * @brief createCPUSchedulerCBox
     * @return Combo box with the list of schedulers as possible selections
     */
    QComboBox *createCPUSchedulerCBox();

    /**
     * @brief updateCPUTable    updates the CPU-Scheduler table using the given CPU-Scheduler
     *                          correspondence
     * @param cpuSchedulerMap
     */
    void updateCPUTable(map<unsigned int, QString> cpuSchedulerMap);

    /**
     * @brief updateTaskTable   updates the Task-CPU table using the given CPU-Scheduler
     *                          correspondence
     * @param taskCPUMap
     */
    void updateTaskTable(map<QString, unsigned int> taskCPUMap);


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

    /**
     * @brief   on_writeFile
     *          Writes a JSON file with the current Task-CPU and CPU-Scheduler correspondence
     */
    void on_writeFile();

    /**
     * @brief   on_readFile
     *          Reads a JSON file with a Task-CPU and CPU-Scheduler correspondence
     */
    void on_readFile();

private:

    /// GUI Object
    Ui::taskAllocationWindow *ui;

    ///Map that contains the pointers to the combo boxes related to the task-CPU table
    map<QString, QComboBox*> taskBoxMap;

    ///Map that contains the pointers to the combo boxes related to the CPU-scheduler table
    map<unsigned int, QComboBox*> cpuBoxMap;

    /// Partioned Multi Processor (with manual task allocation) simulation executor
    PartionedManualMPSimExecutor simulator;

    void getTaskCPUMap(map<QString, unsigned int> &taskCPUMap);
    void getCPUSchedulerMap(map<unsigned int, QString> &cpuSchedulerMap);

    /**
     * @brief   getScheduler
     *          Returns the scheduler type for a given CPU index, extracting the data from the table
     * @param   cpuIndex
     * @return  Scheduler Type
     */
    schedulerTypes getScheduler(unsigned int cpuIndex);

    /**
     * @brief   getTaskCPU
     *          Returns the cpu index for a given task name, extracting the data from the table
     * @param   taskName
     * @return  CPU index
     */
    unsigned int getTaskCPU(QString taskName);

    /**
     * @brief   fillWithTasks
     *          Adds the task that are scheduled by the MainKernel (and not by a VM) to the Task-CPU
     *          table
     * @param   startIndex  Start row index in the Task-cpu table
     */
    void fillWithTasks(unsigned int &startIndex);

    /**
     * @brief   fillWithVMs
     *          Adds the VM to the Task-CPU table
     * @param   startIndex  Start row index in the Task-cpu table
     */
    void fillWithVMs(unsigned int &startIndex);

    /**
     * @brief   eraseTaskTable
     *          Erases the task-CPU table
     */
    void eraseTaskTable();

    /**
     * @brief   eraseTaskTable
     *          Erases the CPU-Scheduler table
     */
    void eraseCPUTable();

    /**
     * @brief   extractEditFieldData
     *          Extract and validates the maximum simulation time from the text edit
     * @param   simulTime   maximum simulation time
     */
    void extractEditFieldData(int &simulTime);

    /**
     * @brief   createSimCPUScheduler
     *          Extracts the CPU-Scheduler correspondences from the table and fills
     *          the data structure passed as a parameter
     * @param   kernelCPUSchedulerMap
     */
    void createSimCPUScheduler(map<unsigned int, schedulerTypes> &kernelCPUSchedulerMap);

    /**
     * @brief   createSimTaskCPU
     *          Extracts the Task-CPU correspondences from the table and fills
     *          the data structure passed as a parameter
     * @param   ernelTaskCPUMap
     */
    void createSimTaskCPU(map<string, unsigned int> &kernelTaskCPUMap);

    /// Menu Bar
    QMenuBar *menuBar;

    /// File Menu
    QMenu *fileMenu;

    /// Read (JSON File) Action in the file menu
    QAction *read;

    /// Write (JSON File) Action in the file menu
    QAction *write;

    /**
     * @brief   createMenu
     *          Creates the menu
     */
    void createMenu();

    /**
     * @brief   deleteMenu
     *          Deletes the menu
     */
    void deleteMenu();

};

#endif // TASKALLOCATIONWINDOW_H
