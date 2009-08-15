#include "DrawingArea.h"

#include <QtGui>
#include <iostream>

#define NODERADIUS 20.0
#define MARGIN 250.0

DrawingArea::DrawingArea(QWidget* parent)
{
	m_time = 0;
	m_xScaling = 1;
	m_yScaling = 1;
	m_xOffset = 0;
	m_yScaling = 0;
	setGeometry(0, 0, WIDTH, HEIGHT);
	this->resize(WIDTH, HEIGHT);
}

void DrawingArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setViewport(0, 0, WIDTH, HEIGHT);
	QLinearGradient* gradient = new QLinearGradient(0, 0, WIDTH, HEIGHT);
	gradient->setColorAt(0, Qt::darkGray);
	gradient->setColorAt(1, Qt::black);

	QBrush* brush = new QBrush(*gradient);
	painter.setBrush(*brush);
	painter.drawRect(0, 0, WIDTH, HEIGHT);

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
	calculateParameters();
}

void DrawingArea::drawScene(QPainter* painter)
{
	Nodes currentTime = m_scene[m_time];

	//Draw the nodes
	Nodes::iterator it;
	for(it = currentTime.begin(); it != currentTime.end(); it++)
	{
		int nodeX = (it->second.x_coord - m_xOffset) * m_xScaling;
		int nodeY = (it->second.y_coord - m_yOffset) * m_yScaling;
		QString nodeId;
		QString node = "Node ";
		nodeId.setNum(it->first);
		node.append(nodeId);

		painter->setFont(QFont("Arial", 10));
		painter->setRenderHint(QPainter::Antialiasing, true);
		painter->setPen(QPen(Qt::black, 2, Qt::DashDotLine, Qt::RoundCap));
		painter->drawEllipse(nodeX, nodeY, 20, 20);
		painter->drawText(nodeX + 25, nodeY + 15, node);

		drawLinks(painter, it->second.neighbors, nodeX, nodeY);
	}
}

void DrawingArea::calculateParameters()
{
	int xMax = 0;
	int yMax = 0;
	int xMin = 0;
	int yMin = 0;

	TimeState::iterator times;

	//streams.each do |time, value|
	for (times = m_scene.begin(); times != m_scene.end(); times++)
	{
		Nodes::iterator nodes;

		//value.each do |nodes, value|
		for (nodes = times->second.begin();
				nodes != times->second.end(); nodes++)
		{
			if (nodes->second.x_coord > xMax)
			{
				xMax = nodes->second.x_coord;
			}

			if (nodes->second.x_coord < xMin)
			{
				xMin = nodes->second.x_coord;
			}

			if (nodes->second.y_coord > yMax)
			{
				yMax = nodes->second.y_coord;
			}

			if (nodes->second.y_coord < yMin)
			{
				yMin = nodes->second.y_coord;
			}
		}
	}

	double offset = (NODERADIUS * 2);

	if (xMax != xMin)
	{
		m_xScaling = (HEIGHT - offset) / (xMax - xMin);
	}
	else
	{
		m_xScaling = (HEIGHT - offset) / (xMax);
	}

	if (yMax != yMin)
	{
		m_yScaling = (HEIGHT - offset) / (yMax - yMin);
	}
	else
	{
		m_yScaling = (HEIGHT - offset) / (yMax);
	}

	m_xOffset = xMin;
	m_yOffset = yMin;
}

void DrawingArea::drawLinks(
		QPainter* painter,
		neighbor_tuple& nbrs,
		int srcX,
		int srcY)
{
	neighbor_tuple::iterator neighbors;
	for (neighbors = nbrs.begin(); neighbors != nbrs.end(); neighbors++)
	{
		NodeData tgtData = m_scene[m_time][*neighbors];

		int tgtX = (tgtData.x_coord - m_xOffset) * m_xScaling;
		int tgtY = (tgtData.y_coord - m_yOffset) * m_yScaling;

		painter->setPen(QPen(Qt::black, 2, Qt::DotLine, Qt::RoundCap));
		painter->drawLine(srcX + 10, srcY + 10, tgtX + 10, tgtY + 10);
	}
}
