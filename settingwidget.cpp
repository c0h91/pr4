#include "settingwidget.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include "recordsprocess.h"

SettingWidget* SettingWidget::instance() {
    static SettingWidget* instance = new SettingWidget();
    return instance;
}

SettingWidget::SettingWidget() : QWidget(nullptr) {
    setWindowTitle("Настройки");

    QGridLayout* my_layout = new QGridLayout(this);
    setLayout(my_layout);

    QLabel *enterPath = new QLabel("Путь к таблице рекордов: ", this);
    pathLineEdit = new QLineEdit(this);
    pathLineEdit->setText(RecordsProcess::instance()->getFilePath());

    QPushButton *saveButton = new QPushButton("Сохранить", this);

    my_layout->addWidget(enterPath, 0, 0);
    my_layout->addWidget(pathLineEdit, 0, 1);
    my_layout->addWidget(saveButton, 1, 0, 1, 2);

    connect(saveButton, &QPushButton::clicked, this, &SettingWidget::savePressed);
}

void SettingWidget::savePressed() {
    QString filePath = pathLineEdit->text();

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Путь к файлу не указан");
        return;
    }

    QFileInfo fileInfo(filePath);

    if (!fileInfo.exists()) {
        QMessageBox::warning(this, "Ошибка", "Указанный путь не существует");
        return;
    }

    if (fileInfo.suffix() != "txt") {
        QMessageBox::warning(this, "Ошибка", "Неправильный формат файла. Ожидается файл с расширением .txt");
        return;
    }

    RecordsProcess::instance()->setFilePath(filePath);
    this->close();
}
