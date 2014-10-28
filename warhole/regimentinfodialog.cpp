#include "regimentinfodialog.h"
#include "ui_regimentinfodialog.h"

RegimentInfoDialog::RegimentInfoDialog(RegimentAbstract* reg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegimentInfoDialog)
{
    ui->setupUi(this);

    r = reg;

    ui->checkBox->setChecked(r->getSkirmishers());
    ui->textEdit->append(r->getGroups().first().getModel()->getSpecialRules());
}

RegimentInfoDialog::~RegimentInfoDialog()
{
    delete ui;
}

RegimentAbstract *&RegimentInfoDialog::getR()
{
    return r;
}

void RegimentInfoDialog::setR(RegimentAbstract *value)
{
    r = value;
}

void RegimentInfoDialog::accept()
{
    r->setSkirmishers(ui->checkBox->isChecked());
    r->getGroups().first().getModel()->setSpecialRules(ui->textEdit->toPlainText());
    QDialog::accept();
}

