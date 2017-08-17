#ifndef PRINTER_H
#define PRINTER_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QMessageBox>
#include <vector>

#include "layer.h"
#include "segment.h"

class printer : public QWidget
{
    Q_OBJECT

    public:
    printer();
    void paintEvent(QPaintEvent*);
    std::vector<layer> part;
    unsigned int currentLayer;

    public slots:
    void openDialog();
    //void printLayerContour(std::vector<segment> segs);

    private:
    QPushButton *m_boutonDialogue;
    QLCDNumber *m_lcd;
    QSlider *m_slider;
};

#endif // PRINTER_H
