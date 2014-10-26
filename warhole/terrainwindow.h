#ifndef TERRAINWINDOW_H
#define TERRAINWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <QFileDialog>

#include "Utilities/QLogger/QLogger.h"
#include "defines.h"
#include "game/terrain/terrain.h"
#include "graphics/enhancedgraphicsview.h"
#include "graphics/rulergraphics.h"
#include "graphics/terraingraphics.h"

namespace Ui {
class TerrainWindow;
}

class TerrainWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit TerrainWindow(QWidget *parent = 0);
    ~TerrainWindow();

    void refreshScene();
    void clearAllUI();
    void loadCurrentTerrainInUI();

private slots:
    void on_checkBox_clicked(bool checked);
    void on_addButton_clicked();
    void on_toolButtonImage_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg1);
    void on_checkBox_toggled(bool checked);
    void on_treeViewExistingTerrains_clicked(const QModelIndex &index);

    void on_editButton_clicked();

    void on_removeButton_clicked();

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    bool sceneRefresh;
    Ui::TerrainWindow *ui;
    QFileSystemModel* model;
    QStandardItemModel* terrains;
    QPixmap currentPixmap;
    Terrain currentTerrain;
    QGraphicsScene* scene;
    TerrainGraphics* terrainItem;
    EnhancedGraphicsView* view;
    QString currentSelectedPath;
};

#endif // TERRAINWINDOW_H
