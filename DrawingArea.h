#ifndef DRAWING_AREA_H
#define DRAWING_AREA_H

#include <QWidget>

class DrawingArea : public QWidget
{
	Q_OBJECT

	public:
	DrawingArea(QWidget* parent = 0);
	void paintEvent(QPaintEvent* event);
	void draw();
	void setTime(const double& time);

	private:

	double m_time;
};

#endif
