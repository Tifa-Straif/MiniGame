#include "mvscene.h"
#include "mvform.h"

MvForm::MvForm(QWidget *parent):QMainWindow(parent)
{
	setupUi(this);
        setWindowTitle(trUtf8("MiniFuckingGame"));
	scene = new MvScene;
	graphicsView->setScene(scene);
}
