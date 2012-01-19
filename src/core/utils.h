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
 */

#ifndef GALLERY_CORE_UTILS_H_
#define GALLERY_CORE_UTILS_H_

#include <QObject>
#include <QList>
#include <QSet>

#include "core/data-collection.h"
#include "core/data-object.h"

template <class F, class T>
QList<T> CastListToType(const QList<F>& from) {
  QList<T> to;
  
  F from_element;
  foreach (from_element, from) {
    T to_element = qobject_cast<T>(from_element);
    Q_ASSERT(to_element != NULL);
    
    to.append(to_element);
  }
  
  return to;
}

template <class F, class T>
QSet<T> CastSetToType(const QSet<F>& from) {
  QSet<T> to;
  
  F from_element;
  foreach (from_element, from) {
    T to_element = qobject_cast<T>(from_element);
    Q_ASSERT(to_element != NULL);
    
    to.insert(to_element);
  }
  
  return to;
}

template <class T, class A>
QSet<T> FilterSetOnlyType(const QSet<T>& from) {
  QSet<T> to;
  
  T element;
  foreach (element, from) {
    A casted_element = qobject_cast<A>(element);
    if (casted_element != NULL)
      to.insert(element);
  }
  
  return to;
}

template <class T, class A>
QList<T> FilterListOnlyType(const QList<T>& from) {
  QList<T> to;
  
  T element;
  foreach (element, from) {
    A casted_element = qobject_cast<A>(element);
    if (casted_element != NULL)
      to.append(element);
  }
  
  return to;
}

// For casting a QVariant to a QObject-based object.
//
// NOTE: This uses Q_ASSERT to verify that the QVariant properly casts.
template <class T>
T VariantToObject(QVariant var) {
  QObject* obj = qvariant_cast<QObject*>(var);
  Q_ASSERT(obj != NULL);
  
  T to = qobject_cast<T>(obj);
  Q_ASSERT(to != NULL);
  
  return to;
}

// Like VariantToObject, but no assertions (returns NULL if not a proper
// cast)
template <class T>
T UncheckedVariantToObject(QVariant var) {
  QObject* obj = qvariant_cast<QObject*>(var);
  
  return (obj != NULL) ? qobject_cast<T>(obj) : NULL;
}

#endif  // GALLERY_CORE_UTILS_H_
