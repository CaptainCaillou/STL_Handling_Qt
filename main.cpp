#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QWidget>
#include <QFont>
#include <QString>
#include <qlabel.h>
#include <QFuture>


#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <windows.h>

#include "Process/filereader.h"
#include "Types/datatypes.h"
#include "Types/segment.h"
#include "Types/layer.h"
#include "Printer/printer.h"

#include "Types/part.h"

#include "Process/slicer.h"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  part part_1;

  //first load the part
  fileReader* FileReader = new fileReader;
  FileReader->decodeFile(&part_1,"../STL_Handler/TestFiles/cubehole.STL");
  //free the memory
  delete FileReader;

  //slicing part
  Slicer* slicer = new Slicer;
  slicer->setPart(part_1);
  slicer->setSlicerWidth(0.0002);
  //then slice the part
  slicer->start();
  int state = 0;
  for(int i = 0; !slicer->isFinished() ; i++)
  {
    state =  slicer->getState();
    if (state != -1)
      std::cout << "Slice in progress : " << state << std::endl;
    Sleep(125);
  }

  //just for safety, but we normally don't need to wait
  slicer->wait();
  std::cout << "Slice finished" << std::endl;

  //then we copy the part sliced to our main part
  part_1 = slicer->getPart();

  //we free the memory
  delete slicer;

  return app.exec();
}
