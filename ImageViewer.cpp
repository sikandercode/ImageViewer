#include "ImageViewer.h"
#include <QWheelEvent>
#include "ui_ImageViewer.h"

namespace {
const int ZOOM_PERCENTAGE = 25;
}

ImageViewer::ImageViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    ui->imageLabel->setParent(this);
    delete ui->scrollArea->takeWidget();
    ui->scrollAreaWidgetContents = nullptr;
    ui->scrollArea->setWidget(ui->imageLabel);

    connect(ui->zoomInButton, SIGNAL(clicked(bool)), SLOT(zoomIn()));
    connect(ui->zoomOutButton, SIGNAL(clicked(bool)), SLOT(zoomOut()));
    connect(ui->fitToWindowButton, SIGNAL(clicked(bool)), SLOT(fitToWindow()));
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::setFilePath(const QString& filePath)
{
    m_filePath = filePath;
}

bool ImageViewer::loadImage()
{
    if (m_filePath.isEmpty()) {
        return false;
    }

    if (m_image.load(m_filePath)) {
        m_scaleFactor = 1.0;
        setScaledImage();
        return true;
    }
    return false;
}

void ImageViewer::setScaledImage()
{
    QPixmap scaledPixmap = scaledImage();
    if (!scaledPixmap.isNull()) {
        ui->imageLabel->setFixedSize(scaledPixmap.size());
        ui->imageLabel->setPixmap(scaledPixmap);
    }
}

QPixmap ImageViewer::scaledImage()
{
    QSize scaledSize = getScaledSize();
    QPixmap scaledPixmap;
    if (!m_image.isNull()) {
        scaledPixmap = m_image.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    return scaledPixmap;
}

QSize ImageViewer::getScaledSize()
{
    QSize scaledSize = size();
    scaledSize.setHeight(scaledSize.height() - ui->toolbarFrame->height());
    scaledSize *= m_scaleFactor;
    scaledSize.setWidth(scaledSize.width() - 5);
    scaledSize.setHeight(scaledSize.height() - 5);
    return scaledSize;
}

void ImageViewer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    setScaledImage();
}

void ImageViewer::zoomIn()
{
    m_scaleFactor = (m_scaleFactor *  (100 + ZOOM_PERCENTAGE)) / 100;
    setScaledImage();
}

void ImageViewer::zoomOut()
{
    m_scaleFactor = (m_scaleFactor * 100) / (100 + ZOOM_PERCENTAGE);
    setScaledImage();
}

void ImageViewer::fitToWindow()
{
    m_scaleFactor = 1.0;
    setScaledImage();
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    if (QApplication::keyboardModifiers() & Qt::ControlModifier) {
        if (delta > 0) {
            zoomIn();
        } else {
            zoomOut();
        }
    }
}
