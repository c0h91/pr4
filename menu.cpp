#include "menu.h"
#include <QPushButton>
#include <QGridLayout>
#include "playwidget.h"
#include "settingwidget.h"
#include "recordwidget.h"
#include <QMessageBox>
#include "recordsprocess.h"
#include <qDebug>

Menu::Menu() : QWidget(nullptr), recordsProcess(RecordsProcess::instance()) {
    setWindowTitle("Меню");
    setMinimumSize(240, 70);

    play = new QPushButton("Играть", this);
    setting = new QPushButton("Настройки", this);
    records = new QPushButton("Статистика", this);

    QGridLayout *my_layout = new QGridLayout(this);
    this->setLayout(my_layout);
    my_layout->addWidget(play, 0, 0);
    my_layout->addWidget(setting, 1, 0);
    my_layout->addWidget(records, 2, 0);

    connect(play, SIGNAL(clicked(bool)), this, SLOT(playClicked()));
    connect(setting, SIGNAL(clicked(bool)), this, SLOT(settingsClicked()));
    connect(records, SIGNAL(clicked(bool)), this, SLOT(showRecords()));
}

void Menu::playClicked() {
    PlayWidget* playWidget = PlayWidget::instance();
    if (!playWidget->isVisible()) {
        playWidget->show();
    } else {
        playWidget->raise();
        playWidget->activateWindow();
    }
}

void Menu::settingsClicked() {
    SettingWidget* settingsWidget = SettingWidget::instance();

    connect(settingsWidget, &SettingWidget::recordPathChanged, this, &Menu::updateRecordPath, Qt::UniqueConnection);

    if (recordWidget) {
        connect(settingsWidget, &SettingWidget::recordPathChanged, recordWidget, &RecordWidget::loadRecords, Qt::UniqueConnection);
    }

    settingsWidget->show();
}

void Menu::updateRecordPath(const QString& path) {
    recordsProcess->setFilePath(path);

    if (recordWidget) {
        recordWidget->loadRecords(path);
    }
}

void Menu::showRecords() {
    QString recordPath = recordsProcess->getFilePath();
    //qDebug() << "Record path: " << recordPath;

    if (recordPath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Путь к статистике не задан.");
        return;
    }

    if (!recordWidget) {
        recordWidget = new RecordWidget();
        recordWidget->setAttribute(Qt::WA_DeleteOnClose, false);
    }

    recordWidget->updateRecordPath(recordPath);

    if (!recordWidget->isVisible()) {
        recordWidget->show();
    } else {
        recordWidget->raise();
        recordWidget->activateWindow();
    }
}

void Menu::addRecordClicked() {
    if (!recordWidget) {
        recordWidget = new RecordWidget();
        recordWidget->setAttribute(Qt::WA_DeleteOnClose, false);
    }

    recordWidget->show();
}
