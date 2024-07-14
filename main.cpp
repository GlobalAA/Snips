#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include <QtGui/QIcon>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QAction>
#include <QString>
#include <cstdlib>

#include "headers/config.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QIcon icon(":/file/assets/logo.png");

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(icon);
    QMenu* trayMenu = new QMenu();

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    Config cfg(*trayIcon);
    Config::ConfigFields parsed = cfg.parseConfig();

    for (const auto& site : parsed.sites) {
        QAction *site_action = new QAction(site.title, trayMenu);
        site_action->setIcon(QIcon(":/file/assets/web.png"));
        trayMenu->addAction(site_action);

        QObject::connect(site_action, &QAction::triggered, [site]() {
            std::system(("xdg-open " + site.url.toStdString()).c_str());
        });
    }

    for (const auto& command : parsed.cmds) {
        QAction *cmd_action = new QAction(command.title, trayMenu);
        cmd_action->setIcon(QIcon(":/file/assets/cmd.png"));
        trayMenu->addAction(cmd_action);

        QObject::connect(cmd_action, &QAction::triggered, [command]() {
            std::system(command.command.toStdString().c_str());
        });
    }

    return app.exec();
}
