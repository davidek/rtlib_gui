#ifndef QP_VMWINDOW_H
#define QP_VMWINDOW_H

#include <QDialog>
#include "gui_types.h"

class TaskSet;

namespace Ui {
class QP_VMWindow;
}

/**
    QT Dialog that allows to insert a VM specifing the budget/period parameters

    @author Casini Daniel
*/
class QP_VMWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QP_VMWindow(QWidget *parent = 0);
    ~QP_VMWindow();

    /**
     * @brief   setTaskSet
     * @param   value Task Set window pointer
     */
    void setTaskSet(TaskSet *value);

    /**
     * @brief   updateVMDefaultNameEdit
     *          Sets a default name for the new VM, based upon the number of inserted VM
     */
    void updateVMDefaultNameEdit();

    void setEditWindow(bool value);

    void setData(QString vmName);
private slots:

    /**
     * @brief   on_buttonBox_accepted
     *          Inserts the VM (button handler)
     */
    void on_buttonBox_accepted();

private:

    /// GUI Object
    Ui::QP_VMWindow *ui;

    /// Parameters of the VM to be inserted
    VMData serverData;

    /// Pointer to the task set window
    TaskSet *taskSet;

    bool editWindow;

    /**
     * @brief   extractServerData
     *          Validates the text box data
     */
    void extractServerData();

};

#endif // QP_VMWINDOW_H
