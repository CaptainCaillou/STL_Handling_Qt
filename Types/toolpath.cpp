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
    QString retour;
    retour.sprintf("G0 X%0.5f Y%0.5f Z%0.5f\n", x1, y1, z1);
    return retour;
}

QString toolPath::getGCodeEnd() {
    QString retour;
    retour.sprintf("G1 X%0.5f Y%0.5f Z%0.5f\n", x2, y2, z2);
    return retour;
}

