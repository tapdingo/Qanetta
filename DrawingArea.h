#ifndef DRAWING_AREA_H
#define DRAWING_AREA_H

#include <QWidget>

#include "DataTypes.h"

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
	double m_time;
	TimeState m_scene;
};

#endif
