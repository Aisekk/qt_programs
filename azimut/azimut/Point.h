#ifndef POINT_H
#define POINT_H

#include <QFloat16>
#include <cmath>
using namespace std;
typedef double real;
const real pi = 3.14159;

class Point
{
    real m_latitude;
    real m_longitude;
public:
    Point();
    ~Point();

    real latitude() const;
    real longitude() const;
    real azimuth(double lat, double lon) const;

    void setLatitude(real lat);
    void setLongitude(real lon);
};

#endif // POINT_H
