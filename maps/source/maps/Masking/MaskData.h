#ifndef MASKDATA_H
#define MASKDATA_H

#include "Types.h"

class MaskData
{
public:
    MaskData();

    int getMaskState_X() const;
    int getMaskState_Y() const;
    Mask getMaskState() const;

    void setX_of_MaskState(int X);
    void setY_of_MaskState(int Y);
    void setMaskState(Mask maskState);
    void reset();
private:
    int m_maskState_X{};
    int m_maskState_Y{};
    int m_resetCoordinate{};
    Mask m_maskState{};   
};

#endif // MASKSDATA_H
