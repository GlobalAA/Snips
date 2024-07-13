#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include <QtGui/QIcon>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QAction>
#include <QString>

#include "config.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QIcon icon(":/file/keyboard-key-a.png");

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(icon);
    QMenu* trayMenu = new QMenu();

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    Config cfg(*trayIcon);
    Config::ConfigFields sites = cfg.parseConfig();

    for (const auto& site : sites.sites) {
        QAction *site_action = new QAction(site.title, trayMenu);
        trayMenu->addAction(site_action);

        QObject::connect(site_action, &QAction::triggered, [site]() {
            std::system(("xdg-open " + site.url.toStdString()).c_str());
        });
    }

    return app.exec();
}
