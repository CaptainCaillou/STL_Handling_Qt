#ifndef STLFILEOBJECT_H
#define STLFILEOBJECT_H

#include <QApplication>
#include <QString>

class StlFileObject
{
public:
    StlFileObject();
    int decodeFile(QString stl_data_brut);
};

#endif // STLFILEOBJECT_H
