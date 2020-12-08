/* huffmanzip-window.cpp
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

#include "huffmanzip-window.h"
#include <iostream>

HuffmanzipWindow::HuffmanzipWindow()
	: Glib::ObjectBase("HuffmanzipWindow")
	, Gtk::Window()
	, headerbar(nullptr)
	, label(nullptr)
{
	builder = Gtk::Builder::create_from_resource("/top/bobby285271/huffmanzip/huffmanzip-window.ui");
	builder->get_widget("headerbar", headerbar);
	builder->get_widget("label", label);
	builder->get_widget("startBtn", startBtn);
	builder->get_widget("fileSelect", fileSelect);
	builder->get_widget("destDir", destDir);
	builder->get_widget("isReverse", isReverse);
	add(*label);
	label->show();
	set_titlebar(*headerbar);
	headerbar->show();
	startBtn->signal_clicked().connect(sigc::mem_fun(*this,&HuffmanzipWindow::startBtnClicked));
}

void HuffmanzipWindow::startBtnClicked(){
	std::cout << isReverse->get_active() << std::endl;
	startBtn->set_sensitive(false);
	fileSelect->set_sensitive(false);
	destDir->set_sensitive(false);
	isReverse->set_sensitive(false);
	label->set_text("Processing");
	std::cout << fileSelect->get_filename() << std::endl;
	std::cout << destDir->get_filename() << std::endl;
}
