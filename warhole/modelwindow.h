#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include <typeinfo>

#include <game/option/optionmodel.h>
#include <game/model/modelcavalry.h>
#include <game/model/modelcharacter.h>
#include <game/model/modelcharriot.h>
#include <game/model/modelinfantery.h>
#include <game/model/modelmonster.h>
#include <game/model/modelwarmachine.h>
#include <game/model/modelfactory.h>

#include <game/stats/statsmodel.h>

#include <game/paramsfromUI/paramsfromuimodel.h>
#include <Utilities/QLogger/QLogger.h>

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

    void enableChampionUI(bool b);
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
    void on_addOption_2_clicked();
    void on_deleteOption_2_clicked();
    void closeEvent(QCloseEvent*);

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    Ui::ModelWindow *ui;
    QGraphicsScene* scene;
    QStandardItemModel* options;
    QStandardItemModel* regOptions;
    QStandardItemModel* crew;
    QPixmap* image;

    ModelCavalry* cav;
    ModelCharacter* hero;
    ModelCharriot* charriot;
    ModelInfantery* inf;
    ModelMonster* monster;
    ModelWarMachine* machine;

    ModelAbstract* poupik = NULL;

    ParamsfromUImodel* pfUI;
    ModelFactory fac;

    static const QStringList OPTION_HEADER;
};

#endif // MODELWINDOW_H
