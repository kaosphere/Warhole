#include "warholeinfodialog.h"
#include "ui_warholeinfodialog.h"

#include <QFile>
#include <QTextStream>
#include <QTextCursor>
#include "version.h"

WarholeInfoDialog::WarholeInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarholeInfoDialog)
{
    ui->setupUi(this);

    setWindowTitle("Warhole " +
                   WARHOLE_VERSION_STRING +
                   tr(" - Infos"));

    // Fill dev info
    QString info;

    info = "Warhole " + WARHOLE_VERSION_STRING + "\n\n" +
            "Developped By : \n" +
            "Alexandre Jumeline\n" +
            "Perrine Fauconnier\n\n";

    ui->label->setText(info);


    // Fill license
    QFile data(":/text/ressources/license.txt");
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        while ( !in.atEnd() )
       {
          QString line = in.readLine();
          ui->textEdit->append(line);
       }
    }
    QTextCursor tmpCursor = ui->textEdit->textCursor();
    tmpCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor(tmpCursor);
}

WarholeInfoDialog::~WarholeInfoDialog()
{
    delete ui;
}
