#ifndef STLFILEOBJECT_H
#define STLFILEOBJECT_H

#include "Types/datatypes.h"
#include "Types/triangle.h"

#include <QApplication>
#include <QString>

class StlFileObject
{
public:
    StlFileObject();
    std::vector<triangle> decodeFile(QString fileURL);
    std::vector<triangle> decodeBinarySTL(QString fileURL);
};

#endif // STLFILEOBJECT_H
