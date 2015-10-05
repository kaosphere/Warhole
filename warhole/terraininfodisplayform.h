#ifndef TERRAININFODISPLAYFORM_H
#define TERRAININFODISPLAYFORM_H

#include <QWidget>
#include <game/terrain/terrain.h>

namespace Ui {
class TerrainInfoDisplayForm;
}

class TerrainInfoDisplayForm : public QWidget
{
    Q_OBJECT

public:
    explicit TerrainInfoDisplayForm(Terrain t, QWidget *parent = 0);
    ~TerrainInfoDisplayForm();

    Terrain getT() const;
    void setT(const Terrain &value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::TerrainInfoDisplayForm *ui;
    Terrain ter;
};

#endif // TERRAININFODISPLAYFORM_H
