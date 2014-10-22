#ifndef TERRAIN_H
#define TERRAIN_H

#include <QObject>
#include <QtCore>

enum TerrainType{
	FOREST = 0, 
	RIVER,
	OBSTACLE,
	BUILDING,
	HILL,
	CLIFF,
	MARSHES,
	OTHER
}

enum CoverType{
	NO_COVER = 0,
	LIGHT_COVER,
	HEAVY_COVER
}

class Terrain : public QObject
{
	Q_OBJECT

public:
	explicit Terrain();
	virtual ~Terrain();

	friend QDataStream operator<<(QDataStream& out, const Terrain& obj);
	friend QDataStream operator>>(QDataStream& in, Terrain& obj);

private:
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
};

#endif	//TERRAIN_H
