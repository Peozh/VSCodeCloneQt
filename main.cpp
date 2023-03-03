#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <mytabwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "vsCodeClone_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
//    MyTabWidget w2;
//    w2.show();
    return a.exec();
}
