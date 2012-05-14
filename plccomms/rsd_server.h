#ifndef RSD_SERVER_H
#define RSD_SERVER_H


void ServerStart(void); //needs to run in it's own thread!

void* SocketHandler(void* lp); //needs to accept a QString or char* instead of taking direct userinput!


#endif
