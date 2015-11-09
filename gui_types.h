#ifndef GUI_TYPES
#define GUI_TYPES

#include <QString>
#include "guiexception.h"
#include <map>

using namespace std;

/**
 * @brief   The allocationModes enum represents the allocation modes for a Partioned Multiprocessor Kernel
 */
enum allocationModes { AUTOMATIC, MANUAL, N_ALLOCATION_MODES};

/**
 * @brief   The schedulerTypes enum represents the available scheduler types
 */
enum schedulerTypes { EDF, RM};

/**
 * @brief   The allocationStrategies enum represents the available automatic task allocation strategies
 *          in a Partioned Multiprocessor Real Time Kernel
 */
enum allocationStrategies { NEXT_FIT, BEST_FIT, WORST_FIT, FIRST_FIT, FIRST_FIT_DECR, N_ALLOCATION_STRATEGIES};

/**
    Data class that contains the parameters of a Periodic Task

    @author Casini Daniel
*/
class PeriodicTaskData{

public:

    PeriodicTaskData();

    /**
     * @brief PeriodicTaskData
     * @param name      Task name
     * @param phase     Task phase
     * @param ci        Task computation time
     * @param ti        Task period
     * @param di        Task deadline
     * @param kernel    Task Kernel (main kernel or a VM name)
     */
    PeriodicTaskData(QString name, int phase, int ci, int ti, int di, QString kernel);

    QString name() const;
    void setName(const QString &name);

    int phase() const;
    void setPhase(int phase);

    int ci() const;
    void setCi(int ci);

    int ti() const;
    void setTi(int ti);

    int di() const;
    void setDi(int di);

    QString kernel() const;
    void setKernel(const QString &kernel);

private:

    /// Task name
    QString _name;

    /// Task phase
    int _phase;

    /// Task computation time
    int _ci;

    /// Task period
    int _ti;

    /// Task deadline
    int _di;

    /// Task kernel name ('MainKernel', or a VM name)
    QString _kernel;
};


/**
    Data class that contains the parameters of a VM implemented as a Periodic Server

    @author Casini Daniel
*/
class VMData{

public:

    VMData();

    /**
     * @brief VMData
     * @param name      Virtual Machine name
     * @param budget    Virtual Machine (server) budget
     * @param period    Virtual Machine (server) period
     */
    VMData(QString name, int budget, int period);

    int budget() const;
    void setBudget(int budget);

    int period() const;
    void setPeriod(int period);

    void addTask(PeriodicTaskData *task);
    PeriodicTaskData* removeTask(QString name);

    QString name() const;
    void setName(const QString &name);

private:

    /// Virtual Machine name
    QString _name;

    /// Virtual Machine (server) budget
    int _budget;

    /// Virtual Machine (server) period
    int _period;

};

#endif // GUI_TYPES


