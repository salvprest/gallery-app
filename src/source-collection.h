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

/**
  * A SourceCollection is a collection of DataSources of a particularly finalized
  * type.  In general (but with notable exceptions) a SourceCollection holds
  * every instance of a particular type; thus, there's usually only one instance
  * of a SourceCollection for that type.  For examine, if Photo is a DataSource,
  * there is one PhotoCollection that knows about every Photo instantiated in
  * the system.  This is similar in intent (but not implementation or design) to
  * Smalltalk's allInstances keyword.
  */

#ifndef GALLERY_SOURCE_COLLECTION_H_
#define GALLERY_SOURCE_COLLECTION_H_

#include "data-collection.h"

class SourceCollection : public DataCollection {
  Q_OBJECT
  
public:
  SourceCollection();
  
protected:
  virtual void notify_contents_altered(const QSet<DataObject*>* added,
    const QSet<DataObject*>* removed);
};

#endif  // GALLERY_SOURCE_COLLECTION_H_
