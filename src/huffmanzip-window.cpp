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
	: Glib::ObjectBase("HuffmanzipWindow"),
	  Gtk::Window(),
	  headerbar(nullptr),
	  label(nullptr),
	  startbtn(nullptr),
	  fileselect(nullptr),
	  destdir(nullptr),
	  progressbar(nullptr),
	  isreverse(nullptr),
	  box(nullptr)
{
	setlocale(LC_ALL, "zh_CN.UTF-8");
	builder = Gtk::Builder::create_from_resource("/top/bobby285271/huffmanzip/huffmanzip-window.ui");
	builder->get_widget("headerbar", headerbar);
	builder->get_widget("box", box);
	builder->get_widget("label", label);
	builder->get_widget("startbtn", startbtn);
	builder->get_widget("fileselect", fileselect);
	builder->get_widget("destdir", destdir);
	builder->get_widget("isreverse", isreverse);
	builder->get_widget("progressbar", progressbar);
	destdir->set_filename("./");
	progressbar->set_visible(false);
	add(*box);
	label->show();
	set_titlebar(*headerbar);
	headerbar->show();
	startbtn->signal_clicked().connect(sigc::mem_fun(*this, &HuffmanzipWindow::startBtnClicked));
}

void HuffmanzipWindow::startBtnClicked()
{
	startbtn->set_sensitive(false);
	fileselect->set_sensitive(false);
	destdir->set_sensitive(false);
	isreverse->set_sensitive(false);
	label->set_text("请稍候");
	progressbar->set_visible(true);
	progressbar->set_fraction(0.1);
	std::string originFilePath = fileselect->get_filename();
	std::string realFileName;
	for (size_t i = originFilePath.size() - 1; originFilePath[i] != '/'; i--)
	{
		realFileName += originFilePath[i];
	}
	std::reverse(realFileName.begin(), realFileName.end());
	std::string destFilePath = destdir->get_filename() + '/' + realFileName + ".out";

	try
	{
		if (isreverse->get_active())
		{
			destTree tree(originFilePath.c_str());
			tree.get_decode_result(destFilePath.c_str());
		}
		else
		{
			orgTree tree(originFilePath.c_str());
			tree.get_encode_result(destFilePath.c_str());
		}
		label->set_text("完成");
	}
	catch (const char *e)
	{
		label->set_text("出现未知错误");
		std::cerr << e << std::endl;
	}
	catch (const std::exception &e)
	{
		label->set_text("出现未知错误");
	}
	startbtn->set_sensitive(true);
	fileselect->set_sensitive(true);
	destdir->set_sensitive(true);
	isreverse->set_sensitive(true);
	progressbar->set_visible(false);
}
