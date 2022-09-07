#include "Die.h"

Die::Die(int X, int Y, double val, int testIndex, int slotIndex,
         Mask maskState, MaskButtonState maskButtonState) :
    m_X(X), m_Y(Y), m_value(val), m_testIndex(testIndex), m_slotIndex(slotIndex),
    m_maskState(maskState), m_maskButtonState(maskButtonState)
{
    m_value_normal = val;
}
//-------------------------------------------------------------------------------------------
int Die::getX() const{                          return m_X;}
int Die::getY() const{                          return m_Y;}
double Die::getValue() const{                   return m_value;}
size_t Die::getTestIndex() const{               return m_testIndex;}
size_t Die::getSlotIndex() const{               return m_slotIndex;}
Mask Die::getMaskState() const{                 return m_maskState;}
MaskButtonState Die::maskButtonState() const{   return m_maskButtonState;}
//-------------------------------------------------------------------------------------------
void Die::setNormalValue(const double multiplier)
{
    m_value_normal *= multiplier;
}
void Die::setMaskState(Mask state)
{
    m_maskState = state;
}
void Die::setMaskButtonState(MaskButtonState state)
{
    m_maskButtonState = state;
}
//-------------------------------------------------------------------------------------------
void Die::changeValueTo(ValuePrefix prefix)
{
    switch (prefix)
    {
    case ValuePrefix::norm: { m_value = m_value_normal; break; }
    case ValuePrefix::pico: { m_value = m_value_normal*(1.0e+12); break; }
    case ValuePrefix::nano: { m_value = m_value_normal*(1.0e+9); break; }
    case ValuePrefix::micro: { m_value = m_value_normal*(1.0e+6); break; }
    case ValuePrefix::milli: { m_value = m_value_normal*(1.0e+3); break; }
    case ValuePrefix::kilo: { m_value = m_value_normal*(1.0e-3); break; }
    case ValuePrefix::mega: { m_value = m_value_normal*(1.0e-6); break; }
    case ValuePrefix::giga: { m_value = m_value_normal*(1.0e-9); break; }
    case ValuePrefix::tera: { m_value = m_value_normal*(1.0e-12); break; }
    default: break;
    }
}
//===========================================================================================
