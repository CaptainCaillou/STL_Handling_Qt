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

#include "mainwindow.h"

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

{   //QApplication::setAttribute(Qt::AA_UseDesktopOpenGL); // Fix pour openGL sur Windows

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
