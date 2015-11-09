#ifndef TASKSETWRITER_H
#define TASKSETWRITER_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "guicontext.h"

/**
    Class used to write a JSON File the tasks and VMs of a task set.

    @author Casini Daniel
*/
class TaskSetWriter
{
public:
    /**
     * @brief taskSetWriter
     * @param filename
     */
    TaskSetWriter(QString filename);

    /**
     * @brief writeJSON writes the JSON task-set file
     */
    void writeJSON();
private:

    QString _filename;
};

#endif // TASKSETWRITER_H
