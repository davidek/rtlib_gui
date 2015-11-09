#ifndef ERASETASK_H
#define ERASETASK_H

#include <QDialog>
#include <QVariant>
#include "guicontext.h"
#include "rttask.hpp"


class TaskSet;

namespace Ui {
class RemoveTask;
}

/**
    QT Dialog that allows to select a task to remove

    @author Casini Daniel
*/
class RemoveTask : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveTask(QWidget *parent = 0);
    ~RemoveTask();

    /**
     * @brief   setTaskSet
     * @param   value Task Set window pointer
     */
    void setTaskSet(TaskSet *value);

    /**
     * @brief   loadVMList
     *          loads the task names in the remove combo box
     */
    void loadTaskList();

private slots:
    /**
     * @brief   on_buttonBox_accepted
     *          Removes the selected task
     */
    void on_buttonBox_accepted();

private:
    /// GUI Object
    Ui::RemoveTask *ui;

    /// Pointer to the task set window
    TaskSet *taskSet;
};

#endif // ERASETASK_H
