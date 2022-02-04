#include "loveLetter.hh"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString& locale : uiLanguages) {
    const QString baseName = "Confectionary_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  loveLetter w;
  w.show();
  return a.exec();
}
