#include "helpinformation.h"
#include "ui_helpinformation.h"

HelpInformation::HelpInformation(QWidget *parent)
    : QWidget(parent), ui(new Ui::HelpInformation) {
  ui->setupUi(this);

  connect(ui->backButton, SIGNAL(clicked()), ui->textBrowser, SLOT(backward()));
  connect(ui->homeButton, SIGNAL(clicked()), ui->textBrowser, SLOT(home()));
  connect(ui->nextButton, SIGNAL(clicked()), ui->textBrowser, SLOT(forward()));

  connect(ui->textBrowser, SIGNAL(backwardAvailable(bool)), ui->backButton,
          SLOT(setEnabled(bool)));
  connect(ui->textBrowser, SIGNAL(anchorClicked(QUrl)), this,
          SLOT(on_textBrowser_anchorClicked(QUrl)));
  connect(ui->textBrowser, SIGNAL(forwardAvailable(bool)), ui->nextButton,
          SLOT(setEnabled(bool)));

  ui->textBrowser->setSource(
      QUrl::fromLocalFile(":/helpInformation/index.html"));
}

HelpInformation::~HelpInformation() { delete ui; }
