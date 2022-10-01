#ifndef TASK3_H
#define TASK3_H

#include <stdio.h>
class Feature
{
public:
    enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};

    Feature() : type(eUnknown), points(0) {    } // порядок в списке инициализации должен совпадать с порядком объявления членов-данных класса
    ~Feature()
    {
        if (points)
            delete points; // удаление динамического массива производится оператором delete[]
    }

    bool isValid()
    {
        return type != eUnknown;
    }

    bool read(FILE* file)
    {
        if (fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType))
            return false;
        short n = 0;
        switch (type)
        {
        case eCircle: n = 3; break;
        case eTriangle:    n = 6; break; // треугольник строится по 3 точкам
        case eSquare: n = 8; break; // квадрат строится по 4 точкам
        default: type = eUnknown; return false;
        }
        points = new double[n];
        if (!points)
            return false;
        return fread(&points, sizeof(double), n, file) == n*sizeof(double);
    }
    void draw()
    {
        switch (type)
        {
        case eCircle: drawCircle(points[0], points[1], points[2]); break; // массив точек не должен содержать значение радиуса
        case eTriangle: drawPoligon(points, 6); break;
        case eSquare: drawPoligon(points, 8); break;
        }
    }

protected:
    void drawCircle(double centerX, double centerY, double radius);
    void drawPoligon(double* points, int size);

    double* points; // точка должна быть представлена структурой, содержащей координаты точки
    FeatureType type;
};


int useFeature()
{
    Feature feature;
    FILE* file = fopen("features.dat", "r");
    feature.read(file);
    if (!feature.isValid())
        return 1;
    return 0;
}

#endif // TASK3_H
