#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QWidget>
#include <QFont>
#include <qlabel.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget fenetre;
    fenetre.setFixedSize(1920/2, 1080/2);
    QFile input("../STL_Handler/test.stl");

    QPushButton buttonTest("test", &fenetre);
    buttonTest.move(500,50);
    QLabel TxtBlock(&fenetre);


    if (!input.open(QIODevice::ReadOnly))
        std::cerr << "Can't open file" << std::endl;
    if (input.isOpen())
    {
        std::cout << "file open" << std::endl;
        QString stl_data_brut = input.readAll();
        TxtBlock.setText(stl_data_brut);
        input.close();

    }

    fenetre.show();
    return app.exec();
}
