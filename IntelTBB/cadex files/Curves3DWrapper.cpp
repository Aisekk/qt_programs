#include "Curves3DWrapper.h"
#include "Circle.h"

using namespace CurvesLibrary;

Curves3DWrapper::Curves3DWrapper(const Curves3D& curves) : _curves(curves) {}

double Curves3DWrapper::cbegin() const
{
    return GetCurveParameterValue(_curves.cbegin());
}

double Curves3DWrapper::cend() const
{
    return GetCurveParameterValue(_curves.cend());
}

Curves3DWrapper::ConstIterator Curves3DWrapper::begin() const
{
    return Curves3DWrapper::ConstIterator(_curves.cbegin());
}

Curves3DWrapper::ConstIterator Curves3DWrapper::end() const
{
    return Curves3DWrapper::ConstIterator(_curves.cend());
}

double Curves3DWrapper::GetCurveParameterValue(const Curves3D::const_iterator& it) const
{
    auto curve = *it;
    if (curve->GetType() == Curve3D::Circle)
    {
        auto circle = std::static_pointer_cast<Circle>(curve);
        return circle->GetRadius();
    }
    return 0.0;
}