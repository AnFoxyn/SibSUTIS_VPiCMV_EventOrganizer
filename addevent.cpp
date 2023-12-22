#include "addevent.h"
#include "ui_addevent.h"

AddEvent::AddEvent(QWidget *parent) : QWidget(parent), ui(new Ui::AddEvent) {
  ui->setupUi(this);

  this->setMaximumSize(this->width(), this->height());
  this->setMinimumSize(this->width(), this->height());

  ui->startTimeEdit->setTime(QTime::currentTime());
  ui->endTimeEdit->setTime(QTime::currentTime());

  ui->dateEdit->setDate(QDate::currentDate());
}

AddEvent::~AddEvent() { delete ui; }

void AddEvent::on_cancelButton_clicked() { close(); }

void AddEvent::on_addButton_clicked() {

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
  //  if (date < QDate::currentDate()) {
  //    QMessageBox::information(nullptr, "Event Organizer | Уведомление",
  //                             "Нельзя организовать мероприятие в прошлом");
  //    return;
  //  }

  emit sendToWidget(name, description, timeStart, timeEnd, organizer, date);

  ui->nameLineEdit->clear();
  ui->descriptionTextEdit->clear();
  ui->startTimeEdit->clear();
  ui->endTimeEdit->clear();
  ui->organizerLineEdit->clear();
  ui->dateEdit->clear();
  close();
}
