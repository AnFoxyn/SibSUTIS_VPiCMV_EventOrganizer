#ifndef DATABASE_H
#define DATABASE_H

#include <QDate>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#define DATABASE_NAME "Database.db"
#define TABLE "Events"
#define TABLE_ID "id"
#define TABLE_NAME "Name"
#define TABLE_DESCRIPTION "Description"
#define TABLE_TIME_START "TimeStart"
#define TABLE_TIME_END "TimeEnd"
#define TABLE_ORGANIZER "Organizer"
#define TABLE_DATE "Date"

class Database : public QObject {
  Q_OBJECT

public:
  explicit Database(QObject *parent = nullptr);
  ~Database();

  void connectToDatabase();

  bool insertIntoTable(const QString &name, const QString &description,
                       const QTime &timeStart, const QTime &timeEnd,
                       const QString &organizer, const QDate &date);
  bool editInTable(const int &id, const QString &name,
                   const QString &description, const QTime &timeStart,
                   const QTime &timeEnd, const QString &organizer,
                   const QDate &date);
  bool deleteFromDatabase(const int id);

private:
  QSqlDatabase db;

  bool createTable();

  bool openDatabase();
  bool restoreDatabase();
  void closeDatabase();
};

#endif // DATABASE_H
