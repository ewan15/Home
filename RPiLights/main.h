#ifndef _MAIN_H
#define _MAIN_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <thread>



int CreateGPIO(int GPIO);
int turnOnLight(int GPIO);
int turnOffLight(int GPIO);
void Question();
void Options(std::string option);
#endif
