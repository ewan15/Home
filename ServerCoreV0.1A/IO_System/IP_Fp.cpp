#include "IP_Fp.h"

void IP_To_Hostname(std::string IP_Addr_Str){
  std::ifstream IP_Hostname_fp ("../Config/IP.txt");
  std::string line;
  if (IP_Hostname_fp.is_open())
  {
    while ( getline (IP_Hostname_fp,line) )
    {
      std::size_t Equals_Sign_Pos = line.find("=");
      std::size_t Space_Pos = line.find(" ");
      std::string IP_Addr = line.substr(Equals_Sign_Pos, Space_Pos);
      std::cout << "IP Address is: " << IP_Addr << '\n';
    }
    IP_Hostname_fp.close();
  }
  //std::cout << "Config RPi open!" << std::endl;
  IP_Hostname_fp.close();
}

void Save_IP_Hostname_Fp(std::string IP, std::string Hostname){
  std::ofstream IP_Hostname_fp ("Config/IP.txt", std::ios::out);
  if(IP_Hostname_fp.is_open()) {
    std::string OutputStr = "IP="+IP+" HOSTNAME=" + Hostname;
    IP_Hostname_fp << OutputStr;
    IP_Hostname_fp.close();
  }
}

void Find_Hostname(std::string Hostname) {
  std::ifstream IP_Hostname_fp ("Config/IP.txt",std::ios::in);
  if(IP_Hostname_fp.is_open()) {
    std::string buffer;
    while( getline(IP_Hostname_fp,buffer) ) {
      std::cout << buffer << std::endl;

      std::size_t found = buffer.find("=");
      found=buffer.find("=",found+1,6);
      if (found!=std::string::npos)
        std::cout << "Hostname pos:" << found << '\n';
      }

      IP_Hostname_fp.close();
    }
  else {
    std::cout << "Unable to open file" << std::endl;
  }
}
