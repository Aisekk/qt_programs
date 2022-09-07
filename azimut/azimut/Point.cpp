#include "Point.h"

Point::Point() : m_latitude(90), m_longitude(90){}
Point::~Point(){}
//-------------------------------------------------------------------------------------------------
real Point::latitude() const{ return m_latitude; }
real Point::longitude() const{ return m_longitude; }
real Point::azimuth(double lat, double lon) const
{
    bool lat_p = (lat < -90.0) || (lat > 90.0);
    bool lon_p = (lon < -180.0) || (lon > 180.0);
    bool lat_this = (m_latitude < -90.0) || (m_latitude > 90.0);
    bool lon_this = (m_longitude < -180.0) || (m_longitude > 180.0);
    if(lat_p || lon_p || lat_this || lon_this) return real(0.0);

    //перевод в радианы
    real phi1 = m_latitude*pi/180.0;
    real lam1 = m_longitude*pi/180.0;
    real phi2 = lat*pi/180.0;
    real lam2 = lon*pi/180.0;

    //аргумент азимута
    real arg = cos(phi1)*tan(phi2)/sin(lam2 - lam1) - sin(phi1)/tan(lam2 - lam1);
    //азимут (в исключительных случаях азимут полагается = 90 градусов)
    real az{};
    if(qIsNaN(arg) || qIsInf(arg)) az = pi/2;
    else az = pi/2 - atan(arg);

    if(!qIsNaN(az) && qIsFinite(az)) return az;
    return real(0.0);
}
//-------------------------------------------------------------------------------------------------
void Point::setLatitude(real lat){ m_latitude = lat; }
void Point::setLongitude(real lon){ m_longitude = lon; }
//-------------------------------------------------------------------------------------------------
