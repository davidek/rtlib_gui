#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "guicontext.h"

class JSONWriter
{
public:
    JSONWriter(QString);
    virtual void writeJSON() = 0;
private:
    QString _filename;
};

#endif // JSONWRITER_H
