#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QLineEdit>
#include <QString>
#include <QValidator>
#include <QSettings>
#include <QMessageBox>

#include <memory>

class Validator
{
public:
    static void validateValue(const QLineEdit* pLine, const QDoubleValidator* pValidator,
                              std::shared_ptr<QSettings> spSettings, const QString& key, bool& error)
    {
        QString str = pLine->text(); int pos = 0;
        if(pValidator->validate(str, pos) == QValidator::Acceptable)
            spSettings->setValue(key, str);
        else
        {
            if(error == false)
            QMessageBox::warning(0, "Ошибка ввода значения", "Диапазон ввода: [-1.0e+308; 1.0e+308]");
            error = true;

        }
    }
    //-------------------------------------------------------------------------------------
    static double valueToDouble(const QString& str)
    {
        double value;
        if(str.contains(",") && !str.contains("."))
        {
            QLocale german(QLocale::German);
            value = german.toDouble(str);
        }
        else
        {
            QLocale c(QLocale::C);
            value = c.toDouble(str);
        }
        return value;
    }
    //-------------------------------------------------------------------------------------
};

#endif // VALIDATOR_H
