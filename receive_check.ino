// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"                        //Initializes the Library


unsigned char Flag_Recv = 0;
unsigned char len = 5;                      //Defines the Length of the data
unsigned char buf[8];                       //Defines the size of the Array
char str[20];

MCP_CAN CAN(10);                            //Set CS to pin 10

void setup()
{
    Serial.begin(500000);                   

START_INIT:

    if(CAN_OK == CAN.begin(CAN_1000KBPS))   //init can bus : baudrate = 1Mbps
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
    CAN.init_Mask(0,0,0xFF);                  //Sets the Mask to be 0xFF
    CAN.init_Mask(1,0,0xFF);                  //Sets the Mask to be 0xFF
    CAN.init_Filt(0,0,0x520);                 //Filters for 0x520 Address
}


void loop()
{
  int canId = CAN.getCanId();
  if(CAN_MSGAVAIL == CAN.checkReceive())      // check if data coming
    {
            CAN.readMsgBuf(&len, buf);        // read data,  len: data length, buf: data buf
            Serial.print(buf[0]);             //Prints the first indicies
            Serial.print("\t");
            Serial.println();
            return;
    }
}
