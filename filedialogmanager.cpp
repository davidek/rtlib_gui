#include "filedialogmanager.h"

FileDialogManager *FileDialogManager::inst = 0;

FileDialogManager &FileDialogManager::getInstance(){

    if (inst == 0)
        inst = new FileDialogManager();

    return *inst;
}


FileDialogManager::FileDialogManager()
{}

QString FileDialogManager::openJSONLoadFileDialog()
{
    QString pathname;
    QFileDialog myDialog;

    myDialog.setFileMode(QFileDialog::ExistingFiles);
    pathname = myDialog.getOpenFileName(0, "Load", "", "*.json" );

    return pathname;
}

QString FileDialogManager::openJSONSaveFileDialog(){

    QString pathname;
    QFileDialog myDialog;

    myDialog.setFileMode(QFileDialog::ExistingFiles);
    pathname = myDialog.getSaveFileName(0, "Save", "", "*.json");

    return pathname;

}
