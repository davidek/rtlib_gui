#ifndef CPUDIALOG_H
#define CPUDIALOG_H

#include <QDialog>
#include "guicontext.h"

namespace Ui {
class CPUDialog;
}

/**
    QTDialog that allows to select the number of CPUs in which the simulation is executed.
    This choiche is implemented as a window in order to make easier to extend the CPU insertion,
    allowing to specify all the CPU parameters (power consumption parameters, speed, ...).
    Actually all the used CPUs are intended as CPUs created by the UniformCPUFactory
    (speed = 1, no power consumption parameters)

    @author Casini Daniel
*/
class CPUDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CPUDialog(QWidget *parent = 0);
    ~CPUDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CPUDialog *ui;
};

#endif // CPUDIALOG_H
