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

int Save_IP_Hostname_Fp(std::string IP, std::string Hostname){
  std::ofstream IP_Hostname_fp ("Config/IP.txt", std::fstream::in | std::fstream::out | std::fstream::app);
  if(IP_Hostname_fp.is_open()) {
    //IP_Hostname_fp.seekp(IP_Hostname_fp.end);
    std::string OutputStr = "\nIP="+IP+" HOSTNAME=" + Hostname;
    IP_Hostname_fp << OutputStr;
    IP_Hostname_fp.close();
    std::cout << "Added user to IP.txt" << std::endl;
  }
}

int Find_Hostname(std::string Hostname) {
  std::cout << "Checking if hostname is taken..." << std::endl;
  std::ifstream IP_Hostname_fp ("Config/IP.txt");
  int succ = 0;
  if(IP_Hostname_fp.is_open()) {
    std::string buffer;
    std::string hostBuffer;
    while( getline(IP_Hostname_fp,buffer) ) {
      std::cout << buffer << std::endl;
      std::size_t found = buffer.find("=");
      found=buffer.find("=",found+1);
      if (found!=std::string::npos)
        //std::cout << "Hostname pos:" << found << '\n';
        hostBuffer = buffer.substr(found+1);
        std::cout << "Checking hostname: " << hostBuffer << std::endl;
        if (hostBuffer.compare(Hostname) == 0) {
          std::cout << "Taken" << std::endl;
          succ = 1;
          return 1;
        }
      }
      IP_Hostname_fp.close();
    }
  else {
    std::cout << "Unable to open file" << std::endl;
  }
  if (succ == 0) {
    std::cout << "Not taken!" << std::endl;
    return 0;
  }
}
