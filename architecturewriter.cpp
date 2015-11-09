#include "architecturewriter.h"


ArchitectureWriter::ArchitectureWriter(QString filename) : _filename(filename)
{

}



void ArchitectureWriter::writeJSON( map<QString, unsigned int> taskCPUMap,
                                    map<unsigned int, QString> cpuSchedulerMap)
{
    QJsonArray taskCPUAssociationArray, cpuSchedulerArray;

    int         cpu;
    QString     taskName;
    QJsonObject taskCPUObj, cpuSchedObj;

    for (map<QString, unsigned int>::iterator  it=taskCPUMap.begin(); it != taskCPUMap.end(); it++){
        taskName = it->first;
        cpu = it->second;
        taskCPUObj["task_name"] = taskName;
        taskCPUObj["cpu_index"] = cpu;
        taskCPUAssociationArray.append(taskCPUObj);
    }

    QJsonObject obj;
    obj["task_cpu"] = taskCPUAssociationArray;
    QString scheduler;
    for (map<unsigned int, QString>::iterator it =cpuSchedulerMap.begin();
         it != cpuSchedulerMap.end(); it++){
        cpu = it->first;
        scheduler = it->second;
        cpuSchedObj["cpu_index"] = cpu;
        cpuSchedObj["scheduler_type"] = scheduler;
        cpuSchedulerArray.append(cpuSchedObj);
    }

    obj["cpu_sched"] = cpuSchedulerArray;

    QFile outputFile(_filename);
    outputFile.open(QIODevice::WriteOnly);

    /* Point a QTextStream object at the file */
    QTextStream outStream(&outputFile);

    /* Write the line to the file */
    outStream << QJsonDocument(obj).toJson(QJsonDocument::Compact);

    /* Close the file */
    outputFile.close();
}
