#include "DrawingArea.h"

#include <QtGui>

DrawingArea::DrawingArea(QWidget* parent)
{
	m_time = 0;
	setGeometry(0, 0, 800, 600);
	this->resize(800, 600);
}

void DrawingArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setViewport(0, 0, 800, 600);
	QLinearGradient* gradient = new QLinearGradient(0, 0, 800, 600);
	gradient->setColorAt(0, Qt::darkGray);
	gradient->setColorAt(1, Qt::black);

	QBrush* brush = new QBrush(*gradient);
	painter.setBrush(*brush);
	painter.drawRect(0, 0, 800, 600);

	QString string;
	string.setNum(m_time);
	painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
	painter.setFont(QFont("Arial", 20));
	painter.drawText(20, 30, string);

	if (m_scene.size() > 0)
	{
		drawScene(&painter);
	}
}

void DrawingArea::setTime(const double& time)
{
	m_time = time;
}

void DrawingArea::setScene(const TimeState& scene)
{
	m_scene = scene;
}

void DrawingArea::drawScene(QPainter* painter)
{
}
