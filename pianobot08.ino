// pin assignments


#define PIN_C1 12
#define PIN_CSHARP1 4
#define PIN_D1 11
#define PIN_DSHARP1 3
#define PIN_E1 10
#define PIN_F1 9
#define PIN_FSHARP1 2
#define PIN_G1 8
#define PIN_GSHARP1 A0
#define PIN_A1 7
#define PIN_ASHARP1 0
#define PIN_B1 6
#define PIN_C2 5
#define PIN_CSHARP2 A1
char sharp = 0;
unsigned int quarterNoteDelay = 1200;
unsigned int noteDelay;


char song[] = "qchdeeeeeeq#g";


void setup()
{
  Serial.begin(9600);
  pinMode(PIN_C1, OUTPUT);
  pinMode(PIN_CSHARP1, OUTPUT);
  pinMode(PIN_D1, OUTPUT);
  pinMode(PIN_DSHARP1, OUTPUT);
  pinMode(PIN_E1, OUTPUT);
  pinMode(PIN_F1, OUTPUT);
  pinMode(PIN_FSHARP1, OUTPUT);
  pinMode(PIN_G1, OUTPUT);
  pinMode(PIN_GSHARP1, OUTPUT);
  pinMode(PIN_A1, OUTPUT);
  pinMode(PIN_ASHARP1, OUTPUT);
  pinMode(PIN_B1, OUTPUT);
  pinMode(PIN_C2, OUTPUT);


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
        
        case 'E':
        noteDelay = quarterNoteDelay / 2;
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
        break;
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
    	Serial.write("F1");
  	}
  	playnote(PIN_F1, noteDelay, 400);
 	 
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
        case 'c2':    
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
  	for (int thisPin = 2; thisPin < 7; thisPin++) {
    	digitalWrite(thisPin, LOW);
  	}
	}
	Serial.flush();
    
  }


}


int playnote(int note, unsigned int duration, unsigned int afterNote)
{
  digitalWrite(note, HIGH);
  delay(duration);
  digitalWrite(note, LOW);
  delay(afterNote);
}















