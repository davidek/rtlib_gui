#ifndef GUICONTEXT_H
#define GUICONTEXT_H

#include <list>
#include <texttrace.hpp>
#include <json_trace.hpp>
#include <periodicservervm.hpp>
#include <QString>
#include "gui_types.h"
#include "mapcontainer.h"

#define GUI_CONTEXT         GUIContext::getInstance()
#define TASKS_DATA          GUI_CONTEXT.getTasksData().getContainer()
#define VMS_DATA            GUI_CONTEXT.getVmData().getContainer()
#define TASKS               GUI_CONTEXT.getTasks().getContainer()
#define VMs                 GUI_CONTEXT.getPeriodicVMs().getContainer()

using namespace RTSim;

/**
    GUI Context class. It implements the state of the simulation that will be executed, i.e. it contains
    the tasks, the VMs and the simulation data that will be used in the execution.
    It is a singleton

    @author Casini Daniel
*/
class GUIContext //singleton
{
public:

    /**
     * @brief   getInstance
     *          Singleton method that returns the instance
     * @return  GUIContext instance
     */
    static GUIContext   &getInstance();

    /**
     * @brief   erasePeriodicTask
     *          Removes all the periodic tasks from 'tasks'
     */
    void                erasePeriodicTask();

    /**
     * @brief   addPeriodicTasks
     *          Converts all the periodic task data contained in 'tasksData' in PeriodicTask
     *          that can be scheduled by RTSim and adds them to 'tasks'
     */
    void                addPeriodicTasks();

    /**
     * @brief   addVMs
     *          Converts all the VM data contained in 'VMsData' in PeriodicTask
     *          that can be scheduled by RTSim and adds them to 'VMs'
     */
    void                addVMs();

    /**
     * @brief   addPeriodicTaskData
     *          Adds a PeriodicTaskData object
     * @param   name    task name
     * @param   phase   task phase
     * @param   ci      task computation time
     * @param   ti      task period
     * @param   di      task deadline
     * @param   kernel  kernel that schedules the task (a VM name or 'MainKernel')
     */
    void                addPeriodicTaskData(const QString &name, int phase, int ci, int ti, int di, QString kernel);

    /**
     * @brief   removePeriodicTaskData
     * @param   name  name that is the key (in the map tasksData) of the object to remove
     */
    void                removePeriodicTaskData(QString name);

    /**
     * @brief   erasePeriodicTaskData
     *          Erases tasksData
     */
    void                erasePeriodicTaskData();

    /**
     * @brief   addVMData
     *          Adss a VMData object
     * @param   name    VM name
     * @param   budget  server(VM implementation) budget
     * @param   period  periodic(VM implementation) budget
     */
    void                addVMData(QString name, int budget, int period);

    /**
     * @brief   removeVMData
     * @param   name    name that is the key (in the map VMsData) of the object to remove
     */
    void                removeVMData(QString name);

    /**
     * @brief   eraseVMData
     *          Erases VMsData
     */
    void                eraseVMData();

    /**
     * @brief getTaskKernel
     * @param   taskName    task name as QString
     * @return  returns the kernel of the specified task (a VM name or 'MainKernel')
     */
    QString             getTaskKernel(QString taskName);

    /**
     * @brief getTaskKernel
     * @param   taskName    task name as std string
     * @return  returns the kernel of the specified task (a VM name or 'MainKernel')
     */
    QString             getTaskKernel(string taskName);

    /**
     * @brief   addPeriodicTask
     *          Adds a PeriodicTask to 'tasks'
     * @param   name    task name
     * @param   phase   task phase
     * @param   ci      task computation time
     * @param   ti      task period
     * @param   di      task deadline
     * @return  the PeriodicTask created
     */
    PeriodicTask        *addPeriodicTask(const QString &name, int phase, int ci, int ti, int di);

    /**
     * @brief   addPeriodicTask
     *          Adds a PeriodicTask to 'tasks'
     * @param   taskData    PeriodicTaskData object
     * @return  the PeriodicTask created
     */
    PeriodicTask        *addPeriodicTask(PeriodicTaskData *taskData);

    /**
     * @brief   createPeriodicTask
     *          Creates a PeriodicTask object
     * @param   name    task name
     * @param   phase   task phase
     * @param   ci      task computation time
     * @param   ti      task period
     * @param   di      task deadline
     * @return  the PeriodicTask created
     */
    PeriodicTask        *createPeriodicTask(const QString &name, int phase, int ci, int ti, int di);

    /**
     * @brief   addVM
     *          Adds a PeriodicServerVM from VMData
     * @param   vmData
     * @return  the PeriodicServerVM created
     */
    PeriodicServerVM    *addVM(VMData *vmData);

    /**
     * @brief   erasePeriodicServerVM
     *          Erases periodicVMs
     */
    void                erasePeriodicServerVM();

    /**
     * @brief   removeTasksByVM
     *          Removes all the tasks scheduled by the VM specified as parameter
     * @param   vmName
     */
    void                removeTasksByVM(QString vmName);

    /**
     * @brief   moveTasksVM
     *          Moves all the tasks scheduled by the VM 'oldVMName' to the VM 'VMName'
     * @param   oldVMName
     * @param   VMName
     */
    void                moveTasksVM(QString oldVMName, QString VMName);

    /**
     * @brief   taskInserted
     * @param   taskName  task name
     * @return  true if a task with name = 'taskName' exists in tasksData
     */
    bool                taskInserted(QString taskName);

    /**
     * @brief   getHyperPeriod
     *          Computes the hyperperiod
     * @return  The hyperperiod
     */
    unsigned int        getHyperPeriod();

    /**
     * @brief   showMessageBox
     *          shows a QT message box
     * @param   Message to be displayed
     */
    void                showMessageBox(string message);

    /**
     * @brief   getVMCounter
     * @return  the number of inserted VM
     */
    unsigned int        getVMCounter() const;

    /**
     * @brief   getTaskData
     * @param   taskName
     * @return  the PeriodicTaskData object with the given name
     */
    PeriodicTaskData    *getTaskData(QString taskName);

    /**
     * @brief   getTask
     * @param   taskName
     * @return  the PeriodicTask object with the given name
     */
    PeriodicTask        *getTask(QString taskName);

    /**
     * @brief   getVMData
     * @param   vmName
     * @return  the VMData object with the given name
     */
    VMData              *getVMData(QString vmName);

    /**
     * @brief   getVM
     * @param   vmName
     * @return  the PeriodicServerVM object with the given name
     */
    PeriodicServerVM    *getVM(QString vmName);

    /**
     * @brief   getKernel
     * @param   taskName
     * @return  the server that schedules the task
     */
    Server              *getKernel(string taskName);

    unsigned int getTaskCount() const;

    unsigned int getNCPU() const;
    void setNCPU(unsigned int value);

    void setVMCounter(unsigned int value);

    MapContainer<QString, PeriodicTask *> &getTasks();

    MapContainer<QString, PeriodicTaskData *> &getTasksData();

    MapContainer<QString, PeriodicServerVM *> &getPeriodicVMs();

    MapContainer<QString, VMData *> &getVmData();

private:

    /// GUIContext singleton instance
    static GUIContext *inst;

    /// Singleton private constructor
    GUIContext();

    /// Tasks
    MapContainer<QString, PeriodicTask *> tasks;

    /// Tasks Data
    MapContainer<QString, PeriodicTaskData *> tasksData;

    /// PeriodicServerVMs
    MapContainer<QString, PeriodicServerVM *> periodicVMs;

    /// VM Data
    MapContainer<QString, VMData *> vmData;

    /// Number of tasks
    unsigned int taskCounter;

    /// Number of VMs
    unsigned int VMCounter;

    /// Number of CPUs
    unsigned int nCPU;

    /**
     * @brief   addTasks2VM
     *          Adds each task to the VM specified in 'tasksData'
     * @param   vm
     */
    void addTasks2VM(PeriodicServerVM *vm);

    /**
     * @brief   removePeriodicTask
     *          Removes a PeriodicTask from 'tasks'
     * @param   name
     */
    void removePeriodicTask(QString name);


};

#endif // GUICONTEXT_H
