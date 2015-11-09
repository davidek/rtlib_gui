#ifndef TRACEPARSER_H
#define TRACEPARSER_H

#include <qstring.h>
#include "gui_types.h"
#include <list>
#include <map>
#include "taskevent.h"
#include "serverevent.h"
#include "executionguiobject.h"
#include "serverbudgetguiobj.h"
#include "architectureparameter.h"
#include <QFile>
#include <QDebug>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <algorithm>

#include "jsonloader.h"

#define ServerData  VMData

/**
    This class reads a JSON file that constitutes the a simulation trace and expose some methods to
    retrieve the data structures that contains the parsed data

    @author Casini Daniel
*/
class TraceParser : public JSONLoader
{

public:

    TraceParser(QString filename);

    /**
     * @brief   readJson
     *          Reads (and parses) the JSON file
     */
    void readJson();

    std::list<QString>                                  &getTaskNames();

    std::list<TaskEvent>                                &getTaskEventList(QString task);

    std::list<ExecutionGUIObject*>                      &getExecList(QString task);

    std::list<ServerBudgetGUIObj*>                      &getBudgetStatus(QString server);

    ArchitectureParameter                               getArchParam();

    std::map<unsigned int, SimpleTaskEvent>             &getTaskSimpleEventsMap(QString task);

    std::map<QString, std::list<ServerBudgetGUIObj*> >  getBudgetStatusMap() const;

    std::map<QString, std::list<ServerEvent> >          getServerEvtMap() const;


    std::map<QString, ServerData *>                     getServerData() const;

    ServerData                                          *getServerData(QString name);

    std::list<QString>                                  &getServerNames();

private:

    /// List of the task names present in the JSON File
    std::list<QString> taskNames;

    /// List of the server names present in the JSON File
    std::list<QString> serverNames;

    /// Map of the execution events present in the JSON File, the key is the task name
    std::map<QString, std::list<ExecutionGUIObject*> > execEvtMap;

    /// Map of budget status object present obtained fromJSON File, the key is the server name
    std::map<QString, std::list<ServerBudgetGUIObj *> > budgetStatusMap;

    /// Data of the servers present in the JSON File, the key is the server name
    std::map<QString, ServerData *>  serverData;

    /// Task name - Task Event correspondence
    std::map<QString, std::list<TaskEvent> > taskEvtMap;

    /// Server name - Server Event correspondence
    std::map<QString, std::list<ServerEvent> > serverEvtMap;

    /// Task name - (time, simpleTaskEvent) correspondence
    std::map<QString, std::map<unsigned int, SimpleTaskEvent> > taskSimpleEventsMap;

    /// Simulation Parameter obtained from the file
    ArchitectureParameter archParam;

    /**
     * @brief   extractEvents
     *          Extract the tasks and server events from the json array
     * @param   jsonArray JSON array obtained by the parser from the JSON file
     */
    void extractEvents(QJsonArray jsonArray);

    /**
     * @brief   initDataStructures
     *          Initializes some parser data structure
     */
    void initDataStructures();

    /**
     * @brief   initServerDataStructures
     *          Initializes some server data structure
     */
    void initServerDataStructures();

    /**
     * @brief   initTaskDataStructures
     *          Initializes some task data structure
     */
    void initTaskDataStructures();

    /**
     * @brief   extractNames
     *          Extract names of servers and tasks from the json array
     * @param   jsonArray       JSON array obtained by the parser from the JSON file
     */
    void extractNames(QJsonArray jsonArray);

    /**
     * @brief   examineServerEvents
     *
     * @param   serverName  server name
     * @param   budgetList  result variable, server status object list
     */
    void examineServerEvents(QString serverName, list<ServerBudgetGUIObj *> &budgetList);

    /**
     * @brief   examineTaskEvents
     *          Extract the simple events (deadline miss, scheduled, ...) and execution information
     *          for a task, while tracks the number of CPUs and the maximum time in which an event exists
     * @param   taskName        task name
     * @param   execList        result variabile, execution object list for the given task
     * @param   simpleEvents    result variabile, simple event object list for the given task
     * @param   server          result variabile, true if the given task is also a server
     * @param   maxCpuIndex     result variable, to track the number of CPUs
     * @param   maxTime         result variable, to track the total simulation time
     */
    void examineTaskEvents(QString taskName, list<ExecutionGUIObject *> &execList, map<unsigned int, SimpleTaskEvent> &simpleEvents, bool &server, unsigned int &maxCpuIndex, unsigned int &maxTime);
};

#endif // TRACEPARSER_H
