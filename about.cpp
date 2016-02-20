/***************************************************************************
 *   Copyright (C) 2008-2010 by Чернов А.А.                                *
 *   valexlin@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "about.h"
#include "config.h"

#include <QBoxLayout>
#include <QTextBrowser>
#include <QPushButton>

GAboutDlg::GAboutDlg(QWidget* parent)
 : QDialog(parent)
{
    static QString text = tr("<body bgcolor=\"%1\"><p>EOS Camera Astro Movie Record<br/>"
										  "Version %2"
					  "<center>Authors:</center>"
					  "Chernov Aleksey - main programmer (<a href=\"mailto:valexvir@yandex.ru\">valexvir@yandex.ru</a>)<br/>"
					  "Uterr - autofocus programmer <br/>"
					  "Golubinsky Yury - Mac OS X port (<a href=\"mailto:urix@me.com\">urix@me.com</a>)<br/>"
					  "Lukyanenko Vlad - homepage design (<a href=\"mailto:xkimx@rambler.ru\">xkimx@rambler.ru</a>)<br/>"
					  "Emel'yanov Denis - icon maker (<a href=\"mailto:suzuntu@yandex.ru\">suzuntu@yandex.ru</a>)<br/>"
					  "insaner - mousewhell patch<br/>"
                      "Koroy Vladimir -Planet Tracking (<a href=\"mailto:wkoroy@gmail.com\">wkoroy@gmail.com</a>)<br/>"
					  "<br/>"
					  "homepage: <a href=\"http://valexvir.narod.ru\">http://valexvir.narod.ru</a><br/>"
					  "sf.net page: <a href=\"http://sf.net/projects/eos-movrec\">http://sf.net/projects/eos-movrec</a><br/>"
					  "forum: <a href=\"http://forum.ixbt.com/topic.cgi?id=20:26019\">http://forum.ixbt.com/topic.cgi?id=20:26019</a>"
					  "</p>"
					  "<p>This program is free software; you can redistribute it and/or modify "
					  "it under the terms of the GNU General Public License as published by "
					  "the Free Software Foundation; either version 2 of the License, or "
					  "(at your option) any later version.</p>"
					  "</body>"
					);


	setModal(true);
	setWindowTitle(tr("About"));
	QVBoxLayout* main_layout = new QVBoxLayout(this);
	QTextBrowser *browser = new QTextBrowser(this);
	browser->setOpenExternalLinks(true);
	browser->setFrameStyle(QFrame::NoFrame);
	browser->setMinimumSize(360, 270);
	QString color_name = palette().color(QPalette::Window).name();
	text.replace("%1", color_name);
	text.replace("%2", QString(VERSION));
	browser->setText(text);
	main_layout->addWidget(browser, 0);
	QHBoxLayout* btn_layout = new QHBoxLayout();
	btn_layout->addStretch(10);
	QPushButton* okBtn = new QPushButton(tr("&OK"), this);
	okBtn->setDefault(true);
	btn_layout->addWidget(okBtn, 0);
	btn_layout->addStretch(10);
	main_layout->addLayout(btn_layout, 0);

	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
}

GAboutDlg::~GAboutDlg()
{
}
