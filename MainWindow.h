#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

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
		 * \brief Crate the status bar
		 */
		void createStatusBar();
		QStatusBar* m_statusBar;  //!< The main status bar

};

#endif
