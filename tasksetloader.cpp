
#include "tasksetloader.h"
#include "guiexception.h"

TaskSetLoader::TaskSetLoader(QString filename) : JSONLoader(filename){}

TaskSetLoader::~TaskSetLoader()
{
}

void TaskSetLoader::readJson()
{

    GUIContext &context = GUIContext::getInstance();

    readFile();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(_fileStr.toUtf8());
    QJsonObject   jsonObject  = jsonResponse.object();

    if(jsonObject["tasks"].isNull() && jsonObject["VMs"].isNull())
      throw NotValidTaskSetJSONFormatException("Wrong JSON format to load a task set", "taskLoader");

    QJsonArray jsonArray = jsonObject["VMs"].toArray();

    /* Obtaining task names */
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();

        context.addVMData(obj["VM_name"].toString(),
                          obj["budget"].toInt(),
                          obj["period"].toInt());
    }

    jsonArray = jsonObject["tasks"].toArray();

    QString kernel;

    /* Obtaining task names */
    foreach (const QJsonValue & value, jsonArray) {

        QJsonObject obj = value.toObject();
        kernel = (obj["kernel"].isNull()) ? "MainKernel" : obj["kernel"].toString();

        context.addPeriodicTaskData(    obj["task_name"].toString(),
                                        obj["phase"].toInt(),
                                        obj["computation_time"].toInt(),
                                        obj["period"].toInt(),
                                        obj["deadline"].toInt(),
                                        kernel);
    }


}
