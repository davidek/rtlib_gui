#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "schedule.h"
#include "taskset.h"
#include "globalmrtwindow.h"
#include "guicontext.h"
#include "taskallocationmodewindow.h"
#include <QPainter>
#include <QColor>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <string>
#include <QDesktopWidget>
#include "cpudialog.h"
#include "globalmrtwindow.h"
#include <mrtkernel.hpp>
#include "scrollschedulewindow.h"
#include "filedialogmanager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    /**
     * @brief   on_taskSetBtn_clicked
     *          Opens the task set window
     */
    void on_taskSetBtn_clicked();

    /**
     * @brief   on_traceViewerActionMenu
     *          Opens a window manager that allows to choose a trace json file to
     *          visualize a RTSIM schedule
     */
    void on_traceViewerActionMenu();

    /**
     * @brief   on_CPUButton_clicked
     *          Opens a dialog to specify the CPUs
     */
    void on_CPUButton_clicked();

    /**
     * @brief   on_globalActionMenu
     *          Opens the MultiProcessor Global Scheduling window
     */
    void on_globalActionMenu();

    /**
     * @brief   on_partionedActionMenu
     *          Opens the MultiProcessor Partioned Scheduling window
     */
    void on_partionedActionMenu();

    void on_aboutMenu();


private:
    /// GUI Object
    Ui::MainWindow *ui;

    /// Task set window
    TaskSet taskSet;

    /// Global Scheduling window
    GlobalMRTWindow gMRTWin;

    /// Partioned Scheduling allocation mode window
    TaskAllocationModeWindow partionedModeWin;

    /// CPU dialog
    CPUDialog cpuDialog;

    /// Schedule menu
    QMenu *scheduleMenu;

    /// TraceViewer menu
    QMenu *traceViewerMenu;

    /// About menu
    QMenu *aboutMenu;

    /// Global Scheduling action, in the Schedule menu
    QAction *globalSched;

    /// Partioned Scheduling action, in the Schedule menu
    QAction *partionedSched;

    /// Open JSON trace file action, in the TraceViewer menu
    QAction *traceVOpen;

    /// About action in the about menu
    QAction *aboutRTSim;

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

protected:
    void  closeEvent(QCloseEvent* evt);
};

#endif // MAINWINDOW_H
