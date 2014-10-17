#include "statsdisplaywidget.h"
#include "ui_statsdisplaywidget.h"

StatsDisplayWidget::StatsDisplayWidget(StatsModel s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsDisplayWidget)
{
    ui->setupUi(this);

    ui->title->setText(s.getName());

    ui->labelModelM2->setText(s.getM());
    ui->labelModelBS2->setText(s.getBs());
    ui->labelModelWS2->setText(s.getWs());
    ui->labelModelA2->setText(s.getA());
    ui->labelModelI2->setText(s.getI());
    ui->labelModelLd2->setText(s.getLd());
    ui->labelModelT2->setText(s.getT());
    ui->labelModelS2->setText(s.getS());
    ui->labelModelW2->setText(s.getW());
    ui->labelChampionPts->setText(QString::number(s.getPoints()));
}

StatsDisplayWidget::~StatsDisplayWidget()
{
    delete ui;
}
