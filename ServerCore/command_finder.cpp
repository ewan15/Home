#include "command_finder.h"
#include "IO_System/IP_Fp.h"

void Scan_Command(std::string msg) {
  //Find_Hostname(msg);
  std::istringstream iss(msg);
  while (iss) {
      std::string word;
      iss >> word;
      if (word.compare("light")== 0) {
        std::cout << "Word says light" << std::endl;
      }
      if (word.compare("node") == 0) {
        printNodes();
      }
  }
}

void printNodes() {
  std::ifstream IP_Hostname_fp ("Config/IP.txt",std::ios::in);
  if(IP_Hostname_fp.is_open()) {
    std::string buffer;
    std::cout << std::endl << "############# Users on network ###############" << std::endl << std::endl;
    while( getline(IP_Hostname_fp,buffer) ) {
      std::cout << buffer << std::endl;
    }
  }
}
