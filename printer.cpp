﻿#include "printer.h"

#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QPixmap>

#include <vector>

printer::printer() : QWidget() {
    //setFixedSize(230, 120);
    currentLayer = 0;
    m_boutonDialogue = new QPushButton("Nothing", this);
    m_boutonDialogue->move(40, 50);

    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(openDialog()));
}

void printer::openDialog() {
    if(currentLayer < part.size())
    currentLayer++;
    std::cout << "Current layer: " << currentLayer << std::endl;
}

void printer::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    std::cout << "part.size() = " << part.data()->contours.size() << std::endl;
    for(unsigned int j = 0; j < part.data()->contours.size(); j++) {
        painter.drawLine(QPoint(part[currentLayer].contours[j].p1.x*40 + 300,part[currentLayer].contours[j].p1.y*40 + 300),
                         QPoint(part[currentLayer].contours[j].p2.x*40 + 300,part[currentLayer].contours[j].p2.y*40 + 300));

        std::cout << "part[" << currentLayer << "][" << j  << "].p1.x,part[";
        std::cout <<            currentLayer << "][" << j  << "].p1.y : [";
        std::cout << part[currentLayer].contours[j].p1.x;
        std::cout << ",";
        std::cout << part[currentLayer].contours[j].p1.y;
        std::cout << "] " << std::endl;
        std::cout <<        "part[" << currentLayer << "][" << j;
        std::cout << "].p2.x,part[" << currentLayer << "][" << j;
        std::cout << "].p2.y :   [" << part[currentLayer].contours[j].p2.x;
        std::cout << ","            << part[currentLayer].contours[j].p2.y;
        std::cout << "] " << std::endl;

    }
}