#ifndef MAGICALOBJECTWINDOW_H
#define MAGICALOBJECTWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <QDir>

#include "defines.h"
#include "game/magicalObject/magicalobject.h"
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

    void updateTreeView(QString raceDir);
    void clearWindow();

private slots:
    void on_comboRace_currentTextChanged(const QString &raceDir);
    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_editButton_clicked();

private:
    Ui::MagicalObjectWindow *ui;
    QFileSystemModel *model;
    QList<MagicalObject> objectList;
    QStandardItemModel* objects;

    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    static const QStringList OBJECT_HEADER;
};

#endif // MAGICALOBJECTWINDOW_H
