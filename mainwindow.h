#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Types/part.h"
#include "Process/slicer.h"
#include "Process/filereader.h"
#include "Process/gcodegenerator.h"

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

    void on_boutonSlicer_clicked();

    void updateFileReadingProgressBar();

    void updateSliceProgressBar();

    void updateExportProgressBar();



    void on_boutonEcrireFichier_clicked();

    void on_boutonParcourir_2_clicked();

    void on_checkBox_clicked();

    void on_x_minus_clicked();

    void on_x_plus_clicked();

    void on_y_plus_clicked();

    void on_y_minus_clicked();

    void on_z_plus_clicked();

    void on_z_minus_clicked();

    void on_checkBox_5_clicked();

    void on_spinBox_sliceHeight_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    part part_1;
    fileReader *FileReader;
    Slicer *slicer;
    GCodeGenerator *exporteur;
    QTimer *timer_fileReading;
    QTimer *timer_slice;
    QTimer *timer_export;
    void MAJVue3D(void);
};

#endif // MAINWINDOW_H
