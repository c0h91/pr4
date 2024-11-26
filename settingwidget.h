#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QLineEdit>

class SettingWidget : public QWidget {
    Q_OBJECT
public:
    static SettingWidget* instance();

signals:
    void recordPathChanged(const QString& path);

public slots:
    void savePressed();

private:
    SettingWidget();
    QLineEdit *pathLineEdit;

    SettingWidget(const SettingWidget&) = delete;
    SettingWidget& operator=(const SettingWidget&) = delete;
};

#endif // SETTINGWIDGET_H
