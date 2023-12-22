#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent), ui(new Ui::Settings) {
  ui->setupUi(this);

  this->setMaximumSize(this->width(), this->height());
  this->setMinimumSize(this->width(), this->height());
}

Settings::~Settings() { delete ui; }

void Settings::catchSettings(const QString &path, const QString &style) {
  ui->pathLabel->setText(path);

  if (style == "Dark") {
    ui->styleDarkRadioButton->setChecked(true);
    ui->styleLightRadioButton->setChecked(false);
  } else {
    ui->styleDarkRadioButton->setChecked(false);
    ui->styleLightRadioButton->setChecked(true);
  }
  return;
}

void Settings::on_setPathButton_clicked() {
  QString changePath = QFileDialog::getExistingDirectory(
      nullptr, "Выбрать директорию", ui->pathLabel->text());
  if (!changePath.isNull())
    ui->pathLabel->setText(changePath);
  else
    return;
}

void Settings::on_styleDarkRadioButton_clicked() {
  ui->styleDarkRadioButton->setChecked(true);
  ui->styleLightRadioButton->setChecked(false);
  return;
}

void Settings::on_styleLightRadioButton_clicked() {
  ui->styleDarkRadioButton->setChecked(false);
  ui->styleLightRadioButton->setChecked(true);
  return;
}

void Settings::on_saveButton_clicked() {
  QString path = ui->pathLabel->text();

  QString style;
  if (ui->styleDarkRadioButton->isChecked())
    style = "Dark";
  else if (ui->styleLightRadioButton->isChecked())
    style = "Light";

  emit sendToWidgetUpdate(path, style);
  close();
}

void Settings::on_cancelButton_clicked() { close(); }
