#include "mvscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QtCore>

MvScene::MvScene(QObject *parent) : QGraphicsScene(parent)
{
        makeMap();
	setBackgroundBrush(QBrush(QColor(255,255,255), QPixmap("bg.jpg")));
}


//По нажатию левой клавиши размещает смайлы, правой - удаляет. Считывает положение мыши
void MvScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	if (mouseEvent->button() == Qt::LeftButton) 
                placeSmile(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
	if (mouseEvent->button() == Qt::RightButton) {
		QGraphicsItem * item = itemAt(mouseEvent->scenePos());
		if (item)
                        if (item->data(0) == "Smile")
				removeItem(item);
	}
			
}


//Рисуем карту. Где 1 - там земля, где 0 - ничего. Так как карта - одномерный массив, то переводим координаты в одномерные.
void MvScene::makeMap()
{
    int map[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,
                 0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,
                 0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
                 0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,
                 0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,
                 0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
                 0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
                 0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
                 0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,
                 0,1,1,0,0,1,1,1,0,0,0,1,1,0,0,
                 0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,
                 0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
                 0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                 };
        QBrush brush(QColor(255, 255, 255), QPixmap("mapGrass.jpg"));
        QPen pen(Qt::NoPen);
        for (int x = 0; x < 15; x++){
            for(int y = 0; y < 15; y++){
                if(map[x+15*y] == 1){
                QGraphicsItem * item =
                        addRect(QRectF(50*x,50*y,50,50), pen, brush);
                item->setData(0,"Map");
                }
            }
        }
}

//проверка на соударение объектов
QGraphicsItem * MvScene::itemCollidesWith(QGraphicsItem * item)
{
	QList<QGraphicsItem *> collisions = collidingItems(item);
	foreach (QGraphicsItem * it, collisions) {
        	if (it == item)
        	     continue;
		return it;
 	}
	return NULL;
}


//размещаем смайл на карте. для того, чтобы карта была сеткой, положение мыши округляем до ближайщего квадрата размером 50х50
void MvScene::placeSmile(float x, float y)
{
        QGraphicsItem *	smile = addPixmap(QPixmap("Smile.png"));
        div_t x1 = div(x,50);
        div_t y1 = div(y,50);
        smile->translate(x1.quot*50, y1.quot*50);
        if (itemCollidesWith(smile)->data(0)=="Map")
             smile->setData(0, "Smile");

        else{
            removeItem(smile);
        }
}
