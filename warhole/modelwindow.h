#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include <typeinfo>

#include <option/optionmodel.h>
#include <model/modelcavalry.h>
#include <model/modelcharacter.h>
#include <model/modelcharriot.h>
#include <model/modelinfantery.h>
#include <model/modelmonster.h>
#include <model/modelwarmachine.h>
#include <model/modelfactory.h>

#include <stats/statsmodel.h>

#include <paramsfromUI/paramsfromuimodel.h>

#include"defines.h"

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
    void load(QString path);
    void fillUI(ModelAbstract *m, QString path);
    void setModelProperties(ParamsfromUImodel *p);
    void save(QString path);

private slots:
    void on_comboUnitType_currentIndexChanged(int index);
    void on_toolButtonImage_pressed();
    void on_pushButtonCancel_clicked();
    void on_addOption_clicked();
    void on_deleteOption_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonRmv_clicked();

private:
    Ui::ModelWindow *ui;
    QGraphicsScene* scene;
    QStandardItemModel* options;
    QStandardItemModel* crew;
    QPixmap* image;

    ModelCavalry* cav;
    ModelCharacter* hero;
    ModelCharriot* charriot;
    ModelInfantery* inf;
    ModelMonster* monster;
    ModelWarMachine* machine;

    ModelAbstract* poupik;

    ParamsfromUImodel* pfUI;
    ModelFactory fac;
};

#endif // MODELWINDOW_H
