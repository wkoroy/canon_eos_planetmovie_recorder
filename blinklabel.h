/***************************************************************************
 *   Copyright (C) 2008-2009 by Чернов А.А.                                *
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

#ifndef _blinklabel_h
#define _blinklabel_h

#include <QLabel>

class QTimer;

class QBlinkLabel: public QLabel
{
	Q_OBJECT
public:
	QBlinkLabel(QWidget* parent);
	QBlinkLabel(const QString& text, QWidget* parent);
	~QBlinkLabel();
	void start();
	void stop();
protected slots:
	void slotTimer();
protected:
	virtual void paintEvent(QPaintEvent* event);
private:
	QTimer* BlinkTimer;
	int BlinkPos;
};

#endif	// _blinklabel_h
