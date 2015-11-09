#ifndef TASKSET_H
#define TASKSET_H

#include <QWidget>
#include <QTableWidget>
#include <map>
#include <list>
#include "rttask.hpp"
#include "guicontext.h"
#include "inserttask.h"
#include "tasksetloader.h"
#include "tasksetwriter.h"
#include <QHeaderView>
#include <iostream>
#include <string>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

#include "removetask.h"
#include "removevm.h"


#include "insertvmmode.h"
#include "selecttaskwindow.h"

#include "selectvm.h"


using namespace RTSim;

namespace Ui {
class TaskSet;
}


/**
    QTWidget that represent a TaskSet windows that shows tasks and VMs, and allows to add, remove and
    erase them.
    It is also possibile to save/load the task set to/from a JSON file

    @author Casini Daniel
*/
class TaskSet : public QWidget
{
    Q_OBJECT

public:

    TaskSet(QWidget *parent);

    /**
     * @brief   addTask2Table
     *          Adds a task to the Task Table
     * @param   name    task name
     * @param   phase   task phase
     * @param   ci      task computation time
     * @param   ti      task period
     * @param   di      task deadline
     * @param   kernel  task kernel (a VM name or 'MainKernel')
     */
    void addTask2Table(QString name, int phase, int ci, int ti, int di, QString kernel);

    /**
     * @brief   addVM2Table
     *          Adds a VM to the VM Table
     * @param   name    VM name
     * @param   budget  VM budget
     * @param   period  VM period
     */
    void addVM2Table(QString name, int budget, int period);

    /**
     *  @brief  updateTaskTableContent
     *          Updates the task table with the tasks(data) currently present in the context class
     */
    void updateTaskTableContent();

    /**
     *  @brief  updateTaskTableContent
     *          Updates the task table with the tasks(data) currently present in the context class
     */
    void updateVMTableContent();
    ~TaskSet();

private slots:

    /**
     * @brief   on_addVM
     *          Opens the insertVM window
     */
    void on_addVM();

    /**
     * @brief   on_addTask
     *          Opens the insertTask window
     */
    void on_addTask();

    /**
     * @brief   on_readFile
     *          Allows to select the JSON file path and reads it
     */
    void on_readFile();

    /**
     * @brief   on_writeFile
     *          Allows to select the JSON file path and writes it
     */
    void on_writeFile();

    /**
     * @brief   on_removeTask
     *          Opens the remove task window
     */
    void on_removeTask();

    /**
     * @brief   on_editTask
     *          Opens the edit task window
     */
    void on_editTask();

    /**
     * @brief   on_eraseTasks
     *          Erases all the tasks
     */
    void on_eraseTasks();

    /**
     * @brief   on_removeVM
     *          Opens the remove VM window
     */
    void on_removeVM();

    /**
     * @brief   on_editVM
     *          Opens the edit VM window
     */
    void on_editVM();

    /**
     * @brief   on_eraseVM
     *          Erases all the VMs
     */
    void on_eraseVM();

    /**
     * @brief   on_okButton_clicked
     *          Closes this window
     */
    void on_okButton_clicked();


private:

    ///GUI Object
    Ui::TaskSet *ui;

    /// Current row in the task table
    unsigned int    currentRowTaskTable;

    /// Current row in the VM table
    unsigned int    currentRowVMTable;

    /// Remove Task Window
    RemoveTask      removeTaskWindow;

    /// To Modify Task Window
    SelectTaskWindow    modifyTaskWindow;

    /// To Modify Task Window
    SelectVMWindow    modifyVMWindow;

    /// Remove VM Window
    RemoveVM        removeVMWindow;

    /// Insert VM Window
    InsertVMMode    insertVMWindow;

    /// Insert Task Window
    InsertTask      insertTaskWindow;

    /// Menu bar
    QMenuBar    *menuBar;

    /// File menu
    QMenu       *fileMenu;

    /// Task menu
    QMenu       *taskMenu;

    /// VM menu
    QMenu       *vmMenu;

    /// Read action (JSON File), in the file menu
    QAction     *read;

    /// Write action (JSON File), in the file menu
    QAction     *write;

    /// Add task action, in the task menu
    QAction     *addTask;

    /// Remove task action, in the task menu
    QAction     *removeTask;

    /// Edit task action, in the task menu
    QAction     *editTask;

    /// Erase task action, in the task menu
    QAction     *eraseTasks;

    /// Add VM action, in the VM menu
    QAction     *addVM;

    /// Edit VM action, in the VM menu
    QAction     *editVM;

    /// Remove VM action, in the VM menu
    QAction     *removeVM;

    /// Erase VM action, in the VM menu
    QAction     *eraseVM;

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

    /**
     * @brief   addElement
     *          Adds an item to the specified table
     * @param   table
     * @param   text    cell content
     * @param   row     row index
     * @param   col     column index
     */
    void addElement(QTableWidget *table, QString text, unsigned int row, unsigned int col);

    /**
     * @brief   confirmEraseVMs
     *          Shows a message box to confirm the VM cancellation
     */
    void confirmEraseVMs();
};

#endif // TASKSET_H
