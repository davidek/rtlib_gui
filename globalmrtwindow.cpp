#include "globalmrtwindow.h"
#include "ui_globalmrtwindow.h"

#include "guiexception.h"
#include "scrollschedulewindow.h"

#include "gui_types.h"

using namespace RTSim;

GlobalMRTWindow::GlobalMRTWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GlobalMRTWindow)
{
    ui->setupUi(this);

    updateWindow();
}

GlobalMRTWindow::~GlobalMRTWindow()
{
    delete ui;
}

void GlobalMRTWindow::updateWindow()
{
    unsigned int time = GUI_CONTEXT.getHyperPeriod();
    ui->simulTimeEdit->setText(QString::number(time));
}

int GlobalMRTWindow::extractSimTimeEditFieldData(){

    bool    isInteger;
    int     simulTime = ui->simulTimeEdit->text().toInt(&isInteger);

    if( !isInteger || simulTime < 0){
        throw InputDataFormatException("Not valid data format");
    }

    return simulTime;
}

schedulerTypes GlobalMRTWindow::getSchedulerType(){
    QComboBox *box = ui->schedulerBox;
    return (schedulerTypes) box->currentIndex();
}



void GlobalMRTWindow::on_runButton_clicked()
{
    simulator.setNCPU(GUI_CONTEXT.getNCPU());
    simulator.setSimulTime(extractSimTimeEditFieldData());
    simulator.setSchedType(getSchedulerType());

    simulator.simulate();
}
