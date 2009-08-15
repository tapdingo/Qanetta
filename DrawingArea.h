#ifndef DRAWING_AREA_H
#define DRAWING_AREA_H

#include <QWidget>

#include "DataTypes.h"

#define WIDTH  998
#define HEIGHT 725

class DrawingArea : public QWidget
{
	Q_OBJECT

	public:
	DrawingArea(QWidget* parent = 0);
	void paintEvent(QPaintEvent* event);
	void draw();
	void setTime(const double& time);
	void setScene(const TimeState& TimeState);

	private:

	void drawScene(QPainter* painter);
	void calculateParameters();
	void drawLinks(Nodes& nodes);
	double m_time;
	TimeState m_scene;

	double m_xScaling;
	double m_yScaling;
	int m_xOffset;
	int m_yOffset;
};

#endif
