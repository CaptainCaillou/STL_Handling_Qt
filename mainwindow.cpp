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

#include "Vue3D/glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Timer qui met à jour la progressBar du chargement de fichier
  timer_fileReading = new QTimer(this);
  connect(timer_fileReading, SIGNAL(timeout()), this, SLOT(updateFileReadingProgressBar()));

  // Timer qui met à jour la progressBar du slicing
  timer_slice = new QTimer(this);
  connect(timer_slice, SIGNAL(timeout()), this, SLOT(updateSliceProgressBar()));

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_boutonParcourir_clicked() {
  QString NomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier d'entrée"), "", tr("Fichier 3D (*.stl)"));
  ui->champFichier->setText(NomFichier);
}

void MainWindow::on_boutonLireFichier_clicked() {
  // L'utilisateur clique sur le bouton pour charger le fichier STL,
  // il faut donc créer un thread qui va lire le fichier et créer la liste des triangles.

  //first load the part
  FileReader = new fileReader;
  FileReader->setPart(part_1);
  FileReader->setFileUrl(ui->champFichier->text());
  FileReader->start();

  // On démarre la fonction qui met à jour la progressBar et qui supprime le slicer à la fin
  timer_fileReading->start(1);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value) {
  MAJVue3D();
}

void MainWindow::MAJVue3D(void) {
  //ui->VueOpenGL->paintGL();

}
void MainWindow::updateFileReadingProgressBar() {
  int state = FileReader->getState();

  if (state != -1)
    ui->progressBarFile->setValue(state);

  if (FileReader->isFinished()) {
    ui->progressBarFile->setValue(100);
    part_1 = FileReader->getPart();
    delete FileReader;
    std::cout << "FileReading finished" << std::endl;
    timer_fileReading->stop();
  }
}

void MainWindow::updateSliceProgressBar() {
  int state = slicer->getState();

  //printf("State : %d\n", state);
  if (state != -1)
    ui->progressBarSlice->setValue(state);

  if (slicer->isFinished()) {
    ui->progressBarSlice->setValue(100);
    part_1 = slicer->getPart();
    delete slicer;
    std::cout << "Slice finished" << std::endl;
    timer_slice->stop();


    ui->openGLWidget->loadPart(part_1);
  }
}

void MainWindow::on_boutonSlicer_clicked() {
  //slicing part
  slicer = new Slicer;
  slicer->setPart(part_1);
  slicer->setSlicerWidth(0.0002);
  //then slice the part
  slicer->start();

  // On démarre la fonction qui met à jour la progressBar et qui supprime le slicer à la fin
  timer_slice->start(10);
}

static float oldZoom = 0;
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
  ui->openGLWidget->zoom((ui->horizontalSlider->value() - oldZoom)/10);
  ui->openGLWidget->update();
  oldZoom = position;
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
  ui->openGLWidget->zoom((ui->horizontalSlider->value() - oldZoom)/10);
  ui->openGLWidget->update();
  oldZoom = ui->horizontalSlider->value();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
  ui->openGLWidget->zoom((ui->horizontalSlider->value() - oldZoom)/10);
  ui->openGLWidget->update();
  oldZoom = ui->horizontalSlider->value();
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
  ui->openGLWidget->zoom((ui->horizontalSlider->value() - oldZoom)/10);
  ui->openGLWidget->update();
  oldZoom = ui->horizontalSlider->value();
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
  ui->openGLWidget->zoom((ui->horizontalSlider->value() - oldZoom)/10);
  ui->openGLWidget->update();
  oldZoom = ui->horizontalSlider->value();
}

void MainWindow::on_horizontalSlider_rangeChanged(int,int)
{

}


void MainWindow::on_checkBox_clicked()
{
  this->ui->openGLWidget->VisualizeEdge = this->ui->checkBox->isChecked();
  ui->openGLWidget->update();
}
