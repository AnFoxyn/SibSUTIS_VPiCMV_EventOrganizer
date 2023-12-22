#ifndef EDITEVENT_H
#define EDITEVENT_H

#include <QBuffer>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class EditEvent;
}

class EditEvent : public QWidget {
  Q_OBJECT

public:
  explicit EditEvent(QWidget *parent = nullptr);
  ~EditEvent();

public slots:
  void catchInfo(const int &id, const QString &name, const QString &description,
                 const QTime &timeStart, const QTime &timeEnd,
                 const QString &organizer, const QDate &date);

private slots:
  void on_saveButton_clicked();
  void on_cancelButton_clicked();

signals:
  void sendToWidgetUpdate(const int &id, const QString &name,
                          const QString &description, const QTime &timeStart,
                          const QTime &timeEnd, const QString &organizer,
                          const QDate &date);

private:
  Ui::EditEvent *ui;
  QString pathImage;
  QByteArray savePic;
  int id;
};

#endif // EDITEVENT_H
