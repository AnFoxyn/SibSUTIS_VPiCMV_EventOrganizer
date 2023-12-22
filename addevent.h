#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QBuffer>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

#include "database.h"

namespace Ui {
class AddEvent;
}

class AddEvent : public QWidget {
  Q_OBJECT

public:
  explicit AddEvent(QWidget *parent = nullptr);
  ~AddEvent();

private slots:
  void on_addButton_clicked();
  void on_cancelButton_clicked();

private:
  Ui::AddEvent *ui;
  Database *db;

signals:
  void sendToWidget(const QString &name, const QString &description,
                    const QTime &timeStart, const QTime &timeEnd,
                    const QString &organizer, const QDate &date);
};

#endif // ADDEVENT_H
