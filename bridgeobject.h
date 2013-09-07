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
    bool isMuted();
    void mute(bool m);
    void open(QString uri);
    void play(int speed);
    void pause();
    void setPosition(int x, int y, int width, int height);
    void setFullscreen();
    void reboot();
    QString getSerialNumber();


private:

    QQuickItem *root;


};

#endif // BRIDGEOBJECT_H
