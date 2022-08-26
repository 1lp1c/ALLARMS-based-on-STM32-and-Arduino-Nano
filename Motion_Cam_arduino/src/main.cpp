#include <Arduino.h>

#include <SPI.h>
#include "LoRa.h"

// DEFINE------------------------------------

//------------------------------------------

// GLOBAL VARIABLE---------------------------
// LoRa RA-02~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LoRa RA-02 FREQUENCY~~~~~~~~~~~~~~~~~~~~~~
long double lora_frequency_to_send_data = 433000000.0;
long double lora_frequency_to_get_data = 444000000.0;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
String confirm_get_data = String("GET_DATA_FROM_PIDR_2_433_444_FREQUENCY_TEST_WITH_LONG_CONFIRM_DATA_12378978896564132_564654_6545646664%:?%;?:%;(*?:(*?%(12345678"); // CONFIRM GETTING DATA BY HAB
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//------------------------------------------

// GLOBAL BOOL-------------------------------
volatile boolean motion_Cam_flug = false; // FLUG FOR INTERRUPT
//------------------------------------------

// FUNCTION DECLARATION---------------------
void LORA_transmit();
void LORA_receive();
void LORA_callback();
//------------------------------------------

// FUNCTON FOR SET FLUG AFTER INTERRUPT-----
void motion_Cam()
{
  motion_Cam_flug = true;
}
//------------------------------------------

void setup()
{
  // INTERRUPT INIT----------------------------
  pinMode(3, INPUT_PULLUP);                // PIN  FOR INTERRUPTION
  attachInterrupt(1, motion_Cam, FALLING); // CONFIGURING INTERRUPTOIN
  //-------------------------------------------

  // START SERIAL------------------------------
  Serial.begin(115200);
  while (!Serial)
    ; // IF SERIAL HASN'T STARTED WE DONT GO TO OTHER PART OF PROGRAM
  // DEBUG SERIAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Serial.println("MOTOIN CAM BASED ON ARDUINO NANO IS ONN");
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //-------------------------------------------

  // FIRST LORA START---------------------------
  if (!LoRa.begin(444E6))
  {
    Serial.println("Starting LoRa failed!"); // IF LORA HASN'T STARTED
    while (1)
      ; // WE DONT GO TO OTHER PART OF PROGRAMM BECOSE LORA HASN'T STARDED
  }
  //-------------------------------------------

  // FOR RANDOM DELAY--------------------------------------------
  randomSeed(analogRead(A1)); // к пину A1 ничего не подключается
  //-------------------------------------------------------------
}

// LOOP TO YE LOOP))
void loop()
{
  if (motion_Cam_flug == true)
  {
    LORA_transmit();

    LORA_callback();
  }
}
//------------------

// FUNCTION FOR TRANSMIT ALLARM DATA FOR HUB
//------------------------------------------
void LORA_transmit()
{
  if (LoRa.begin(lora_frequency_to_send_data))
  { // RESTERT LORA TO OTHER FREQUENCY
    for (int i = 0; i < 4; i++)
    {
      // LORA SEND DATA------------------------
      LoRa.beginPacket();
      LoRa.print("ALLARM");
      LoRa.endPacket();
      //---------------------------------------

      // FOR DEBAGING--------------------------
      Serial.println("command send");
      //---------------------------------------

      delay(65); // FOR STM32 GET THIS DATA
      delay(random(35, 123));
    }
  }
}
//------------------------------------------

// FUNCTION FOR RECEIVE CALLBACK FROM HUB AND STOP TRANSMITTING ALLARM DATA
//------------------------------------------
void LORA_callback()
{
  // FUNCTION'S VARIABLES-------------------
  int count = 0; // щоб прийняти данні N разів
  uint16_t count_to_syebaca = 0;
  int packetSize = 0;
  // BOOLEAN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  boolean go_out_from_while_lora_available = false;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //----------------------------------------

  if (LoRa.begin(lora_frequency_to_get_data)) // RESTERT LORA TO OTHER FREQUENCY
  {
    while (true)
    {
      packetSize = LoRa.parsePacket(); // GET PACKET SIZE (NUMBER OF SYMBOLS)

      if (packetSize)
      {
        while (LoRa.available())
        {
          count++;

          // GET DATA FROM OTHER DEVICE------------
          String RxBuffer = LoRa.readString();
          // FOR DEBAGING~~~~~~~~~~~~~~~~~~~~~~~~~~
          {
            Serial.print("RxBuffer = ");
            Serial.print(RxBuffer);
          }
          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //---------------------------------------

          // FOR DEBAGING--------------------------
          {
            Serial.print("   ");
            Serial.print("count = ");
            Serial.println(count);
          }
          //---------------------------------------

          // STOP SENDING ALLARM DATA AFTER CONFIRM GETTING ALLARM DATA BY HAB
          if (RxBuffer == confirm_get_data)
          {
            motion_Cam_flug = false;
            go_out_from_while_lora_available = true;
            break;
          }
          //------------------------------------------------------------------

          // GO OUT FROM THIS FUNCTOIN IF GETTED DATA DOESN'T RESPONS STRING FOR CONFIRM DATA
          if (count == 10)
          {
            go_out_from_while_lora_available = true;
            break;
          }
          //---------------------------------------------------------------------------------
        }

        // IF RxBuffer == confirm_get_data - WE GO OUT FROM THIS FUNCTION
        if (go_out_from_while_lora_available)
          break;
        //---------------------------------------------------------------
      }

      // IF CONFIRM DATA FROM HAB HASN'T CAME - GO OUT FROM THIS FUNCTION AND SEND ALLARM DATA TO HAB AGAIN
      count_to_syebaca++;
      if (count_to_syebaca > 30000)
      {
        // FOR DEBAGING--------------------------
        Serial.println("syebaca");
        //---------------------------------------
        break;
      }
      //---------------------------------------------------------------------------------------------------
    }
  }
}
//------------------------------------------