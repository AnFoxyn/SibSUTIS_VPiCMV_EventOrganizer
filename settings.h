#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFileDialog>
#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget {
  Q_OBJECT

public:
  explicit Settings(QWidget *parent = nullptr);
  ~Settings();

public slots:
  void catchSettings(const QString &path, const QString &style);

private slots:
  void on_saveButton_clicked();
  void on_cancelButton_clicked();
  void on_setPathButton_clicked();
  void on_styleDarkRadioButton_clicked();
  void on_styleLightRadioButton_clicked();

private:
  Ui::Settings *ui;

signals:
  void sendToWidgetUpdate(const QString &path, const QString &style);
};

#endif // SETTINGS_H
