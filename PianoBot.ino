#include <Wire.h>


// pin assignments


#define NOTES_OFF 0x00
#define PIN_C1 0x01
#define PIN_CSHARP1 0x02
#define PIN_D1 0x04
#define PIN_DSHARP1 0x08
#define PIN_E1 0x10
#define PIN_F1 0x20
#define PIN_FSHARP1 0x40
#define PIN_G1 0x80
#define PIN_GSHARP1 0x01
#define PIN_A1 0x02
#define PIN_ASHARP1 0x04
#define PIN_B1 0x08a
#define PIN_C2 0x10
#define PIN_CSHARP2 0x20


char sharp = 0;
unsigned int quarterNoteDelay = 1200;
unsigned int noteDelay;


// for when we hard code a song into the program
// char song[] = "qchdeeeeeeq#g";


void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(0x20);
  Wire.beginTransmission(0x22);
  Wire.write(NOTES_OFF);
  Wire.endTransmission();
	digitalWrite(7, HIGH);


  sharp = 0;
  noteDelay = quarterNoteDelay;
}


void loop()
{
 
  //the song goes here!
	if (Serial.available() > 0) {
  	int inByte = Serial.read();


   	 
  	// do something different depending on the character received.  
  	switch (inByte) {
    	case ' ':
      	// ignore spaces
      	break;
 	 
    	case '#':
      	sharp = 1; // sharp found.  Next note will be played sharp unless it is an E or B when it will be ignored
      	break;
   	 
    	case 'h':
    	case 'H':
      	noteDelay = quarterNoteDelay * 2;
      	break;


    	case 'w':
    	case 'W':
      	noteDelay = quarterNoteDelay * 4;
      	break;
   	 
    	case 'q':
    	case 'Q':
      	noteDelay = quarterNoteDelay;
      	break;
          	 
 	 
    	case 'a':    
      	if (sharp)
      	{
        	playnote(PIN_ASHARP1, noteDelay, 400);
        	Serial.write("ASHARP1");
      	}
      	else
      	{
        	playnote(PIN_A1, noteDelay, 400);
        	Serial.write("A1");
      	}
      	break;
   	 
    	case 'b':    
      	playnote(PIN_B1, noteDelay, 400);
      	Serial.write("B1");
      	break;
 	 
    	case 'c':    
      	if (sharp)
      	{
        	playnote(PIN_CSHARP1, noteDelay, 400);
        	Serial.write("CSHARP1");
        	sharp = 0;
      	}
      	else
      	{
        	playnote(PIN_C1, noteDelay, 400);
        	Serial.write("C1");
      	}
      	break;
     	 
    	case 'd':
      	if (sharp)
      	{
        	playnote(PIN_DSHARP1, noteDelay, 400);
        	Serial.write("DSHARP1");
      	}
      	else
      	{
        	playnote(PIN_D1, noteDelay, 400);
        	Serial.write("D1");
      	}
      	break;
     	 
    	case 'e':    
      	playnote(PIN_E1, noteDelay, 400);
      	Serial.write("E1");
      	break;
    
    	case 'f':
      	if (sharp)
      	{
        	playnote(PIN_FSHARP1, noteDelay, 400);
        	Serial.write("FSHARP1");
        	sharp = 0;
      	}
      	else
      	{
        	playnote(PIN_F1, noteDelay, 400);
        	Serial.write("F1");
      	}
      	break;
   	 
    	case 'g':    
      	if (sharp)
      	{
        	playnote(PIN_GSHARP1, noteDelay, 400);
        	Serial.write("GSHARP1");
        	sharp = 0;
      	}   
        	else
      	{
        	playnote(PIN_G1, noteDelay, 400);
        	Serial.write("G1");
      	}
      	break;
   	 
    	case 'C':    
      	if (sharp)
      	{
        	playnote(PIN_CSHARP2, noteDelay, 400);
        	Serial.write("CSHARP2");
        	sharp = 0;
      	}
      	else
      	{
        	playnote(PIN_C2, noteDelay, 400);
        	Serial.write("C2");
      	}
      	break;
 
    	default:
      	// turn all the LEDs off:
      	for (int thisPin = 2; thisPin < 7; thisPin++)
      	{
        	digitalWrite(thisPin, LOW);
      	}
  	}
  	Serial.flush();
    
  }


}


int playnote(unsigned int note, unsigned int duration, unsigned int afterNote)
{
  //digitalWrite(note, HIGH);
  //delay(duration);
  //digitalWrite(note, LOW);
  //delay(afterNote);
  Serial.write(note);
  Serial.flush();
  Wire.beginTransmission(0x20);
  Wire.write(note);
  Wire.endTransmission();
  delay(duration);
  Wire.beginTransmission(0x20);
  Wire.write(NOTES_OFF);
  Wire.endTransmission();
  delay(afterNote);
}


// calculate which I2C address based on the note played
int iinfo(int note)
{
  if((note >= PIN_C1)&&(note <= PIN_G1))
	return 0x20;
  else
	if((note >= PIN_GSHARP1)&&(note <= PIN_B1))
  	return 0x22;
	else
  	0;
}











