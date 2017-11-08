#ifndef PRINTER_H
#define PRINTER_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QMessageBox>
#include <vector>

#include "Types/layer.h"
#include "Types/segment.h"

class printer : public QWidget
{
    Q_OBJECT

    public:
    printer();
    void paintEvent(QPaintEvent*);
    unsigned int currentLayer;

    public slots:
    void incrementLayer();
    void decrementLayer();
    void firstLayer();


    private:
    QPushButton *m_boutonInc;
    QPushButton *m_boutonDec;
    QPushButton *m_boutonFL;
    QLCDNumber *m_lcd;
    QSlider *m_slider;
};

#endif // PRINTER_H
