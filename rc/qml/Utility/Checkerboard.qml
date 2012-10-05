/*
 * Copyright (C) 2011 Canonical Ltd
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
 * Lucas Beeler <lucas@yorba.org>
 * Charles Lindsay <chaz@yorba.org>
 */

import QtQuick 2.0
import "../../js/Gallery.js" as Gallery
import "../../js/GalleryUtility.js" as GalleryUtility

Item {
  id: checkerboard
  
  signal activated(variant object, variant objectModel, variant activatedRect)
  
  signal movementStarted()
  signal movementEnded()
  
  property alias model: grid.model
  property alias delegate: grid.delegate

  property alias contentX: grid.contentX
  property alias contentY: grid.contentY
  property alias footer: grid.footer
  
  property real itemWidth: Gallery.getDeviceSpecific('photoThumbnailWidth')
  property real itemHeight: Gallery.getDeviceSpecific('photoThumbnailHeight')
  property real minGutterWidth: Gallery.getDeviceSpecific('photoGridGutterWidth')
  property real minGutterHeight: Gallery.getDeviceSpecific('photoGridGutterHeight')
  property real topExtraGutter: 0
  property real bottomExtraGutter: 0
  property real leftExtraGutter: 0
  property real rightExtraGutter: 0
  
  property bool allowActivation: true
  property bool inSelectionMode: false
  property bool allowSelectionModeChange: true
  property bool singleSelectionOnly: false // Enforces always exactly one selected.
  property int selectedCount: (model) ? model.selectedCount : 0
  
  // readonly
  property variant singleSelectedItem // Only if singleSelectionOnly is true.
  property real delegateWidth: itemWidth + gutterWidth
  property real delegateHeight: itemHeight + gutterHeight

  // internal
  property real itemAreaWidth: width - leftExtraGutter - rightExtraGutter
  property real minDelegateWidth: itemWidth + minGutterWidth
  property int columns: Math.max(1, Math.floor(itemAreaWidth / minDelegateWidth))
  property real gutterWidth: Math.floor(itemAreaWidth / columns - itemWidth)
  property real gutterHeight: minGutterHeight
  
  function selectAll() {
    if (model)
      model.selectAll();
  }
  
  function unselectAll() {
    if (model)
      model.unselectAll();
  }

  function ensureIndexVisible(index, centered) {
    grid.positionViewAtIndex(index, centered ? GridView.Center : GridView.Visible);
  }

  function scrollToTop() {
    gridScroller.restart();
  }

  // Ensures the view is inside its normal bounds after you've mucked with
  // things manually.
  function returnToBounds() {
    grid.returnToBounds();
  }

  // Uses black magic to hunt for the delegate instance with the given index.
  // Returns undefined if there's no currently-instantiated delegate with that
  // index.
  function getDelegateInstanceAt(index) {
    for(var i = 0; i < grid.contentItem.children.length; ++i) {
      var item = grid.contentItem.children[i];
      // We have to check for the specific objectName we gave our delegates in
      // CheckerboardDelegate, since we also get some items that were not our
      // delegates here.
      if (item.objectName == "checkerboardDelegate" && item.index == index)
        return item;
    }
    return undefined;
  }
  
  function getRectOfItem(item, relativeTo, adjustForGutter) {
    var rect = GalleryUtility.getRectRelativeTo(item, relativeTo);
    
    if (adjustForGutter) {
      // Now we have to adjust for the gutter inside the delegate.
      rect.x += gutterWidth / 2;
      rect.y += gutterHeight / 2;
      rect.width -= gutterWidth;
      rect.height -= gutterHeight;
    }
    
    return rect;
  }
  
  // Uses getDelegateInstanceAt() to get the delegate instance with the given
  // index, then returns a rect with its coords relative to the given object.
  function getRectOfItemAt(index, relativeTo) {
    var item = getDelegateInstanceAt(index);
    
    return (item) ? getRectOfItem(item, relativeTo, true) : undefined;
  }
  
  function getVisibleDelegates() {
    return GalleryUtility.getVisibleItems(grid, grid, function(child) {
      return child.objectName == "checkerboardDelegate"
    });
  }
  
  clip: true
  
  Image {
    anchors.fill: parent

    source: "../../img/background-paper.png"
    fillMode: Image.Tile
  }

  GridView {
    id: grid
    objectName: "grid"
    
    anchors.fill: parent
    anchors.topMargin: topExtraGutter
    anchors.bottomMargin: bottomExtraGutter
    anchors.leftMargin: leftExtraGutter
    anchors.rightMargin: rightExtraGutter
    
    cellWidth: delegateWidth
    cellHeight: delegateHeight
    
    onMovementStarted: checkerboard.movementStarted()
    onMovementEnded: checkerboard.movementEnded()
    
    // "Grid-shift" transition
    displaced: Transition {
      NumberAnimation { 
        easing.type: Easing.InQuint
        properties: "x,y"
        duration: Gallery.FAST_DURATION
      }
    }
  }

  NumberAnimation {
    id: gridScroller

    target: grid
    property: "contentY"
    to: 0

    easing.type: Easing.OutQuad
    duration: 200
  }
}
