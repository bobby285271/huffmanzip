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

HuffmanzipWindow::HuffmanzipWindow()
	: Glib::ObjectBase("HuffmanzipWindow")
	, Gtk::Window()
	, headerbar(nullptr)
	, box(nullptr)
{
	setlocale(LC_ALL, "zh_CN.UTF-8");
	builder = Gtk::Builder::create_from_resource("/top/bobby285271/huffmanzip/huffmanzip-window.ui");
	builder->get_widget("headerbar", headerbar);
	builder->get_widget("box", box);
	builder->get_widget("label", label);
	builder->get_widget("startBtn", startBtn);
	builder->get_widget("fileSelect", fileSelect);
	builder->get_widget("destDir", destDir);
	builder->get_widget("isReverse", isReverse);
	builder->get_widget("progressbar", progressbar);
	destDir->set_filename("./");
	progressbar->set_visible(false);
	add(*box);
	label->show();
	set_titlebar(*headerbar);
	headerbar->show();
	startBtn->signal_clicked().connect(sigc::mem_fun(*this,&HuffmanzipWindow::startBtnClicked));
}

void HuffmanzipWindow::startBtnClicked()
{
	progressbar->set_visible(true);
	progressbar->set_fraction(0.1);
	std::cout << isReverse->get_active() << std::endl;
	startBtn->set_sensitive(false);
	fileSelect->set_sensitive(false);
	destDir->set_sensitive(false);
	isReverse->set_sensitive(false);
	label->set_text(fileSelect->get_filename());
	auto fff = fileSelect->get_filename() + ".out";
	const char *ff = fff.c_str();
	std::cout << ff << std::endl;
	std::ofstream Un(ff);
	if(!Un){std::cout << "1" << std::endl;}
	else std::cout << "11111" << std::endl;
	Un << 111 << std::endl;
	Un.close();
	std::cout << fileSelect->get_filename() << std::endl;
	std::cout << destDir->get_filename() << std::endl;
}
