/*
* Copyright (c), 2014
* -  Alexandre Jumeline
* -  Perrine Fauconnier
* All rights reserved.
*
* This file is part of Warhole.
*
* Warhole is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* Warhole is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Warhole.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VERSION_H
#define VERSION_H

#include <QString>

const int WARHOLE_MAJOR_VERSION(1);
const int WARHOLE_MINOR_VERSION(1);
const int WARHOLE_BUILD_NUMBER(2);
const QString WARHOLE_BUILD_SPECIAL_MENTION("Dev");

const QString WARHOLE_VERSION_STRING("v" +
                                     QString::number(WARHOLE_MAJOR_VERSION) + "." +
                                     QString::number(WARHOLE_MINOR_VERSION) + "." +
                                     QString::number(WARHOLE_BUILD_NUMBER) + "-" +
                                     WARHOLE_BUILD_SPECIAL_MENTION);

const QString WARHOLE_WIKI_URL("https://github.com/kaosphere/Warhole/wiki");

#endif // VERSION_H
