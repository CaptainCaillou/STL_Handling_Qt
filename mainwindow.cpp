#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "Types/datatypes.h"
#include "Types/segment.h"
#include "Types/layer.h"
#include "Printer/printer.h"

#include "Types/part.h"

#include "Process/filereader.h"
#include "Process/slicer.h"
#include "Process/gcodegenerator.h"

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

  // Timer qui met à jour la progressBar de l'exportation
  timer_export = new QTimer(this);
  connect(timer_export, SIGNAL(timeout()), this, SLOT(updateExportProgressBar()));

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_boutonParcourir_clicked() {
  QString NomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier d'entrée"), "%USERPROFILE%/", tr("Fichier 3D (*.stl)"));
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
    ui->openGLWidget->loadPart(part_1);
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

  }
}


void MainWindow::updateExportProgressBar() {
  int state = exporteur->getState();

  //printf("State : %d\n", state);
  if (state != -1)
    ui->progressBarExport->setValue(state);

  if (exporteur->isFinished()) {
    ui->progressBarExport->setValue(100);
    delete exporteur;
    std::cout << "Export finished" << std::endl;
    timer_export->stop();
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



void MainWindow::on_boutonEcrireFichier_clicked()
{
  if (ui->champFichierExport->text().isEmpty()) return;
  exporteur = new GCodeGenerator();
  exporteur->setPart(part_1);
  exporteur->setFileUrl(ui->champFichierExport->text());
  exporteur->start();
  timer_export->start(10);
}

void MainWindow::on_checkBox_clicked()
{
  this->ui->openGLWidget->VisualizeEdge = this->ui->checkBox->isChecked();
  ui->openGLWidget->update();
}

void MainWindow::on_checkBox_5_clicked()
{
  this->ui->openGLWidget->VisualizeGrid = this->ui->checkBox_5->isChecked();
  ui->openGLWidget->update();
}

void MainWindow::on_boutonParcourir_2_clicked()
{
  QString NomFichier = QFileDialog::getSaveFileName(this, tr("Sauvegarder le fichier de sortie"), "%USERPROFILE%/", tr("Fichier GCODE (*.gcode)"));
  ui->champFichierExport->setText(NomFichier);
}

void MainWindow::on_x_minus_clicked()
{
  part_1.translate( - this->ui->move_step->text().toFloat(), 0, 0);
  ui->openGLWidget->loadLogo(part_1);
  ui->openGLWidget->releaseMProgram();
  ui->openGLWidget->update();
}

void MainWindow::on_x_plus_clicked()
{
  part_1.translate(this->ui->move_step->text().toFloat(), 0, 0);
  ui->openGLWidget->loadLogo(part_1);
  ui->openGLWidget->releaseMProgram();
  ui->openGLWidget->update();
}

void MainWindow::on_y_plus_clicked()
{
  part_1.translate(0, this->ui->move_step->text().toFloat(), 0);
  ui->openGLWidget->loadLogo(part_1);
  ui->openGLWidget->releaseMProgram();
  ui->openGLWidget->update();
}

void MainWindow::on_y_minus_clicked()
{
  part_1.translate(0, - this->ui->move_step->text().toFloat(), 0);
  ui->openGLWidget->loadLogo(part_1);
  ui->openGLWidget->releaseMProgram();
  ui->openGLWidget->update();
}

void MainWindow::on_z_plus_clicked()
{
  part_1.translate(0, 0, this->ui->move_step->text().toFloat());
  ui->openGLWidget->loadLogo(part_1);
  ui->openGLWidget->releaseMProgram();
  ui->openGLWidget->update();
}

void MainWindow::on_z_minus_clicked()
{
  part_1.translate(0, 0, this->ui->move_step->text().toFloat());
  ui->openGLWidget->loadLogo(part_1);
  ui->openGLWidget->releaseMProgram();
  ui->openGLWidget->update();
}


