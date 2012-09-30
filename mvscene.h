#include <QGraphicsScene>

class MvScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MvScene(QObject *parent = 0);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
    void makeMap();
    QGraphicsItem * itemCollidesWith(QGraphicsItem * item);
    void placeSmile(float x, float y);

};
