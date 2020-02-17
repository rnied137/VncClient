#ifndef VNCCLI_H
#define VNCCLI_H

#include <QThread>
#include <signal.h>
#include <rfb/rfbclient.h>
#include <iostream>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QThread>

class VncCli: public QObject
{

    Q_OBJECT
public:
    VncCli(QObject * parent = 0);


private:
    rfbClient * cl;


private:
    static rfbBool resize(rfbClient* client);
    static void update(rfbClient* cl,int x,int y,int w,int h);
    static rfbCredential* get_credential(rfbClient* cl, int credentialType);

public:
   void doSetup(QThread & thread);

public slots:
   void doWork();
};

#endif // VNCCLI_H
