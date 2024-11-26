#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <recordwidget.h>
#include <recordsprocess.h>

class Menu : public QWidget {
    Q_OBJECT
public:
    Menu();

public slots:
    void playClicked();
    void settingsClicked();
    void updateRecordPath(const QString& path);
    void showRecords();
    void addRecordClicked();

private:
    RecordsProcess* recordsProcess; // Экземпляр для управления записями
    QPushButton *play;
    QPushButton *setting;
    QPushButton *records;
    QString recordPath;
    RecordWidget* recordWidget = nullptr;
};

#endif // MENU_H
