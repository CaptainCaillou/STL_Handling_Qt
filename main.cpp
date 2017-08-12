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
    std::vector<triangle> triangles;
    QApplication app(argc, argv);
    StlFileObject StlFileObj;
    QWidget window;
    window.setFixedSize(1920/2, 1080/2);
    QFile input("../STL_Handler/test.stl");
    QPushButton buttonTest("test", &window);
    buttonTest.move(500,50);
    QLabel TxtBlock(&window);
    QString stl_raw_data_data;

    if (!input.open(QIODevice::ReadOnly))
        std::cerr << "Can't open file" << std::endl;
    if (input.isOpen())
    {
        std::cout << "file open" << std::endl;
        stl_raw_data_data = input.readAll();
        triangles =  StlFileObj.decodeFile(stl_raw_data_data);
        //TxtBlock.setText(stl_raw_data_data);
        input.close();
        layer test;
        test.height = 0.00;
        test.width = 0.2;
        int cpt = 0;

        for(test.height = 0; test.height < 3; test.height += test.width) {
            for(unsigned int i = 0 ; i < triangles.size(); i++) {
                if(triangles[i].getCrossingSegment(test).p1.z) {
                    /*
                    std::cout << i << std:: endl;
                    std::cout << "    p1:" << triangles[i].p1;
                    std::cout << "    p2:" << triangles[i].p2;
                    std::cout << "    p3:" << triangles[i].p3;
                    std::cout << triangles[i].getCrossingSegment(test);
                    */
                    cpt++;
                }
            }
            std::cout << "from " << test.height <<" to " << test.height + test.width << ", " << cpt<< "segments" << std::endl;
            cpt = 0;
        }
    }
    window.show();
    return app.exec();
}
