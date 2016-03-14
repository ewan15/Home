#include "connection.h"
#include "main.h"

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
  }else{
    std::cout << "Connected! \nPlease enter the name of the system" << std::endl;
    std::string UI_Num;
    getline(std::cin, UI_Num);
    char *UI_Num_Chr = new char[UI_Num.length() + 1];
    std::strcpy(UI_Num_Chr, UI_Num.c_str());
    send(listenFd, UI_Num_Chr, sizeof(UI_Num_Chr), 0);
  }

  for(;;)
  {
      char s[100];
      //cin.clear();
      //cin.ignore(256, '\n');
      char* test;
      recv(listenFd, s, sizeof(s), 0);
      std::cout << "Command: " << s << ":end" << std::endl;
      if (strcmp(s,"light off") == 0) {
        if (turnOffLight(4)==0) {
          std::cerr << "Unable to run turnOffLight" << std::endl;
        }
      }
      else if (strcmp(s,"light on") == 0) {
        if (turnOnLight(4)==0) {
          std::cerr << "Unable to run turnOnLight" << std::endl;
        }
      }
      else{
        std::cout << "Unkown command from remote users" << std::endl;
      }
  }
}
