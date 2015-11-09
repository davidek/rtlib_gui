#ifndef TRACEVIEW_H
#define TRACEVIEW_H

#include <QWidget>
#include "executionguiobject.h"
#include "taskevent.h"
#include <QPainter>
#include <QColor>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <map>


#include "executionguiobject.h"
#include "taskevent.h"

#define     STD_TICK_LENGTH             20
#define     STD_TEXTX_POS               10
#define     STD_FONT_WIDTH              10
#define     STD_VERTLINE_LENGTH         10
#define     STD_TICKLINE_HEIGHT         10
#define     STD_VERTLINE_HEIGHT         20
#define     STD_TEXTTIME_YOFFSET        10
#define     STD_NAMESTR_LEN             8
#define     STD_VERTLINETEXT_LEN        5
#define     STD_VERTLINETEXT_OFFSET     10 * STD_VERTLINETEXT_LEN
#define     STD_LINEXPOS_START          STD_TEXTX_POS  + STD_FONT_WIDTH * STD_NAMESTR_LEN + STD_VERTLINETEXT_OFFSET

namespace Ui {
class TraceView;
}

/**
    Base class for a trace view. A Trace View is intended as a widget that represents the content
    of a trace file over time.

    @see TaskSchedule, BudgetStatusView

    @author Casini Daniel
*/
class TraceView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief TraceView                 Creates a TraceView object
     * @param parent                    Pointer to the parent widget (can be null)
     * @param name                      Trace Widget name, that is displayed on the left
     * @param y                         Y coordinate of the timeline in the widget reference frame
     * @param nVertLines                Number of short horizontal lines along the vertical axis
     * @param maxTime                   Maximum time, i.e., number of intervals along the x axis
     * @param textVertY_Offset          Offset (on the y axis) related to the text displayed along the horizontal lines in the y axis
     * @param leftStringLen             Lenght of the text displayed at the left of the widget (name)
     * @param vertLineTextLengthOffset  Offset (on the x axis) related to the text displayed along the horizontal lines in the y axis
     */
    TraceView(QWidget *parent, QString name, unsigned int y, unsigned int nVertLines, unsigned int maxTime, unsigned int textVertY_Offset, unsigned int leftStringLen = STD_NAMESTR_LEN, unsigned int vertLineTextLengthOffset = STD_VERTLINETEXT_OFFSET);

    ~TraceView();

    /**
     * @brief   drawStructure
     *          Draw the chart structure (x-y axis with the related lines, ...)
     * @param   leftString
     * @param   vertSize
     */
    void drawStructure(QString leftString, int vertSize);

protected:

    /// Trace Widget name, that is displayed on the left
    QString traceName;

    /// Maximum time, i.e., number of intervals along the x axis
    unsigned int maxTime;

    /// Number of short horizontal lines along the vertical axis
    unsigned int nVertLines;

    /// X (start) coordinate of the timeline in the widget reference frame
    unsigned int lineXPosStart;

    /// Width of the selected font
    unsigned int fontWidth;

    /// Y coordinate of the timeline in the widget reference frame
    unsigned int lineYPos;

    /// Length of a time interval
    unsigned int tickLength;

    /// Length of a 'short' horizontal line along the y axis
    unsigned int vertLineLength;

    /// Height of the 'short' vertical line that represents a time unit along the x axis
    unsigned int tickLineHeight;

    /// Height of a vertical 'y-axis unit'
    unsigned int vertLineHeight;

    /// Vertical offset for the time text
    unsigned int textTimeYOffset;

    /// Offset on the x-axis for the trace name text
    unsigned int textXPos;

    /// Offset (on the y axis) related to the text displayed along the horizontal lines in the y axis
    unsigned int textVertYOffset;

    /// Offset (on the x axis) related to the text displayed along the horizontal lines in the y axis
    unsigned int _vertLineTextLengthOffset;

    /// Color used to fill the solid shapes in the view
    QColor color;

private:

    /// GUI Object
    Ui::TraceView *ui;
};

#endif // TRACEVIEW_H
