#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();

    bool loadImage();
    void setFilePath(const QString& filePath);

private slots:
    void zoomIn();
    void zoomOut();
    void fitToWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QPixmap scaledImage();
    void setScaledImage();
    QSize getScaledSize();

    Ui::ImageViewer *ui;
    QPixmap m_image;
    double m_scaleFactor = 1.0;
    QString m_filePath;
};

#endif // IMAGEVIEWER_H
