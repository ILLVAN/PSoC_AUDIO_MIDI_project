#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <String.h>
#include <ArduinoJson.h>

#define SDA 21
#define SCL 22
#define LED 2
#define RXD2 16
#define TXD2 17
#define OErestart 19
HardwareSerial psocSerial(2); 

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(SCL, SDA, U8X8_PIN_NONE);

//''''''''''NOTES AND SCALES '''''''''''''''''''''''
String notes[108]= {"C0 ", "C#0", "D0 ", "D#0", "E0 ", "F0 ", "F#0", "G0 ", "G#0", "A0 ", "A#0", "B0 ", "C1 ", "C#1", "D1 ", "D#1", "E1 ", "F1 ", "F#1", "G1 ", "G#1", "A1 ", "A#1", "B1 ", "C2 ", "C#2", "D2 ", "D#2", "E2 ", "F2 ", "F#2", "G2 ", "G#2", "A2 ", "A#2", "B2 ", "C3 ", "C#3", "D3 ", "D#3", "E3 ", "F3 ", "F#3", "G3 ", "G#3", "A3 ", "A#3", "B3 ", "C4 ", "C#4", "D4 ", "D#4", "E4 ", "F4 ", "F#4", "G4 ", "G#4", "A4 ", "A#4", "B4 ", "C5 ", "C#5", "D5 ", "D#5", "E5 ", "F5 ", "F#5", "G5 ", "G#5", "A5 ", "A#5", "B5 ", "C6 ", "C#6", "D6 ", "D#6", "E6 ", "F6 ", "F#6", "G6 ", "G#6", "A6 ", "A#6", "B6 ", "C7 ", "C#7", "D7 ", "D#7", "E7 ", "F7 ", "F#7", "G7 ", "G#7", "A7 ", "A#7", "B7 ", "C8 ", "C#8", "D8 ", "D#8", "E8 ", "F8 ", "F#8", "G8 ", "G#8", "A8 ", "A#8", "B8 "};
String chromatic = "chromatic";
uint8_t cScales[6][8][8] =  {{      // WORLD PENTATONICS                       
     {0, 2, 4, 7, 9, 0, 0, 0},          // 0 major pentatonic
     {0, 3, 5, 7, 10, 0, 0, 0},         // 1 minor pentatonic
     {0, 1, 5, 7, 8, 0, 0, 0},          // 2 kumoi penta [japan] 
     {0, 1, 5, 6, 10, 0, 0, 0},         // 3 iwato penta [japan] 
     {0, 1, 3, 7, 8, 0, 0, 0},          // 4 pelog penta [bali] 
     {0, 2, 5, 7, 9, 0, 0, 0},          // 5 hyojo penta [china] 
     {0, 3, 6, 7, 11, 0, 0, 0},         // 6 penta [china] 
     {0, 2, 5, 7, 10, 0, 0, 0},         // 7 penta [egypt]                                                           
    },                                  // BLUES & MINORS
    {{0, 3, 5, 6, 7, 10, 0, 0},         // 0 blues
     {0, 2, 3, 5, 7, 9, 11, 0},         // 1 melodic minor [MM1]
     {0, 2, 3, 5, 7, 9, 10, 0},         // 2 dorian [II]  
     {0, 1, 3, 5, 6, 8, 10, 0},         // 3 phrygian  [III]
     {0, 3, 5, 7, 10, 0, 0, 0},         // 4 minor pentatonic
     {0, 2, 3, 5, 7, 8, 11, 0},         // 5 harmonic minor [HM1]
     {0, 2, 3, 5, 7, 8, 10, 0},         // 6 aeolian [VI]
     {0, 1, 3, 5, 6, 8, 10, 0},         // 7 locrian [VII]
    },                                  // DOMINANT 7
    {{0, 2, 4, 0, 7, 9, 10, 0},         // 0 mixolydian_avoid4                         
     {0, 2, 4, 6, 7, 9, 10, 0},         // 1 mixolydian_#11 [MM4] 
     {0, 1, 4, 0, 7, 8, 10, 0},         // 2 HM5 mixolydian_b9b13_avoid4
     {0, 1, 3, 4, 6, 8, 10, 0},         // 3 altered/superlocrian [MM7]       
     {0, 2, 4, 0, 7, 8, 10, 0},         // 4 mixolydian_b13_avoid4  
     {0, 1, 3, 4, 6, 7, 9, 10},         // 5 HTFT [half tone full tone] 
     {0, 2, 4, 6, 8, 10, 0, 0},         // 6 FT [full tone scale]   
     {0, 2, 4, 5, 7, 9, 10, 0},         // 7 mixolydian [V-7]   
    },                                  // CHURCH MODES
    {{0, 2, 4, 7, 9, 0, 0, 0},          // 0 major pentatonic
     {0, 2, 4, 5, 7, 9, 11, 0},         // 1 ionic [I]
     {0, 2, 3, 5, 7, 9, 10, 0},         // 2 dorian [II]
     {0, 1, 3, 5, 6, 8, 10, 0},         // 3 phrygian [III]
     {0, 2, 4, 6, 7, 9, 11, 0},         // 4 lydian [IV]
     {0, 2, 4, 5, 7, 9, 10, 0},         // 5 mixolydian [V7]
     {0, 2, 3, 5, 7, 8, 10, 0},         // 6 aeolian [VI]
     {0, 1, 3, 5, 6, 8, 10, 0},         // 7 locrian [VII]
    },                                  // HARMONIIC MINOR MODES
    {{0, 3, 5, 7, 8, 11, 0, 0},         // 0 HM penta+_b6°7
     {0, 2, 3, 5, 7, 8, 11, 0},         // 1 harmonic minor [HM1]
     {0, 1, 3, 5, 6, 9, 10, 0},         // 2 locrian_°6 [HM2]
     {0, 2, 4, 5, 6, 9, 11, 0},         // 3 ionic_#5 [HM3]                                   
     {0, 2, 3, 6, 7, 9, 10, 0},         // 4 dorian_#11 [HM4]
     {0, 1, 4, 5, 7, 8, 10, 0},         // 5 mixo_b9b13 [HM5]
     {0, 3, 4, 6, 7, 9, 11, 0},         // 6 lydian_#9 [HM6]                                   
     {0, 1, 3, 4, 6, 8, 9, 0},          // 7 HM7                                 
    },                                  // MELODIC MINOR MODES
    {{0, 3, 5, 7, 9, 11, 0, 0},         // 0 MM penta+_°6°7
     {0, 2, 3, 5, 7, 9, 11, 0},         // 1 melodic minor [MM1]
     {0, 1, 3, 5, 7, 9, 10, 0},         // 2 dorian_b2 [MM2] 
     {0, 2, 4, 6, 8, 9, 11, 0},         // 3 lydian_#5 [MM3]                                    
     {0, 2, 4, 6, 7, 9, 10, 0},         // 4 mixolydian_#11 [MM4]   
     {0, 2, 4, 5, 7, 8, 10, 0},         // 5 mixolydian_b13 [MM5]      
     {0, 2, 3, 5, 6, 8, 10, 0},         // 6 locrian_°9 [MM6]                                    
     {0, 1, 3, 4, 6, 8, 10, 0},         // 7 altered/superlocrian [MM7]                              
    }
};   

const String cScaleGroupNames[6] = {"WORLD PENTA" , "BLUES & MINs", "DOMINANT-7", "CHURCH MODES", "HARMONIC MIN", "MELODIC MIN"};
const String cScaleNames[6][8] = {
    // WORLD PENTATONICS
    {
        "0 major pentatonic",
        "1 minor pentatonic",
        "2 kumoi penta [japan]",
        "3 iwato penta [japan]",
        "4 pelog penta [bali]",
        "5 hyojo penta [china]",
        "6 penta [china]",
        "7 penta [egypt]"
    },
    // BLUES & MINORS
    {
        "0 blues",
        "1 melodic minor [MM1]",
        "2 dorian [II]",
        "3 phrygian [III]",
        "4 minor pentatonic",
        "5 harmonic minor [HM1]",
        "6 aeolian [VI]",
        "7 locrian [VII]"
    },
    // DOMINANT 7
    {
        "0 mixolydian_avoid4",
        "1 mixolydian_#11 [MM4]",
        "2 HM5 mixolydian_b9b13_avoid4",
        "3 altered/superlocrian [MM7]",
        "4 mixolydian_b13_avoid4",
        "5 HTFT [half tone full tone]",
        "6 FT [full tone scale]",
        "7 mixolydian [V-7]"
    },
    // CHURCH MODES
    {
        "0 major pentatonic",
        "1 ionic [I]",
        "2 dorian [II]",
        "3 phrygian [III]",
        "4 lydian [IV]",
        "5 mixolydian [V7]",
        "6 aeolian [VI]",
        "7 locrian [VII]"
    },
    // HARMONIC MINOR MODES
    {
        "0 HM penta+_b6*7",
        "1 harmonic minor [HM1]",
        "2 locrian_*6 [HM2]",
        "3 ionic_#5 [HM3]",
        "4 dorian_#11 [HM4]",
        "5 mixo_b9b13 [HM5]",
        "6 lydian_#9 [HM6]",
        "7 HM7"
    },
    // MELODIC MINOR MODES
    {
        "0 MM penta+_*6*7",
        "1 melodic minor [MM1]",
        "2 dorian_b2 [MM2]",
        "3 lydian_#5 [MM3]",
        "4 mixolydian_#11 [MM4]",
        "5 mixolydian_b13 [MM5]",
        "6 locrian_*9 [MM6]",
        "7 altered/superlocrian [MM7]"
    }
};
const String cScaleShorts[6][8] = {
    // WORLD PENTATONICS
    {
        "MAJ penta",
        "min penta",
        "kumoi [japan]",
        "iwato [japan]",
        "pelog [bali]",
        "hyojo [china]",
        "penta [china]",
        "penta [egypt]"
    },
    // BLUES & MINORS
    {
        "blues",
        "MM1",
        "dor [II]",
        "phrygian [III]",
        "min penta",
        "HM1",
        "aeolian [VI]",
        "locrian [VII]"
    },
    // DOMINANT 7
    {
        "mixo_av4",
        "mixo#11 [MM4]",
        "mixoHM5_b9b13av4",
        "alt/sloc [MM7]",
        "mixob13_av4",
        "HTFT",
        "FT ",
        "mixo [V7]"
    },
    // CHURCH MODES
    {
        "MAJ penta",
        "ionic [I]",
        "dorian [II]",
        "phrygian [III]",
        "lydian [IV]",
        "mixolyd [V7]",
        "aeolian [VI]",
        "locrian [VII]"
    },
    // HARMONIC MINOR MODES
    {
        "HM penta+_b6*7",
        "HM1",
        "locri_*6 [HM2]",
        "ionic_#5 [HM3]",
        "dor_#11 [HM4]",
        "mixo_b9b13 [HM5]",
        "lyd#9 [HM6]",
        "HM7"
    },
    // MELODIC MINOR MODES
    {
        "MM penta_*6*7",
        "MM1",
        "dor_b2 [MM2]",
        "lyd_#5 [MM3]",
        "mixo#11 [MM4]",
        "mixo_b13 [MM5]",
        "locr_*9 [MM6]",
        "alt/sloc [MM7]"
    }
};
//###################################################



hw_timer_t *displayTimer = NULL;
const int capacity = 150;         // ca JSON_OBJECT_SIZE(xmembers) + x*JSON_OBJECT_SIZE(1member);
StaticJsonDocument<capacity> JSONrec;

volatile boolean dataToDisplay = 1;
volatile double freq;
volatile uint16_t intFreq;
volatile String note;
volatile uint8_t noteIndex;
volatile uint8_t mode;         
char displayRoot[5] = "n#Y";  
char displayNote[5] = "n#Y";
char displayGroupName[40] = "helloGroup";
char displayScaleName[40] = "helloScale";
uint8_t recRoot2display;
uint8_t recNote2display;
uint8_t recGroup2display;
uint8_t recScale2display;


volatile uint8_t cScaleGroupSelect = 100;                                 // 0 world penta | 1 blues and minors | 2 dominant scales | 3 church modes | 100 chromatic
const uint8_t cScaleGroupsLength = 6;                                     // scale groups count
volatile uint8_t cScaleSelect = 100; 
volatile uint8_t displayTimerFlag = 0;

// void IRAM_ATTR onPSoCTimer(){
//   if(psocSerial.available()){
//     psocTimerFlag = 1;
//   }
// }


void IRAM_ATTR onDisplayTimer(){ 
  displayTimerFlag = 1;
}

void setup() {
  pinMode(OErestart, OUTPUT);
  digitalWrite(OErestart, HIGH);
  Serial.begin(115200);
  Serial.println("USB SERIAL RUNNING");
  psocSerial.begin(115200, SERIAL_8N1, RXD2, TXD2); 
  Serial.println("PSOC SERIAL RUNNING");
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0,0);
  displayTimer = timerBegin(0, 80, true); 
  timerAttachInterrupt(displayTimer , &onDisplayTimer, true);
  timerAlarmWrite(displayTimer, 100, true); 
  timerAlarmEnable(displayTimer);
  digitalWrite(OErestart, LOW);
}

void loop() {
  while (psocSerial.available()){
    String serialReceive = psocSerial.readStringUntil('\r');   
    //Serial.println(serialReceive);
    uint8_t recStartIdx = (serialReceive.indexOf('|'));
    serialReceive.remove(0, recStartIdx + 1);
      // Serial.println("Start " + (String)  recStartIdx);
    uint8_t recEndIdx = (serialReceive.lastIndexOf('|'));
    serialReceive.remove(recEndIdx);
    Serial.println(serialReceive);
      // Serial.println("Stop " + (String)  recEndIdx);  
    DeserializationError err = deserializeJson(JSONrec, serialReceive);
    if (err) {
      Serial.println(err.f_str());
    }
    else{
      recRoot2display = JSONrec["Rt"];
      Serial.println("Root " + (String) recRoot2display);
      recNote2display = JSONrec["Nt"];
      Serial.println("Note " + (String)  recNote2display);
      recGroup2display = JSONrec["Gp"];
      Serial.println("Group " + (String) recGroup2display);
      recScale2display = JSONrec["Sc"];
      Serial.println("Scale " + (String)  recScale2display);
      Serial.println("~~~~");
    }
  }
  if (displayTimerFlag){
    u8x8.clearLine(1);
    u8x8.setCursor(0,1);
    u8x8.print("R: ");
    u8x8.print(notes[recRoot2display]);
    u8x8.clearLine(2);
    u8x8.setCursor(0,2);
    u8x8.print("N: ");
    u8x8.print(notes[recNote2display]);
    u8x8.clearLine(3);
    u8x8.clearLine(4);
    u8x8.clearLine(5);
    u8x8.setCursor(0,3);
    u8x8.print("G: ");
    if (recGroup2display == 100){
       u8x8.print(chromatic);
    }
    else{
      u8x8.print(cScaleGroupNames[recGroup2display]);
      u8x8.setCursor(0,5);
      u8x8.print(cScaleShorts[recGroup2display][recScale2display]);
    }
    
    u8x8.clearLine(6);
    u8x8.clearLine(7);
    displayTimerFlag = 0;
  }
  Serial.print("...");
  digitalWrite(OErestart, HIGH);
  delay(15);
  digitalWrite(OErestart, LOW);
}
