#ifndef TASKEVENT_H
#define TASKEVENT_H

#include <QString>

/**
 * @brief   The SimpleTaskEvent enum represents task events and is used by the parser and the task scheduler viewer
 *          to parse and show json trace files
 */
enum SimpleTaskEvent { ARRIVAL, D_MISS, N_SIMPLE_EVENTS};

/**
    Class that contains a task event read from a tracefile.

    @see TraceParser

    @author Casini Daniel
*/
class TaskEvent
{
public:

    TaskEvent();

    /**
     * @brief TaskEvent
     * @param time          time in which the event occurs
     * @param arrival       task arrival time
     * @param cpu           cpu in which the event occurs
     * @param taskName      task name
     * @param eventType     event type (scheduled, arrival, ...)
     * @param server        true if the task is also aserver
     */
    TaskEvent(unsigned int time, unsigned int arrival, unsigned int cpu, QString taskName, QString eventType, bool server) :
        _time(time), _arrival(arrival), _cpu(cpu), _taskName(taskName), _eventType(eventType), _server(server) {}

    unsigned int time() const;
    void setTime(unsigned int time);

    QString eventType() const;
    void setEventType(const QString &eventType);

    QString taskName() const;
    void setTaskName(const QString &taskName);

    unsigned int arrival() const;
    void setArrival(unsigned int arrival);

    unsigned int cpu() const;
    void setCpu(unsigned int cpu);

    bool isServer() const;
    void setServer(const bool &server);

private:

    /**
     * @brief TaskEvent
     * @param time          time in which the event occurs
     * @param arrival       task arrival time
     * @param cpu           cpu in which the event occurs
     * @param taskName      task name
     * @param eventType     event type (scheduled, arrival, ...)
     * @param server        true if the task is also a server
     */

    /// time in which the event occurs
    unsigned int _time;

    /// event type (scheduled, arrival, ...)
    QString _eventType;

    /// task name
    QString _taskName;

    /// task arrival time
    unsigned int _arrival;

    /// cpu in which the event occurs
    unsigned int _cpu;

    /// true if the task is also a server
    bool _server;
};

#endif // TASKEVENT_H
