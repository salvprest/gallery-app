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
 * Lucas Beeler <lucas@yorba.org>
 * Jim Nelson <jim@yorba.org>
*/

#ifndef GALLERY_GALLERY_STANDARD_IMAGE_PROVIDER_H_
#define GALLERY_GALLERY_STANDARD_IMAGE_PROVIDER_H_

#include <QObject>
#include <QQuickImageProvider>
#include <QFileInfo>
#include <QImage>
#include <QSize>
#include <QString>
#include <QUrl>

class GalleryStandardImageProvider
  : public QObject, public QQuickImageProvider {
  Q_OBJECT
  
 public:
  static const char* PROVIDER_ID;
  static const char* PROVIDER_ID_SCHEME;
  
  virtual ~GalleryStandardImageProvider();
  
  static void Init();
  
  static GalleryStandardImageProvider* instance();
  
  static QUrl ToURL(const QFileInfo& file);
  
  virtual QImage requestImage(const QString& id, QSize* size,
    const QSize& requestedSize);
  
 private:
  static GalleryStandardImageProvider* instance_;
  
  GalleryStandardImageProvider();
};

#endif // GALLERY_GALLERY_STANDARD_IMAGE_PROVIDER_H_
