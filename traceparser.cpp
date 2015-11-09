#include "traceparser.h"
#include "guiexception.h"

using namespace std;

TraceParser::TraceParser(QString filename) : JSONLoader(filename){}

void TraceParser::extractNames(QJsonArray jsonArray){

    /* Obtaining task and server names */
    foreach (const QJsonValue & value, jsonArray) {

        QJsonObject obj = value.toObject();

        if(!obj["task_name"].isNull())
            taskNames.push_back(obj["task_name"].toString());

        else if(!obj["server_name"].isNull()){
            taskNames.push_back(obj["server_name"].toString());
            serverNames.push_back(obj["server_name"].toString());
        }
    }

    //Sort is needed because unique eliminates only the consecutive duplicates
    taskNames.sort();
    taskNames.unique();

    serverNames.sort();
    serverNames.unique();
}

void TraceParser::initTaskDataStructures(){

    QString name;
    /* Initialize a list of task events for each task in a map with the task name as key */
    for(list<QString>::iterator taskNameIter = taskNames.begin();
        taskNameIter != taskNames.end(); taskNameIter++){

        name = *taskNameIter;

        list<TaskEvent> taskEvtList;
        list<ExecutionGUIObject*> execList;
        taskEvtMap[name] = taskEvtList;
        execEvtMap[name] = execList;

    }

}

void TraceParser::initServerDataStructures(){

    QString name;
    /* Initialize a list of server events for each task in a map with the server name as key */

    for(list<QString>::iterator serverNameIter = serverNames.begin();
        serverNameIter != serverNames.end(); serverNameIter++){

        name = *serverNameIter;
        list<ServerBudgetGUIObj*> serverBudgetList;
        list<ServerEvent> serverEvtList;
        budgetStatusMap[name] = serverBudgetList;
        serverEvtMap[name] = serverEvtList;

    }
}

void TraceParser::initDataStructures(){
    initTaskDataStructures();
    initServerDataStructures();
}

void TraceParser::extractEvents(QJsonArray jsonArray){

    bool    server;
    QString name;

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();

        if(!obj["task_name"].isNull())
          server = false;
        else
          server = true;

        name = (!server ? obj["task_name"].toString() : obj["server_name"].toString());

        TaskEvent evt(  obj["time"].toString().toInt(),
                        obj["arrival"].toString().toInt(),
                        obj["cpu_num"].toString().toInt(),
                        name,
                        obj["event_type"].toString(), server);

        taskEvtMap[name].push_back(evt);

        if(server){

          ServerEvent sEvt(name, obj["event_type"].toString(),
                                 obj["time"].toString().toUInt(),
                                 obj["budget"].toString().toUInt(),
                                 obj["current_budget"].toString().toUInt(),
                                 obj["period"].toString().toUInt());

          serverEvtMap[name].push_back(sEvt);
        }
    }
}

void TraceParser::examineTaskEvents(QString taskName, list<ExecutionGUIObject*> &execList, map<unsigned int, SimpleTaskEvent> &simpleEvents, bool &server, unsigned int &maxCpuIndex, unsigned int &maxTime){

    TaskEvent           temp;
    ExecutionGUIObject  *newExecObj;

    for(list<TaskEvent>::iterator eventIter = taskEvtMap[taskName].begin();
        eventIter != taskEvtMap[taskName].end(); eventIter++)
    {
        /*Fills the execution slots data structure */
        temp = *eventIter;
        server = temp.isServer();

        if((temp.eventType().compare("scheduled") == 0
            && ((temp.taskName().compare(taskName)== 0)))){

            newExecObj = new ExecutionGUIObject();
            newExecObj->setTStart(temp.time());
            newExecObj->setCpu(temp.cpu());

            if(temp.cpu() > maxCpuIndex)
                maxCpuIndex = temp.cpu();

        }
        else if(((temp.eventType().compare("descheduled") == 0)     ||
                 (temp.eventType().compare("end_instance") == 0))   &&
                 (temp.taskName().compare(taskName)== 0)){

            newExecObj->setTEnd(temp.time());
            execList.push_back(newExecObj);

        }
        else if((temp.eventType().compare("dline_miss") == 0)
                 && ((temp.taskName().compare(taskName)== 0))){

            simpleEvents[temp.time()] = D_MISS;

        }
        else if((temp.eventType().compare("arrival") == 0)
                 && ((temp.taskName().compare(taskName)== 0))){

             simpleEvents[temp.time()] = ARRIVAL;

         }

        if(temp.time() > maxTime)
            maxTime = temp.time();

    }
}

void TraceParser::examineServerEvents(QString serverName, list<ServerBudgetGUIObj*> &budgetList){

    ServerEvent         serverEvt;
    ServerData          *server_data;
    ServerBudgetGUIObj  *newBudgetObj;

    bool    first = true;
    int     budget;

    for(list<ServerEvent>::iterator eventIter = serverEvtMap[serverName].begin();
        eventIter != serverEvtMap[serverName].end(); eventIter++)
    {
        serverEvt = *eventIter;
        if(first){
          first = false;
          server_data = new ServerData(serverName,
                                       serverEvt.budget(),
                                       serverEvt.period());
          serverData[serverName] = server_data;
        }

        budget = serverEvt.currentBudget();
        newBudgetObj = new ServerBudgetGUIObj();
        newBudgetObj->setTime(serverEvt.time());
        newBudgetObj->setName(serverEvt.serverName());
        newBudgetObj->setCurrentBudget(budget);
        budgetList.push_back(newBudgetObj);
    }
}

void TraceParser::readJson()
{

    readFile();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(_fileStr.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["events"].toArray();

    if(jsonObject["events"].isNull())
      throw NotValidTraceJSONFormatException("Wrong JSON format for a schedule", "traceParser", "");

    extractNames(jsonArray);
    initDataStructures();

    extractEvents(jsonArray);

    ServerBudgetGUIObj *newBudgetObj;

    unsigned int        maxCpuIndex = 0, maxTime = 0;
    bool                server = false;
    QString             taskName;
    int                 budget;

    for(list<QString>::iterator taskNameIter = taskNames.begin();
      taskNameIter != taskNames.end(); taskNameIter++)
    {
        taskName = *taskNameIter;

        list<ExecutionGUIObject*> execList;
        list<ServerBudgetGUIObj*> budgetList;
        map<unsigned int, SimpleTaskEvent> simpleEvents;

        execList = execEvtMap[taskName];
        examineTaskEvents(taskName, execList, simpleEvents, server, maxCpuIndex, maxTime);

        if(server){
          examineServerEvents(taskName, budgetList);
        }

        //push last budget, to keep it constant in the graphical representation
        newBudgetObj = new ServerBudgetGUIObj();
        newBudgetObj->setTime(maxTime);
        newBudgetObj->setCurrentBudget(budget);
        budgetList.push_back(newBudgetObj);

        execEvtMap[taskName] = execList;
        budgetStatusMap[taskName] = budgetList;
        taskSimpleEventsMap[taskName] = simpleEvents;

        server = false;
    }

    archParam.setNTask(taskNames.size());
    archParam.setNCPU(maxCpuIndex + 1);
    archParam.setMaxTime(maxTime);

}

list<QString> &TraceParser::getTaskNames()
{
    return taskNames;
}

list<TaskEvent> &TraceParser::getTaskEventList(QString task)
{
    return taskEvtMap[task];
}

list<ExecutionGUIObject *> &TraceParser::getExecList(QString task)
{
    return execEvtMap[task];
}

list<ServerBudgetGUIObj *> &TraceParser::getBudgetStatus(QString server)
{
    return budgetStatusMap[server];
}

ArchitectureParameter TraceParser::getArchParam()
{
    return archParam;
}

map<unsigned int, SimpleTaskEvent> &TraceParser::getTaskSimpleEventsMap(QString task)
{
    return taskSimpleEventsMap[task];
}

map<QString, list<ServerBudgetGUIObj *> > TraceParser::getBudgetStatusMap() const
{
    return budgetStatusMap;
}

map<QString, list<ServerEvent> > TraceParser::getServerEvtMap() const
{
    return serverEvtMap;
}

map<QString, ServerData *> TraceParser::getServerData() const
{
    return serverData;
}

VMData *TraceParser::getServerData(QString name)
{
    return serverData[name];
}

list<QString> &TraceParser::getServerNames()
{
    return serverNames;
}




