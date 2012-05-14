#include "serverthread.h"
#include "rsd_server.h"

ServerThread::ServerThread()
{
}


void ServerThread::run()
{
    ServerStart();
    exec();
}

