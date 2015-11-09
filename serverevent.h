#ifndef SERVEREVENT_H
#define SERVEREVENT_H

#include <QString>

/**
    Class that contains a server event read from a tracefile.

    @see TraceParser

    @author Casini Daniel
*/
class ServerEvent
{
public:

    ServerEvent();

    /**
     * @brief ServerEvent
     * @param serverName    server name
     * @param eventType     event type (replenishment, scheduled, ...)
     * @param time          time in which the event occurs
     * @param budget        maximum budget of the server
     * @param currentBudget budget of the server at the given time
     * @param period        period of the server
     */
    ServerEvent(QString serverName, QString eventType, int time, int budget, int currentBudget, int period);

    QString eventType() const;
    void setEventType(const QString &eventType);

    QString serverName() const;
    void setServerName(const QString &serverName);

    int budget() const;
    void setBudget(int budget);

    int currentBudget() const;
    void setCurrentBudget(int currentBudget);

    int period() const;
    void setPeriod(int period);

    int time() const;
    void setTime(int time);

private:

    /// Event type (replenishment, scheduled, ...)
    QString _eventType;

    /// Server name
    QString _serverName;

    /// Time in which the event occurs
    int _time;

    /// Maximum budget of the server
    int _budget;

    /// Budget of the server at the given time
    int _currentBudget;

    /// Period of the server
    int _period;

};

#endif // SERVEREVENT_H
