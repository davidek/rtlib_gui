#include "taskschedule.h"
#include "ui_taskschedule.h"


using namespace std;

unsigned int TaskSchedule::instanceCounter = 0;
QColor TaskSchedule::taskScheduleColors[COLORS_NUM] = {Qt::yellow, Qt::darkYellow, Qt::cyan, Qt::green, Qt::darkRed, Qt::blue};

TaskSchedule::TaskSchedule(QWidget *parent, QString taskName, unsigned int y, unsigned int nProc, unsigned int maxTime, std::list<ExecutionGUIObject*> execList, std::map<unsigned int, SimpleTaskEvent> simpleEvents, int taskNameLen) :
    TraceView(0, taskName, y, nProc, maxTime, STD_TASK_TEXTY_OFFSET), _execList(execList), _simpleEvents(simpleEvents),
    ui(new Ui::TaskSchedule)
{
    ui->setupUi(this);

    color = taskScheduleColors[instanceCounter % COLORS_NUM];
    instanceCounter++;
}

TaskSchedule::~TaskSchedule()
{
    delete ui;
}

void TaskSchedule::drawExecution(unsigned int tStart, unsigned int tEnd, unsigned int cpu){

    QPainter p(this);
    p.setPen( Qt::black );
    p.setBrush( color );
    p.drawRect( lineXPosStart + tStart*tickLength   , lineYPos - (vertLineHeight * (cpu + 1)),
                (tEnd - tStart)*tickLength          , vertLineHeight);
}

void TaskSchedule::drawSimpleEvents(){

    QPainter p(this);
    unsigned int time;

    SimpleTaskEvent event;
    for(std::map<unsigned int, SimpleTaskEvent>::iterator simpleEvIter = _simpleEvents.begin();
        simpleEvIter != _simpleEvents.end(); simpleEvIter++)
    {
        time = simpleEvIter->first;
        event = simpleEvIter->second;
        switch(event){
            case D_MISS:
                p.setPen(QPen(Qt::red, 3));
                p.drawLine(lineXPosStart + time*tickLength, lineYPos - vertLineHeight*nVertLines, lineXPosStart + time*tickLength , lineYPos );
                break;
            case ARRIVAL:
                p.setPen(QPen(Qt::black, 3));
                p.drawLine(lineXPosStart + time*tickLength, lineYPos - vertLineHeight*nVertLines, lineXPosStart + time*tickLength , lineYPos );
                break;
        }
    }
}
unsigned int TaskSchedule::getTickLength() const
{
    return tickLength;
}

void TaskSchedule::setTickLength(unsigned int value)
{
    tickLength = value;
}

unsigned int TaskSchedule::getLineYPos() const
{
    return lineYPos;
}

void TaskSchedule::setLineYPos(unsigned int value)
{
    lineYPos = value;
}

unsigned int TaskSchedule::getLineXPosStart() const
{
    return lineXPosStart;
}

void TaskSchedule::setLineXPosStart(unsigned int value)
{
    lineXPosStart = value;
}

unsigned int TaskSchedule::getCpuHeight() const
{
    return vertLineHeight;
}

void TaskSchedule::setCpuHeight(unsigned int value)
{
    vertLineHeight = value;
}


void TaskSchedule::paintEvent(QPaintEvent *event)
{
    ExecutionGUIObject *temp;
    for(std::list<ExecutionGUIObject*>::iterator execIter = _execList.begin();
        execIter != _execList.end(); execIter++){

        temp = *execIter;
        drawExecution(temp->getTStart(), temp->getTEnd(), temp->getCpu());

    }

    drawStructure("CPU ", nVertLines);
    drawSimpleEvents();
}
