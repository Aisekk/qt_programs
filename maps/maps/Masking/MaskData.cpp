#include "MaskData.h"

MaskData::MaskData()
{
    m_resetCoordinate = 1000;
    m_maskState_X = m_resetCoordinate;
    m_maskState_Y = m_resetCoordinate;
    m_maskState = Mask::no;
}
//---------------------------------------------------------------------------------------
int MaskData::getMaskState_X() const{                    return m_maskState_X;}
int MaskData::getMaskState_Y() const{                    return m_maskState_Y;}
Mask MaskData::getMaskState() const{                     return m_maskState;}
//---------------------------------------------------------------------------------------
void MaskData::reset()
{
    m_maskState_X = m_resetCoordinate;
    m_maskState_Y = m_resetCoordinate;
    m_maskState = Mask::no;
}
//---------------------------------------------------------------------------------------
void MaskData::setX_of_MaskState(int X)
{
    m_maskState_X = X;
}
void MaskData::setY_of_MaskState(int Y)
{
    m_maskState_Y = Y;
}
void MaskData::setMaskState(Mask maskState)
{
    m_maskState = maskState;
}
//---------------------------------------------------------------------------------------
