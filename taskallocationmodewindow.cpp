#include "taskallocationmodewindow.h"
#include "ui_taskallocationmodewindow.h"

#include "taskallocationwindow.h"
#include "guiexception.h"

#include "scrollschedulewindow.h"
using namespace RTSim;


TaskAllocationModeWindow::TaskAllocationModeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskAllocationModeWindow)
{
    ui->setupUi(this);

    updateWindow();

    setFixedSize(this->size());
}

void TaskAllocationModeWindow::updateWindow(){
    ui->nCPUEdit->setText(QString::number(GUI_CONTEXT.getNCPU()));

    unsigned int time = GUI_CONTEXT.getHyperPeriod();
    ui->simulTimeEdit->setText(QString::number(time));
}

TaskAllocationModeWindow::~TaskAllocationModeWindow()
{
    delete ui;
}



void TaskAllocationModeWindow::on_modeCbox_currentIndexChanged(int index)
{
    allocationModes mode = (allocationModes) index;
    switch(mode){
        case AUTOMATIC: ui->next_run_Button->setText("Run");
                        ui->schedulingCBox->setEnabled(true);
                        ui->allocationCBox->setEnabled(true);
                        ui->nCPUEdit->setEnabled(true);
                        ui->simulTimeEdit->setEnabled(true);
                        break;
        case MANUAL:    ui->next_run_Button->setText("Next");
                        ui->schedulingCBox->setEnabled(false);
                        ui->allocationCBox->setEnabled(false);
                        ui->nCPUEdit->setEnabled(false);
                        ui->simulTimeEdit->setEnabled(false);
    }
}

schedulerTypes TaskAllocationModeWindow::getSchedulerFactoryType(){
    return (schedulerTypes) ui->schedulingCBox->currentIndex();
}

allocationStrategies TaskAllocationModeWindow::getAllocationStrategy(){
    return (allocationStrategies) ui->allocationCBox->currentIndex();
}

void TaskAllocationModeWindow::extractEditFieldData(unsigned int &nCPU, int &simulTime){

    bool isInteger, isInteger2;

    nCPU = ui->nCPUEdit->text().toUInt(&isInteger);
    simulTime = ui->simulTimeEdit->text().toInt(&isInteger2);

    if( !isInteger || !isInteger2 ||
        nCPU < 0  ||  simulTime < 0){
            throw InputDataFormatException("Not valid data format");
    }

}

void TaskAllocationModeWindow::runAutomatic(){

    unsigned int nCPU;
    int simulTime;

    try{
        extractEditFieldData(nCPU, simulTime);
    }catch(InputDataFormatException &e){
        GUI_CONTEXT.showMessageBox(e.what());
        return;
    }

    // Sets the data structures needed for the simulation
    simulator.setNCPU(nCPU);
    simulator.setSimulTime(simulTime);
    simulator.setSchedType(getSchedulerFactoryType());
    simulator.setAllocationStrategyType(getAllocationStrategy());

    simulator.simulate();
}

void TaskAllocationModeWindow::on_next_run_Button_clicked()
{
    allocationModes mode = (allocationModes) ui->modeCbox->currentIndex();
    switch(mode){
        case AUTOMATIC: runAutomatic();
                        break;
        case MANUAL:    allocationWin.updateWindow();
                        allocationWin.show();
                        break;
    }
}
