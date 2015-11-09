#include "traceview.h"
#include "ui_traceview.h"

using namespace std;


TraceView::TraceView(QWidget *parent,  QString name, unsigned int y,
                     unsigned int n_VertLines, unsigned int max_time, unsigned int textVertY_Offset, unsigned int leftStringLen, unsigned int vertLineTextLengthOffset) :
    QWidget(parent),
    ui(new Ui::TraceView)
{
    ui->setupUi(this);

    traceName = name;
    lineYPos = y;
    nVertLines = n_VertLines;
    maxTime = max_time;

    textXPos = STD_TEXTX_POS ;
    fontWidth = STD_FONT_WIDTH ;
    tickLength = STD_TICK_LENGTH ;
    vertLineLength = STD_VERTLINE_LENGTH;
    vertLineHeight = STD_VERTLINE_HEIGHT;
    tickLineHeight = STD_TICKLINE_HEIGHT;
    textTimeYOffset = STD_TEXTTIME_YOFFSET;

    lineXPosStart = textXPos + fontWidth*leftStringLen;
    textVertYOffset  = textVertY_Offset;
    _vertLineTextLengthOffset = vertLineTextLengthOffset;
    lineXPosStart += _vertLineTextLengthOffset;
}

TraceView::~TraceView()
{
    delete ui;
}

void TraceView::drawStructure(QString leftString, int vertSize){

    QString s;
    QPainter p(this); // painter

    p.setPen( Qt::black ); // black outline

    //Draw task name
    p.drawText(textXPos, lineYPos - 10, traceName);

    //Draw vertical line for the vertical dimension at the beginning of the timeline
    p.drawLine(lineXPosStart, lineYPos - vertLineHeight * vertSize, lineXPosStart, lineYPos );


    //Draw the cpu spaces along the precedent vertical line and write the given string
    for(int i=1; i<=vertSize; i++){
        s = leftString;
        s.append(QString::number(i-1));

        _vertLineTextLengthOffset = 10*s.length();

        p.drawText(lineXPosStart - _vertLineTextLengthOffset, lineYPos - vertLineHeight * i + textVertYOffset, s);
        p.drawLine(lineXPosStart, lineYPos - (vertLineHeight * i), lineXPosStart + vertLineLength, lineYPos - (vertLineHeight * i));
    }

    //Draw the timeline and draw a small vertical line for each tick and writing the tick number
    for(unsigned int i=0; i<=maxTime*tickLength; i+=tickLength){

        p.drawLine( lineXPosStart+i, lineYPos, lineXPosStart + (i + tickLength), lineYPos );
        p.drawLine( lineXPosStart+i, lineYPos - tickLineHeight, lineXPosStart + i, lineYPos );

        s = QString::number(i/tickLength);

        p.drawText(lineXPosStart+i-2, lineYPos + textTimeYOffset , s);
    }

    adjustSize();
}
