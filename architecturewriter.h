#ifndef ARCHITECTUREWRITER_H
#define ARCHITECTUREWRITER_H

#include "jsonwriter.h"

using namespace std;

/**
    Class used to write a JSON File the task-cpu and
    cpu-scheduler type correspondence.

    @see ArchitectureLoader

    @author Casini Daniel
*/
class ArchitectureWriter
{
public:

    ArchitectureWriter(QString filename);

    /**
     * @brief writeJSON
     * @param taskCPUMap        Task-CPU correspondence that has to be written in the file
     * @param cpuSchedulerMap   CPU-Scheduler correspondence that has to be written in the file
     */
    void writeJSON( map<QString, unsigned int> taskCPUMap,
                    map<unsigned int, QString> cpuSchedulerMap);
private:

    ///name of the json file
    QString _filename;

};


#endif // ARCHITECTUREWRITER_H
