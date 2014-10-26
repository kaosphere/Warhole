#ifndef TERRAIN_H
#define TERRAIN_H

#include <QObject>
#include <QtCore>
#include <QPixmap>

#include "defines.h"
#include "Utilities/QLogger/QLogger.h"

enum TerrainType{
    FOREST = 0,
    RIVER,
    OBSTACLE,
    BUILDING,
    HILL,
    CLIFF,
    MARSHES,
    OTHER
};

enum CoverType{
    NO_COVER = 0,
    LIGHT_COVER,
    HEAVY_COVER
};

class Terrain : public QObject
{
	Q_OBJECT

public:
    explicit Terrain(QObject* parent = 0);
    Terrain(const Terrain& other, QObject* parent = 0);
    Terrain(QString n, TerrainType t, CoverType c,
            bool sb, bool d, bool s, bool r,
            int w, int h, QPixmap i, QString sr,
            QObject* parent = 0);
	virtual ~Terrain();

    friend QDataStream& operator<<(QDataStream& out, const Terrain& obj);
    friend QDataStream& operator>>(QDataStream& in, Terrain& obj);

    QString getName() const;
    void setName(const QString &value);

    TerrainType getType() const;
    void setType(const TerrainType &value);

    CoverType getCover() const;
    void setCover(const CoverType &value);

    bool getSightBreaker() const;
    void setSightBreaker(bool value);

    bool getDangerous() const;
    void setDangerous(bool value);

    bool getSurmountable() const;
    void setSurmountable(bool value);

    QPixmap getTerrainImage() const;
    void setTerrainImage(const QPixmap &value);

    bool getResize() const;
    void setResize(bool value);

    int getWidth() const;
    void setWidth(int value);

    int getHeigth() const;
    void setHeigth(int value);

    Terrain &operator =(const Terrain &other);
    bool operator==(const Terrain& other);

    static void initTerrainSystem();
    void save(QString path);
    void load(QString path);

    QString displayString();
    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    QString name;
    TerrainType type;
    CoverType cover;
    bool sightBreaker;
	bool dangerous;
	bool surmountable;
	QPixmap terrainImage;
	bool resize;
	int width;
	int heigth;
    QString specialRules;
};

Q_DECLARE_METATYPE(Terrain)

#endif	//TERRAIN_H
