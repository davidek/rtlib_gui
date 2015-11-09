#include "taskallocationviewer.h"
#include "ui_taskallocationviewer.h"

#include "guicontext.h"

using namespace RTSim;

TaskAllocationViewer::TaskAllocationViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskAllocationViewer)
{
    ui->setupUi(this);

    _currentRowTaskTable = 0;
    ui->taskTable->setRowCount(0);
    ui->taskTable->setColumnCount(2);
    QStringList m_taskTableHeader;
    m_taskTableHeader<<"Name"<<"Task Utilization";
    ui->taskTable->setHorizontalHeaderLabels(m_taskTableHeader);

    _currentRowCPUTable = 0;
    ui->cpuTable->setRowCount(0);
    ui->cpuTable->setColumnCount(4);
    QStringList m_cpuTableHeader;
    m_cpuTableHeader<<"CPU #"<<"Task"<<"Task Util."<<"Cumulative Util.";
    ui->cpuTable->setHorizontalHeaderLabels(m_cpuTableHeader);
}

TaskAllocationViewer::~TaskAllocationViewer()
{
    delete ui;
}

void TaskAllocationViewer::updateWindow(const multimap<unsigned int, string> &allocationStatusMap,
                                        const list<string> &allocatedTasks)
{
    cleanWindow();

    _allocationStatusMap = allocationStatusMap;
    _allocatedTasks = allocatedTasks;

    fillTaskTable();
    fillCPUTable();
}

void TaskAllocationViewer::addElement(QTableWidget *table, QString text, unsigned int row, unsigned int col){
    QTableWidgetItem* newItem = new QTableWidgetItem();
    newItem->setText(text);
    table->setItem(row, col, newItem);
}

void TaskAllocationViewer::eraseTaskTable()
{
    ui->taskTable->setRowCount(0);
    _currentRowTaskTable = 0;
}

void TaskAllocationViewer::eraseCPUTable()
{
    ui->cpuTable->setRowCount(0);
    _currentRowCPUTable = 0;
}

void TaskAllocationViewer::cleanWindow()
{
    eraseTaskTable();
    eraseCPUTable();

    _utilizationMap.clear();
}

void TaskAllocationViewer::fillTaskTable()
{
    string  name;
    QString qName;

    PeriodicTaskData    *taskData;
    VMData              *vmData;

    double utilization;

    // Examines all the task in the order in which the allocator has processed them
    for(list<string>::iterator it=_allocatedTasks.begin(); it!=_allocatedTasks.end(); it++){

        name = *it;
        qName = QString::fromStdString(name);

        // Computes utilization
        if(GUI_CONTEXT.getTasksData().isPresent(qName)){

            taskData = GUI_CONTEXT.getTaskData(qName);
            utilization = (double)taskData->ci() / (double)taskData->ti();
        }
        else{

            vmData = GUI_CONTEXT.getVMData(qName);
            utilization = (double)vmData->budget() / (double)vmData->period();
        }

        // Stores the utilization in a data structure
        _utilizationMap[qName] = utilization;

        ui->taskTable->setRowCount(_currentRowTaskTable + 1);

        addElement(ui->taskTable, qName, _currentRowTaskTable, 0);
        addElement(ui->taskTable, QString::number(utilization), _currentRowTaskTable, 1);

        _currentRowTaskTable++;
    }

    ui->taskTable->update();
    ui->taskTable->resizeColumnsToContents();
}

void TaskAllocationViewer::fillCPUTable()
{
    bool first = true;
    unsigned int oldCPUIndex, CPUIndex;

    double utilization, cumulativeUtil;

    string  name;
    QString cpuStr;

    multimap<unsigned int, string>::iterator allocationIter;

    for (allocationIter=_allocationStatusMap.begin(); allocationIter!=_allocationStatusMap.end(); allocationIter++){

        CPUIndex = allocationIter->first;
        cpuStr = "CPU " + QString::number(CPUIndex);

        ui->cpuTable->setRowCount(_currentRowCPUTable + 1);

        if(first){

            oldCPUIndex = CPUIndex;
            first = false;
            cumulativeUtil = 0;
            addElement(ui->cpuTable, cpuStr, _currentRowCPUTable, 0);

        }
        else if (oldCPUIndex != CPUIndex){

            oldCPUIndex = CPUIndex;
            cumulativeUtil = 0;
            addElement(ui->cpuTable, cpuStr, _currentRowCPUTable, 0);

        }

        name = allocationIter->second;
        utilization = _utilizationMap[QString::fromStdString(name)];

        cumulativeUtil += utilization;

        addElement(ui->cpuTable, QString::fromStdString(name), _currentRowCPUTable, 1);
        addElement(ui->cpuTable, QString::number(utilization), _currentRowCPUTable, 2);
        addElement(ui->cpuTable, QString::number(cumulativeUtil), _currentRowCPUTable, 3);

        _currentRowCPUTable++;
    }

    ui->cpuTable->update();
    ui->cpuTable->resizeColumnsToContents();
}


void TaskAllocationViewer::on_okButton_clicked()
{
    this->close();
}
