#include "terrainwindow.h"
#include "ui_terrainwindow.h"

#include "version.h"

using namespace QLogger;

const QString TerrainWindow::LOG_ID_INFO = "TerrainWindow_info";
const QString TerrainWindow::LOG_ID_TRACE = "TerrainWindow_trace";
const QString TerrainWindow::LOG_ID_WARN = "TerrainWindow_warm";
const QString TerrainWindow::LOG_ID_ERR = "TerrainWindow_err";


TerrainWindow::TerrainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TerrainWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    ui->setupUi(this);

    setWindowTitle("Warhole " +
                   WARHOLE_VERSION_STRING +
                   tr(" - Création de décors"));

    terrainItem = NULL;

    sceneRefresh = true;



    view = new EnhancedGraphicsView();
    view->setMinimumHeight(250);
    ui->horizontalLayout_19->addWidget(view);

    scene = new QGraphicsScene();
    view->setScene(scene);

    model = new QFileSystemModel(this);
    ui->treeViewExistingTerrains->setModel(model);
    ui->treeViewExistingTerrains->setRootIndex(model->setRootPath(TERRAIN_PATH));
    // hide size, type and date collumns
    ui->treeViewExistingTerrains->hideColumn(1);
    ui->treeViewExistingTerrains->hideColumn(2);
    ui->treeViewExistingTerrains->hideColumn(3);
}

TerrainWindow::~TerrainWindow()
{
    delete model;
    delete ui;
    delete scene;
    if(terrainItem) delete terrainItem;
}

void TerrainWindow::on_checkBox_clicked(bool checked)
{
    ui->spinBox->setEnabled(checked);
    ui->spinBox_2->setEnabled(checked);
}

void TerrainWindow::clearAllUI()
{
    sceneRefresh = false;
    ui->lineEditName->clear();
    ui->lineEditImage->clear();
    scene->clear();
    ui->spinBox->clear();
    ui->spinBox_2->clear();
    ui->checkBox->setChecked(false);
    ui->checkBoxDangerous->setChecked(false);
    ui->checkBoxSight->setChecked(false);
    ui->checkBoxUnsurmountable->setChecked(false);
    ui->textEdit->clear();
    ui->comboCover->setCurrentIndex(0);
    ui->comboType->setCurrentIndex(0);
    sceneRefresh = true;
}

void TerrainWindow::on_addButton_clicked()
{
    Terrain t;

    //TODO check valid pixmap
    if(currentPixmap.isNull() && ui->lineEditName->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Veuillez choisir une image pour le terrain."));
        return;
    }
    if(ui->comboCover->currentIndex() == 0 && ui->comboType->currentIndex() == 0)
    {
        QMessageBox::warning(this, tr("Warning"), tr("Veuillez choisir un type de terrain, et un type de couvert."));
        return;
    }

    t.setName(ui->lineEditName->text());
    t.setType((TerrainType)(ui->comboType->currentIndex() - 1)); // -1 because first index is <aucune>
    t.setCover((CoverType)(ui->comboCover->currentIndex() - 1));
    t.setSightBreaker(ui->checkBoxSight->isChecked());
    t.setDangerous(ui->checkBoxDangerous->isChecked());
    t.setSurmountable(!ui->checkBoxUnsurmountable->isChecked());
    t.setResize(ui->checkBox->isChecked());
    t.setHeigth(ui->spinBox->value());
    t.setWidth(ui->spinBox_2->value());
    t.setSpecialRules(ui->textEdit->toPlainText());
    t.setTerrainImage(currentPixmap);

    QFile f;
    QString path = TERRAIN_PATH + "/" + ui->comboType->currentText() +  + "/" + ui->lineEditName->text() + ".ter";
    f.setFileName(path);

    if(f.exists())
    {
        int rep = QMessageBox::question(this,tr("Ecraser"),
                tr("Le décor existe déjà, voulez vous l'écraser?"), QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            t.save(path);
        }
        else if (rep == QMessageBox::No)
        {
            return;
        }
    }
    else{
        t.save(path);
    }

    clearAllUI();
}

void TerrainWindow::refreshScene()
{
    scene->clear();

    // Add ruler for comparison
    RulerGraphics* r = new RulerGraphics(12, "");
    r->setPos(0,0);
    r->setZValue(1);
    scene->addItem(r);

    currentTerrain.setTerrainImage(currentPixmap);
    if(ui->checkBox->isChecked())
    {
        currentTerrain.setResize(true);
        currentTerrain.setWidth(ui->spinBox_2->value());
        currentTerrain.setHeigth(ui->spinBox->value());
    }
    else currentTerrain.setResize(false);
    terrainItem = new TerrainGraphics(currentTerrain);
    scene->addItem(terrainItem);
}

void TerrainWindow::on_toolButtonImage_clicked()
{
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir Image"),
                ".", tr("Fichiers images (*.png *.jpg *.bmp)"));

    ui->lineEditImage->setText(fileName);


    if(currentPixmap.load(fileName))
    {
        refreshScene();
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("URL de l'image non valide"));
        QLog_Info(LOG_ID_INFO, "on_toolButtonImage_pressed() : invalid image with path : " + fileName);
    }
}

void TerrainWindow::on_spinBox_valueChanged(int arg1)
{
    currentTerrain.setHeigth(arg1);
    if(terrainItem && sceneRefresh) refreshScene();
}

void TerrainWindow::on_spinBox_2_valueChanged(int arg1)
{
    currentTerrain.setWidth(arg1);
    if(terrainItem && sceneRefresh) refreshScene();
}

void TerrainWindow::on_checkBox_toggled(bool checked)
{
    currentTerrain.setResize(checked);
    if(terrainItem && sceneRefresh) refreshScene();
}

void TerrainWindow::on_treeViewExistingTerrains_clicked(const QModelIndex &index)
{
    QString name = index.data().toString();
    QStringList pieces = name.split(".");
    if(pieces.last() == "ter")
    {
        currentSelectedPath = model->filePath(index);
    }
    else currentSelectedPath = "";

    QLog_Info(LOG_ID_INFO, "on_treeViewExistingTerrains_clicked() : current selected path : " + currentSelectedPath);
}

void TerrainWindow::loadCurrentTerrainInUI()
{
    ui->lineEditName->setText(currentTerrain.getName());
    currentPixmap = currentTerrain.getTerrainImage();
    ui->spinBox->setValue(currentTerrain.getHeigth());
    ui->spinBox_2->setValue(currentTerrain.getWidth());
    ui->checkBox->setChecked(currentTerrain.getResize());
    ui->checkBoxDangerous->setChecked(currentTerrain.getDangerous());
    ui->checkBoxSight->setChecked(currentTerrain.getSightBreaker());
    ui->checkBoxUnsurmountable->setChecked(!currentTerrain.getSurmountable());
    ui->textEdit->clear();
    ui->textEdit->append(currentTerrain.getSpecialRules());
    ui->comboCover->setCurrentIndex((int)currentTerrain.getCover() + 1);    // +1 because first index is <aucune>
    ui->comboType->setCurrentIndex((int)currentTerrain.getType() + 1);
}


void TerrainWindow::on_editButton_clicked()
{
    if(currentSelectedPath.isEmpty())
        QMessageBox::warning(this, tr("warning"), tr("Veuillez sélectionner le décor à éditer"));
    else
    {
        currentTerrain.load(currentSelectedPath);
        loadCurrentTerrainInUI();
        refreshScene();
    }
}

void TerrainWindow::on_removeButton_clicked()
{
    QItemSelectionModel *selection = ui->treeViewExistingTerrains->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();

    if(indexElementSelectionne.isValid())
    {
        int rep = QMessageBox::question(this,tr("Effacer"),
                                        tr("Voulez-vous vraiment effacer ce décor ?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (rep == QMessageBox::Yes)
        {
            QFile f;
            f.setFileName(model->filePath(indexElementSelectionne));
            f.remove();
        }
        else if (rep == QMessageBox::No)
        {
            QMessageBox::critical(this, tr("Annulation"), tr("Opération annulée"));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Info"), tr("Veuillez sélectionner un régiment a supprimer."));
    }
}
