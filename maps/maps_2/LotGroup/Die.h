#ifndef DIE_H
#define DIE_H

#include "Types.h"

class Die
{
public:
    Die(int X, int Y, double val, int testIndex, int slotIndex,
        Mask maskState, MaskButtonState maskButtonState);

    int getX() const;
    int getY() const;
    double getValue() const;
    size_t getTestIndex() const;
    size_t getSlotIndex() const;
    Mask getMaskState() const;
    MaskButtonState maskButtonState() const;

    void setNormalValue(const double multiplier);
    void setMaskState(Mask state);
    void setMaskButtonState(MaskButtonState state);
    void changeValueTo(ValuePrefix prefix);
    //=====================================================================================
private:
    int m_X{};
    int m_Y{};
    double m_value{};
    double m_value_normal{};

    size_t m_testIndex{};
    size_t m_slotIndex{};
    Mask m_maskState{};
    MaskButtonState m_maskButtonState{};
};

#endif // DIE_H
