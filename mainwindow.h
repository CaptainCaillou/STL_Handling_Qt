#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_VueOpenGL_destroyed();

private:
    Ui::MainWindow *ui;

    void MAJVue3D(void);
};

#endif // MAINWINDOW_H
