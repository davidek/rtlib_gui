#ifndef TRACEDATA_H
#define TRACEDATA_H

#include <QString>

enum Event { SCHED, NUM_EVENTS};
class TraceData
{ 
public:

    Event evt;
    QString taskName;
    TraceData(QString evt, QString taskName);
};

#endif // TRACEDATA_H
