#ifndef REGIMENTGRAPHICS_H
#define REGIMENTGRAPHICS_H

#include <QGraphicsObject>
#include <QKeyEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QKeyEvent>
#include <QCursor>

#include "modelgraphics.h"
#include "distances.h"
#include "game/regiment/regimentabstract.h"
#include "Utilities/QLogger/QLogger.h"
#include "getintdialog.h"
#include "statsdisplayform.h"
#include "regimentinfodialog.h"

class RegimentGraphics : public QGraphicsObject
{
    Q_OBJECT
public:
    RegimentGraphics(QGraphicsItem* parent = 0);
    RegimentGraphics(const RegimentAbstract& r, bool isOwnedByMe, QGraphicsItem* parent = 0);
    virtual ~RegimentGraphics();

    void initModels();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    RegimentAbstract getRegiment() const;
    void setRegiment(const RegimentAbstract &value);

    virtual QPainterPath shape() const;
    QString getRegimentID() const;
    void setRegimentID(QString value);

    QString getOwner() const;
    void setOwner(const QString &value);

    bool getIsOwnedByMe() const;
    void setIsOwnedByMe(bool value);

    void removeDeads(int nb);

    int getRegimentWidth() const;
    void setRegimentWidth(int value);

    void updateChildrenPositions();
    void addModels(int nb);
    
    QDataStream& serializeOut(QDataStream& out);
    QDataStream& serializeIn(QDataStream& in);
    
    friend QDataStream& operator<<(QDataStream& out, const RegimentGraphics& obj);
    friend QDataStream& operator>>(QDataStream& in, RegimentGraphics& obj);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private slots:
    void updateOwnership();
    void removeRegimentRequest();
    void removeDeadRequest();
    void changeRegimentWidthRequest();
    void addModelRequest();
    void changeRegimentInfoRequest();
    void closeInfoRect();

private:
    void initRegimentGraphics();
    void updateChildrenBrushes();

    void paintClassicRegiment(QPainter *painter);
    void paintSkirmishRegiment(QPainter *painter);

    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    static const int DEFAULT_REGIMENT_WIDTH;

    bool initialized;
    bool hasImage;
    bool rot;
    bool firstRot;

    RegimentAbstract regiment;

    //! regimentWidth.
    /*!
    * Stores the number of models wide of the regiment to be displayed.
    * Default value is 5 models wide.
    */
    int regimentWidth;

    QString owner;

    bool isOwnedByMe;

    QList<ModelGraphics*> models;

    QPen* childrenPen;

    QBrush childrenBrush;

    QString regimentID;

    QAction* actionRemoveRegiment;
    QAction* actionChangeRegimentWidth;
    QAction* actionRemoveDeads;
    QAction* actionAddModels;
    QAction* actionChangeRegInfo;
    QAction* actionShowStats;

    QGraphicsRectItem* infoRect;

private slots:
    void updateRegiment();
    void showStats();

signals:

    void removeRegimentRequest(QString);
    void removeDeadsRequest(QString, int);
    void changeWidthRequest(QString, int);
    void addModelRequest(QString, int);
    void changeRegimentInfoRequest(QString, RegimentAbstract);
    void showStats(RegimentAbstract);
    void ownerChanged();

    //! regimentDataChanged.
    /*!
    * This signal is sent when a value has changed in the regiment.
    */
    void regimentDataChanged();

    //! regimentMoved.
    /*!
    * This signal is sent when the graphic regiment is moved.
    */
    void regimentMoved(QString, QPointF, QTransform);

    //! regimentUpdated.
    /*!
    * This signal is casted when a new regiment is set in place of the previous
    * one. This signal is different from regimentDataChanged() because we don't
    * want to repaint the graphical object each time we change a value in the regiment.
    * But when a new regiment is set, it means that the display has to be updated.
    */
    void regimentUpdated();

};

#endif // REGIMENTGRAPHICS_H
