#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QLibraryInfo>
#include <QTime>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QTranslator qtLanguageTranslator;
  qtLanguageTranslator.load(QString("QtLanguage_") + QString("ru_RU"));
  qApp->installTranslator(&qtLanguageTranslator);

  MainWindow window;
  window.show();
  return app.exec();
}
