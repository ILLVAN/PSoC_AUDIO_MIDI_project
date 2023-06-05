// ESP32 PSoC connector via UART

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

HardwareSerial psocSerial(2);                                       // Sserial used fpr PSoC communication

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(SCL, SDA, U8X8_PIN_NONE);     // display constructor

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

const String cScaleGroupNames[6] = {"WORLD PENTA" , "BLUES & MINs", "DOMINANT-7", "CHURCH MODES", "HARMONIC MIN", "MELODIC MIN"};  // display strings
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
const String cScaleShorts[6][8] = {   // short names to fit on screen
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



hw_timer_t *displayTimer = NULL;        // timer for updating the display
const int capacity = 180;               // ca JSON_OBJECT_SIZE(xmembers) + x*JSON_OBJECT_SIZE(1member); (JSON discouninued at the moment)
StaticJsonDocument<capacity> JSONrec;   // JSON buffer

volatile boolean dataToDisplay = 1; // Flag to indicate whether there is data to be displayed
volatile double freq; // Frequency variable
volatile uint16_t intFreq; // Integer frequency variable
volatile String note; // Note variable
volatile uint8_t noteIndex; // Index of the note
volatile uint8_t mode; // Mode variable

char displayRoot[5] = "n#Y"; // Character array for displaying root note
char displayNote[5] = "n#Y"; // Character array for displaying note
char displayGroupName[40] = "helloGroup"; // Character array for displaying group name
char displayScaleName[40] = "helloScale"; // Character array for displaying scale name

uint8_t recRootDisplay; // Display variable for received root note
uint8_t recNoteDisplay; // Display variable for received note
int8_t recOffsetDisplay; // Display variable for received offset
uint8_t recGroupDisplay; // Display variable for received group
uint8_t recScaleDisplay; // Display variable for received scale

uint8_t recRootDisplayOld; // Old display variable for received root note
uint8_t recNoteDisplayOld; // Old display variable for received note
int8_t recOffsetDisplayOld; // Old display variable for received offset
uint8_t recGroupDisplayOld; // Old display variable for received group
uint8_t recScaleDisplayOld; // Old display variable for received scale


volatile uint8_t cScaleGroupSelect = 100; // 0 world penta | 1 blues and minors | 2 dominant scales | 3 church modes | 4 HM | 5 MM | 100 chromatic
const uint8_t cScaleGroupsLength = 6;   // scale groups count
volatile uint8_t cScaleSelect = 100; // variable for selecting the scale
volatile uint8_t displayTimerFlag = 0; // Flag indicating if display should be updated

void IRAM_ATTR onDisplayTimer(){ 
  displayTimerFlag = 1; // Timer setting displayFlag
}

void setup() {
  pinMode(OErestart, OUTPUT); // Set OErestart pin as OUTPUT
  digitalWrite(OErestart, HIGH); // Set OErestart pin to HIGH
  Serial.begin(115200); // Initialize serial communication with baud rate 115200
  Serial.println("USB SERIAL RUNNING"); // Print message to indicate USB serial is running
  psocSerial.begin(115200, SERIAL_8N1, RXD2, TXD2); // Initialize PSOC serial communication with baud rate 115200 and specific pins
  Serial.println("PSOC SERIAL RUNNING"); // Print message to indicate PSOC serial is running
  u8x8.begin(); // Initialize u8x8 display
  u8x8.setPowerSave(0); // Disable power-saving mode of the display
  u8x8.setFont(u8x8_font_chroma48medium8_r); // Set the font for the display
  u8x8.setCursor(0,0); // Set the cursor position on the display
  displayTimer = timerBegin(0, 80, true); // Initialize and configure a timer
  timerAttachInterrupt(displayTimer , &onDisplayTimer, true); // Attach an interrupt function to the timer
  timerAlarmWrite(displayTimer, 1000, true); // Set the timer alarm to trigger every 1000 microseconds
  timerAlarmEnable(displayTimer); // Enable the timer alarm
  digitalWrite(OErestart, HIGH); // Set OErestart pin to HIGH to anable voltage shifting
}

void loop() {
  while (psocSerial.available()) {
    String serialReceive = psocSerial.readStringUntil('\r'); // Read serial data until a carriage return is encountered
    uint8_t recStartIdx = (serialReceive.indexOf('|')); // Find the index of the first occurrence of '|'
    serialReceive.remove(0, recStartIdx + 1); // Remove the characters before and including the '|'
    uint8_t recEndIdx = (serialReceive.lastIndexOf('|')); // Find the index of the last occurrence of '|'
    serialReceive.remove(recEndIdx); // Remove the characters after and including the '|'

    int tempIntArray[5], r = 0, t = 0;
    for (int i=0; i < serialReceive.length(); i++) {
      if(serialReceive.charAt(i) == ',') { // Check if the character is a comma
        tempIntArray[t] = serialReceive.substring(r, i).toInt(); // Convert the substring to an integer and store it in the temporary array
        r = (i + 1); // Update the starting index for the next substring
        t++; // Increment the temporary array index
      }
    }
    recRootDisplay = tempIntArray[0]; // Assign the received root display value from the temporary array
    recNoteDisplay = tempIntArray[1]; // Assign the received note display value from the temporary array
    recOffsetDisplay = tempIntArray[2]; // Assign the received offset display value from the temporary array
    recGroupDisplay = tempIntArray[3]; // Assign the received group display value from the temporary array
    recScaleDisplay = tempIntArray[4]; // Assign the received scale display value from the temporary array


    // old JSON VERSION.. discontinued: slow, too many bytes - but more comfortable
    // DeserializationError err = deserializeJson(JSONrec, serialReceive);
    // if (err) {
    //   Serial.println(err.f_str());
    // }
    // else{
    //   recRootDisplay = JSONrec["Rt"];
    //   Serial.println("Root " + (String) recRootDisplay);
    //   recNoteDisplay = JSONrec["Nt"];
    //   recOffsetDisplay = JSONrec["O2"];
    //   recGroupDisplay = JSONrec["Gp"];
    //   recScaleDisplay = JSONrec["Sc"];
    //   
    // }
    // -------------------
  }
  if (displayTimerFlag) {
    // OPTIONAL DEBUG PRINTS USB UART
    Serial.println("Root " + (String) recRootDisplay); // Print the received root display value
    Serial.println("Note " + (String) recNoteDisplay); // Print the received note display value
    Serial.println("Off2 " + (String) recOffsetDisplay); // Print the received offset display value
    Serial.println("Group " + (String) recGroupDisplay); // Print the received group display value
    Serial.println("Scale " + (String) recScaleDisplay); // Print the received scale display value

    if (recRootDisplay != recRootDisplayOld) {
      u8x8.clearLine(1); // Clear line 1 of the display
      u8x8.setCursor(0,1); // Set the cursor to line 1
      u8x8.print("root1: "); // Print the label for root1
      u8x8.print(notes[recRootDisplay]); // Print the corresponding note for root1
    }
    if (recRootDisplay != recRootDisplayOld || recOffsetDisplay != recOffsetDisplayOld) {
      u8x8.clearLine(2); // Clear line 2 of the display
      u8x8.setCursor(0,2); // Set the cursor to line 2
      u8x8.print("root2: "); // Print the label for root2
      u8x8.print(notes[recRootDisplay + recOffsetDisplay + 16]); // Print the corresponding note for root2
      if (recOffsetDisplay + 16 >= 0) {
        u8x8.print("+"); // Print a "+" sign if the offset is positive or zero
      }
      u8x8.print((String) (recOffsetDisplay + 16)); // Print the offset value
    }
    if (recNoteDisplay != recNoteDisplayOld) {
      u8x8.clearLine(3); // Clear line 3 of the display
      u8x8.setCursor(0,3); // Set the cursor to line 3
      u8x8.print("note1: "); // Print the label for note1
      u8x8.print(notes[recNoteDisplay]); // Print the corresponding note for note1
    }
    if (recNoteDisplay != recNoteDisplayOld || recOffsetDisplay != recOffsetDisplayOld) {
      u8x8.clearLine(4); // Clear line 4 of the display
      u8x8.setCursor(0,4); // Set the cursor to line 4
      u8x8.print("note2: "); // Print the label for note2
      u8x8.print(notes[recNoteDisplay + recOffsetDisplay + 16]); // Print the corresponding note for note2
    }

    if (recGroupDisplay != recGroupDisplayOld || recScaleDisplay != recScaleDisplayOld) {
      u8x8.clearLine(5); // Clear line 5 of the display
      u8x8.clearLine(6); // Clear line 6 of the display
      u8x8.setCursor(0,5); // Set the cursor to line 5
      if (recGroupDisplay == 100) {
        u8x8.print(chromatic); // Print the chromatic scale if the group is 100
      }
      else {
        u8x8.print(cScaleGroupNames[recGroupDisplay]); // Print the name of the scale group
        u8x8.setCursor(0,6); // Set the cursor to line 6
        u8x8.print(cScaleShorts[recGroupDisplay][recScaleDisplay]); // Print the short name of the scale within the group
      }
    }
    u8x8.clearLine(0); // Clear line 0 of the display
    u8x8.clearLine(7); // Clear line 7 of the display
    displayTimerFlag = 0; // Reset the display timer flag
    Serial.println("..."); // Print ellipsis to indicate end of display update

    recRootDisplayOld = recRootDisplay; // Store the current root display value for comparison in the next iteration
    recNoteDisplayOld = recNoteDisplay; // Store the current note display value for comparison in the next iteration
    recOffsetDisplayOld = recOffsetDisplay; // Store the current offset display value for comparison in the next iteration
    recGroupDisplayOld = recGroupDisplay; // Store the current group display value for comparison in the next iteration
    recScaleDisplayOld = recScaleDisplay; // Store the current scale display value for comparison in the next iteration
  }
}
