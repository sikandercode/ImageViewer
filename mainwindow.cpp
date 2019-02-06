#include "MainWindow.h"
#include <QFileDialog>
#include "ImageViewer.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openButton, SIGNAL(clicked(bool)), SLOT(onOpenFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFile()
{
    QString fileName =  QFileDialog::getOpenFileName(
              this,
              "Open Image File",
              QDir::currentPath(),
              "JPG files (*.jpg);; PNG files (*.png)");

    if (m_imageViewer == nullptr) {
        m_imageViewer = new ImageViewer(this);
        ui->imageViewerVLayout->addWidget(m_imageViewer);
    }

    if (m_imageViewer && !fileName.isEmpty()) {
        m_imageViewer->setFilePath(fileName);
        m_imageViewer->loadImage();
    }
}
