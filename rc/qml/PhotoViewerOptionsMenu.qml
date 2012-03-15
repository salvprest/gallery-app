/*
 * Copyright (C) 2011-2012 Canonical Ltd
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
 * Lucas Beeler <lucas@yorba.org>
 */

import QtQuick 1.1

PopupMenu {
  model: ListModel {
    ListElement {
      title: "Edit"
    }

    ListElement {
      isSeparator: true
    }

    ListElement {
      title: "Set as Background"
      iconFilename: "../img/dummy-menu-photo-icon.png"
      hasCueRectangle: true
    }

    ListElement {
      isSeparator: true
    }

    ListElement {
      title: "Print"
      hasBottomBorder: true
    }

    ListElement {
      title: "Export to Connected Device"
    }
  }
}