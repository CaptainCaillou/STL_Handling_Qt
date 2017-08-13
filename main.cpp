#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QWidget>
#include <QFont>
#include <QString>
#include <qlabel.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "stlfileobject.h"
#include "datatypes.h"
#include "segment.h"
#include "layer.h"
#include "printer.h"

std::ostream& operator<<(std::ostream& str, const segment& seg){
    str << "p1: x " << seg.p1.x << "\t y " << seg.p1.y << "\t z " << seg.p1.z << std::endl;
    str << "p2: x " << seg.p2.x << "\t y " << seg.p2.y << "\t z " << seg.p2.z << std::endl;
    return (str);
}

std::ostream& operator<<(std::ostream& str, const point& point){
    str << "x " << point.x << "\t y " << point.y << "\t z " << point.z << std::endl;
    return (str);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<triangle> triangles;
    StlFileObject StlFileObj;
    QFile input("../STL_Handler/test.stl");
    QString stl_raw_data_data;

    printer fenetre;

    if (!input.open(QIODevice::ReadOnly))
        std::cerr << "Can't open file" << std::endl;
    if (input.isOpen())
    {
        std::cout << "file open" << std::endl;
        stl_raw_data_data = input.readAll();
        triangles =  StlFileObj.decodeFile(stl_raw_data_data);

        input.close();
        layer test;
        test.height = 0.00;
        test.width = 0.2;
        int cpt = 0;

        test.getContour(triangles);

        for(test.height = 0; test.height < 3; test.height += test.width) {
            for(unsigned int i = 0 ; i < triangles.size(); i++) {
                if(test.getCrossingSegment(triangles[i]).p1.z) {
                    cpt++;
                }
            }
            std::cout << "from " << test.height <<" to " << test.height + test.width << ", " << cpt<< "segments" << std::endl;
            cpt = 0;

            fenetre.printLayerContour(test.contours);
        }
    }
    fenetre.show();
   return app.exec();
}
