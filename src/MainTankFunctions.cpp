#include <Arduino.h>
#include "GlobalVar.h"
#include "Pumps.h"
#include "MainTankFunctions.h"

//Create objects for each pump
Pumps MainPump(MainPumpPin, "MainPump");
Pumps AuxPump(AuxPumpPin, "AuxPump");
Pumps MixPump1(MixPump1Pin, "MixPump1");
Pumps MixPump2(MixPump2Pin, "MixPump2");

//Create function MainTank_Init()
void MainTank_Init()
{
    //Initialize the solenoid valve
    pinMode(SolenoidValveInPin, OUTPUT);
    pinMode(SolenoidValveOutPin, OUTPUT);
    digitalWrite(SolenoidValveInPin, LOW);
    digitalWrite(SolenoidValveOutPin, LOW);

    //Initialize the float switches
    pinMode(FloatSwitchHighPin, INPUT_PULLUP);
    pinMode(FloatSwitchMidPin, INPUT_PULLUP);
    pinMode(FloatSwitchLowPin, INPUT_PULLUP);

    //Initialize the pumps
    MainPump.OFF();
    AuxPump.OFF();
    MixPump1.OFF();
    MixPump2.OFF();
}

//Create function MainTank_GetLevel()
byte MainTank_GetLevel()
{
    //Read the float switches
    if (digitalRead(FloatSwitchHighPin) == HIGH)
    {
        MainTankLevel = 3;
    }
    else if (digitalRead(FloatSwitchMidPin) == HIGH)
    {
        MainTankLevel = 2;
    }
    else if (digitalRead(FloatSwitchLowPin) == HIGH)
    {
        MainTankLevel = 1;
    }
    else
    {
        MainTankLevel = 0;
    }
    return MainTankLevel;
}

//Create function to MainTank_Fill() to target level then stop
void MainTank_Fill(byte targetLevel)
{
    //Check if the target level is higher than the current level
    if (targetLevel > MainTankLevel)
    {
        //Check if the solenoid valve is not already in the target position
        if (digitalRead(SolenoidValveInPin) == LOW)
        {
            //Turn on the solenoid valve
            digitalWrite(SolenoidValveInPin, HIGH);
            digitalWrite(SolenoidValveOutPin, LOW);
        }
    }
    //Check if the target level is lower than the current level
    else if (targetLevel < MainTankLevel)
    {
        //Check if the solenoid valve is not already in the target position
        if (digitalRead(SolenoidValveOutPin) == LOW)
        {
            //Turn on the solenoid valve
            digitalWrite(SolenoidValveInPin, LOW);
            digitalWrite(SolenoidValveOutPin, HIGH);
        }
    }
    //Check if the target level is equal to the current level
    else
    {
        MainTank_Lock();
    }
}

//Create function to MainTank_Flush() to target level then stop
void MainTank_Flush(byte targetLevel);
{
    //Check if the target level is higher than the current level
    if (targetLevel > MainTankLevel)
    {
        //Check if the solenoid valve is not already in the target position
        if (digitalRead(SolenoidValveOutPin) == LOW)
        {
            //Turn on the solenoid valve
            digitalWrite(SolenoidValveInPin, LOW);
            digitalWrite(SolenoidValveOutPin, HIGH);
        }
    }
    //Check if the target level is lower than the current level
    else if (targetLevel < MainTankLevel)
    {
        //Check if the solenoid valve is not already in the target position
        if (digitalRead(SolenoidValveInPin) == LOW)
        {
            //Turn on the solenoid valve
            digitalWrite(SolenoidValveInPin, HIGH);
            digitalWrite(SolenoidValveOutPin, LOW);
        }
    }
    //Check if the target level is equal to the current level
    else
    {
        MainTank_Lock();
    }
}

//Create function to MainTank_Lock()
void MainTank_Lock();
{
    //Lock the main tank
    digitalWrite(SolenoidValveInPin, LOW);
    digitalWrite(SolenoidValveOutPin, LOW);
}

//Create function to MainTank_Irrigate()
void MainTank_Irrigate();
{
    //Check if the main pump is not already running
    if (MainPump.PumpRunning == false)
    {
        //Turn on the main pump
        MainPump.ON();
    }
}

//Create function to MainTank_Mix() for a given time period. Then alternate between MixPump1 and MixPump2 for 30 seconds each. All other pumps must not run.
void MainTank_Mix(byte times);
{
    //Check if the main pump is running. If so, turn it off
    if (MainPump.PumpRunning == true)
    {
        MainPump.OFF();
    }
    //Check if the aux pump is running. If so, turn it off
    if (AuxPump.PumpRunning == true)
    {
        AuxPump.OFF();
    }
    //Turn on MixPump1 for 30 seconds then turn off. Turn on MixPump2 for 30 seconds then turn off. Repeat for times seconds.
    for (byte i = 0; i < times; i++)
    {
        MixPump1.ON();
        delay(30000);
        MixPump1.OFF();
        delay(30000);
        MixPump2.ON();
        delay(30000);
        MixPump2.OFF();
    }

}






