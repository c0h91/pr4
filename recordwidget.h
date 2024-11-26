#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include <QTableWidget>

class RecordWidget : public QWidget {
    Q_OBJECT
public:
    explicit RecordWidget(QWidget* parent = nullptr);

    void loadRecords(const QString& filePath);

public slots:
    void updateRecordPath(const QString& newPath);
    void updateTable(const QStringList& records);
    void updateRecords();

private:
    QTableWidget* table;
    QString currentFilePath;
};

#endif // RECORDWIDGET_H
