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
    int loop = 0;
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
    //IP_To_Hostname(ipstr);


    char Username[512];
    //memset(Username,'0',sizeof(Username));
    if (recv(connFd, Username, 512, 0)==-1) {
      std::cout << "Error reading Username" << std::endl;
      close(connFd);
      pthread_exit(NULL);
    }else{
      std::cout << "Username is: " << Username << std::endl;
    }
    if (Find_Hostname(Username) != 0) {
      close(connFd);
      pthread_exit(NULL);
    }
    if (RPi_Checker(Username)==1) {
      std::cout << Username << " is a raspberry pi" << std::endl;
      RPi = 1;
    }else{
      RPi = 0;
    }
    if (Save_IP_Hostname_Fp(ipstr, Username)==-1) {
      std::cout << "Hostname already exists" << std::endl;
      loop = 0;
    }
    else{
      while (loop == 0) {
        char recvStr[5] = "secv";
        if (send(connFd, recvStr, 512, 0)==-1){
          std::cout << "connection error testing connection" << std::endl;
          loop = 1;
          break;
        }
        if (recv(connFd, msg, 512, 0)==-1) {
          std::cout << "connection error when recv closing connection" << std::endl;
          loop = 1;
          break;
        }
        std::cout << std::endl << Username << " Said: " << msg << std::endl;
        if (send(connFd, recvStr, 512, 0)==-1){
          std::cout << "connection error when sending data to client" << std::endl;
          loop = 1;
          break;
        }
        if (loop == 0) {
          std::cout << "Command being scanned" << std::endl ;
          Scan_Command(msg);
        }
      }
    }
    std::cout << "\nClosing thread and conn" << std::endl;
    close(connFd);
}
