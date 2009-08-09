#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

#include "DrawingArea.h"
#include "VanettaParser.h"

class QSlider;
class QSpinBox;

/*!
 * \brief The Main Window Form Class
 *
 * This Window handles all UI related stuff
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		/*!
		 * \brief Construct the Main Form Object
		 */
		MainWindow();

	private:

		/*!
		 * \brief Create the status bar
		 */
		void createStatusBar();

		/*!
		 * \brief Creates the top tool bar
		 */
		void createToolBar();

		QStatusBar* m_statusBar;  //!< The main status bar
		QSlider* m_slider;  //!< The slider Box for choosing a timestamp
		QSpinBox* m_spinBox;  //!< Spin Box for choosing a timestamp
		DrawingArea* m_drawing;  //!< Center Drawing Area

		QAction* parseAction;
		QAction* exportAction;
		QToolBar* topToolBar;

		private slots:
			void timeChanged(int time);
			void exportScene();
			void parseFile();
};

#endif
