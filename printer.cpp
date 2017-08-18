#include "printer.h"

#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QPixmap>

#include <vector>

printer::printer() : QWidget() {
    setGeometry(QRect(100, 100, 1000, 900));
    currentLayer = 0;
    m_boutonInc = new QPushButton("Next Layer", this);
    m_boutonDec = new QPushButton("Previous Layer", this);
    m_boutonFL  = new QPushButton("First Layer", this);

    m_boutonInc->move(40, 40);
    m_boutonDec->move(40, 70);
    m_boutonFL ->move(40, 100);
    part.clear();
    QObject::connect(m_boutonInc, SIGNAL(clicked()), this, SLOT(incrementLayer()));
    QObject::connect(m_boutonDec, SIGNAL(clicked()), this, SLOT(decrementLayer()));
    QObject::connect(m_boutonFL , SIGNAL(clicked()), this, SLOT(firstLayer()));

}

void printer::incrementLayer() {
    if(currentLayer < part.size()-1)
        currentLayer++;
    std::cout << "Current layer: " << currentLayer << std::endl;
    this->clearMask();
    this->repaint();
}
void printer::decrementLayer() {
    if(currentLayer > 0)
        currentLayer--;
    std::cout << "Current layer: " << currentLayer << std::endl;
    this->clearMask();
    this->repaint();
}
void printer::firstLayer() {
    currentLayer = 0;
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
