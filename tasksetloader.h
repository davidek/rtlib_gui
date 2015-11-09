#ifndef TASKSETLOADER_H
#define TASKSETLOADER_H

#include "guicontext.h"
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

/**
    Class used to load from a JSON File the task-set parameters (computation time, period, ...)
    Inherits JSONLoader

    @see JSONLoader

    @author Casini Daniel
*/
class TaskSetLoader : public JSONLoader
{
public:

    /**
     * @brief taskSetLoader
     * @param filename
     */
    TaskSetLoader(QString filename);

    ~TaskSetLoader();

    /**
     * @brief readJson  Reads the JSON file
     */
    void readJson();

};

#endif // TASKSETLOADER_H
