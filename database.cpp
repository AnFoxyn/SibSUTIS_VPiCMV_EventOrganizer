#include "Database.h"

Database::Database(QObject *parent) : QObject(parent) {}
Database::~Database() {}

bool Database::createTable() {
  QSqlQuery query;

  if (!query.exec("CREATE TABLE " TABLE " (" TABLE_ID
                  " INTEGER PRIMARY KEY AUTOINCREMENT," TABLE_NAME
                  " TINYTEXT                 NOT NULL," TABLE_DESCRIPTION
                  " TEXT                             ," TABLE_TIME_START
                  " TIME                     NOT NULL," TABLE_TIME_END
                  " TIME                     NOT NULL," TABLE_ORGANIZER
                  " TINYTEXT                 NOT NULL," TABLE_DATE
                  " DATE                     NOT NULL"
                  " )")) {
    qDebug() << "Невозможно создать таблицу " << TABLE;
    qDebug() << query.lastError().text();
    return false;
  } else
    return true;
}

bool Database::openDatabase() {
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(DATABASE_NAME);

  if (db.open())
    return true;
  else
    return false;
}
bool Database::restoreDatabase() {
  if (this->openDatabase()) {
    if (!this->createTable())
      return false;
    else
      return true;
  } else {
    qDebug() << "Не удалось восстановить базу данных";
    return false;
  }
}
void Database::closeDatabase() { db.close(); }

void Database::connectToDatabase() {
  if (!QFile(DATABASE_NAME).exists())
    this->restoreDatabase();
  else
    this->openDatabase();
}

bool Database::insertIntoTable(const QString &name, const QString &description,
                               const QTime &timeStart, const QTime &timeEnd,
                               const QString &organizer, const QDate &date) {

  QSqlQuery query;

  query.prepare(
      "INSERT INTO " TABLE " ( " TABLE_NAME ", " TABLE_DESCRIPTION
      ", " TABLE_TIME_START ", " TABLE_TIME_END ", " TABLE_ORGANIZER
      ", " TABLE_DATE " ) "
      "VALUES (:Name, :Description, :TimeStart, :TimeEnd, :Organizer, :Date)");

  query.bindValue(":Name", name);
  query.bindValue(":Description", description);
  query.bindValue(":TimeStart", timeStart);
  query.bindValue(":TimeEnd", timeEnd);
  query.bindValue(":Organizer", organizer);
  query.bindValue(":Date", date);

  if (!query.exec()) {
    qDebug() << "Ошибка синтаксиса в инструкции INSERT INTO " << TABLE;
    qDebug() << query.lastError().text();
    return false;
  } else
    return true;
}

bool Database::editInTable(const int &id, const QString &name,
                           const QString &description, const QTime &timeStart,
                           const QTime &timeEnd, const QString &organizer,
                           const QDate &date) {
  QSqlQuery query(db);

  query.prepare("UPDATE " TABLE " SET " TABLE_NAME "=:Name, " TABLE_DESCRIPTION
                "=:Description, " TABLE_TIME_START
                "=:TimeStart, " TABLE_TIME_END "=:TimeEnd, " TABLE_ORGANIZER
                "=:Organizer, " TABLE_DATE "=:Date "
                "WHERE " TABLE_ID "=:Id");

  query.bindValue(":Id", id);
  query.bindValue(":Name", name);
  query.bindValue(":Description", description);
  query.bindValue(":TimeStart", timeStart);
  query.bindValue(":TimeEnd", timeEnd);
  query.bindValue(":Organizer", organizer);
  query.bindValue(":Date", date);

  if (!query.exec()) {
    qDebug() << "ОШИБКА: Не удается отредактировать запись в таблице " << TABLE;
    qDebug() << query.lastError().text();
    return false;
  } else
    return true;
}

bool Database::deleteFromDatabase(const int id) {
  QSqlQuery query(db);

  query.prepare("DELETE FROM " TABLE " WHERE " TABLE_ID "= :ID ;");
  query.bindValue(":ID", id);

  if (!query.exec()) {
    qDebug() << "ОШИБКА: Не удается удалить запись в таблице " << TABLE;
    qDebug() << query.lastError().text();
    return false;
  } else {
    return true;
  }
}
