#include <iostream>
#include <cmath>
using namespace std;
typedef double real;
const real pi = 3.14;//lat - vertical, lon - horizontal
const real R = 6.4e6;//m
//точка
struct point{ real latitude; real longitude;
              point(real lat, real lon): latitude(lat), longitude(lon){} };
real distanceM(const point& p1, const point& p2)
{
    //радианы
    real phi1 = p1.latitude*pi/180.0, phi2 = p2.latitude*pi/180.0;
    real lam1 = p1.longitude*pi/180.0, lam2 = p2.longitude*pi/180.0;
    //географические координаты
    real x1 = R*cos(phi1)*cos(lam1), x2 = R*cos(phi2)*cos(lam2);
    real y1 = R*cos(phi1)*sin(lam1), y2 = R*cos(phi2)*sin(lam2);
    real z1 = R*sin(phi1), z2 = R*sin(phi2);
    //расстояние между точками (прямая)
    real h = sqrt(pow(x1-x2,2) + pow(y1-y2,2) + pow(z1-z2,2));
    //угол напротив h
    real angle = 2.0*asin(h/(2.0*R));
    return R*angle;//географическое расстояние (дуга)
}
real distanceEquator(const point& p1, const point& p2)
{
    real lam1 = p1.longitude/180.0*pi, lam2 = p2.longitude/180.0*pi;//radian
    real angle = fabs(lam1-lam2);
    return R*angle;
}
real distanceEquatorRightAngle(){ return R*pi/2.0; }
real equatorLengthHalf(){ return pi*R; }
void calc(const point& p1, const point& p2)
{
    cout << "Distance between (" << p1.latitude << ";" << p1.longitude
         << ") and (" << p2.latitude << ";" << p2.longitude << "): "
         << distanceM(p1,p2) << endl;
}

int main()
{
    point p1(0.0, 0.0); point p2(1.0, 180.0); calc(p1,p2);
    point p3(0.0, 0.0); point p4(2.0, 180.0); calc(p3,p4);
    point p5(0.0, 0.0); point p6(5.0, 180.0); calc(p5,p6);
    point p7(0.0, 0.0); point p8(10.0, 180.0); calc(p7,p8);
    point p9(0.0, 0.0); point p10(179.0, 180.0); calc(p9,p10);
    cout << endl;
    //---------------------------------------------------------------------------------------------
    cout << "On equator: " << endl;
    point p1e(0.0, 0.0);
    point p2e(0.0, 90.0);
    cout << "Distance between (" << p1e.latitude << ";" << p1e.longitude
         << ") and (" << p2e.latitude << ";" << p2e.longitude << "): "
         << distanceM(p1e,p2e) << endl;
    cout << "Distance between (" << p1e.latitude << ";" << p1e.longitude
         << ") and (" << p2e.latitude << ";" << p2e.longitude << "), simple formula: "
         << distanceEquator(p1e,p2e) << endl;
    cout << "Distance between (" << 0 << ";" << 0
         << ") and (" << 0 << ";" << 90 << "), right angle: "
         << distanceEquatorRightAngle() << endl << endl;
    //---------------------------------------------------------------------------------------------
    cout << "Equator length / 2: " << endl;
    point p1l(0.0, 0.0);
    point p2l(0.0, 180);
    cout << "Distance between (" << p1l.latitude << ";" << p1l.longitude
         << ") and (" << p2l.latitude << ";" << p2l.longitude << "): "
         << distanceM(p1l,p2l) << endl;
    cout << "Distance between (" << 0 << ";" << 0
         << ") and (" << 0 << ";" << 180 << "), simple formula: "
         << equatorLengthHalf() << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
