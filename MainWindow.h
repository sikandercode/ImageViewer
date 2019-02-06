#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class ImageViewer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onOpenFile();

private:
    Ui::MainWindow *ui;
    ImageViewer *m_imageViewer = nullptr;
};

#endif // MAINWINDOW_H
