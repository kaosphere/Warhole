#ifndef MODELWINDOW_H
#define MODELWINDOW_H

#include <QWidget>
#include <QObject>
#include <QtCore>
#include <QtWidgets>

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

private:
    Ui::ModelWindow *ui;
    QGraphicsScene* scene;
};

#endif // MODELWINDOW_H
