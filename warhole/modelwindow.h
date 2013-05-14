#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "option/optionmodel.h"
#include "model/modelanimal.h"

namespace Ui {
class ModelWindow;
}

class ModelWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit ModelWindow(QWidget *parent = 0);
    ModelWindow(QString f, QWidget *parent = 0);
    ~ModelWindow();

    void loadAnimalWidget();
    void loadCavaleryWidget();
    void loadCharacterWidget();
    void loadCharriotWidget();
    void loadInfanteryWidget();
    void loadMonsterWidget();
    void loadWarMachineWidget();
    void loadWidgets(bool l);

private slots:
    void on_comboUnitType_currentIndexChanged(int index);
    void on_toolButtonImage_pressed();
    void on_pushButtonCancel_clicked();
    void on_addOption_clicked();

    void on_deleteOption_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonLoad_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonAdd_2_clicked();

private:
    Ui::ModelWindow *ui;
    QGraphicsScene* scene;
    QStandardItemModel* options;
    QStandardItemModel* crew;
    QPixmap* image;
    ModelAbstract* model;
};

#endif // MODELWINDOW_H
