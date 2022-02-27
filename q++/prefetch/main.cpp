#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QStringList>
#include <QTextStream>

QTextStream out(stdout);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "prefetch_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QTextStream consoleOutput(stdout);
    consoleOutput << QObject::tr("translate example") << endl;

    return a.exec();
}
