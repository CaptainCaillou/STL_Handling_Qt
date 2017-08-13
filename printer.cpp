#include "printer.h"

#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QPixmap>

#include <vector>

printer::printer() : QWidget()
{
    setFixedSize(230, 120);

    m_boutonDialogue = new QPushButton("Nothing", this);
    m_boutonDialogue->move(40, 50);

    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(openDialog()));
}

void printer::openDialog()
{
    std::cout << "Nothing" << std::endl;
    // Vous insérerez ici le code d'ouverture des boîtes de dialogue
}

void printer::printLayerContour(std::vector<segment> segs) {

}

void printer::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawArc(50,30,150,150,0,16*360);
}
