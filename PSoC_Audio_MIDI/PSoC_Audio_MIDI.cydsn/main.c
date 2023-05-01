/*******************************************************************************
* File: main.c      
*
*******************************************************************************/

#include <project.h>
#include <stdio.h>
#define START_FREQ_DIV 120
#define MAX_FREQ_DIV 8000

CY_ISR_PROTO(userModeTimer_ISR);

const char notes[108][3] = {"C0 ", "C#0", "D0 ", "D#0", "E0 ", "F0 ", "F#0", "G0 ", "G#0", "A0 ", "A#0", "B0 ", "C1 ", "C#1", "D1 ", "D#1", "E1 ", "F1 ", "F#1", "G1 ", "G#1", "A1 ", "A#1", "B1 ", "C2 ", "C#2", "D2 ", "D#2", "E2 ", "F2 ", "F#2", "G2 ", "G#2", "A2 ", "A#2", "B2 ", "C3 ", "C#3", "D3 ", "D#3", "E3 ", "F3 ", "F#3", "G3 ", "G#3", "A3 ", "A#3", "B3 ", "C4 ", "C#4", "D4 ", "D#4", "E4 ", "F4 ", "F#4", "G4 ", "G#4", "A4 ", "A#4", "B4 ", "C5 ", "C#5", "D5 ", "D#5", "E5 ", "F5 ", "F#5", "G5 ", "G#5", "A5 ", "A#5", "B5 ", "C6 ", "C#6", "D6 ", "D#6", "E6 ", "F6 ", "F#6", "G6 ", "G#6", "A6 ", "A#6", "B6 ", "C7 ", "C#7", "D7 ", "D#7", "E7 ", "F7 ", "F#7", "G7 ", "G#7", "A7 ", "A#7", "B7 ", "C8 ", "C#8", "D8 ", "D#8", "E8 ", "F8 ", "F#8", "G8 ", "G#8", "A8 ", "A#8", "B8 "};
const uint16 intFrequency[108] = {16, 17, 18, 19, 21, 22, 23, 25, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3730, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5919, 6272, 6645, 7040, 7459, 7902};
const double frequency[108] = {16.35,17.32,18.35,19.45,20.60,21.83,23.12,24.50,25.96,27.50,29.14,30.87,32.70,34.65,36.71,38.89,41.20,43.65,46.25,49.00,51.91,55.00,58.27,61.74,65.41,69.30,73.42,77.78,82.41,87.31,92.50,98.00,103.83,110.00,116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880.00,932.33,987.77,1046.50,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760.00,1864.66,1975.53,2093.00,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520.00,3729.31,3951.07,4186.01,4434.92,4698.63,4978.03,5274.04,5587.65,5919.91,6271.93,6644.88,7040.00,7458.62,7902.13};

volatile uint16 delayMS = 20;
volatile uint8 onOffCount = 0;
char transmitBuffer[100];
volatile double freq;
volatile uint16 intFreq;
volatile char note[3];
volatile uint8 noteIndex;
volatile uint8 playing;
volatile uint8 mode = 0;            // set default mode   
volatile uint8 modeFlag = 0;
volatile uint8 checkingMode = 1;    // set bool if checking mode or not 
uint16 freqClockDivCounter = START_FREQ_DIV;
volatile uint dice1;
volatile uint dice2;

// MODECHECK FUNCTION checks mode on 4 state cube
void modecheck(){
    dice1 = Pin_Dice_1_Read();
    dice2 = Pin_Dice_2_Read();
    if(dice1 == 0 && dice2 == 0 && mode != 0){
        mode = 0;
        Pin_Dice_LED_1_Write(0);
        Pin_Dice_LED_2_Write(0);
        UART_1_PutString("MODE 0 \n\r");
    }
    else if(dice1 == 0 && dice2 == 1 && mode != 1){
        mode = 1;  
        Pin_Dice_LED_1_Write(0);
        Pin_Dice_LED_2_Write(1);
        UART_1_PutString("MODE 1 \n\r");
    }
    else if(dice1 == 1 && dice2 == 0 && mode != 2){
        mode = 2;
        Pin_Dice_LED_1_Write(1);
        Pin_Dice_LED_2_Write(0);
        UART_1_PutString("MODE 2 \n\r");
    }
    else if(dice1 == 1 && dice2 == 1 && mode != 3){
        mode = 3;
        Pin_Dice_LED_1_Write(1);
        Pin_Dice_LED_2_Write(1);
        UART_1_PutString("MODE 3 \n\r");
    }
}

void longSweep(){ // FREQ SWEEP 6kHz to 30Hz SHOWING FREQS AND DIV VIA UART
    if (freqClockDivCounter > MAX_FREQ_DIV){
        freqClockDivCounter = START_FREQ_DIV;
    }
    freq = 250000 / freqClockDivCounter;
    intFreq = freq;
    for (uint i=0; i < sizeof(intFrequency)/sizeof(intFrequency[0]); i++){
        if (intFreq == intFrequency[i]){
            noteIndex = i;
            sprintf(transmitBuffer, "%c%c%c : %iHz DIV: %i\n\r", notes[noteIndex][0],notes[noteIndex][1], notes[noteIndex][2], intFreq, freqClockDivCounter) ;
            UART_1_PutString(transmitBuffer);
        }
    }
    Clock_1_SetDividerValue(freqClockDivCounter);
    freqClockDivCounter++;
    delayMS = (MAX_FREQ_DIV / freqClockDivCounter) + 20;
    CyDelay(delayMS);
}

int main(){
    CyGlobalIntEnable;
	UART_1_Start();
    UART_1_PutString("Hello");
    WaveDAC8_1_Start();
    Timer_Mode_Start();
    Clock_Mode_Start();
    isr_checkMode_StartEx(userModeTimer_ISR);  
    for(;;){
        if (checkingMode && modeFlag){
            modecheck();
            modeFlag = 0;
        }
        switch (mode){
            case 0:     
                longSweep();
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
        }
    }
}

CY_ISR(userModeTimer_ISR){ 
    modeFlag = 1;
    Timer_Mode_ReadStatusRegister();
}
/* [] END OF FILE */
