#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->setMaximumSize(this->width(), this->height());
  this->setMinimumSize(this->width(), this->height());

  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");
  if (!settings.value("path").toString().isNull())
    dirPath = settings.value("path").toString();
  if (!settings.value("style").toString().isNull())
    prefersStyle = settings.value("style").toString();
  settings.endGroup();

  QFile qssFile__Dark(":/styles/dark.qss"),
      qssFile__Light(":/styles/light.qss");

  qssFile__Dark.open(QFile::ReadOnly);
  styleDark = QLatin1String(qssFile__Dark.readAll());
  qssFile__Dark.close();

  qssFile__Light.open(QFile::ReadOnly);
  styleLight = QLatin1String(qssFile__Light.readAll());
  qssFile__Light.close();

  if (prefersStyle == "Dark")
    qApp->setStyleSheet(styleDark);
  else
    qApp->setStyleSheet(styleLight);

  connect(ui->calendarWidget, SIGNAL(clicked(QDate)), this,
          SLOT(slotCalendar()));
  ui->dateLabel->setText(QDate::currentDate().toString("dd.MM.yyyy"));

  db = new Database();
  db->connectToDatabase();

  model = new QSqlTableModel;
  model->setTable(TABLE);
  model->setHeaderData(0, Qt::Horizontal, "id");

  ui->tableView->setModel(model);
  ui->tableView->setColumnHidden(0, true);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

  updateTable();
  settingsForm = new Settings();
  settingsForm->setWindowModality(Qt::ApplicationModal);
  addForm = new AddEvent();
  addForm->setWindowModality(Qt::ApplicationModal);
  editForm = new EditEvent();
  editForm->setWindowModality(Qt::ApplicationModal);

  connect(settingsForm, SIGNAL(sendToWidgetUpdate(QString, QString)), this,
          SLOT(updateSettings(QString, QString)));
  connect(this, SIGNAL(sendSettings(QString, QString)), settingsForm,
          SLOT(catchSettings(QString, QString)));
  connect(
      addForm,
      SIGNAL(sendToWidget(QString, QString, QTime, QTime, QString, QDate)),
      this,
      SLOT(addEventDatabase(QString, QString, QTime, QTime, QString, QDate)));
  connect(
      this,
      SIGNAL(sendForEdit(int, QString, QString, QTime, QTime, QString, QDate)),
      editForm,
      SLOT(catchInfo(int, QString, QString, QTime, QTime, QString, QDate)));
  connect(editForm,
          SIGNAL(sendToWidgetUpdate(int, QString, QString, QTime, QTime,
                                    QString, QDate)),
          this,
          SLOT(editEventDataBase(int, QString, QString, QTime, QTime, QString,
                                 QDate)));

  connect(ui->menu_addEvent, SIGNAL(triggered()), this, SLOT(slotAdd()));
  connect(ui->menu_editEvent, SIGNAL(triggered()), this, SLOT(slotEdit()));
  connect(ui->menu_deleteEvent, SIGNAL(triggered()), this, SLOT(slotDelete()));
  connect(ui->menu_saveEvent, SIGNAL(triggered()), this, SLOT(slotSave()));
  connect(ui->menu_settings, SIGNAL(triggered()), this, SLOT(slotSettings()));
  connect(ui->menu_exit, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(ui->reference_help, SIGNAL(triggered()), this, SLOT(slotInfo()));
  connect(ui->reference_about, SIGNAL(triggered()), this, SLOT(slotAbout()));

  connect(ui->addButton, SIGNAL(clicked()), this, SLOT(slotAdd()));
  connect(ui->editButton, SIGNAL(clicked()), this, SLOT(slotEdit()));
  connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(slotSave()));
  connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(slotDelete()));
}

MainWindow::~MainWindow() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");
  settings.setValue("path", dirPath);
  settings.setValue("style", prefersStyle);
  settings.endGroup();

  delete ui;
}

void MainWindow::slotSettings() {
  emit sendSettings(dirPath, prefersStyle);
  settingsForm->show();
}

void MainWindow::updateSettings(const QString &path, const QString &style) {
  dirPath = path;
  prefersStyle = style;

  if (prefersStyle == "Dark")
    qApp->setStyleSheet(styleDark);
  else
    qApp->setStyleSheet(styleLight);
}

void MainWindow::slotCalendar() {
  QDate date = ui->calendarWidget->selectedDate();
  ui->dateLabel->setText(date.toString("dd.MM.yyyy"));
  updateTable();
}

void MainWindow::updateTable() {
  currRow = -1;
  currID = -1;

  QDate date = ui->calendarWidget->selectedDate();

  model->select();
  model->setSort(6, Qt::AscendingOrder);
  model->setFilter("Date >= \'" + date.toString("yyyy-MM-dd") + "\'");

  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("Описание"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("Время начала"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("Время окончания"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("Организатор"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("Дата"));

  if (currRow == -1) {
    ui->menu_editEvent->setEnabled(false);
    ui->menu_deleteEvent->setEnabled(false);
    ui->menu_saveEvent->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
  } else {
    ui->menu_editEvent->setEnabled(true);
    ui->menu_deleteEvent->setEnabled(true);
    ui->menu_saveEvent->setEnabled(true);
    ui->editButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
    ui->saveButton->setEnabled(true);
  }

  if (model->rowCount() == 0) {
    ui->label->show();
    ui->tableView->hide();
    return;
  }

  ui->label->hide();
  ui->tableView->show();

  ui->tableView->horizontalHeader()->setSectionResizeMode(1,
                                                          QHeaderView::Stretch);
  ui->tableView->horizontalHeader()->setSectionResizeMode(2,
                                                          QHeaderView::Stretch);
  ui->tableView->horizontalHeader()->setSectionResizeMode(3,
                                                          QHeaderView::Stretch);
  ui->tableView->horizontalHeader()->setSectionResizeMode(4,
                                                          QHeaderView::Stretch);
  ui->tableView->horizontalHeader()->setSectionResizeMode(5,
                                                          QHeaderView::Stretch);
  ui->tableView->horizontalHeader()->setSectionResizeMode(6,
                                                          QHeaderView::Stretch);

  ui->tableView->verticalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::slotAdd() { addForm->show(); }

void MainWindow::addEventDatabase(const QString &name,
                                  const QString &description,
                                  const QTime &timeStart, const QTime &timeEnd,
                                  const QString &organizer, const QDate &date) {
  db->insertIntoTable(name, description, timeStart, timeEnd, organizer, date);
  updateTable();
  currRow = -1;
  currID = -1;
}

void MainWindow::slotEdit() {
  if (currRow != -1) {
    QString name = model->data(model->index(currRow, 1)).toString();
    QString description = model->data(model->index(currRow, 2)).toString();
    QTime timeStart = model->data(model->index(currRow, 3)).toTime();
    QTime timeEnd = model->data(model->index(currRow, 4)).toTime();
    QString organizer = model->data(model->index(currRow, 5)).toString();
    QDate date = model->data(model->index(currRow, 6)).toDate();

    emit sendForEdit(currID, name, description, timeStart, timeEnd, organizer,
                     date);
    editForm->show();
  }
}

void MainWindow::editEventDataBase(const int &id, const QString &name,
                                   const QString &description,
                                   const QTime &timeStart, const QTime &timeEnd,
                                   const QString &organizer,
                                   const QDate &date) {
  currRow = -1;
  currID = -1;

  db->editInTable(id, name, description, timeStart, timeEnd, organizer, date);
  updateTable();
}

void MainWindow::slotSave() {
  if (currRow != -1) {
    QString filename = QFileDialog::getSaveFileName(nullptr, "Сохранить файл",
                                                    dirPath, "*.txt");

    if (!filename.isNull())
      dirPath = filename.left(filename.lastIndexOf("/"));
    else
      return;

    QFile out(filename);
    if (out.open(QIODevice::WriteOnly)) {
      QString name = model->data(model->index(currRow, 1)).toString();
      QString description = model->data(model->index(currRow, 2)).toString();
      QTime timeStart = model->data(model->index(currRow, 3)).toTime();
      QTime timeEnd = model->data(model->index(currRow, 4)).toTime();
      QString organizer = model->data(model->index(currRow, 5)).toString();
      QDate date = model->data(model->index(currRow, 6)).toDate();

      QTextStream stream(&out);
      stream << "Название:       \t" << name << "\n"
             << "Описание:       \t" << description << "\n"
             << "Время начала:   \t" << timeStart.toString("hh:mm") << "\n"
             << "Время окончания:\t" << timeEnd.toString("hh:mm") << "\n"
             << "Организатор:    \t" << organizer << "\n"
             << "Дата проведения:\t" << date.toString("dd.MM.yyyy") << "\n";
      out.close();
    }
  }
}

void MainWindow::slotDelete() {

  if (currRow != -1) {
    QString name = model->data(model->index(currRow, 1)).toString();
    int n = QMessageBox::warning(
        0, "Event Organizer | Удаление мероприятия",
        "Вы действительно хотите удалить мероприятие \n\'" + name + "\'?",
        "Удалить", "Отмена", QString(), 0, 1);
    if (!n) {
      db->deleteFromDatabase(currID);
      updateTable();
      currRow = -1;
      currID = -1;
    }
  }
}

void MainWindow::slotInfo() {
  HelpInformation *form = new HelpInformation();
  form->setWindowModality(Qt::ApplicationModal);
  form->show();
}

void MainWindow::slotAbout() {
  QMessageBox::about(this, "Event Organizer | О программе",
                     "Версия:  2.1 (последняя)\n"
                     "Группа:  ИП-111\n"
                     "Cтудент: Корнилов А.А.\n"
                     "--------------------------------\n"
                     "© 2021-2025 уч.год, СибГУТИ");
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
  ui->menu_editEvent->setEnabled(true);
  ui->menu_deleteEvent->setEnabled(true);
  ui->menu_saveEvent->setEnabled(true);
  ui->editButton->setEnabled(true);
  ui->deleteButton->setEnabled(true);
  ui->saveButton->setEnabled(true);
  currID = model->data(model->index(index.row(), 0)).toInt();
  currRow = index.row();
}
