#ifndef TASK3_H
#define TASK3_H

#include <stdio.h>
#include <iostream>

class Feature
{
public:
    enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};

    // память для points необходимо выделять в конструкторе в соответствии с RAII и после чтения type из файла
    // память для figure (см. ниже) также выделять в конструкторе
    Feature() : type(eUnknown), points(0) {    } // порядок инициализации полей должен совпадать с порядком их объявления в классе
    ~Feature()
    {
        if (points)
            delete points; // удаление динамического массива производится оператором delete[]
    }

    bool isValid()
    {
        return type != eUnknown;
    }

    // в методе bool read(FILE* file) должны читаться из файла только геометрические данные фигур
    bool read(FILE* file)
    {
        if (fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType)) // type должно читаться из файла до создания *this
            return false;
        short n = 0;
        switch (type)
        {
        case eCircle: n = 3; break;
        case eTriangle:    n = 6; break;
        case eSquare: n = 8; break;
        default: type = eUnknown; return false;
        }
        points = new double[n]; // выделение памяти для points в конструкторе Feature()
        if (!points)
            return false;
        return fread(&points, sizeof(double), n, file) == n*sizeof(double);
    }
    // для рисования фигур необходимо определить отдельные классы и полиморфный объект фигуры должен создаваться динамически в конструкторе Feature
    void draw()
    {
        switch (type)
        {
        case eCircle: drawCircle(points[0], points[1], points[2]); break; // массив координат не должен содержать значение радиуса
        case eTriangle: drawPoligon(points, 6); break;
        case eSquare: drawPoligon(points, 8); break;
        case eUnknown: break; // обработка eUnknown
        default: break; // и default
        }
    }

protected:
    // методы рисования конкретных фигур перенести в класс Figure
    void drawCircle(double centerX, double centerY, double radius);
    void drawPoligon(double* points, int size);

    double* points; // точка должна быть представлена структурой, содержащей координаты точки
    FeatureType type;
    // добавить поле:
    // Figure* figure = nullptr; - указатель на абстрактный базовый класс фигуры
};


int useFeature()
{
    Feature feature; // feature должен создаваться после удачного открытия файла
    // Перед созданием feature необходимо прочитать из файла Feature::type и инициализировать feature его значением
    // Затем прочитать данные фигур
    FILE* file = fopen("features.dat", "r");
    feature.read(file);
    if (!feature.isValid()) // проверка корректности должна быть перед чтением данных фигуры
        return 1;
    return 0;
}



enum class FigureType {Unknown, Circle, Triangle, Square};

class Figure
{
public:
    virtual ~Figure() = default;
    virtual void draw(double* geometry) = 0;
};

class Circle : public Figure
{
public:
    Circle() : Figure() {/*...*/ }
    void draw(double* geometry) override
    {
        auto centerX = geometry[0];
        auto centerY = geometry[1];
        auto radius = geometry[2];

        // drawing
        std::cout << "circle drawing" << std::endl;
    }
};

class Polygon : public Figure
{
public:
    Polygon(short size) : Figure(), _size(size) { /*...*/  }
    void draw(double* geometry) override
    {
        std::cout << "polygon drawing" << std::endl;
    }
private:
    short _size = 0;
};

class NewFeature
{
public:
    NewFeature(FigureType type) : _type(type)
    {
        bool isPolygon = false;

        switch (_type)
        {
        case FigureType::Circle:
            _geomObjectsCount = 3; break;
        case FigureType::Triangle:
            _geomObjectsCount = 6; isPolygon = true; break;
        case FigureType::Square:
            _geomObjectsCount = 8; isPolygon = true; break;
        default:
            _type = FigureType::Unknown; break;
        }

        if(_type != FigureType::Unknown)
        {
            _geometry = new double[_geomObjectsCount];

            if(isPolygon)
            {
                _figure = new Polygon(_geomObjectsCount);
            }
            else
            {
                if(_type == FigureType::Circle)
                    _figure = new Circle();
            }
        }
    }
    ~NewFeature()
    {
        delete [] _geometry;
        delete _figure;
    }

    bool isValid()
    {
        return _type != FigureType::Unknown;
    }

    bool read(FILE* file)
    {
        if (!_geometry)
            return false;
        return fread(&_geometry, sizeof(double), _geomObjectsCount, file) == _geomObjectsCount * sizeof(double);
    }
    void draw()
    {
        if(_figure)
            _figure->draw(_geometry);
    }
private:
    FigureType _type;
    short _geomObjectsCount = 0;
    double* _geometry = nullptr; // не points, т.к. кроме точек может содержать еще значение радиуса
    Figure* _figure = nullptr;
};

int newMain()
{
    FILE* file = fopen("features.dat", "r");
    if(file)
    {
        FigureType type;
        if (fread(&type, sizeof(FigureType), 1, file) != sizeof(FigureType))
            return 1;
        NewFeature feature(type);
        if (!feature.isValid())
            return 1;
        if(feature.read(file))
        {
            feature.draw();
        }
    }
    return 0;
}


#endif // TASK3_H
