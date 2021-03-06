#include "MainWindow.h"

#include <QtGui>

MainWindow::MainWindow()
{

	m_drawing = new DrawingArea(this);
	setCentralWidget(m_drawing);

	createStatusBar();
	this->resize(1000, 800);

	parseAction = new QAction(tr("&Parse File"), this);
	parseAction->setStatusTip(tr("Open a trace file for parsing"));

	exportAction = new QAction(tr("&Export Scene"), this);
	exportAction->setStatusTip(tr("Export the current scene"));

	createToolBar();

	connect(parseAction, SIGNAL(triggered()), this, SLOT(parseFile()));
	connect(exportAction, SIGNAL(triggered()), this, SLOT(exportScene()));

	connect(m_spinBox, SIGNAL(valueChanged(int)), this, SLOT(timeChanged(int)));
	connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(timeChanged(int)));
}

void MainWindow::createStatusBar()
{
	m_slider = new QSlider(Qt::Horizontal);
	m_spinBox = new QSpinBox;
	m_statusBar = statusBar();
	m_statusBar->addWidget(m_spinBox);
	m_statusBar->addWidget(m_slider);

}

void MainWindow::createToolBar()
{
	topToolBar = addToolBar(tr("&File"));
	topToolBar->addAction(parseAction);
	topToolBar->addAction(exportAction);
}

void MainWindow::timeChanged(int time)
{
	m_spinBox->setValue(time);
	m_slider->setValue(time);
	m_drawing->setTime(time);
	m_drawing->update();
}

void MainWindow::exportScene()
{
	QMessageBox msgBox;
	msgBox.setText("Exporting is not yet implemented");
	msgBox.exec();
}

void MainWindow::parseFile()
{
	dataBuf.clear();
	QString fileName = QFileDialog::getOpenFileName(
			this,
			tr("Open File to parse..."), ".",
			tr("Vanetta Trace Files (*.tr)"));

	if (fileName.isEmpty())
	{
		return;
	}
	VanettaParser::getInstance()->setParseFile(fileName.toAscii().data());
	VanettaParser::getInstance()->parseFile(dataBuf);

	QString parsed;
	QString lines = " Timesteps found";

	m_slider->setMaximum(dataBuf.size());
	m_spinBox->setMaximum(dataBuf.size());

	parsed.setNum(dataBuf.size());
	parsed.append(lines);
	QMessageBox msg;
	msg.setText("Parsing Finished");
	msg.setInformativeText(parsed);
	msg.exec();
	m_drawing->setScene(dataBuf);
	m_drawing->update();
}
