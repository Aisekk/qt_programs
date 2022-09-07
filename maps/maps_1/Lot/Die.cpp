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
void Die::changeValue_to_norm(){            m_value = m_value_normal;}
void Die::changeValue_to_milli(){           m_value = m_value_normal*(1.0e+3);}
void Die::changeValue_to_micro(){           m_value = m_value_normal*(1.0e+6);}
void Die::changeValue_to_nano(){            m_value = m_value_normal*(1.0e+9);}
void Die::changeValue_to_pico(){            m_value = m_value_normal*(1.0e+12);}
void Die::changeValue_to_kilo(){            m_value = m_value_normal*(1.0e-3);}
void Die::changeValue_to_mega(){            m_value = m_value_normal*(1.0e-6);}
void Die::changeValue_to_giga(){            m_value = m_value_normal*(1.0e-9);}
void Die::changeValue_to_tera(){            m_value = m_value_normal*(1.0e-12);}
//===========================================================================================
