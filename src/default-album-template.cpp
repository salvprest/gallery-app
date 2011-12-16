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
 */

#include "default-album-template.h"

#include "album.h"

DefaultAlbumTemplate* DefaultAlbumTemplate::instance_ = NULL;

DefaultAlbumTemplate::DefaultAlbumTemplate()
  : AlbumTemplate("Default Album Template") {
  // TODO: For now, album layouts are hardcoded here, which is a bit fragile
  // as they must exactly descrive their respective templates, and changes
  // there must be reflected here.  For now, this will have to do, although
  // in the future a more robust solution will be implemented.
  AddPage(new AlbumTemplatePage("Template A", "qrc:/rc/qml/AlbumPreviewA.qml", 2,
    PORTRAIT, PORTRAIT));
  AddPage(new AlbumTemplatePage("Template B", "qrc:/rc/qml/AlbumPreviewB.qml", 3,
    LANDSCAPE, LANDSCAPE, PORTRAIT));
}

DefaultAlbumTemplate* DefaultAlbumTemplate::instance() {
  if (instance_ == NULL)
    instance_ = new DefaultAlbumTemplate();
  
  return instance_;
}