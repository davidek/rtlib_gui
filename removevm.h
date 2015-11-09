#ifndef REMOVEVM_H
#define REMOVEVM_H

#include <QDialog>

class TaskSet;

namespace Ui {
class RemoveVM;
}

/**
    QT Dialog that allows to select a VM to remove

    @author Casini Daniel
*/
class RemoveVM : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveVM(QWidget *parent = 0);
    ~RemoveVM();

    /**
     * @brief setTaskSet
     * @param value Task Set window pointer
     */
    void setTaskSet(TaskSet *value);

    /**
     * @brief   loadVMList
     *          loads the VM names in the remove combo box
     */
    void loadVMList();

    /**
     * @brief   loadRemoveList
     *          loads the 'Remove' string and the VM list (except the one selected in the remove
     *          combo box) to show what to do with the tasks assigned to the VM that will
     *          be removed (remove or move to another VM)
     */
    void loadRemoveList();

    /**
     * @brief   updateTasks
     *          Perform the remove operation and updates the task set window
     */
    void updateTasks();

private slots:

    /**
     * @brief   on_buttonBox_accepted
     *          Removes the selected VM and eventually moves its tasks
     */
    void on_buttonBox_accepted();

    /**
     * @brief   on_vmComboBox_currentTextChanged
     *          Current text changed event handler to update the list of VM where is possible
     *          to move the tasks currently scheduled by the VM that will be removed
     */
    void on_vmComboBox_currentTextChanged(const QString &arg1);

private:

    /// GUI Object
    Ui::RemoveVM *ui;

    /// Pointer to the task set window
    TaskSet *taskSet;
};

#endif // REMOVEVM_H
