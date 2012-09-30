#include <QMainWindow>
#include "ui_mainform.h" 

class MvScene;

class MvForm : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
	MvForm(QWidget *parent = 0);
private:
  	MvScene * scene;
};
