#include "terraininfodisplayform.h"
#include "ui_terraininfodisplayform.h"
#include <QVBoxLayout>


TerrainInfoDisplayForm::TerrainInfoDisplayForm(Terrain t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TerrainInfoDisplayForm)
{
    ui->setupUi(this);

    ter = t;
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(ui->pushButton);
    layout->addWidget(ui->label);

    QString info;

    info.append(ter.getName() + "\n");
    switch(ter.getType())
    {
    case FOREST:
        info.append(tr("Forêt\n\n"));
        break;
    case RIVER:
        info.append(tr("Rivière\n\n"));
        break;
    case OBSTACLE:
        info.append(tr("Obstacle\n\n"));
        break;
    case BUILDING:
        info.append(tr("Bâtiment\n\n"));
        break;
    case HILL:
        info.append(tr("Colline\n\n"));
        break;
    case CLIFF:
        info.append(tr("Falaise\n\n"));
        break;
    case MARSHES:
        info.append(tr("Marais\n\n"));
        break;
    case OTHER:
        info.append(tr("Autre\n\n"));
        break;
    default:
        break;
    }

    switch(ter.getCover())
    {
    case NO_COVER:
        info.append(tr("Pas de couvert\n"));
        break;
    case LIGHT_COVER:
        info.append(tr("Couvert léger\n"));
        break;
    case HEAVY_COVER:
        info.append(tr("Couvert lourd\n"));
        break;
    default:
        break;
    }

    if(ter.getDangerous()) info.append(tr("Terrain dangereux\n"));

    if(ter.getSightBreaker()) info.append(tr("Bloque les lignes de vue\n"));
    else info.append(tr("Ne bloque pas les lignes de vue\n"));

    if(!ter.getSurmountable()) info.append(tr("Terrain infranchissable\n"));

    info.append(ter.getSpecialRules());

    ui->label->setText(info);
}

TerrainInfoDisplayForm::~TerrainInfoDisplayForm()
{
    delete ui;
}

Terrain TerrainInfoDisplayForm::getT() const
{
    return ter;
}

void TerrainInfoDisplayForm::setT(const Terrain &value)
{
    ter = value;
}

void TerrainInfoDisplayForm::on_pushButton_clicked()
{
    this->deleteLater();
}
