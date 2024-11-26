#include "playwidget.h"
#include <QLabel>
#include <QGridLayout>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <recordsprocess.h>

PlayWidget* PlayWidget::instance() {
    static PlayWidget* instance = new PlayWidget();
    return instance;
}

PlayWidget::PlayWidget() : QWidget(nullptr) {
    setWindowTitle("Игра");

    QGridLayout* my_layout = new QGridLayout(this);
    setLayout(my_layout);
    setMinimumSize(300, 200);

    QLabel *nameLabel = new QLabel("Ваше имя: ", this);
    nameEdit = new QLineEdit(this);
    QLabel *scoreLabel = new QLabel("Ваши очки: ", this);
    scoreEdit = new QLineEdit(this);
    saveButton = new QPushButton("Ок", this);

    my_layout->addWidget(nameLabel, 0, 0);
    my_layout->addWidget(nameEdit, 0, 1);
    my_layout->addWidget(scoreLabel, 2, 0);
    my_layout->addWidget(scoreEdit, 2, 1);
    my_layout->addWidget(saveButton, 3, 2, 1, 2);

    connect(saveButton, &QPushButton::clicked, this, &PlayWidget::saveRecord);
}

void PlayWidget::saveRecord() {
    QString name = nameEdit->text();
    QString score = scoreEdit->text();

    if (name.isEmpty() || score.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите все данные");
        return;
    }

    QString recordPath = RecordsProcess::instance()->getFilePath();
    if (recordPath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Путь к файлу статистики не задан");
        return;
    }

    RecordsProcess::instance()->saveRecord(name, score);

    nameEdit->clear();
    scoreEdit->clear();
    emit RecordsProcess::instance()->recordsUpdated();
}
