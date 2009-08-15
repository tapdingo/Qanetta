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
	m_painter = &painter;
	m_painter->setRenderHint(QPainter::Antialiasing);
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
		drawScene();
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

void DrawingArea::drawScene()
{
	Nodes currentTime = m_scene[m_time];

	//Clear the old stuff out
	m_linkList.clear();
	m_nodeList.clear();
	m_rList.clear();

	//Draw the nodes
	Nodes::iterator it;
	for(it = currentTime.begin(); it != currentTime.end(); it++)
	{
		int id = it->first;
		int nodeX = (it->second.x_coord - m_xOffset) * m_xScaling;
		int nodeY = (it->second.y_coord - m_yOffset) * m_yScaling;

		m_nodeList[id].x_coord = nodeX;
		m_nodeList[id].y_coord = nodeY;

		addLinks(it->second.neighbors, id);
		addRoutes(it->second.topology, it->second.neighbors, id);
	}

	drawLinks();
	drawNodes();
	drawRtable();
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

void DrawingArea::drawLinks()
{
	LinkList::iterator neighbors;
	for (neighbors = m_linkList.begin(); neighbors != m_linkList.end(); neighbors++)
	{

		int srcId = neighbors->src;
		int srcX = m_nodeList[srcId].x_coord;
		int srcY = m_nodeList[srcId].y_coord;

		int tgtId = neighbors->tgt;
		int tgtX = m_nodeList[tgtId].x_coord;
		int tgtY = m_nodeList[tgtId].y_coord;

		m_painter->setPen(QPen(Qt::black, 2, Qt::DotLine, Qt::RoundCap));
		m_painter->drawLine(srcX + 10, srcY + 10, tgtX + 10, tgtY + 10);
	}
}

void DrawingArea::drawRtable()
{
	QString rTableString ("Target NextHop");

	RoutingList::iterator rTables;

	for (rTables = m_rList.begin(); rTables != m_rList.end(); rTables++)
	{
		int nodeId = rTables->first;
		int rTableX = m_nodeList[nodeId].x_coord + 20;
		int rTableY = m_nodeList[nodeId].y_coord + 20;

		link_tuple rTable = rTables->second;
		if (rTable.size() > 0)
		{
			//20 * size for the links , 20 for the Caption
			int rTableSize = 18 * rTable.size() + 20;
			m_painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
			m_painter->drawRoundRect(rTableX, rTableY, 130, rTableSize);

			int textX = rTableX + 12;
			int textY = rTableY + 15;
			m_painter->drawText(textX, textY, rTableString);
			textY += 20;

			link_tuple::iterator nit;
			for (nit = rTable.begin(); nit != rTable.end(); nit++)
			{
				QString tgt;
				tgt.setNum(nit->first);
				QString nHop;
				nHop.setNum(nit->second);
				QString tableLine;
				tableLine.append("  ");
				tableLine.append(tgt);
				tableLine.append("           ");
				tableLine.append(nHop);
				m_painter->drawText(textX, textY, tableLine);
				textY += 16;
			}
		}
	}
}

void DrawingArea::drawNodes()
{
	NodeList::iterator it;
	for (it = m_nodeList.begin(); it != m_nodeList.end(); it++)
	{
		int nodeX = it->second.x_coord;
		int nodeY = it->second.y_coord;
		m_painter->setFont(QFont("Arial", 10));
		m_painter->setRenderHint(QPainter::Antialiasing, true);
		m_painter->setPen(QPen(Qt::black, 2, Qt::DashDotLine, Qt::RoundCap));
		m_painter->drawEllipse(nodeX , nodeY, 20, 20);

		QString node;
		node = "Node ";
		QString nodeId;
		nodeId.setNum(it->first);
		node.append(nodeId);
		m_painter->drawText(nodeX + 25, nodeY + 15, node);
	}
}

void DrawingArea::addLinks(neighbor_tuple& nbrs, int id)
{
	neighbor_tuple::iterator neighbors;
	for (neighbors = nbrs.begin(); neighbors != nbrs.end(); neighbors++)
	{
		NeighborTuple neigh;
		neigh.src = id;
		neigh.tgt = *neighbors;
		m_linkList.push_back(neigh);
	}
}

void DrawingArea::addRoutes(link_tuple& topo, neighbor_tuple& neigh, int id)
{
	link_tuple rTable = topo;

	neighbor_tuple::iterator it;
	for (it = neigh.begin(); it != neigh.end(); it++)
	{
		rTable[*it] = *it;
	}

	m_rList[id] = rTable;
}
