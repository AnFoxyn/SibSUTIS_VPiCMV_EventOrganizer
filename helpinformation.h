#ifndef HELPINFORMATION_H
#define HELPINFORMATION_H

#include <QFile>
#include <QWidget>

namespace Ui {
class HelpInformation;
}

class HelpInformation : public QWidget {
  Q_OBJECT

public:
  explicit HelpInformation(QWidget *parent = nullptr);
  ~HelpInformation();

private:
  Ui::HelpInformation *ui;
};

#endif // HELPINFORMATION_H
