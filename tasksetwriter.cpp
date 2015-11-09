#include <QFile>
#include <QDebug>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "guicontext.h"
#include "tasksetwriter.h"

TaskSetWriter::TaskSetWriter(QString filename) : _filename(filename)
{

}

void TaskSetWriter::writeJSON()
{

    QJsonArray taskArray;
    QJsonArray vmArray;

    map<QString, PeriodicTaskData *> tasksData = TASKS_DATA;
    map<QString, PeriodicTaskData *>::iterator taskIter;
    PeriodicTaskData *tempPTask;
    QJsonObject task;
    for (taskIter=tasksData.begin(); taskIter != tasksData.end(); taskIter++){
        tempPTask = taskIter->second;
        task["task_name"] = tempPTask->name();
        task["phase"] = (int)tempPTask->phase();
        task["period"] = (int)tempPTask->ti();
        task["deadline"] = (int)tempPTask->di();
        task["computation_time"] = (int)tempPTask->ci();
        task["kernel"] = tempPTask->kernel();
        taskArray.append(task);
    }

    map<QString, VMData *> vmData = VMS_DATA;
    map<QString, VMData *>::iterator vmIter;

    VMData *tempVM;
    QJsonObject vm;

    for (vmIter=vmData.begin(); vmIter != vmData.end(); vmIter++){
        tempVM = vmIter->second;
        vm["VM_name"] = tempVM->name();
        vm["budget"] = (int)tempVM->budget();
        vm["period"] = (int)tempVM->period();
        vmArray.append(vm);
    }

    QJsonObject obj;

    obj["tasks"] = taskArray;
    obj["VMs"] = vmArray;

    QFile outputFile(_filename);
    outputFile.open(QIODevice::WriteOnly);

    /* Point a QTextStream object at the file */
    QTextStream outStream(&outputFile);

    /* Write the line to the file */
    outStream << QJsonDocument(obj).toJson(QJsonDocument::Compact);

    /* Close the file */
    outputFile.close();
}
