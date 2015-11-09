#include "jsonloader.h"

void JSONLoader::readFile(){
    QFile file(_filename);

    if(file.open(QIODevice::ReadOnly))
      qDebug() << "open ok";
    else{

      qDebug() << "open FAILED";

      if(!file.exists())
          qDebug()<<"File does not exists";

    }

    _fileStr = (QString)file.readAll();
    file.close();

}

