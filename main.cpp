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
#include <thread>

#include "FileHandling/stlfileobject.h"
#include "Types/datatypes.h"
#include "Types/segment.h"
#include "Types/layer.h"
#include "Printer/printer.h"

#include "Types/part.h"

#include "Process/slicer.h"


Slicer slicer;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  part part_1;

  StlFileObject StlFileObj;
  //first load the part
  //TODO

  //then slice the part
  //slicer.slice(&part_1, 0.1);

  return app.exec();
}
