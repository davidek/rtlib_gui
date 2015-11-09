#include "rtsimulationexecutor.h"
#include "guiexception.h"
#include "scrollschedulewindow.h"
#include <QMessageBox>

#include "guicontext.h"

#include <QFile>

#include "filedialogmanager.h"

RTSimulationExecutor::RTSimulationExecutor() : scheduleWin(0)
{

}

RTSimulationExecutor::~RTSimulationExecutor()
{
    if(scheduleWin)
        delete scheduleWin;
}

void RTSimulationExecutor::showResult(){

    try{
        scheduleWin = new ScrollScheduleWindow("run_trace.json");
        scheduleWin->show();
    }
    catch (NotValidTraceJSONFormatException &e) {
        GUI_CONTEXT.showMessageBox(e.what());
        return;
    }

    saveResult();
}

void RTSimulationExecutor::saveResult(){

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(  0, "Save Trace", "Save JSON tracefile??",
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {

        QString pathname;
        pathname = FileDialogManager::getInstance().openJSONSaveFileDialog();

        if(!pathname.isEmpty()){

            pathname = (pathname.contains(".json")) ? pathname : pathname + ".json";

            QFile::copy("run_trace.json", pathname);
            QFile::remove("run_trace.json");

            GUI_CONTEXT.showMessageBox("File successfully saved");
        }

    }
    else
        QFile::remove("run_trace.json");


}
