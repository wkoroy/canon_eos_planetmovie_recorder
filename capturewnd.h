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

#ifndef _capturewnd_h
#define _capturewnd_h

#include <QWidget>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>

class GEOSCaptureWnd: public QWidget
{
public:
	GEOSCaptureWnd(QWidget* parent);
	~GEOSCaptureWnd();
	void setShowLiveImage(bool s)
	{
		ShowLiveImage = s;
	}
	void setShowWhiteBox(bool w)
	{
		ShowWhiteBox = w;
		repaint();
	}

    void settracking(bool _istracking)
    {
        istracking=_istracking;
    }
    void setdelta(int _delta)
    {
        delta=_delta;
    }


    void settrackfreq(int _trackfrec)
    {
        trackfrec=_trackfrec;
    }


	// called from other thread
	void lockFocusingArea();
	void unlockFocusingArea();
	int** getFocusingArea();
	QSize getFocusingAreaSize();
	void setText(const QString& text);
	void clearText();
	void setZoomPositionDivisor(double zpd_x, double zpd_y) { ZPD_x = zpd_x; ZPD_y = zpd_y; }
	// call only from other thread!
	void waitPicture();
    void movezoompos(QPoint p);
protected:
	//virtual void showEvent(QShowEvent* event);
	virtual void paintEvent(QPaintEvent * event);
	virtual void closeEvent(QCloseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void customEvent(QEvent* event);
private:
    int getbwcolor(QImage *img, int i, int j);

	void clearFocusArea();
private:
    bool istracking;
    int delta;
    int trackfrec;
	QImage LiveImage;
	int max_frame_size;
	unsigned char* frame;
	bool ShowLiveImage;
	bool ShowWhiteBox;
	int Zoom;
	QRect ZoomRect;
	QPoint MousePressPoint;
	double ZPD_x, ZPD_y;
	bool ZoomRectMoving;
	int** FocusArea;
	QRect FocusAreaRect;
	QMutex FocusMutex;
	QMutex WaitMutex;
	QWaitCondition FocusCond;
	QString Text;
};

#endif	// _capturewnd_h
