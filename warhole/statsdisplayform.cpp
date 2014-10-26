#include "statsdisplayform.h"
#include "ui_statsdisplayform.h"

StatsDisplayForm::StatsDisplayForm(RegimentAbstract r, bool owned, QString owner, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsDisplayForm)
{
    ui->setupUi(this);

    ModelAbstract* m = r.getGroups().first().getModel();

    QVBoxLayout* v = new QVBoxLayout(this);
    StatsDisplayWidget* w1 = new StatsDisplayWidget(m->getStats());
    v->addWidget(ui->pushButton);
    v->addWidget(w1);
    if(m->getChampion())
    {
        StatsDisplayWidget* w2 = new StatsDisplayWidget(m->getChampionStats());
        v->addWidget(w2);
    }
    v->addWidget(ui->label);

    QString text;
    text.append("Appartient à : " + owner + "\n\n");

    if(r.getGroups().first().getModel()->getMusician())
        text.append(tr("Musicien\n"));
    if(r.getGroups().first().getModel()->getBanner())
        text.append(tr("Étandard\n"));
    if(r.getGroups().first().getModel()->getChampion())
        text.append(tr("Champion\n"));

    if(owned)
    {
        text.append(tr("Options : \n"));
        for(int i = 0; i< m->getOptions().size(); ++i)
        {
            if(m->getOptions().at(i).isActivated())
            {
                text.append("- ");
                text.append(m->getOptions()[i].displayString());
            }
        }
        if(!r.getGroups().first().getObjects().isEmpty())
        {
            text.append("\nObjets magiques : \n");
            for(int i = 0; i<r.getGroups().first().getObjects().size(); ++i)
            {
                text.append("- ");
                text.append(r.getGroups().first().getObjects().at(i).displayString());
            }
        }
    }
    text.append("\n" + m->getSpecialRules());
    ui->label->setText(text);
}

StatsDisplayForm::~StatsDisplayForm()
{
    delete ui;
}

void StatsDisplayForm::on_pushButton_clicked()
{
    this->deleteLater();
}
