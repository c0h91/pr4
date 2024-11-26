#include "recordwidget.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "recordsprocess.h"
#include <QHeaderView>

RecordWidget::RecordWidget(QWidget* parent)
    : QWidget(parent), table(new QTableWidget(this)) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(table);
    setLayout(layout);
    setMinimumSize(400, 300);

    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    table->setColumnCount(0);
    table->setRowCount(0);
    table->setHorizontalHeaderLabels(QStringList());

    connect(RecordsProcess::instance(), &RecordsProcess::recordPathChanged, this, &RecordWidget::updateRecordPath);
    connect(RecordsProcess::instance(), &RecordsProcess::recordsUpdated, this, &RecordWidget::updateRecords);
}

void RecordWidget::loadRecords(const QString& filePath) {
    QFile file(filePath);

    if (!file.exists()) {
        QMessageBox::warning(this, "Ошибка", "Файл не существует.");
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл с рекордами.");
        return;
    }

    QTextStream in(&file);
    QString header = in.readLine();

    if (header.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл пуст или имеет неверный формат.");
        file.close();
        return;
    }

    QStringList headers = header.split(" ");
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);

    table->setRowCount(0);
    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList data = line.split(" ");

        if (data.size() != headers.size()) {
            QMessageBox::warning(this, "Ошибка", "Некорректная строка в файле: " + line);
            continue;
        }

        table->insertRow(row);
        for (int col = 0; col < data.size(); ++col) {
            table->setItem(row, col, new QTableWidgetItem(data[col]));
        }
        ++row;
    }

    file.close();

    table->resizeColumnsToContents();
    table->resizeRowsToContents();
}

void RecordWidget::updateRecordPath(const QString& newPath) {
    currentFilePath = newPath;
    loadRecords(newPath);
}

void RecordWidget::updateRecords() {
    QStringList records = RecordsProcess::instance()->loadRecords();
    updateTable(records);
}

void RecordWidget::updateTable(const QStringList& records) {
    QTableWidget *table = this->table;

    QStringList recordData = records.last().split(" ");

    QString name = recordData[0];
    QString score = recordData[1];

    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row, 0, new QTableWidgetItem(name));
    table->setItem(row, 1, new QTableWidgetItem(score));

    table->resizeColumnsToContents();
    table->resizeRowsToContents();
}
