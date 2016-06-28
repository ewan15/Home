#ifndef _IP_FP_H_
#define _IP_FP_H_

#include <iostream>
#include <string>
#include <fstream>
#include <istream>

void IP_To_Hostname(std::string IP_Addr_Str);
int Save_IP_Hostname_Fp(std::string IP, std::string Hostname);
int Find_Hostname(std::string);

#endif
