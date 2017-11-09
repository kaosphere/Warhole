#include "UI/mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QFile>

#include "warlibinitializer.h"
#include <Utilities/QLogger/QLogger.h>


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);

    // Initialization of the warlib
    WarlibInit::initWarlib();

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8") );

    QFile File(":/stylesheet/ressources/darkstyle.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    //a.setStyle("windows");
    a.setStyleSheet(StyleSheet);

    MainWindow w;

    w.show();
    
    return a.exec();
}
