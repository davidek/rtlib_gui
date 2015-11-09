#ifndef TASKALLOCATIONVIEWER_H
#define TASKALLOCATIONVIEWER_H

#include <QWidget>
#include <QTableWidget>

#include <partionedmrtkernel.hpp>

using namespace RTSim;

namespace Ui {
class TaskAllocationViewer;
}

/**
    QTWidget that shows the automatic task allocation

    @see AbsTaskAllocation, PartionedMRTKernel

    @author Casini Daniel
*/
class TaskAllocationViewer : public QWidget
{
    Q_OBJECT

public:

    explicit TaskAllocationViewer(QWidget *parent = 0);
    ~TaskAllocationViewer();

    /**
     * @brief   updateWindow
     *          Updates the window content
     *
     * @param   allocationStatusMap   cpu index - task name correspondence
     * @param   allocatedTasks        list of the allocated task (task not assigned to a VM and VMs) in the order
     *                                in which the task allocator has processed them
     */
    void updateWindow(const multimap<unsigned int, string> &allocationStatusMap, const list<string> &allocatedTasks);

private slots:

    /**
     * @brief   on_okButton_clicked
     *          Closes the window
     */
    void on_okButton_clicked();

private:

    /// GUI Object
    Ui::TaskAllocationViewer *ui;

    /// Current row in task table
    unsigned int _currentRowTaskTable;

    /// Current row in task table
    unsigned int _currentRowCPUTable;

    /// Task name - utilization correspondence
    map<QString, double>            _utilizationMap;

    /// cpu index - assigned task names correspondence
    multimap<unsigned int, string>  _allocationStatusMap;

    /// list of the allocated task (task not assigned to a VM and VMs) in the order
    /// in which the task allocator has processed them
    list<string>                    _allocatedTasks;

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
     * @brief   eraseTaskTable
     *          Erases the CPU table
     */
    void eraseTaskTable();

    /**
     * @brief   eraseCPUTable
     *          Erases the CPU table
     */
    void eraseCPUTable();

    /**
     * @brief   cleanWindow
     *          Cleans the data structures and the window content
     */
    void cleanWindow();

    /**
     * @brief   fillCPUTable
     *          Inserts data in the CPU table
     */
    void fillCPUTable();

    /**
     * @brief   fillTaskTable
     *          Inserts data in the Task table
     */
    void fillTaskTable();
};

#endif // TASKALLOCATIONVIEWER_H
