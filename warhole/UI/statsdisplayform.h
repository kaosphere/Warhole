#ifndef STATSDISPLAYFORM_H
#define STATSDISPLAYFORM_H

#include <QWidget>
#include <QContextMenuEvent>
#include "game/regiment/regimentabstract.h"
#include "game/model/modelcavalry.h"
#include "game/model/modelcharacter.h"
#include "game/model/modelcharriot.h"
#include "statsdisplaywidget.h"
#include <QVBoxLayout>

namespace Ui {
class StatsDisplayForm;
}

class StatsDisplayForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit StatsDisplayForm(RegimentAbstract r, bool owned, QString owner, QWidget *parent = 0);
    ~StatsDisplayForm();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::StatsDisplayForm *ui;
};

#endif // STATSDISPLAYFORM_H
