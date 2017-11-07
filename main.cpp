#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QWidget>
#include <QFont>
#include <QString>
#include <qlabel.h>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "FileHandling/stlfileobject.h"
#include "Types/datatypes.h"
#include "Types/segment.h"
#include "Types/layer.h"
#include "Printer/printer.h"

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
    printer window;

    //QFile input("../STL_Handler/TestFiles/cube10.stl");
    //QFile input("../STL_Handler/TestFiles/test.stl");
    //QFile input("../STL_Handler/TestFiles/cubehole.stl");

        StlFileObject StlFileObj;
        triangles =  StlFileObj.decodeFile("../STL_Handler/TestFiles/cubehole.stl");
        //triangles =  StlFileObj.decodeFile("../STL_Handler/TestFiles/sphere.stl");

        //triangles = StlFileObj.decodeBinarySTL("../STL_Handler/TestFiles/cubeholebin.STL");
        layer lay;
        lay.width =  0.1;
        lay.height = 0;
        bool contour_found = false;
        do
        {
            lay.contours.clear();
            printf("\n##########################\nLayer %f\n", lay.height);
            lay.getContour(triangles);
            window.part.push_back(lay);
            lay.height += lay.width;
            if(lay.contours.size() > 3)
                contour_found = true;
        }while(!contour_found || lay.contours.size() > 0);
    window.show();
    return app.exec();
}
