#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <QPointF>
#include <QString>

class Point
{
public:
    Point(double x, double y, double z, double w = 1);
    double getParameter(int index) const;
    QPointF toQPoint() const;
    Point pointBehind() const;
private:
    double data[4];
};


class Matrix
{
public:
    enum class ProjectionType
    {
        ProjectionOXY,
        ProjectionOXZ,
        ProjectionOYZ,
    };
    enum class RotationType
    {
        RotationOX,
        RotationOY,
        RotationOZ,
    };
    static Matrix GetProjectionMatrix(ProjectionType type);
    static Matrix GetAksonometricMatrix(double angleX, double angleY, double angleZ);
    static Matrix GetScaleMatrix(double scaleX, double scaleY, double scaleZ);
    static Matrix GetRotationMatrix(RotationType type, double angle);
    static Matrix GetTranslationMatrix(double translateX, double translateY, double translateZ);
    static Matrix GetIdentityMatrix();
    static Matrix ComposeFromPoints(std::vector<Point> const& points);
    static std::vector<Point> DecomposeToPoints(Matrix const& matr);

    QString ToQString() const;

    Matrix operator=(Matrix const& other);
    Matrix operator*(Matrix const& other) const;

    Matrix transpose() const;

    Matrix(Matrix const& other);

    ~Matrix();
private:
    Matrix(int _n, int _m);
    void FreeMemory();
    void AllocateMemory(int n, int m);
    void CopyValues(Matrix const& other);
    double **array = nullptr;
    int n = 0, m = 0;
};

#endif
