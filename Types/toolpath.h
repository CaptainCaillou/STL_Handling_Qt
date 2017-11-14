#ifndef TOOLPATH_H
#define TOOLPATH_H

#include <iostream>
#include <QString>

class toolPath
{
public:
    toolPath();
    QString getGCodeBegin();
    QString getGCodeEnd();

    double x1, x2, y1, y2, z1, z2;

private:

};

#endif // TOOLPATH_H
