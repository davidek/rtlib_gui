#ifndef ARCHITECTURELOADER_H
#define ARCHITECTURELOADER_H
#include<map>
#include <QFile>
#include <QDebug>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <iostream>
#include <algorithm>

#include "jsonloader.h"

using namespace std;

/**
    Class used to load from a JSON File the task-cpu and
    cpu-scheduler type correspondence.
    Inherits JSONLoader

    @see JSONLoader

    @author Casini Daniel
*/
class ArchitectureLoader : public JSONLoader
{
public:

    /// Constructor, needs to know the filename
    ArchitectureLoader(QString filename);

    /**
     * @brief   readJson
     *          Read method that fills the argument with the task-cpu
     *          and cpu-scheduler correspondence
     * @param   taskCPUMap
     * @param   cpuSchedulerMap
     */
    void readJson(map<QString, unsigned int> &taskCPUMap,
                  map<unsigned int, QString> &cpuSchedulerMap);

private:

};

#endif // ARCHITECTURELOADER_H
