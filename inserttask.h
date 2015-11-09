#ifndef INSERTTASK_H
#define INSERTTASK_H

#include <QDialog>
#include <QWidget>
#include "rttask.hpp"

#include "guicontext.h"
#include "gui_types.h"

namespace Ui {
class insertTask;
}

class TaskSet;

/**
    QT Dialog that allows to insert a Task specifing the parameterrs

    @author Casini Daniel
*/
class InsertTask : public QDialog
{
    Q_OBJECT

public:

    InsertTask(QWidget *parent = 0, bool editWindow = false);

    ~InsertTask();

    /**
     * @brief   setTaskSet
     *          Set the task set window pointer, that has to be updated after the Task insertion
     * @param   value         task set
     */
    void setTaskSet(TaskSet *value);

    /**
     * @brief   loadKernels
     *          Load the list of VMs (+ MainKernel option) that can be used as Task Kernel in
     *          the proper combo box list
     */
    void loadKernels();

    void setData(int phase, int ci, int ti, int di, QString kernel);

    void setEditWindow();
    void setData(QString taskName);
private slots:

    /**
     * @brief   on_buttonBox_accepted
     *          Perform the task insertion
     */
    void on_buttonBox_accepted();

private:

    /// GUI Object
    Ui::insertTask *ui;

    /// Parameters of the Periodic Task to be inserted
    PeriodicTaskData taskData;

    /// Task set window pointer
    TaskSet *taskSet;

    bool editWindow;

    /**
     * @brief   extractTaskData
     *          Extract and validates the task parameters inserted in the text edits
     */
    void extractTaskData();
};

#endif // INSERTTASK_H
