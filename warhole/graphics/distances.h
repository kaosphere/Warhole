#ifndef DISTANCES_H
#define DISTANCES_H

//convert distances into pixels
#define ONE_INCH_IN_MILLIMETERS 25.4
#define ONE_MILLIMETER 3
#define ONE_INCH 75  //base conversion : one inch = 75 pixels
#define TWELVE_INCHES 12*ONE_INCH
#define ONE_FOOT TWELVE_INCHES
#define TWO_FEET ONE_FOOT*2

#define TERRAIN_Z_VALUE         1.0
#define REGIMENT_Z_VALUE        2.0
#define TEXT_Z_VALUE            3.0
#define TEMPLATE_Z_VALUE        10.0
#define RULER_Z_VALUE           11.0
#define SCATTER_Z_VALUE         12.0
#define REGIMENT_INFO_Z_VALUE   13.0

#endif // DISTANCES_H
