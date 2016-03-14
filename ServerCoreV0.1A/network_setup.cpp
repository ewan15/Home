#include "network_setup.h"
#include "client_connection.h"

int setup_Network(){

    int pId, portNo, listenFd;
    static int connFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;
    pthread_t threadA[100];
    portNo = 5968;

    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenFd < 0)
    {
        std::cerr << "Cannot open socket" << std::endl;
        return 0;
    }
    bzero((char*) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);
    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        std::cerr << "Cannot bind" << std::endl;
        return 0;
    }
    listen(listenFd, 5);
    len = sizeof(clntAdd);
    int noThread = 0;
    while (noThread < 100)
    {
        std::cout << "Listening" << std::endl;
        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);
        if (connFd < 0)
        {
            std::cerr << "Cannot accept connection" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Connection successful" << std::endl;
        }
        pthread_create(&threadA[noThread], NULL, task1, &connFd);
        noThread++;
    }
    for(int i = 0; i < 100; i++)
    {
        pthread_join(threadA[i], NULL);
    }
}
