#include "printer.h"

#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QPixmap>

#include <vector>

printer::printer() : QWidget() {
    setGeometry(QRect(100, 100, 1000, 900));
    currentLayer = 0;
    m_boutonDialogue = new QPushButton("Next Layer", this);
    m_boutonDialogue->move(40, 50);
    part.clear();
    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(openDialog()));
}

void printer::openDialog() {
    if(currentLayer < part.size()-1)
        currentLayer++;
    std::cout << "Current layer: " << currentLayer << std::endl;
    this->clearMask();
    this->repaint();
}

void printer::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    for(unsigned int j = 0; j < part[currentLayer].contours.size(); j++) {
        painter.drawLine(QPoint(part[currentLayer].contours[j].p1.x * 30 + 300,part[currentLayer].contours[j].p1.y * 30 + 300),
                         QPoint(part[currentLayer].contours[j].p2.x * 30 + 300,part[currentLayer].contours[j].p2.y * 30 + 300));
        /*
        std::cout <<        "part[" << currentLayer << "][" << j;
        std::cout << "].p1.x,part[" << currentLayer << "][" << j;
        std::cout << "].p1.y :   [" << part[currentLayer].contours[j].p1.x;
        std::cout << ","            << part[currentLayer].contours[j].p1.y;
        std::cout << "] \t where: " << part[currentLayer].contours[j].p1.where << std::endl;
        std::cout <<        "part[" << currentLayer << "][" << j;
        std::cout << "].p2.x,part[" << currentLayer << "][" << j;
        std::cout << "].p2.y :   [" << part[currentLayer].contours[j].p2.x;
        std::cout << ","            << part[currentLayer].contours[j].p2.y;
        std::cout << "] \t where: " << part[currentLayer].contours[j].p2.where << std::endl;
        */
    }
}
