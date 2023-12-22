#include "editevent.h"
#include "ui_editevent.h"
#include "ui_mainwindow.h"

EditEvent::EditEvent(QWidget *parent) : QWidget(parent), ui(new Ui::EditEvent) {
  ui->setupUi(this);

  this->setMaximumSize(this->width(), this->height());
  this->setMinimumSize(this->width(), this->height());
}

EditEvent::~EditEvent() { delete ui; }

void EditEvent::catchInfo(const int &id, const QString &name,
                          const QString &description, const QTime &timeStart,
                          const QTime &timeEnd, const QString &organizer,
                          const QDate &date) {
  this->id = id;
  ui->nameLineEdit->setText(name);
  ui->descriptionTextEdit->setText(description);
  ui->startTimeEdit->setTime(timeStart);
  ui->endTimeEdit->setTime(timeEnd);
  ui->organizerLineEdit->setText(organizer);
  ui->dateEdit->setDate(date);
}

void EditEvent::on_saveButton_clicked() {
  QString name = ui->nameLineEdit->text();
  if (name == "") {
    QMessageBox::information(nullptr, "Event Organizer | Уведомление",
                             "Заполните поле \"Название\"");
    return;
  }

  QString description = ui->descriptionTextEdit->toPlainText();

  QTime timeStart = ui->startTimeEdit->time();
  QTime timeEnd = ui->endTimeEdit->time();

  QString organizer = ui->organizerLineEdit->text();
  if (organizer == "") {
    QMessageBox::information(nullptr, "Event Organizer | Уведомление",
                             "Заполните поле \"Организатор\"");
    return;
  }

  QDate date = ui->dateEdit->date();
  if (date < QDate::currentDate()) {
    QMessageBox::information(nullptr, "Event Organizer | Уведомление",
                             "Нельзя организовать мероприятие в прошлом");
    return;
  }

  emit sendToWidgetUpdate(id, name, description, timeStart, timeEnd, organizer,
                          date);
  close();
}

void EditEvent::on_cancelButton_clicked() { close(); }
