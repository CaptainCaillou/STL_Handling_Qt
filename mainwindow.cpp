#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "QTGui/QOpenGLFunctions"
#include "QTGui/QOpenGLContext"
#include "QTGui/QPainter"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_boutonParcourir_clicked()
{
    QString NomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier d'entrée"), "", tr("Fichier 3D (*.stl)"));
    ui->champFichier->setText(NomFichier);
}

void MainWindow::on_boutonLireFichier_clicked()
{
    // L'utilisateur clique sur le bouton pour charger le fichier STL,
    // il faut donc créer un thread qui va lire le fichier et créer la liste des triangles.

}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    MAJVue3D();
}

void MainWindow::MAJVue3D(void) {
    //ui->VueOpenGL->paintGL();

}

void MainWindow::on_VueOpenGL_destroyed()
{

}

