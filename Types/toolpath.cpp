#include "toolpath.h"
#include <QString>

toolPath::toolPath()
{
    x1 = 0.;
    x2 = 0.;
    y1 = 0.;
    y2 = 0.;
    z1 = 0.;
    z2 = 0.;
}

QString toolPath::getGCodeBegin() {
    return "G0 X" + QString::number(x1) + " Y" + QString::number(y1) + " Z" + QString::number(z1) + "\n";
}

QString toolPath::getGCodeEnd() {
    return "G1 X" + QString::number(x1) + " Y" + QString::number(y1) + " Z" + QString::number(z1) + "\n";
}

