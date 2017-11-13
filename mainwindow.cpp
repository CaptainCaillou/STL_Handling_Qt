#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "Process/filereader.h"
#include "Types/datatypes.h"
#include "Types/segment.h"
#include "Types/layer.h"
#include "Printer/printer.h"

#include "Types/part.h"

#include "Process/slicer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Timer qui met à jour la progressBar du slicing
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSliceProgressBar()));

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


    //first load the part
    fileReader* FileReader = new fileReader;
    FileReader->decodeFile(&part_1, ui->champFichier->text());
    //free the memory
    delete FileReader;


}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    MAJVue3D();
}

void MainWindow::MAJVue3D(void) {
    //ui->VueOpenGL->paintGL();

}

void MainWindow::updateSliceProgressBar() {
    int state = slicer->getState();

    printf("State : %d\n", state);
    if (state != -1)
        ui->progressBarSlice->setValue(state);

    if (slicer->isFinished()) {
        part_1 = slicer->getPart();
        delete slicer;
        std::cout << "Slice finished" << std::endl;
        timer->stop();
    }
}

void MainWindow::on_boutonSlicer_clicked()
{
    printf("Boop\n");
    //slicing part
    slicer = new Slicer;
    slicer->setPart(part_1);
    slicer->setSlicerWidth(0.0002);
    //then slice the part
    slicer->start();

    // On démarre la fonction qui met à jour la progressBar et qui supprime le slicer à la fin
    timer->start(100);
}
