#include "MainWindow.h"

#include <QtGui>

MainWindow::MainWindow()
{
	createStatusBar();
	this->resize(800, 600);
}

void MainWindow::createStatusBar()
{
	m_statusBar = statusBar();
}

