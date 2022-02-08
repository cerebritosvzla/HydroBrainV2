#include <Arduino.h>
#ifndef MAINTANKFUNCTIONS_H
#define MAINTANKFUNCTIONS_H


void MainTank_Init();
void MainTank_Flush(byte targetLevel);
void MainTank_Fill(byte targetLevel);
void MainTank_Irrigate(int time);
void MainTank_Mix(int time);
byte MainTank_GetLevel();
void MainTank_Lock();
void MainTank_TopUp();








#endif