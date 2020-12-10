/* huffmanzip-window.h
 *
 * Copyright 2020 Bobby Rong
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <gtkmm/builder.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/box.h>
#include <glib/gi18n.h>
#include <iostream>
#include "encode.h"
#include "decode.h"

class HuffmanzipWindow : public Gtk::Window
{
public:
	HuffmanzipWindow();

private:
	Gtk::HeaderBar *headerbar;
	Gtk::Label *label;
	Gtk::Button *startbtn;
	Gtk::FileChooserButton *fileselect, *destdir;
	Gtk::ProgressBar *progressbar;
	Gtk::CheckButton *isreverse;
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Box *box;
	void startBtnClicked();
};
