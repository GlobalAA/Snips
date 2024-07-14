#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QString>
#include <iostream>
#include <nlohmann/json.hpp>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QtWidgets/QSystemTrayIcon>

using json = nlohmann::json;

class Config
{
public:
    Config(QSystemTrayIcon &trayIcon);
    struct ConfigFields;
    struct SiteFields;
    struct CommandFields;

    Config::ConfigFields parseConfig();
private:
    QSystemTrayIcon &trayIcon;
    const QString fileName = "cfg.json";
};

struct Config::SiteFields
{
    QString title;
    QString url;
};

struct Config::CommandFields
{
    QString title;
    QString command;
};

struct Config::ConfigFields
{
    std::vector<Config::SiteFields> sites;
    std::vector<Config::CommandFields> cmds;
};

void from_json(const json& j, Config::SiteFields& s);
void from_json(const json& j, Config::CommandFields& cmd);
void from_json(const json& j, Config::ConfigFields& c);

#endif // CONFIG_HPP
