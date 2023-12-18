#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <cmath>
#include <QDialog>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *g = new QGridLayout;
    area = new PlotArea;
    g -> addWidget(area,                           0, 0, 16, 5);
    g -> addWidget(ui -> TransformationMatrixLabel, 0, 8, 1, 3);
    g -> addWidget(ui -> TransformationMatrix,     1, 8, 1, 3);
    g -> addWidget(ui -> RotationLabel,            2, 8, 1, 2);
    g -> addWidget(ui -> OX,                       3, 8, 1, 2);
    g -> addWidget(ui -> OXLeft,                   4, 8, 1, 1);
    g -> addWidget(ui -> OXRight,                  4, 9, 1, 1);
    g -> addWidget(ui -> OY,                       5, 8, 1, 2);
    g -> addWidget(ui -> OYLeft,                   6, 8, 1, 1);
    g -> addWidget(ui -> OYRight,                  6, 9, 1, 1);
    g -> addWidget(ui -> OZ,                       7, 8, 1, 2);
    g -> addWidget(ui -> OZLeft,                   8, 8, 1, 1);
    g -> addWidget(ui -> OZRight,                  8, 9, 1, 1);
    g -> addWidget(ui -> ScaleButton,              9, 8, 1, 2);
    g -> addWidget(ui -> TranslateButton,          10, 8, 1, 2);
    g -> addWidget(ui -> ProjectionOXY,            11, 8, 1, 2);
    g -> addWidget(ui -> ProjectionOXZ,            12, 8, 1, 2);
    g -> addWidget(ui -> ProjectionOYZ,            13, 8, 1, 2);
    g -> addWidget(ui -> RevertProjection,         14, 8, 1, 2);
    g -> addWidget(ui -> RevertButton,             15, 8, 1, 2);

    UpdateTransformationMatrix();
    centralWidget()->setLayout(g);
    setMinimumSize(900, 700);
    setWindowTitle("LAB 6");
    area->SetFigurePoints(
        {Point(1, 1, 1), Point(4, 1, 1), Point(4, 3, 1), Point(2, 3, 1), Point(2, 4, 1),Point(4,4,1),Point(4,5,1),Point(1,5,1),Point(1,1,1),
         Point(1, 1, 2), Point(4, 1, 2), Point(4, 3, 2), Point(2, 3, 2), Point(2, 4, 2),Point(4,4,2),Point(4,5,2),Point(1,5,2),Point(1,1,2)});
    area->SetInnerFigurePoints(
        {Point(2, 1.5, 1), Point(3.5, 1.5, 1), Point(3.5, 2.5, 1), Point(2, 2.5, 1), Point(2, 1.5, 1),
         Point(2, 1.5, 2), Point(3.5, 1.5, 2), Point(3.5, 2.5, 2), Point(2, 2.5, 2), Point(2, 1.5, 2)});

}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
}


void MainWindow::on_OXLeft_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOX, -rotationAngle));
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_OXRight_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOX, rotationAngle));
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_OYLeft_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOY, -rotationAngle));
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_OYRight_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOY, rotationAngle));
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_OZLeft_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOZ, -rotationAngle));
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_OZRight_clicked()
{
    area -> TransformFigure(Matrix::GetRotationMatrix(Matrix::RotationType::RotationOZ, rotationAngle));
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_ScaleButton_clicked()
{
    QDialog *d = new QDialog();
    d->setWindowTitle("Масштабирование");
    QString prompts[3] = {"x", "y", "z"};
    QLabel *labels[3];
    QLineEdit *edits[3];
    QDoubleValidator *val = new QDoubleValidator(-5, 5, 2);
    val -> setNotation(QDoubleValidator::StandardNotation);
    QGridLayout *l = new QGridLayout(d);
    for (int i = 0; i < 3; ++i)
    {
        labels[i] = new QLabel("Масштабирование по " + prompts[i]);
        edits[i] = new QLineEdit("1");
        edits[i] -> setValidator(val);
        l -> addWidget(labels[i], i, 0, 1, 1);
        l -> addWidget(edits[i], i, 1, 1, 1);
    }
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);
    l -> addWidget(buttonBox, 3, 0, 1, 2);
    connect(buttonBox, &QDialogButtonBox::accepted, d, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, d, &QDialog::reject);
    if (d->exec())
    {
        double scales[3];
        for (int i = 0; i < 3; ++i)
        {
            bool ok;
            scales[i] = edits[i]->text().replace(',', '.').toDouble(&ok);
            if (!ok)
            {
                scales[i] = 1;
            }
        }
        area -> TransformFigure(Matrix::GetScaleMatrix(scales[0], scales[1], scales[2]));
        area -> repaint();
        UpdateTransformationMatrix();
    }
    for (int i = 0; i < 3; ++i)
    {
        delete labels[i];
        delete edits[i];
        labels[i] = nullptr;
        edits[i] = nullptr;
    }
    delete l;
    delete buttonBox;
    delete d;
    delete val;
}

void MainWindow::on_RevertButton_clicked()
{
    area -> ResetTransform();
    UpdateTransformationMatrix();
    area -> repaint();
}

void MainWindow::UpdateTransformationMatrix()
{
    Matrix transform = area -> GetTransformationMatrix();
    ui -> TransformationMatrix -> setText(transform.ToQString());
}

void MainWindow::on_TranslateButton_clicked()
{
    QDialog *d = new QDialog();
    d->setWindowTitle("Перенос");
    QString prompts[3] = {"x", "y", "z"};
    QLabel *labels[3];
    QLineEdit *edits[3];
    QDoubleValidator *val = new QDoubleValidator(-9, 9, 2);
    val -> setNotation(QDoubleValidator::StandardNotation);
    QGridLayout *l = new QGridLayout(d);
    for (int i = 0; i < 3; ++i)
    {
        labels[i] = new QLabel("Перенос по " + prompts[i]);
        edits[i] = new QLineEdit("0");
        edits[i] -> setValidator(val);
        l -> addWidget(labels[i], i, 0, 1, 1);
        l -> addWidget(edits[i], i, 1, 1, 1);
    }
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);
    l -> addWidget(buttonBox, 3, 0, 1, 2);
    connect(buttonBox, &QDialogButtonBox::accepted, d, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, d, &QDialog::reject);
    if (d->exec())
    {
        double translations[3];
        for (int i = 0; i < 3; ++i)
        {
            bool ok;
            translations[i] = edits[i]->text().replace(',', '.').toDouble(&ok);
            if (!ok)
            {
                translations[i] = 0;
            }
        }
        area -> TransformFigure(Matrix::GetTranslationMatrix(translations[0], translations[1], translations[2]));
        area -> repaint();
        UpdateTransformationMatrix();
    }
    for (int i = 0; i < 3; ++i)
    {
        delete labels[i];
        delete edits[i];
        labels[i] = nullptr;
        edits[i] = nullptr;
    }
    delete l;
    delete buttonBox;
    delete d;
    delete val;
}

void MainWindow::on_ProjectionOXY_clicked()
{
    area -> RevertProjection();
    area -> ProjectFigure(Matrix::ProjectionType::ProjectionOXY);
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_ProjectionOXZ_clicked()
{
    area -> RevertProjection();
    area -> ProjectFigure(Matrix::ProjectionType::ProjectionOXZ);
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_ProjectionOYZ_clicked()
{
    area -> RevertProjection();
    area -> ProjectFigure(Matrix::ProjectionType::ProjectionOYZ);
    UpdateTransformationMatrix();
    area -> repaint();
}


void MainWindow::on_RevertProjection_clicked()
{
    area -> RevertProjection();
    UpdateTransformationMatrix();
    area -> repaint();
}
