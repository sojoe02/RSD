#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>

class ServerThread : public QThread
{
public:
    ServerThread();
    void run();
};

#endif // SERVERTHREAD_H
