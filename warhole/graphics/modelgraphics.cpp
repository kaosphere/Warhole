#include "modelgraphics.h"

ModelGraphics::ModelGraphics(QGraphicsItem* parent):
    QGraphicsRectItem(parent)
{
}

ModelGraphics::ModelGraphics(int x, int y, int w, int h, QString n,QGraphicsItem* parent):
    QGraphicsRectItem(x,y,w,h,parent)
{
    modelName = n;
}

ModelGraphics::~ModelGraphics()
{

}

QString ModelGraphics::getModelName() const
{
    return modelName;
}

void ModelGraphics::setModelName(const QString &value)
{
    modelName = value;
}

