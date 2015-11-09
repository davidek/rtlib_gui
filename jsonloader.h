#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QString>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <rttask.hpp>

/**
    JSON Loader base class.
    All the specific loaders should extend it.

    @author Casini Daniel
*/
class JSONLoader
{
public:
    /**
     * @brief JSONLoader    JSON loader constructor
     * @param filename      JSON file pathname
     */
    JSONLoader(QString filename) : _filename(filename){}

protected:

    /// JSON file pathname
    QString _filename;

    /// JSON file as string
    QString _fileStr;

    /**
     * @brief readFile Used to read the file as a string
     */
    void readFile();
};

#endif // JSONLOADER_H
