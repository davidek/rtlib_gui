#include "tracedata.h"

TraceData::TraceData(QString evt, QString taskName)
{
    if(evt.compare("arrival") == 0)
        this->evt = SCHED;
    else
        this->evt = (Event)10;
    this->taskName = taskName;
}

