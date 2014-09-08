#ifndef MAGICALOBJECTWINDOW_H
#define MAGICALOBJECTWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <QDir>

#include "defines.h"
#include "Utilities/QLogger/QLogger.h"

namespace Ui {
class MagicalObjectWindow;
}

class MagicalObjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MagicalObjectWindow(QWidget *parent = 0);
    ~MagicalObjectWindow();

private slots:
    void on_comboRace_currentTextChanged(const QString &raceDir);

private:
    Ui::MagicalObjectWindow *ui;
    QFileSystemModel *model;

    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;
};

#endif // MAGICALOBJECTWINDOW_H
