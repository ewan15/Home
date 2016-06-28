#include "connection.h"
#include "file_sys.h"

int SetupConnection(){
  int listenFd, portNo;
  bool loop = false;
  struct sockaddr_in svrAdd;
  struct hostent *server;
  portNo = 5968;
  //create client skt
  listenFd = socket(AF_INET, SOCK_STREAM, 0);
  if(listenFd < 0)
  {
      std::cerr << "Cannot open socket" << std::endl;
      return 0;
  }
  server = gethostbyname("home.com");
  if(server == NULL)
  {
      std::cerr << "Host does not exist" << std::endl;
      return 0;
  }
  bzero((char *) &svrAdd, sizeof(svrAdd));
  svrAdd.sin_family = AF_INET;
  bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);
  svrAdd.sin_port = htons(portNo);
  int checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
  if (checker < 0)
  {
      std::cout << "Cannot connect!" << std::endl;
      return 0;
  }
  else{
    std::cout << "Connected! \nPlease enter the name of the system" << std::endl;
    std::string UI_Num;
    getline(std::cin, UI_Num);
    send(listenFd, UI_Num.c_str(), 512, 0);
    RecvData(listenFd);
  }
}
int RecvData(int listenFd){
  for (;;) {
    char* output;
    std::cout << ">";
    std::string cmd;
    getline(std::cin, cmd);
    std::cout << "Cmd: " << cmd << std::endl;
    //recv(listenFd, output, 512, 0);
    send(listenFd, cmd.c_str(), 512, 0);
    recv(listenFd, output, 512, 0);
    if (strcmp(output, "Recv")==0) {
      std::cout << output << std::endl;
    }else{
      std::cout << "Packet unsuccessful" << std::endl;
    }
  }
}
