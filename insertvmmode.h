#ifndef INSERTVMMODE_H
#define INSERTVMMODE_H

#include <QWidget>
#include "qp_vmwindow.h"

class TaskSet;

namespace Ui {
class insertVMMode;
}

/**
    QTWidget used to select the mode for the VM insertion.
    Two possibible modes can be:
        - Q-P (Budget and period) mode, implemented
        - Alpha-Delta (bandwidth and max delay) (to do)

    @see QP_VMWindow

    @author Casini Daniel
*/
class InsertVMMode : public QWidget
{
    Q_OBJECT

public:
    explicit InsertVMMode(QWidget *parent = 0);
    ~InsertVMMode();

    /**
     * @brief   setTaskSet
     *          Set the task set window pointer, that has to be updated after the VM insertion
     * @param   value         task set
     */
    void setTaskSet(TaskSet *value);

    void setEditWindow(bool value);

private slots:

    /**
     * @brief   on_next_run_Button_clicked
     *          Opens the window related to the selected insertion mode
     */
    void on_next_run_Button_clicked();

private:

    /// GUI Object
    Ui::insertVMMode *ui;

    /// Q-P insertion mode window object
    QP_VMWindow qpWindow;

    /// Task set window pointer
    TaskSet *taskSet;

    bool editWindow;
};

#endif // INSERTVMMODE_H
