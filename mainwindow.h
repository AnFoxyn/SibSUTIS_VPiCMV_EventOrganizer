#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QSqlTableModel>
#include <QTextDocumentWriter>

#include "addevent.h"
#include "database.h"
#include "editevent.h"
#include "helpinformation.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void slotAdd();
  void slotEdit();
  void slotDelete();
  void slotSave();

  void slotInfo();
  void slotAbout();

  void slotCalendar();
  void slotSettings();

  void updateTable();
  void updateSettings(const QString &path, const QString &style);
  void addEventDatabase(const QString &name, const QString &description,
                        const QTime &timeStart, const QTime &timeEnd,
                        const QString &organizer, const QDate &date);
  void editEventDataBase(const int &id, const QString &name,
                         const QString &description, const QTime &timeStart,
                         const QTime &timeEnd, const QString &organizer,
                         const QDate &date);

signals:
  void sendSettings(const QString &path, const QString &style);
  void sendForEdit(const int &id, const QString &name,
                   const QString &description, const QTime &timeStart,
                   const QTime &timeEnd, const QString &organizer,
                   const QDate &date);

private slots:
  void on_tableView_clicked(const QModelIndex &index);

private:
  Ui::MainWindow *ui;
  Settings *settingsForm;
  AddEvent *addForm;
  EditEvent *editForm;
  Database *db;
  QSqlTableModel *model;
  int currRow = -1;
  int currID = -1;

  QString dirPath = QDir::currentPath();
  QString prefersStyle = "Dark";

  QString styleDark;
  QString styleLight;
};
#endif
