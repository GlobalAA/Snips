#include "config.hpp"

Config::Config(QSystemTrayIcon &p_trayIcon) : trayIcon(p_trayIcon) {}

Config::ConfigFields Config::parseConfig()
{
    QFile file(this->fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->trayIcon.showMessage("Config error", "Not found config file", QSystemTrayIcon::Information, 2000);
        exit(0);
    }

    QTextStream in(&file);
    QString jsonString = in.readAll();
    file.close();

    json j;
    Config::ConfigFields cfg;

    try {
        j = json::parse(jsonString.toStdString());
        cfg = j.get<Config::ConfigFields>();
    }
    catch (json::parse_error &ec) {
        this->trayIcon.showMessage("Config error", "Parsing error", QSystemTrayIcon::Information, 2000);
        exit(0);
    }

    return cfg;
}

void from_json(const json& j, Config::SiteFields& s)
{
    s.title = QString::fromStdString(j.at("title").get<std::string>());
    s.url = QString::fromStdString(j.at("url").get<std::string>());
}

void from_json(const json& j, Config::ConfigFields& c)
{
    j.at("sites").get_to(c.sites);
}
