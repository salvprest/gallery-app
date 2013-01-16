/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * Authors:
 *  Nicolas d'Offay <nicolas.doffay@canonical.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QtTest/QtTest>
#include <QFileInfo>
#include <QUrl>

#include "qml/gallery-standard-image-provider.h"
#include "core/gallery-manager.h"
#include "media/preview-manager.h"

class tst_GalleryStandardImageProvider : public QObject
{
  Q_OBJECT
  GalleryStandardImageProvider gallery_standard_image_provider;

private slots:
  void ToURL();
  void ToFile();
};

void tst_GalleryStandardImageProvider::ToURL()
{
  QFileInfo fi("/tmp/test.jpg");
  QUrl url = gallery_standard_image_provider.ToURL(fi);
  QUrl expect("image://gallery-standard//tmp/test.jpg");
  QCOMPARE(url, expect);
}

void tst_GalleryStandardImageProvider::ToFile()
{

}

QTEST_MAIN(tst_GalleryStandardImageProvider);

#include "tst_gallerystandardimageprovidertest.moc"
