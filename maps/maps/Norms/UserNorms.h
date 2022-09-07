#ifndef USERNORMS
#define USERNORMS
#include "BasicNorms.h"
#include <QString>
#include <QRegExp>

class UserNorms : BasicNorms
{
public:
    UserNorms();
    void UserDesignRules(const QString& TestName, double& CriteriumDown, double& CriteriumUp);
};

#endif //USERNORMS

