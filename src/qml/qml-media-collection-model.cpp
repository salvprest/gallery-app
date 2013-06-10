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
 */

#include "qml-media-collection-model.h"

#include "album.h"
#include "album-collection.h"
#include "album-default-template.h"
#include "data-object.h"
#include "selectable-view-collection.h"
#include "media-source.h"
#include "media-collection.h"
#include "variants.h"
#include "gallery-manager.h"

/*!
 * \brief QmlMediaCollectionModel::QmlMediaCollectionModel
 * \param parent
 */
QmlMediaCollectionModel::QmlMediaCollectionModel(QObject* parent)
    : QmlViewCollectionModel(parent, "mediaSource", NULL)
{
}

/*!
 * \brief QmlMediaCollectionModel::QmlMediaCollectionModel
 * \param parent
 * \param default_comparator
 */
QmlMediaCollectionModel::QmlMediaCollectionModel(QObject* parent,
                                                 DataObjectComparator default_comparator)
    : QmlViewCollectionModel(parent, "mediaSource", default_comparator)
{
}

/*!
 * \brief QmlMediaCollectionModel::RegisterType
 */
void QmlMediaCollectionModel::RegisterType()
{
    qmlRegisterType<QmlMediaCollectionModel>("Gallery", 1, 0, "MediaCollectionModel");
}

/*!
 * \brief QmlMediaCollectionModel::createAlbumFromSelected
 * \return
 */
QVariant QmlMediaCollectionModel::createAlbumFromSelected()
{
    SelectableViewCollection* view = BackingViewCollection();
    if (view->selectedCount() == 0)
        return QVariant();

    Album* album = new Album(GalleryManager::instance()->album_default_template());

    // Attach only the MediaSources in the backing collection
    album->attachMany(FilterSetOnlyType<DataObject*, MediaSource*>(view->getSelected()));

    GalleryManager::instance()->album_collection()->add(album);

    return QVariant::fromValue(album);
}

/*!
 * \brief QmlMediaCollectionModel::destroySelectedMedia
 */
void QmlMediaCollectionModel::destroySelectedMedia()
{
    SelectableViewCollection* view = BackingViewCollection();
    if (view->selectedCount() == 0)
        return;

    GalleryManager::instance()->media_collection()->destroyMany(
                FilterSetOnlyType<DataObject*, MediaSource*>(view->getSelected()),
                true, true);
}

/*!
 * \brief QmlMediaCollectionModel::destroyMedia
 * \param vmedia
 */
void QmlMediaCollectionModel::destroyMedia(QVariant vmedia)
{
    MediaSource* media = VariantToObject<MediaSource*>(vmedia);

    if (media != NULL)
        GalleryManager::instance()->media_collection()->destroy(media, true, true);
}

/*!
 * \brief QmlMediaCollectionModel::monitored
 * \return
 */
bool QmlMediaCollectionModel::monitored() const
{
    return IsMonitoring();
}

/*!
 * \brief QmlMediaCollectionModel::set_monitored
 * \param monitor
 */
void QmlMediaCollectionModel::set_monitored(bool monitor)
{
    if (IsMonitoring() == monitor)
        return;

    if (monitor)
        MonitorSourceCollection(GalleryManager::instance()->media_collection());
    else
        StopMonitoring();

    monitoring_changed();
}

/*!
 * \brief QmlMediaCollectionModel::VariantFor
 * \param object
 * \return
 */
QVariant QmlMediaCollectionModel::VariantFor(DataObject* object) const
{
    MediaSource* media_source = qobject_cast<MediaSource*>(object);

    return (media_source != NULL) ? QVariant::fromValue(media_source) : QVariant();
}

/*!
 * \brief QmlMediaCollectionModel::FromVariant
 * \param var
 * \return
 */
DataObject* QmlMediaCollectionModel::FromVariant(QVariant var) const
{
    return UncheckedVariantToObject<MediaSource*>(var);
}
