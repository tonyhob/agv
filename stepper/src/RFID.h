#include <MFRC522.h>
#include <SPI.h>

//RFID
//Card 1: 31 F6 B1 1B
//Card 2: F3 AB 31 19
//Card 3: B3 99 1E 1D
//Card 4: 31 36 80 1B

#define RST_PIN         5         // Configurable, see typical pin layout above
#define SS_PIN          53        // Configurable, see typical pin layout above
#define IRQ_PIN         2


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::MIFARE_Key key;

volatile bool bNewInt = false;
byte regVal = 0x7F;
void activateRec(MFRC522 mfrc522);
void clearInt(MFRC522 mfrc522);

byte card0[4] = {0x5A, 0x0A, 0xE2, 0x0B};
byte card1[4] = {0x31, 0xF6, 0xB1, 0x1B};
byte card2[4] = {0xF3, 0xAB, 0x31, 0x19};
byte card3[4] = {0xB3, 0x99, 0x1E, 0x1D};
byte card4[4] = {0x31, 0x36, 0x80, 0x1B};
//---------------------------------------------------------- -

//Inductor setting
int Li, Ri;
int i = 0;

void readCard() {
  bNewInt = true;
}

void activateRec(MFRC522 mfrc522) {
  mfrc522.PCD_WriteRegister(mfrc522.FIFODataReg, mfrc522.PICC_CMD_REQA);
  mfrc522.PCD_WriteRegister(mfrc522.CommandReg, mfrc522.PCD_Transceive);
  mfrc522.PCD_WriteRegister(mfrc522.BitFramingReg, 0x87);
}

/*
   The function to clear the pending interrupt bits after interrupt serving routine
*/
void clearInt(MFRC522 mfrc522) {
  mfrc522.PCD_WriteRegister(mfrc522.ComIrqReg, 0x7F);
}