#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class PlayWidget : public QWidget {
    Q_OBJECT

public:
     static PlayWidget* instance();

public slots:
    void saveRecord();

private:
    PlayWidget();

    PlayWidget(const PlayWidget&) = delete;
    PlayWidget& operator=(const PlayWidget&) = delete;

    QLineEdit recordPath;
    QLineEdit *nameEdit;
    QLineEdit *scoreEdit;
    QPushButton *saveButton;
};

#endif // PLAYWIDGET_H
