#include "statsdisplayform.h"
#include "ui_statsdisplayform.h"

StatsDisplayForm::StatsDisplayForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsDisplayForm)
{
    ui->setupUi(this);
}

StatsDisplayForm::~StatsDisplayForm()
{
    delete ui;
}
