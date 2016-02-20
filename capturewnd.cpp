/***************************************************************************
 *   Copyright (C) 2008-2009 by Р§РµСЂРЅРѕРІ Рђ.Рђ.                                *
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

#include "capturewnd.h"
#include "buffer.h"
#include "events.h"

#include <QBuffer>
#include <QImageReader>
#include <QPainter>
#include <QLayout>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>
GEOSCaptureWnd::GEOSCaptureWnd(QWidget* parent)
 : QWidget(parent)
{
    istracking=false;
    delta=20;
    trackfrec=25;
	max_frame_size = 0;
	frame = 0;
	ShowLiveImage = true;
	ShowWhiteBox = true;
	//setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_OpaquePaintEvent, true);
	setMinimumSize(768, 512);
    setMouseTracking(true);
    ZoomRectMoving = false;
    FocusArea = 0;
    ZPD_x = ZPD_y = 5.0;
}


int GEOSCaptureWnd::getbwcolor(QImage *img, int i, int j)
{
    QColor clrCurrent( LiveImage.pixel( QPoint(j,i)));
    int bwcolor= (clrCurrent.red()+clrCurrent.green()+clrCurrent.blue());
    return bwcolor;
}
GEOSCaptureWnd::~GEOSCaptureWnd()
{
    if (frame)
    {
        free(frame);
        frame = 0;
    }
    clearFocusArea();
}

void GEOSCaptureWnd::paintEvent(QPaintEvent* /*event*/)
{

    QColor urect(255,255,255);
    QPainter painter(this);
    if (ShowLiveImage && !LiveImage.isNull())
    {
        painter.drawImage(QPoint(0, 0), LiveImage);
        //        qDebug()<<"h = "<<LiveImage.height()<<"  w="<<LiveImage.width();
        if(istracking)
        {
          // delta  -  чувствительность

        static qint64 countframes=0;
        countframes++;
        QPoint currentobj(0,0);

        static bool isdetect =false;
        if(countframes %trackfrec)
            for(int i=10;i<LiveImage.height();i++)
            {
                for(int j=10;j<LiveImage.width();j++)
                {
                    QColor clrCurrent( LiveImage.pixel( QPoint(j,i)));

                    QColor clrCurrentother( LiveImage.pixel( QPoint(j-3,i-10)));

                   int bwcolor=getbwcolor(&LiveImage,i,j)/3;
                   bwcolor+=getbwcolor(&LiveImage , i-10,j-3)/3;
                   bwcolor+=getbwcolor(&LiveImage , i-5,j-2)/3;
                   bwcolor+=getbwcolor(&LiveImage , i-7,j-10)/3;

                    bwcolor/=4;

                    if(countframes <4)
                    {

                       // if( bwcolor >10)  qDebug()<<" delta ="<<delta<<" bw= "<<bwcolor;
                        if(delta< bwcolor) delta=bwcolor;


                       // if(i==5 && j==5)
                            //qDebug()<<" delta ="<<delta<<" bw= "<<bwcolor;
                    }
                    else
                    {
                      // delta=0;

                        //delta/=10;
                       //

                    int realx,realy;
                    if( bwcolor> delta && !isdetect )
                    {
                 #ifdef DEBUGINFO
                        qDebug()<<" delta ="<<delta;
                        qDebug()<<" color ="<< bwcolor<<"ij"<<i<<" "<<j;// i - y
#endif

                        realx=-LiveImage.width()/2 +j;
                        realy=LiveImage.height()/2 -i;

                        QPoint p= ZoomRect.topLeft();


                        if(Zoom == 1)
                        {
                            p.setX(j-ZoomRect.width()/2);
                            p.setY(i-ZoomRect.height()/2);
                            realx=0;realy=0;
                        }// experimental


                        p.setX(p.x()*ZPD_x+realx);//  rightwork

                        p.setY(p.y()*ZPD_y-realy);//  rightwork
                        //  if( (abs(currentobj.x()-j) >180 )  || ( abs(currentobj.y()-i) >300  ) )
                        int dx=abs(currentobj.x()-j);
                        int dy=abs(currentobj.y()-i);

                        if( abs(realx) > 10  ||  abs(realy) > 12 || Zoom ==1 )
                            QApplication::postEvent(parentWidget(), new GCameraEvent(CAMERA_EVENT_ZOOMPOS_NEEDCHANGE, QVariant(p)));


                        currentobj.setX(j);
                        currentobj.setY(i);

#ifdef DEBUGINFO
                        qDebug()<<" color ="<< bwcolor<<"ij"<<realx<<" "<<realy<<"dy ="<<dy<<"dx  ="<<dx ;// i - y
#endif
                        isdetect=true;

                    }
                    else
                    {


                    }

                }
                }


            }

        else isdetect=false;

}

        if (Zoom == 1 && ShowWhiteBox)
        {
            QPen p(QColor(255, 255, 255));
            p.setWidth(2);
            painter.setPen(p);
            painter.drawRect(ZoomRect);
        }
    }
	else
	{
		QBrush br(QColor(0, 0, 0), Qt::SolidPattern);
		painter.fillRect(0, 0, width(), height(), br);
	}
	if (!Text.isEmpty())
	{
		painter.setPen(QColor(255, 255, 255));
		painter.drawText(50, 100, Text);
	}
}

void GEOSCaptureWnd::closeEvent(QCloseEvent* /*event*/)
{
}

void GEOSCaptureWnd::mousePressEvent(QMouseEvent* event)
{
	ZoomRectMoving = (Zoom == 1 && ZoomRect.contains(event->pos(), true)) || Zoom == 5;
	if (ZoomRectMoving)
		MousePressPoint = event->pos();
}


void GEOSCaptureWnd::movezoompos(QPoint pmv)
{
double delt=5;
    QPoint p = ZoomRect.topLeft();
    if(pmv.x() >0 && pmv.y()>0)
    {
       // pmv.setX(ZoomRect.width()/delt+pmv.x());
       // pmv.setY(ZoomRect.height()/delt+pmv.y());
        pmv.setX(delt+pmv.x());
        pmv.setY(delt+pmv.y());

    }
    p.setX(p.x()*ZPD_x+pmv.x());
    p.setY(p.y()*ZPD_y+pmv.y());
    QApplication::postEvent(parentWidget(), new GCameraEvent(CAMERA_EVENT_ZOOMPOS_NEEDCHANGE, QVariant(p)));
   // ZoomRectMoving = false;
}
void GEOSCaptureWnd::mouseReleaseEvent(QMouseEvent* /*event*/)
{
	if (ZoomRectMoving)
	{
		QPoint p = ZoomRect.topLeft();
		p.setX(p.x()*ZPD_x);
		p.setY(p.y()*ZPD_y);
		QApplication::postEvent(parentWidget(), new GCameraEvent(CAMERA_EVENT_ZOOMPOS_NEEDCHANGE, QVariant(p)));
		ZoomRectMoving = false;
	}
}

void GEOSCaptureWnd::mouseMoveEvent(QMouseEvent* event)
{
	static int cursor_type = 0;
	QPoint pos = event->pos();
	if (Zoom == 1)
	{
		if (ZoomRect.contains(pos, true))
		{
			if (cursor_type == 0)
			{
				setCursor(Qt::OpenHandCursor);
				cursor_type = 1;
			}
		}
		else
		{
			if (cursor_type == 1)
			{
				setCursor(Qt::ArrowCursor);
				cursor_type = 0;
			}
		};
		if (ZoomRectMoving)
		{
			QRect bak_rect = ZoomRect;
			QPoint bak_point = MousePressPoint;
			QPoint off = pos - MousePressPoint;
			ZoomRect.translate(off);
			MousePressPoint = pos;
			if (ZoomRect.left() < 0 || ZoomRect.right() >= LiveImage.width())
			{
				if (ZoomRect.left() < 0)
					ZoomRect.moveLeft(0);
				if (ZoomRect.right() >= LiveImage.width())
					ZoomRect.moveRight(LiveImage.width() - 1);
				MousePressPoint.setX(bak_point.x());
			};
			if (ZoomRect.top() < 0 || ZoomRect.bottom() >= LiveImage.height())
			{
				if (ZoomRect.top() < 0)
					ZoomRect.moveTop(0);
				if (ZoomRect.bottom() >= LiveImage.height())
					ZoomRect.moveBottom(LiveImage.height() - 1);
				MousePressPoint.setY(bak_point.y());
			};
		};
	}
	else if (Zoom == 5)
	{
		if (cursor_type == 0)
		{
			setCursor(Qt::OpenHandCursor);
			cursor_type = 1;
		}
		if (ZoomRectMoving)
		{
			QRect bak_rect = ZoomRect;
			QPoint bak_point = MousePressPoint;
			QPoint off = MousePressPoint - pos;
			off /= 3;
			ZoomRect.translate(off);
			MousePressPoint = pos;
			if (ZoomRect.left() < 0 || ZoomRect.top() < 0 ||
				ZoomRect.right() >= LiveImage.width() || ZoomRect.bottom() >= LiveImage.height())
			{
				ZoomRect = bak_rect;
				MousePressPoint = bak_point;
			}
		}
	}
	else
	{
		if (cursor_type == 1)
		{
			setCursor(Qt::ArrowCursor);
			cursor_type = 0;
		}
	}
}

void GEOSCaptureWnd::waitPicture()
{
	WaitMutex.lock();
	FocusCond.wait(&WaitMutex);
	WaitMutex.unlock();
}

void GEOSCaptureWnd::customEvent(QEvent* event)
{
	static int old_width = 0;
	static int old_height = 0;
	if (event->type() == CAMERA_EVENT_EVF_TRANSMITED && live_buffer::frame)
	{
		if (ShowLiveImage)
		{
			live_buffer::IsPainting = true;
// !!! Start critical section
			live_buffer::ImageMutex.lock();
			int size = live_buffer::frame_size;
			if (max_frame_size < size)
			{
				frame = (unsigned char*)realloc(frame, size);
				max_frame_size = size;
			}
			memcpy(frame, live_buffer::frame, size);
			live_buffer::ImageMutex.unlock();
// !!! End of critical section
			//LiveImage.loadFromData(frame, size, "JPG");
			QByteArray a = QByteArray::fromRawData(reinterpret_cast<const char *>(frame), size);
			QBuffer b;
			b.setData(a);
			b.open(QIODevice::ReadOnly);
			static QImageReader ir;
			ir.setDevice(&b);
			ir.setFormat("jpeg");
// !!! Start critical section
			FocusMutex.lock();
			if (ir.read(&LiveImage))
			{
				if (!LiveImage.isNull())
				{
					live_buffer::frame_width = LiveImage.width();
					live_buffer::frame_height = LiveImage.height();
					if (old_width != live_buffer::frame_width || old_height != live_buffer::frame_height)
					{
						setMinimumSize(live_buffer::frame_width, live_buffer::frame_height);
						setMaximumSize(live_buffer::frame_width, live_buffer::frame_height);
					}
					old_width = live_buffer::frame_width;
					old_height = live_buffer::frame_height;
				}
				FocusCond.wakeAll();
				update(0, 0, live_buffer::frame_width, live_buffer::frame_height);
			}
			live_buffer::IsPainting = false;
			FocusMutex.unlock();
// !!! End of critical section
		}
		event->accept();
	}
	else if (event->type() == CAMERA_EVENT_ZOOM_CHANGED)
	{
		if (!ZoomRectMoving)
		{
			GCameraEvent* e = (GCameraEvent*)event;
			QRect r = e->value().toRect();
			Zoom = r.x();
			ZoomRect = QRect(r.width()/ZPD_x, r.height()/ZPD_y, LiveImage.width()/5, LiveImage.height()/5);
		}
		clearFocusArea();
	}
	event->accept();
}

void GEOSCaptureWnd::lockFocusingArea()
{
	FocusMutex.lock();
}

void GEOSCaptureWnd::unlockFocusingArea()
{
	FocusMutex.unlock();
}

int** GEOSCaptureWnd::getFocusingArea()
{
	if (ZoomRect.width() == 0 || LiveImage.isNull())
		return 0;
	if (!FocusArea)
	{
		int w, h;
		if (Zoom == 1)
		{
			w = ZoomRect.width();
			h = ZoomRect.height();
			FocusAreaRect = ZoomRect;
		}
		else
		{
			w = LiveImage.width();
			h = LiveImage.height();
			FocusAreaRect = QRect(0, 0, w, h);
		}
		int i;
		FocusArea = (int**)malloc(sizeof(int*)*h);
		for (i = 0; i < h; i++)
		{
			FocusArea[i] = (int*)malloc(sizeof(int)*w);
		}
	}
    //QImage img = LiveImage.copy(FocusAreaRect).scaled(FocusAreaRect.width()/2, FocusAreaRect.height()/2, Qt::IgnoreAspectRatio, Qt::FastTransformation).convertToFormat(QImage::Format_RGB32, Qt::ColorOnly);
    //QImage img = LiveImage.copy(FocusAreaRect).convertToFormat(QImage::Format_RGB32, Qt::ColorOnly);
    QImage img = LiveImage.copy(FocusAreaRect);
	int i, j;
	for (i = 0; i < FocusAreaRect.height(); i++)
	{
		for (j = 0; j < FocusAreaRect.width(); j++)
			FocusArea[i][j] = qGray(img.pixel(j, i));
	}
	return FocusArea;
}

QSize GEOSCaptureWnd::getFocusingAreaSize()
{
	return FocusAreaRect.size();
}

void GEOSCaptureWnd::clearFocusArea()
{
	FocusMutex.lock();
	if (FocusArea)
	{
		int i;
		for (i = 0; i < FocusAreaRect.height(); i++)
			free(FocusArea[i]);
		free(FocusArea);
		FocusArea = 0;
	}
	FocusMutex.unlock();
}

void GEOSCaptureWnd::setText(const QString& text)
{
	Text = text;
	//update();
}

void GEOSCaptureWnd::clearText()
{
	Text.clear();
}
