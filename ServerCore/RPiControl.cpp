#include "RPiControl.h"
int RPi_Checker(char* name){
  char checker[100];
  strncpy(checker, (const char*)name, 3);
  //std::cout << checker << std::endl;
  if (strcmp(checker, "RPi") == 0) {
    return 1;//Equal
  }
  else{
    return 0;//Not Equal
  }
}
