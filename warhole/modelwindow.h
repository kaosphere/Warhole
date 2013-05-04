#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "option/optionmodel.h"

namespace Ui {
class ModelWindow;
}

class ModelWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit ModelWindow(QWidget *parent = 0);
    ~ModelWindow();

    void loadAnimalWidget();
    void loadCavaleryWidget();
    void loadCharacterWidget();
    void loadCharriotWidget();
    void loadInfanteryWidget();
    void loadMonsterWidget();
    void loadWarMachineWidget();
    
private slots:
    void on_comboUnitType_currentIndexChanged(int index);
    void on_toolButtonImage_pressed();
    void on_pushButtonCancel_clicked();
    void on_addOption_clicked();

    void on_deleteOption_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::ModelWindow *ui;
    QGraphicsScene* scene;
    QStandardItemModel* options;
    QPixmap* image;
};

#endif // MODELWINDOW_H
