#ifndef FILEDIALOGMANAGER_H
#define FILEDIALOGMANAGER_H

#include <QString>

#include <QUrl>
#include <QFileDialog>

#define FILEDIALOG_MANAGER FileDialogManager::getInstance()

/**
    Utility class that allows to perform standard operation to read and write
    JSON file (opening a file navigator to select a json file, etc).
    It is a Singleton

    @author Casini Daniel
*/
class FileDialogManager //singleton
{
public:

    /**
     * @brief   getInstance Returns the FileManager singleton instance
     * @return  FileDialogManager instance
     */
    static FileDialogManager &getInstance();

    /**
     * @brief   openJSONLoadFileDialog
     *          Opens a file dialog to select the JSON file that has to be loaded
     * @return  File pathname
     */
    QString openJSONLoadFileDialog();

    /**
     * @brief   openJSONSaveFileDialog
     *          Opens a file dialog to select the path and the name of the JSON file that has
     *          to be saved
     * @return  File pathname
     */
    QString openJSONSaveFileDialog();

private:

    ///Singleton FileDialogManager instance
    static FileDialogManager *inst;

    ///Private constructor
    FileDialogManager();
};

#endif // FILEDIALOGMANAGER_H
