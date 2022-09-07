#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include <memory>
using namespace std;

#include <QObject>
#include <QSettings>
#include "LocalSettingsWin.h"
#include "GlobalSettingsWin.h"
#include "Types.h"
class Settings;
//==================================================================================================
namespace SystemSettings
{
extern shared_ptr<QSettings> spSettings;
extern shared_ptr<LocalSettingsWin> spLocalSettingsWin;
extern shared_ptr<GlobalSettingsWin> spGlobalSettingsWin;
extern Settings settings;
//--------------------------------------------------------------------------------------------
void initSettings();
//--------------------------------------------------------------------------------------------
//чтение настроек
void readSettings_GlobalNorm(double &criteriumDn, double &criteriumUp, ValuePrefix valuePrefix);
void readSettings_LocalNorms();
void findTestElemNorm(const QString& testName, double& criterionDn, double& criterionUp,
                      ValuePrefix valuePrefix);
void readTestElemNorms(const QString &groupName, const QString &testName, QString &Dn, QString &Up);
}
//==================================================================================================
class Settings : public QObject
{
    Q_OBJECT
public:
    Settings();
    ~Settings();
    void init(shared_ptr<QSettings> spSettings,
              shared_ptr<LocalSettingsWin> spLocalSettingsWin,
              shared_ptr<GlobalSettingsWin> spGlobalSettingsWin);
public slots:
    //показать окна настроек
    void slotLocalSettingsWin();
    void slotGlobalSettingsWin();
    //--------------------------------------------------------------------------------------------
private:
    shared_ptr<QSettings> m_spSettings{};
    shared_ptr<LocalSettingsWin> m_spLocalSettingsWin{};
    shared_ptr<GlobalSettingsWin> m_spGlobalSettingsWin{};
};
//==================================================================================================


#endif // SYSTEMSETTINGS_H
