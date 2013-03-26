# -*- Mode: Python; coding: utf-8; indent-tabs-mode: nil; tab-width: 4 -*-
# Copyright 2012 Canonical
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3, as published
# by the Free Software Foundation.


"""Tests for the Gallery App"""

from __future__ import absolute_import

from testtools.matchers import Equals, NotEquals
from autopilot.matchers import Eventually

from gallery_app.tests import GalleryTestCase

from os.path import exists


class TestEventsView(GalleryTestCase):
    """Tests the main gallery features"""

    """ This is needed to wait for the application to start.
        In the testfarm, the application may take some time to show up."""
    def setUp(self):
        super(TestEventsView, self).setUp()
        self.assertThat(self.events_view.get_qml_view().visible, Eventually(Equals(True)))

    def tearDown(self):
        super(TestEventsView, self).tearDown()


    def enable_select_mode(self):
        self.reveal_tool_bar()
        self.click_select_icon()

    def click_select_icon(self):
        select_icon = self.events_view.get_select_icon()
        self.click_item(select_icon)

    def click_first_photo(self):
        first_photo = self.events_view.get_first_image_in_event_view()
        self.click_item(first_photo)

    def click_delete_action(self):
        trash_button = self.events_view.get_delete_icon()
        self.click_item(trash_button)


    def test_camera_icon_hover(self):
        """Ensures that when the mouse is over the camera icon it has the
        hovered state."""
        self.reveal_tool_bar()

        camera_icon = self.events_view.get_camera_icon()
        self.pointing_device.move_to_object(camera_icon)

        self.assertThat(camera_icon.hovered, Eventually(Equals(True)))

    def test_select_button_cancel(self):
        """Clicking the cancel button after clicking the select button must
        hide the chromebar automatically."""
        self.enable_select_mode()

        cancel_icon = self.events_view.get_cancel_icon()
        self.click_item(cancel_icon)

        toolbar = self.events_view.get_tool_bar()
        self.assertThat(toolbar.active, Eventually(Equals(False)))

    def test_delete_a_photo(self):
        """Selecting a photo must make the delete button clickable."""
        number_of_photos = self.events_view.number_of_photos_in_event_view()
        self.enable_select_mode()
        self.click_first_photo()
        self.click_delete_action()

        delete_dialog = self.events_view.get_delete_dialog()
        self.assertThat(delete_dialog.visible, Eventually(Equals(True)))

        cancel_item = self.events_view.get_delete_dialog_cancel_button()
        self.click_item(cancel_item)

        self.assertThat(lambda: exists(self.sample_file), Eventually(Equals(True)))

        new_number_of_photos = self.events_view.number_of_photos_in_event_view()
        self.assertThat(new_number_of_photos, Equals(number_of_photos))

        self.click_delete_action()

        delete_dialog = self.events_view.get_delete_dialog()
        self.assertThat(delete_dialog.visible, Eventually(Equals(True)))

        delete_item = self.events_view.get_delete_dialog_delete_button()
        self.click_item(delete_item)

        self.assertThat(lambda: exists(self.sample_file), Eventually(Equals(False)))

        new_number_of_photos = self.events_view.number_of_photos_in_event_view()
        self.assertThat(new_number_of_photos, Equals(number_of_photos-1))
