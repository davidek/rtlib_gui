#ifndef SELECTTASKWINDOW_H
#define SELECTTASKWINDOW_H

#include <QDialog>
#include "inserttask.h"

namespace Ui {
class SelectTaskWindow;
}

class TaskSet;

class SelectTaskWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTaskWindow(QWidget *parent = 0);
    ~SelectTaskWindow();

    void setTaskSet(TaskSet *value);

    void loadTaskList();

private slots:

    void on_buttonBox_accepted();
private:
    Ui::SelectTaskWindow *ui;
    InsertTask modifyTask;
    TaskSet *taskSet;
};

#endif // SELECTTASKWINDOW_H
