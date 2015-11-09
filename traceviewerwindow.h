#ifndef TRACEVIEWER_H
#define TRACEVIEWER_H

#include <QWidget>
#include <QScrollArea>

#include "schedule.h"
#include "orphan_ui_traceviewer.h"

//namespace Ui {
//class TraceViewer;
//}

class TraceViewerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TraceViewerWindow(QWidget *parent = 0);
    ~TraceViewerWindow();
    QString traceFilePath;
    Schedule *scheduleWindow;
    QScrollArea *scrollArea;
private slots:
    void on_fileButton_clicked();

    void on_showSchedButton_clicked();

private:
    Ui::TraceViewer *ui;
};

#endif // TRACEVIEWER_H
