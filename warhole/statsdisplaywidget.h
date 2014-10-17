#ifndef STATSDISPLAYWIDGET_H
#define STATSDISPLAYWIDGET_H

#include <QWidget>
#include "game/stats/statsmodel.h"

namespace Ui {
class StatsDisplayWidget;
}

class StatsDisplayWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit StatsDisplayWidget(StatsModel s, QWidget *parent = 0);
    ~StatsDisplayWidget();
    
private:
    Ui::StatsDisplayWidget *ui;
};

#endif // STATSDISPLAYWIDGET_H
