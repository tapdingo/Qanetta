#include "DrawingArea.h"

#include <QtGui>

DrawingArea::DrawingArea(QWidget* parent)
{
	setGeometry(0, 0, 800, 600);
}

void DrawingArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setViewport(0, 0, 800, 600);
	painter.setPen(Qt::blue);
	painter.setFont(QFont("Arial", 100));
	painter.setBackgroundMode(Qt::OpaqueMode);
	QLinearGradient* gradient = new QLinearGradient(0, 0, 800, 600);
	gradient->setColorAt(0, Qt::darkGray);
	gradient->setColorAt(1, Qt::black);
	QBrush* brush = new QBrush(*gradient);
	painter.drawText(rect(), Qt::AlignCenter, "CHECK");

	painter.setBrush(*gradient);
	painter.drawRect(0, 0, 800, 600);
}
