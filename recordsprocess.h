#ifndef RECORDSPROCESS_H
#define RECORDSPROCESS_H

#include <QObject>
#include <QString>
#include <QStringList>

class RecordsProcess : public QObject {
    Q_OBJECT
public:
    static RecordsProcess* instance() {
        static RecordsProcess instance;
        return &instance;
    }

    QString getFilePath() const;
    void setFilePath(const QString& newPath);

    QStringList loadRecords() const;
    void saveRecord(const QString& name, const QString& score);

signals:
    void recordPathChanged(const QString& newPath);
    void recordsUpdated();

private:
    RecordsProcess() {}
    ~RecordsProcess() {}
    QString filePath = "C:/pr4/stats.txt";
};

#endif // RECORDSPROCESS_H
