#include "architectureloader.h"
#include "guiexception.h"
#include "guicontext.h"

using namespace std;

ArchitectureLoader::ArchitectureLoader(QString filename) : JSONLoader(filename){}


void ArchitectureLoader::readJson(map<QString, unsigned int> &taskCPUMap,
                                  map<unsigned int, QString> &cpuSchedulerMap){

    readFile();

    QJsonDocument   jsonResponse = QJsonDocument::fromJson(_fileStr.toUtf8());
    QJsonObject     jsonObject = jsonResponse.object();

    if(jsonObject["task_cpu"].isNull() && jsonObject["cpu_sched"].isNull())
        throw NotValidArchitectureJSONFormatException("Wrong JSON format for an architecture",
                                                             "architectureLoader");

    QJsonArray      jsonArray = jsonObject["task_cpu"].toArray();

    /* Obtaining task names */
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        taskCPUMap[obj["task_name"].toString()] = obj["cpu_index"].toInt();
    }

    jsonArray = jsonObject["cpu_sched"].toArray();

    /* Obtaining task names */
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        cpuSchedulerMap[obj["cpu_index"].toInt()] = obj["scheduler_type"].toString();
    }

}


