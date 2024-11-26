#include "recordsprocess.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

QString RecordsProcess::getFilePath() const {
    return filePath;
}

void RecordsProcess::setFilePath(const QString& newPath) {
    if (filePath != newPath) {
        filePath = newPath;

        emit recordPathChanged(filePath);
    }
}

QStringList RecordsProcess::loadRecords() const {
    QStringList records;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            records.append(in.readLine());
        }
        file.close();
    }
    return records;
}

void RecordsProcess::saveRecord(const QString& name, const QString& score) {
    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "\n" << name << " " << score;
        file.close();
    }
}
