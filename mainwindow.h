#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Types/part.h"
#include "Process/slicer.h"
#include "Process/filereader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_boutonParcourir_clicked();

    void on_boutonLireFichier_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_boutonSlicer_clicked();

    void updateFileReadingProgressBar();

    void updateSliceProgressBar();

private:
    Ui::MainWindow *ui;

    part part_1;
    fileReader *FileReader;
    Slicer *slicer;
    QTimer *timer_fileReading;
    QTimer *timer_slice;
    void MAJVue3D(void);
};

#endif // MAINWINDOW_H
