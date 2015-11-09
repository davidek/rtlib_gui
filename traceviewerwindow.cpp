#include "traceviewerwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QSizePolicy>
#include <QDesktopWidget>
#include <QRect>

using namespace std;

TraceViewerWindow::TraceViewerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TraceViewer)
{
    ui->setupUi(this);
}

TraceViewerWindow::~TraceViewerWindow()
{
    delete ui;
}

void TraceViewerWindow::on_fileButton_clicked()
{
    QDir dir;
    QFileDialog* myDialog = new QFileDialog(this);
    myDialog->setFileMode(QFileDialog::ExistingFiles);
    myDialog->setNameFilter("JSON Trace Files (*.json)");
    myDialog->setDefaultSuffix(".json");
    //myDialog->setDirectory(dir.absolutePath());
    myDialog->setDirectory("D:/RTSIM/rtlib2/build/examples/mrt");
    //myDialog->setVisible(true);
    traceFilePath = myDialog->getOpenFileName();
    cout<<traceFilePath.toStdString()<<endl;
}



void TraceViewerWindow::on_showSchedButton_clicked()
{
    if(traceFilePath.isEmpty()){
        QMessageBox::information(nullptr, "Error", "Select the trace file first!");
    }
   /* else if(traceFilePath.right(traceFilePath.indexOf('.')).compare("json") != 0){
        cout<<traceFilePath.right(traceFilePath.indexOf('.')).toStdString()<<endl;
        QMessageBox::information(nullptr, "Error", "File format not correct");
    }*/
    else{
        scrollArea= new QScrollArea;
        scheduleWindow = new Schedule(traceFilePath);
        scrollArea->setWidget(scheduleWindow);
        //scrollArea->setSizePolicy(QSizePolicy::Expanding);
        scrollArea->resize(scheduleWindow->getWidth(), scheduleWindow->getHeight());
        QRect rec = QApplication::desktop()->screenGeometry();
        unsigned int desktopHeight = rec.height();
        unsigned int desktopWidth = rec.width();
        if(scheduleWindow->getWidth() > desktopWidth ||
           scheduleWindow->getHeight() > desktopHeight)
            scrollArea->showMaximized();
        else
            scrollArea->show();
        //scrollArea->showNormal();
        //scrollArea->move(QApplication::desktop()->availableGeometry().center() - scrollArea->rect().center());
        //scrollArea->show();
        //scheduleWindow->show();
    }
}
