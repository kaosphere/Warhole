#ifndef STATSDISPLAYFORM_H
#define STATSDISPLAYFORM_H

#include <QWidget>

namespace Ui {
class StatsDisplayForm;
}

class StatsDisplayForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit StatsDisplayForm(QWidget *parent = 0);
    ~StatsDisplayForm();
    
private:
    Ui::StatsDisplayForm *ui;
};

#endif // STATSDISPLAYFORM_H
