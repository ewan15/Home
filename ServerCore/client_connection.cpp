#include "client_connection.h"
#include "RPiControl.h"
#include "IO_System/IP_Fp.h"
#include "command_finder.h"

void *task1 (void *dummyPt)
{
    int connFd = *((int *)dummyPt);
    std::cout << "Thread No: " << pthread_self() << std::endl;
    char msg[512];
    //bzero(msg, 301);
    bool loop = false;
    int RPi=0;

    // Find IP address of client
    socklen_t len;
    struct sockaddr_storage addr;
    char ipstr[INET6_ADDRSTRLEN];
    memset(ipstr,'0',sizeof(ipstr));
    int port;

    len = sizeof(addr);
    getpeername(connFd, (struct sockaddr*)&addr, &len);

    // deal with both IPv4 and IPv6:
    if (addr.ss_family == AF_INET) {
      struct sockaddr_in *s = (struct sockaddr_in *)&addr;
      port = ntohs(s->sin_port);
      inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
    } else { // AF_INET6
      struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
      port = ntohs(s->sin6_port);
      inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
    }
    printf("Peer IP address: %s\n", ipstr);
    IP_To_Hostname(ipstr);


    char Username[512];
    //memset(Username,'0',sizeof(Username));
    if (recv(connFd, Username, 512, 0)==-1) {
      std::cout << "Error reading Username" << std::endl;
      /*std::cout << "\nClosing thread and conn" << std::endl;
      close(connFd);*/
    }else{
      std::cout << "Username is: " << Username << std::endl;
    }

    if (RPi_Checker(Username)==1) {
      std::cout << Username << " is a raspberry pi" << std::endl;
      RPi = 1;
    }else{
      RPi = 0;
    }
    Save_IP_Hostname_Fp(ipstr, Username);
    while (!loop) {
      read(connFd, msg, 512);
      std::cout << Username << " Said: " << msg << std::endl;
      Scan_Command(msg);
    }

    /*char command[300] = "light off";
    //write(connFd, command , sizeof(command));
    if (RPi == 1) {
      if (send(connFd, command, 300, 0) != -1) {
        std::cout << "Sent data to Pi" << std::endl;
        std::cout << "UserDC Recv" << std::endl;
        loop = true;
      }
    }
    std::cout << Username << std::endl;
    while(!loop)
    {
        char command[300] = "light off";
        //write(connFd, command , sizeof(command));
        if (RPi == 1) {
          if (send(connFd, command, 300, 0) == -1) {
            std::cout << "UserDC Recv" << std::endl;
            loop = true;
          }
          std::cout << "Sent data to Pi" << std::endl;
        }
        bzero(test, 301);
        recv(connFd, test, 300, 0);
        if (strcmp(test, "")!=0){
          std::cout << "UserDC Send" << std::endl;
          loop = true;
        }
    }*/
    std::cout << "\nClosing thread and conn" << std::endl;
    close(connFd);
}
