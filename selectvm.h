#ifndef SELECTVM_H
#define SELECTVM_H

#include <QDialog>
#include "qp_vmwindow.h"

namespace Ui {
class SelectVM;
}

class TaskSet;

class SelectVMWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SelectVMWindow(QWidget *parent = 0);
    ~SelectVMWindow();

    void setTaskSet(TaskSet *value);

    void loadVMList();


private slots:

    void on_buttonBox_accepted();

private:
    Ui::SelectVM *ui;
    QP_VMWindow modifyVM;
    TaskSet *taskSet;
};

#endif // SELECTVM_H
