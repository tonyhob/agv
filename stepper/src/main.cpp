#include <Arduino.h>

#include "stepper.h"
#include "RFID.h"

int command = 1;
int k = 0;

void setup()
{
  // Set the maximum speed in steps per second:
  stepperl1.setMaxSpeed(1000);
  stepperr1.setMaxSpeed(1000);
  stepperl2.setMaxSpeed(1000);
  stepperr2.setMaxSpeed(1000);
  Serial.begin(115200); // Initialize serial communications with the PC
  while (!Serial)
    ;          // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin(); // Init SPI bus

  mfrc522.PCD_Init(); // Init MFRC522 card

  /* read and printout the MFRC522 version (valid values 0x91 & 0x92)*/
  Serial.print(F("Ver: 0x"));
  byte readReg = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.println(readReg, HEX);

  /* setup the IRQ pin*/
  pinMode(IRQ_PIN, INPUT_PULLUP);

  /*
     Allow the ... irq to be propagated to the IRQ pin
     For test purposes propagate the IdleIrq and loAlert
  */
  regVal = 0xA0; //rx irq
  mfrc522.PCD_WriteRegister(mfrc522.ComIEnReg, regVal);

  bNewInt = false; //interrupt flag

  /*Activate the interrupt*/
  attachInterrupt(digitalPinToInterrupt(IRQ_PIN), readCard, FALLING);

  Serial.println(F("End setup"));
  //inductor
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop()
{
  //  Li = map(analogRead(A0), 0, 1023, 0, 255);
  //  Ri = map(analogRead(A1), 0, 1023, 0, 255);
  //  i++;
  //  if (i == 500) {
  ////    Serial.print("Left: ");
  ////    Serial.println(Li);
  ////    Serial.print("Right: ");
  ////    Serial.println(Ri);
  //    i = 0;
  //  }
  //  if (Li > Ri) {
  //    forward();
  //  } else if (Ri > Li) {
  //    forward();
  //  }
  if (bNewInt)
  { //new read interrupt
    Serial.print(F("Interrupt. "));
    mfrc522.PICC_ReadCardSerial(); //read the tag data
    // Show some details of the PICC (that is: the tag/card)
    Serial.print(F("Card UID:"));
    int flag = -1;
    if (mfrc522.uid.uidByte[0] == card0[0] && mfrc522.uid.uidByte[1] == card0[1] && mfrc522.uid.uidByte[2] == card0[2] && mfrc522.uid.uidByte[3] == card0[3])
    {
      flag = 0;
    }
    else if (mfrc522.uid.uidByte[0] == card1[0] && mfrc522.uid.uidByte[1] == card1[1] && mfrc522.uid.uidByte[2] == card1[2] && mfrc522.uid.uidByte[3] == card1[3])
    {
      flag = 1;
    }
    else if (mfrc522.uid.uidByte[0] == card2[0] && mfrc522.uid.uidByte[1] == card2[1] && mfrc522.uid.uidByte[2] == card2[2] && mfrc522.uid.uidByte[3] == card2[3])
    {
      flag = 2;
    }
    else if (mfrc522.uid.uidByte[0] == card3[0] && mfrc522.uid.uidByte[1] == card3[1] && mfrc522.uid.uidByte[2] == card3[2] && mfrc522.uid.uidByte[3] == card3[3])
    {
      flag = 3;
    }
    else if (mfrc522.uid.uidByte[0] == card4[0] && mfrc522.uid.uidByte[1] == card4[1] && mfrc522.uid.uidByte[2] == card4[2] && mfrc522.uid.uidByte[3] == card4[3])
    {
      flag = 4;
    }
    if (flag == 0)
    {
      Serial.println("YEs");
    }
    else if (flag == 1)
    {
      command = 2;
    }
    else if (flag == 2)
    {
      command = 2;
    }
    else if (flag == 3)
    {
      command = 2;
    }
    else if (flag == 4)
    {
      command = 0;
    }
    clearInt(mfrc522);
    mfrc522.PICC_HaltA();
    bNewInt = false;
  }
  k++;
  if (k > 1000)
  {
    activateRec(mfrc522);
    k = 0;
  }
  if (command == 1)
  {
    forward();
  }
  else if (command == 0)
  {
    stopmove();
  }
  else if (command == 2)
  {
    left90();
    command = 1;
  }
}
