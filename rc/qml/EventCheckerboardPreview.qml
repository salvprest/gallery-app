/*
 * Copyright (C) 2012 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 * Jim Nelson <jim@yorba.org>
 * Charles Lindsay <chaz@yorba.org>
 */

import QtQuick 1.1
import Gallery 1.0

Item {
  property alias ownerName: photo.ownerName
  property alias event: eventCard.event
  property alias mediaSource: photo.mediaSource
  property alias eventMediaCount: eventCard.mediaCount
  
  MattedPhotoPreview {
    id: photo
    
    anchors.fill: parent
    
    visible: (mediaSource) ? true : false
  }
  
  EventCard {
    id: eventCard
    
    anchors.fill: parent
    
    visible: (event) ? true : false
  }
}
