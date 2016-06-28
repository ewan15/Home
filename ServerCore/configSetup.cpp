#include "configSetup.h"

void configSetup(){
  IP_File_Format();
}
void IP_File_Format(){
  std::ofstream ofs;
  ofs.open("Config/IP.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();
}
