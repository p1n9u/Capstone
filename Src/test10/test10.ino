#include <Time.h>
#include <TimeAlarms.h>
#include <Arduino.h>
#include "BG96.h"

#define DebugSerial Serial
#define M1Serial	Serial1
#define ECGSerial Serial2
#define PWR_PIN		2
#define STAT_PIN	3

BG96 BG96(M1Serial, DebugSerial, PWR_PIN, STAT_PIN);

void setup() {
	// put your setup code here, to run once:
	M1Serial.begin(115200);
	DebugSerial.begin(115200);
  ECGSerial.begin(115200);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

	/* BG96 Power On Sequence */
	if ( BG96.isPwrON() )
	{
		DebugSerial.println("BG96 Power ON Status");
		if ( BG96.pwrOFF() ) {
			DebugSerial.println("BG96 Power Off Error");
		} else {
			DebugSerial.println("BG96 Power Off Success");
			DebugSerial.println("Module Power ON Sequence Start");
			if ( BG96.pwrON() ) {
				DebugSerial.println("BG96 Power ON Error");
			} else
				DebugSerial.println("BG96 Power ON Success");
		}
	}
	else
	{
		DebugSerial.println("BG96 Power OFF Status");
		if ( BG96.pwrON() ) {
			DebugSerial.println("BG96 Power ON Error");
		} else
			DebugSerial.println("BG96 Power ON Success");
	}

	/* BG96 Module Initialization */
	if (BG96.init()) {
		DebugSerial.println("BG96 Module Error!!!");
	}

	/* BG96 Module Power Saving Mode Disable */
	if (BG96.disablePSM()) {
		DebugSerial.println("BG96 PSM Disable Error!!!");
	}

	/* Network Regsistraiton Check */
	while (BG96.canConnect() != 0) {
		DebugSerial.println("Network not Ready !!!");
		delay(2000);
	}

  DebugSerial.println("BG96 Module Ready!!!");
}

void loop() {
  /*
  int i = 0;
  while (i<10000) {
    if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
    } else {
    // send the value of analog input 0:
      Serial.println(analogRead(A0));
    }
    //Wait for a bit to keep serial data from saturating
    delay(1);
    i++;
  }
  */
  char _IP[] = "166.104.185.207";
  int  _PORT = 8087;

  String sendMsg = "";

  int i=0;
  while (i<10) {
    sendMsg += String(i) + "\n";
    i++;
  }
  DebugSerial.println("data passed");
  if (BG96.actPDP() == 0) {
    DebugSerial.println("BG96 PDP Activation!!!");
  }

  if (BG96.socketCreate(1, _IP, _PORT) == 0)
    DebugSerial.println("TCP Socket Create!!!");


    if ( BG96.socketSend(sendMsg.c_str()) == 0 ) {
        DebugSerial.print("[TCP Send] >>  ");
        DebugSerial.println(sendMsg);
    } else {
        DebugSerial.println("Send Fail!!!");
    }

  if (BG96.socketClose() == 0) {
    DebugSerial.println("Socket Close!!!");
  }

  if (BG96.deActPDP() == 0) {
    DebugSerial.println("BG96 PDP DeActivation!!!");
  }

	delay(100);

}
