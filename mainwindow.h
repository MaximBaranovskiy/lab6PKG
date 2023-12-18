#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotarea.h"
#include "matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OXLeft_clicked();

    void on_OXRight_clicked();

    void on_OYLeft_clicked();

    void on_OYRight_clicked();

    void on_OZLeft_clicked();

    void on_OZRight_clicked();

    void on_ScaleButton_clicked();

    void on_RevertButton_clicked();

    void on_TranslateButton_clicked();

    void on_ProjectionOXY_clicked();

    void on_ProjectionOXZ_clicked();

    void on_ProjectionOYZ_clicked();

    void on_RevertProjection_clicked();

private:
    Ui::MainWindow *ui;
    PlotArea *area = nullptr;
    double rotationAngle = 0.15;
    void UpdateTransformationMatrix();
};
#endif // MAINWINDOW_H
