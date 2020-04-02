/*
Disinfecting cabinet for CITE DPU

Zenlab innovation
by krittapan
Date 1/4/2020
For ESP32 ..

*/

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

// pin define

#define Sensor 35

#define Pump 17
#define pilot_lamp_rad 16
#define pilot_lamp_yellow 2
#define pilot_lamp_green 4

HardwareSerial DebugSerial = Serial1;
HardwareSerial MP3Serial = Serial1;

DFRobotDFPlayerMini myMP3Player;

uint8_t WorkStep = 0 ;
bool PumeStep = 0 ;
unsigned int UseCouter = 0 ;
unsigned long UserRelay = 1000;
unsigned long SprayRelay = 1000;
unsigned long SprayTime = 3000;
unsigned long last_time = 0;
 
void setup()
{
  DebugSerial.begin(9600);
  MP3Serial.begin(9600, SERIAL_8N1,16,17);

  DebugSerial.println();
  DebugSerial.println(F("Disinfecting cabinet"));
  DebugSerial.println(F("CITE DPU By krittapan"));

  pinMode(Pump, OUTPUT);
  pinMode(Sensor, INPUT);
  pinMode(pilot_lamp_rad, OUTPUT);
  pinMode(pilot_lamp_yellow, OUTPUT);
  pinMode(pilot_lamp_green, OUTPUT);


  if (!myMP3Player.begin(MP3Serial))
  {
    DebugSerial.println(F("Unable to begin:"));
    DebugSerial.println(F("1.Please recheck the connection!"));
    DebugSerial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  
  myMP3Player.setTimeOut(500);
  //----Set volume----
  myMP3Player.volume(10);  //Set volume value (0~30).
  myMP3Player.volumeUp(); //Volume Up
  myMP3Player.volumeDown(); //Volume Down

  //----Set different EQ----
  myMP3Player.EQ(DFPLAYER_EQ_NORMAL);
  
  //----Set device we use SD as default----
  myMP3Player.outputDevice(DFPLAYER_DEVICE_SD);

  //----Mp3 control----
  //  myMP3Player.sleep();     //sleep
  //  myMP3Player.reset();     //Reset the module
  //  myMP3Player.enableDAC();  //Enable On-chip DAC
  //  myMP3Player.disableDAC();  //Disable On-chip DAC
  //  myMP3Player.outputSetting(true, 15); //output setting, enable the output and set the gain to 15

  //----Read imformation----
  DebugSerial.println(myMP3Player.readState()); //read mp3 state
  DebugSerial.println(myMP3Player.readVolume()); //read current volume
  DebugSerial.println(myMP3Player.readEQ()); //read EQ setting
  DebugSerial.println(myMP3Player.readFileCounts()); //read all file counts in SD card
  DebugSerial.println(myMP3Player.readCurrentFileNumber()); //read current play file number
  DebugSerial.println(myMP3Player.readFileCountsInFolder(3)); //read file counts in folder SD:/03

  //lamp test

  LampControl(1,0,0);
  delay(500);
  LampControl(0,1,0);
  delay(500);
  LampControl(0,0,1);
  delay(500);
  LampControl(0,0,0);

  myPlayer(1);

}

void loop()
{
  DebugSerial.println("WorkStep = "+WorkStep);
  if (WorkStep == 0)
  { 
    WorkStep = (SensorRead()==0)?1:0;
  }
  else if (WorkStep == 1)
  {
    myPlayer(2);
    myPlayer(3);
    myPlayer(4);
    LampControl(0, 1, 0);
    PumpControl();
    WorkStep = 2 ;
  }
  else if (WorkStep == 2)
  {
    LampControl(0, 0, 1);
    myPlayer(5);
    while (SensorRead() == 0)
    {
      ;
    }
    delay(500);
    myPlayer(6);
    UseCouter++;
    DebugSerial.println("UseCouter = "+UseCouter);
    WorkStep=0;
  }
  delay(1); 
}
