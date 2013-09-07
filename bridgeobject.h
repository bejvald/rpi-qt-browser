#ifndef BRIDGEOBJECT_H
#define BRIDGEOBJECT_H

#include <QObject>
#include <qquickview.h>

class bridgeObject : public QObject
{
    Q_OBJECT

public:
    explicit bridgeObject(QQuickItem *parent);
    
signals:

    
public slots:

    int getVolume();
    void setVolume(int volume);
    void open(QString uri);
    void play(int speed);
    void pause();
    void setPosition(int x, int y, int width, int height);
    void setFullscreen();


private:

    QQuickItem *root;


};

#endif // BRIDGEOBJECT_H
