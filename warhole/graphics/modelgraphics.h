#ifndef MODELGRAPHICS_H
#define MODELGRAPHICS_H

#include <QGraphicsRectItem>


//! ModelGraphics class
/*!
* This class inheritates QGraphicsRectItem and enhance it with
* the name of the model that it's represented.
*/
class ModelGraphics : public QGraphicsRectItem
{
public:
    ModelGraphics(QGraphicsItem *parent = 0);
    ModelGraphics(int x, int y, int w, int h, QString n, QGraphicsItem *parent = 0);

    virtual ~ModelGraphics();

    QString getModelName() const;
    void setModelName(const QString &value);

private:
    QString modelName;
};

#endif // MODELGRAPHICS_H
