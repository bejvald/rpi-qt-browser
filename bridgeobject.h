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

    //General device functions
    QString getSerialNumber();
    QString getDisplayMode();
    void setDisplayMode(QString displaymode, int storagemode);
    QString getFirstAudioLanguage();
    void setFirstAudioLanguage(QString lang, int storagemode);
    QString getSecondAudioLanguage();
    void setSecondAudioLanguage(QString lang, int storagemode);
    QString getFirstSubtitleLanguage();
    void setFirstSubtitleLanguage(QString lang, int storagemode);
    QString getSecondSubtitleLanguage();
    void setSecondSubtitleLanguage(QString lang, int storagemode);

    //TODO: Change volume-functions to system-wide
    int getVolume();
    void setVolume(int volume);
    bool isMuted();
    void mute(bool m);
    QString getStandbyState();
    void setStandbyState(bool standby);
    void reboot();

    //Media player functions
    void open(QString uri);
    void play(int speed);
    void pause();
    void setPosition(int x, int y, int width, int height);
    void setFullscreen();




private:

    QQuickItem *root;


};

#endif // BRIDGEOBJECT_H
