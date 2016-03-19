#include "command_finder.h"
#include "IO_System/IP_Fp.h"

void Scan_Command(std::string msg) {
  Find_Hostname(msg);
  std::istringstream iss(msg);
  while (iss) {
      std::string word;
      iss >> word;
      if (word.compare("light")== 0) {
        std::cout << "Word says light" << std::endl;
      }
      std::cout << word << std::endl;
  }
}
