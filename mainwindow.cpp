#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "guiexception.h"
#include "periodicservervm.hpp"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    taskSet(0),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    createMenu();

    taskSet.close();

    setFixedSize(this->size());
}

void MainWindow::createMenu(){

    scheduleMenu = new QMenu("Schedule");
    traceViewerMenu = new QMenu("TraceViewer");
    aboutMenu = new QMenu("About");

    globalSched = scheduleMenu->addAction("Global");
    partionedSched = scheduleMenu->addAction("Partioned");
    traceVOpen = traceViewerMenu->addAction("Open");
    aboutRTSim = aboutMenu->addAction("RTSim");

    ui->menuBar->addMenu(scheduleMenu);
    ui->menuBar->addMenu(traceViewerMenu);
    ui->menuBar->addMenu(aboutMenu);

    connect(globalSched, SIGNAL(triggered()),this,SLOT(on_globalActionMenu()));
    connect(partionedSched, SIGNAL(triggered()),this,SLOT(on_partionedActionMenu()));
    connect(traceVOpen, SIGNAL(triggered()),this,SLOT(on_traceViewerActionMenu()));
    connect(aboutRTSim, SIGNAL(triggered()),this,SLOT(on_aboutMenu()));
}

void MainWindow::deleteMenu(){
    delete globalSched;
    delete partionedSched;
    delete traceVOpen;

    delete scheduleMenu;
    delete traceViewerMenu;
    delete aboutMenu;
}

void MainWindow::closeEvent(QCloseEvent *evt)
{
    qApp->quit();
}


MainWindow::~MainWindow()
{
    deleteMenu();
    delete ui;
}


void MainWindow::on_globalActionMenu(){

    if(GUI_CONTEXT.getTaskCount() == 0){
        GUI_CONTEXT.showMessageBox("Insert a task set first!");
        return;
    }

    gMRTWin.updateWindow();
    gMRTWin.show();
}

void MainWindow::on_partionedActionMenu(){

    if(GUI_CONTEXT.getTaskCount() == 0){
        GUI_CONTEXT.showMessageBox("Insert a task set first!");
        return;
    }

    partionedModeWin.updateWindow();
    partionedModeWin.show();
}

void MainWindow::on_aboutMenu()
{
    GUI_CONTEXT.showMessageBox("Retis Lab RTSIM \r\nMultiprocessor GUI \r\nSupport for Partioned scheduling \r\nCasini Daniel, 2015");
}

void MainWindow::on_taskSetBtn_clicked()
{
    taskSet.show();
}

void MainWindow::on_traceViewerActionMenu()
{
    QString pathname;
    pathname = FileDialogManager::getInstance().openJSONLoadFileDialog();

    if(!pathname.isEmpty()){
        ScrollScheduleWindow *scheduleWin;
        try{
            scheduleWin = new ScrollScheduleWindow(pathname);
            scheduleWin->show();
        }
        catch (NotValidTraceJSONFormatException &e) {
            QMessageBox *msgBox = new QMessageBox();
            msgBox->setText(e.what());
            msgBox->exec();
            return;
        }
    }
}

void MainWindow::on_CPUButton_clicked()
{
    cpuDialog.show();
}

