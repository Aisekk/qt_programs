#ifndef TYPES_H
#define TYPES_H

#include <QVector>
#include <QPair>

enum class Reading{on, off};
enum class MapType{standard, coordinates};
enum class NormsID
{
    Global, Local, Dynamic, Zsh035, Fau035, Norms06, BigNorms,
    SIL10, SIL15, SIL30, SIL100, SIL500, SIL1000,
};
enum class Mask{no, red, blue, gray};
enum class MaskButtonState{unmasked, masked};
enum class MaskButtonType{coord, value};
enum class ValuePrefix{norm, milli, micro, nano, pico, kilo, mega, giga, tera};
enum class ValueFontSize{size_1, size_2, size_3, size_4, size_5};
enum class ReportFormat{TXT, PDF};

using vecPair = QVector< QPair<int,int> >;

#endif // TYPES_H
