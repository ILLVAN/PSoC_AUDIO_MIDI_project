/*******************************************************************************
* File: main.c      
*
*******************************************************************************/

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <ssd1306.h>
#include <font.h>

#define START_FREQ_DIV 1000
#define MAX_FREQ_DIV 8000
#define BASS_OFFSET_UP 12
const uint8 DISPLAY_ADDRESS = 0x3C;// 011110+SA0+RW - 0x3C or 0x3D 

CY_ISR_PROTO(userModeTimer_ISR);
CY_ISR_PROTO(userEcho_ISR);
CY_ISR_PROTO(userUpdateESP_ISR);

CY_ISR_PROTO(but1_isr_neg_vect);
CY_ISR_PROTO(but1_isr_pos_vect);
CY_ISR_PROTO(but2_isr_neg_vect);
CY_ISR_PROTO(but2_isr_pos_vect);
CY_ISR_PROTO(but3_isr_neg_vect);
CY_ISR_PROTO(but3_isr_pos_vect);
CY_ISR_PROTO(analogBut_isr_vect);
CY_ISR_PROTO(adc_isr_vect);

volatile uint8 button1 = 0;
volatile uint8 button2 = 0;
volatile uint8 button3 = 0;
volatile uint8 analogBut = 0;

volatile uint8 muxChannel = 0;
volatile uint8 adcFlag = 0;
int pitch[2] = {0,0};
int oldYinput = 0;
uint8 analogButFlag;
uint8 pitchFlag;

uint8 squarewave[502] = { 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u
};
uint8 sinewave[502] = {127u, 128u, 130u, 131u, 133u, 134u, 136u, 137u, 139u, 141u, 142u, 144u, 145u, 147u, 148u, 150u, 151u, 153u, 154u, 156u, 157u, 159u, 160u, 162u, 163u, 165u, 166u, 168u, 169u, 171u, 172u, 174u, 175u, 177u, 178u, 180u, 181u, 182u, 184u, 185u, 186u, 188u, 189u, 191u, 192u, 193u, 195u, 196u, 197u, 198u, 200u, 201u, 202u, 203u, 205u, 206u, 207u, 208u, 209u, 211u, 212u, 213u, 214u, 215u, 216u, 217u, 218u, 219u, 221u, 222u, 223u, 224u, 225u, 225u, 226u, 227u, 228u, 229u, 230u, 231u, 232u, 233u, 233u, 234u, 235u, 236u, 237u, 237u, 238u, 239u, 239u, 240u, 241u, 241u, 242u, 243u, 243u, 244u, 244u, 245u, 245u, 246u, 246u, 247u, 247u, 247u, 248u, 248u, 249u, 249u, 249u, 249u, 250u, 250u, 250u, 250u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 250u, 250u, 250u, 250u, 249u, 249u, 249u, 249u, 248u, 248u, 247u, 247u, 247u, 246u, 246u, 245u, 245u, 244u, 244u, 243u, 243u, 242u, 241u, 241u, 240u, 239u, 239u, 238u, 237u, 237u, 236u, 235u, 234u, 233u, 233u, 232u, 231u, 230u, 229u, 228u, 227u, 226u, 225u, 225u, 224u, 223u, 222u, 221u, 219u, 218u, 217u, 216u, 215u, 214u, 213u, 212u, 211u, 209u, 208u, 207u, 206u, 205u, 203u, 202u, 201u, 200u, 198u, 197u, 196u, 195u, 193u, 192u, 191u, 189u, 188u, 186u, 185u, 184u, 182u, 181u, 180u, 178u, 177u, 175u, 174u, 172u, 171u, 169u, 168u, 166u, 165u, 163u, 162u, 160u, 159u, 157u, 156u, 154u, 153u, 151u, 150u, 148u, 147u, 145u, 144u, 142u, 141u, 139u, 137u, 136u, 134u, 133u, 131u, 130u, 128u, 127u, 125u, 123u, 122u, 120u, 119u, 117u, 116u, 114u, 112u, 111u, 109u, 108u, 106u, 105u, 103u, 102u, 100u, 99u, 97u, 96u, 94u, 93u, 91u, 90u, 88u, 87u, 85u, 84u, 82u, 81u, 79u, 78u, 76u, 75u, 73u, 72u, 71u, 69u, 68u, 67u, 65u, 64u, 62u, 61u, 60u, 58u, 57u, 56u, 55u, 53u, 52u, 51u, 50u, 48u, 47u, 46u, 45u, 44u, 42u, 41u, 40u, 39u, 38u, 37u, 36u, 35u, 34u, 32u, 31u, 30u, 29u, 28u, 28u, 27u, 26u, 25u, 24u, 23u, 22u, 21u, 20u, 20u, 19u, 18u, 17u, 16u, 16u, 15u, 14u, 14u, 13u, 12u, 12u, 11u, 10u, 10u, 9u, 9u, 8u, 8u, 7u, 7u, 6u, 6u, 6u, 5u, 5u, 4u, 4u, 4u, 4u, 3u, 3u, 3u, 3u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 2u, 3u, 3u, 3u, 3u, 4u, 4u, 4u, 4u, 5u, 5u, 6u, 6u, 6u, 7u, 7u, 8u, 8u, 9u, 9u, 10u, 10u, 11u, 12u, 12u, 13u, 14u, 14u, 15u, 16u, 16u, 17u, 18u, 19u, 20u, 20u, 21u, 22u, 23u, 24u, 25u, 26u, 27u, 28u, 28u, 29u, 30u, 31u, 32u, 34u, 35u, 36u, 37u, 38u, 39u, 40u, 41u, 42u, 44u, 45u, 46u, 47u, 48u, 50u, 51u, 52u, 53u, 55u, 56u, 57u, 58u, 60u, 61u, 62u, 64u, 65u, 67u, 68u, 69u, 71u, 72u, 73u, 75u, 76u, 78u, 79u, 81u, 82u, 84u, 85u, 87u, 88u, 90u, 91u, 93u, 94u, 96u, 97u, 99u, 100u, 102u, 103u, 105u, 106u, 108u, 109u, 111u, 112u, 114u, 116u, 117u, 119u, 120u, 122u, 123u, 125u};
uint8 trianglewave[502] = {126u, 127u, 128u, 129u, 130u, 131u, 132u, 133u, 134u, 135u, 136u, 137u, 138u, 139u, 140u, 141u, 142u, 143u, 144u, 145u, 146u, 147u, 148u, 149u, 150u, 151u, 152u, 153u, 154u, 155u, 156u, 157u, 158u, 159u, 160u, 161u, 162u, 163u, 164u, 165u, 166u, 167u, 168u, 169u, 170u, 171u, 172u, 173u, 174u, 175u, 176u, 177u, 178u, 179u, 180u, 181u, 182u, 183u, 184u, 185u, 186u, 187u, 188u, 189u, 190u, 191u, 192u, 193u, 194u, 195u, 196u, 197u, 198u, 199u, 200u, 201u, 202u, 203u, 204u, 205u, 206u, 207u, 208u, 209u, 210u, 211u, 212u, 213u, 214u, 215u, 216u, 217u, 218u, 219u, 220u, 221u, 222u, 223u, 224u, 225u, 226u, 227u, 228u, 229u, 230u, 231u, 232u, 233u, 234u, 235u, 236u, 237u, 238u, 239u, 240u, 241u, 242u, 243u, 244u, 245u, 246u, 247u, 248u, 249u, 250u, 251u, 252u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u, 24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u, 32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u, 40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u, 48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u, 56u, 57u, 58u, 59u, 60u, 61u, 62u, 63u, 64u, 65u, 66u, 67u, 68u, 69u, 70u, 71u, 72u, 73u, 74u, 75u, 76u, 77u, 78u, 79u, 80u, 81u, 82u, 83u, 84u, 85u, 86u, 87u, 88u, 89u, 90u, 91u, 92u, 93u, 94u, 95u, 96u, 97u, 98u, 99u, 100u, 101u, 102u, 103u, 104u, 105u, 106u, 107u, 108u, 109u, 110u, 111u, 112u, 113u, 114u, 115u, 116u, 117u, 118u, 119u, 120u, 121u, 122u, 123u, 124u, 125u};
uint8 sawtooth[502] = {251u, 250u, 249u, 248u, 247u, 246u, 245u, 244u, 243u, 242u, 241u, 240u, 239u, 238u, 237u, 236u, 235u, 234u, 233u, 232u, 231u, 230u, 229u, 228u, 227u, 226u, 225u, 224u, 223u, 222u, 221u, 220u, 219u, 218u, 217u, 216u, 215u, 214u, 213u, 212u, 211u, 210u, 209u, 208u, 207u, 206u, 205u, 204u, 203u, 202u, 201u, 200u, 199u, 198u, 197u, 196u, 195u, 194u, 193u, 192u, 191u, 190u, 189u, 188u, 187u, 186u, 185u, 184u, 183u, 182u, 181u, 180u, 179u, 178u, 177u, 176u, 175u, 174u, 173u, 172u, 171u, 170u, 169u, 168u, 167u, 166u, 165u, 164u, 163u, 162u, 161u, 160u, 159u, 158u, 157u, 156u, 155u, 154u, 153u, 152u, 151u, 150u, 149u, 148u, 147u, 146u, 145u, 144u, 143u, 142u, 141u, 140u, 139u, 138u, 137u, 136u, 135u, 134u, 133u, 132u, 131u, 130u, 129u, 128u, 127u, 126u, 125u, 124u, 123u, 122u, 121u, 120u, 119u, 118u, 117u, 116u, 115u, 114u, 113u, 112u, 111u, 110u, 109u, 108u, 107u, 106u, 105u, 104u, 103u, 102u, 101u, 100u, 99u, 98u, 97u, 96u, 95u, 94u, 93u, 92u, 91u, 90u, 89u, 88u, 87u, 86u, 85u, 84u, 83u, 82u, 81u, 80u, 79u, 78u, 77u, 76u, 75u, 74u, 73u, 72u, 71u, 70u, 69u, 68u, 67u, 66u, 65u, 64u, 63u, 62u, 61u, 60u, 59u, 58u, 57u, 56u, 55u, 54u, 53u, 52u, 51u, 50u, 49u, 48u, 47u, 46u, 45u, 44u, 43u, 42u, 41u, 40u, 39u, 38u, 37u, 36u, 35u, 34u, 33u, 32u, 31u, 30u, 29u, 28u, 27u, 26u, 25u, 24u, 23u, 22u, 21u, 20u, 19u, 18u, 17u, 16u, 15u, 14u, 13u, 12u, 11u, 10u, 9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 251u, 250u, 249u, 248u, 247u, 246u, 245u, 244u, 243u, 242u, 241u, 240u, 239u, 238u, 237u, 236u, 235u, 234u, 233u, 232u, 231u, 230u, 229u, 228u, 227u, 226u, 225u, 224u, 223u, 222u, 221u, 220u, 219u, 218u, 217u, 216u, 215u, 214u, 213u, 212u, 211u, 210u, 209u, 208u, 207u, 206u, 205u, 204u, 203u, 202u, 201u, 200u, 199u, 198u, 197u, 196u, 195u, 194u, 193u, 192u, 191u, 190u, 189u, 188u, 187u, 186u, 185u, 184u, 183u, 182u, 181u, 180u, 179u, 178u, 177u, 176u, 175u, 174u, 173u, 172u, 171u, 170u, 169u, 168u, 167u, 166u, 165u, 164u, 163u, 162u, 161u, 160u, 159u, 158u, 157u, 156u, 155u, 154u, 153u, 152u, 151u, 150u, 149u, 148u, 147u, 146u, 145u, 144u, 143u, 142u, 141u, 140u, 139u, 138u, 137u, 136u, 135u, 134u, 133u, 132u, 131u, 130u, 129u, 128u, 127u, 126u, 125u, 124u, 123u, 122u, 121u, 120u, 119u, 118u, 117u, 116u, 115u, 114u, 113u, 112u, 111u, 110u, 109u, 108u, 107u, 106u, 105u, 104u, 103u, 102u, 101u, 100u, 99u, 98u, 97u, 96u, 95u, 94u, 93u, 92u, 91u, 90u, 89u, 88u, 87u, 86u, 85u, 84u, 83u, 82u, 81u, 80u, 79u, 78u, 77u, 76u, 75u, 74u, 73u, 72u, 71u, 70u, 69u, 68u, 67u, 66u, 65u, 64u, 63u, 62u, 61u, 60u, 59u, 58u, 57u, 56u, 55u, 54u, 53u, 52u, 51u, 50u, 49u, 48u, 47u, 46u, 45u, 44u, 43u, 42u, 41u, 40u, 39u, 38u, 37u, 36u, 35u, 34u, 33u, 32u, 31u, 30u, 29u, 28u, 27u, 26u, 25u, 24u, 23u, 22u, 21u, 20u, 19u, 18u, 17u, 16u, 15u, 14u, 13u, 12u, 11u, 10u, 9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u};
uint8 squareXSine[502] = { 127u, 128u, 130u, 131u, 133u, 134u, 136u, 137u, 139u, 141u, 
                            142u, 144u, 145u, 147u, 148u, 150u, 151u, 153u, 154u, 156u,
                            157u, 159u, 160u, 162u, 163u, 165u, 166u, 168u, 169u, 171u,
                            172u, 174u, 175u, 177u, 178u, 180u, 181u, 182u, 200u, 220u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u, 252u,
                            220u, 200u, 180u, 160u, 153u, 151u, 150u, 148u, 147u, 145u, 
                            144u, 142u, 141u, 139u, 137u, 136u, 134u, 133u, 131u, 130u,
                            127u, 125u, 123u, 122u, 120u, 119u, 117u, 116u, 114u, 112u, 
                            111u, 109u, 108u, 106u, 105u, 103u, 102u, 100u, 99u, 97u, 
                            96u, 94u, 93u, 91u, 90u, 
    
                            88u, 87u, 85u, 84u, 82u, 81u, 79u, 78u, 76u, 75u,
                            73u, 72u, 71u, 69u, 68u, 67u, 65u, 64u, 62u, 61u, 
                            60u, 58u, 57u, 56u, 55u, 53u, 52u, 51u, 50u, 48u, 
                            47u, 46u, 45u, 44u, 42u, 41u, 40u, 39u, 38u, 37u,
                            25u, 10u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                            0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 7u,
                            14u, 15u, 16u, 16u, 17u, 18u, 19u, 20u, 20u, 21u,
                            22u, 23u, 24u, 25u, 26u, 27u, 28u, 28u, 29u, 30u,
                            31u, 32u, 60u, 90u, 100u, 115u,
                            127u, 128u, 130u, 131u, 133u, 134u, 136u, 137u, 139u, 141u, 142u, 144u, 145u, 147u, 148u, 150u, 151u, 153u, 154u, 156u, 157u, 159u, 160u, 162u, 163u, 165u, 166u, 168u, 169u, 171u, 172u, 174u, 175u, 177u, 178u, 180u, 181u, 182u, 184u, 185u, 186u, 188u, 189u, 191u, 192u, 193u, 195u, 196u, 197u, 198u, 200u, 201u, 202u, 203u, 205u, 206u, 207u, 208u, 209u, 211u, 212u, 213u, 214u, 215u, 216u, 217u, 218u, 219u, 221u, 222u, 223u, 224u, 225u, 225u, 226u, 227u, 228u, 229u, 230u, 231u, 232u, 233u, 233u, 234u, 235u, 236u, 237u, 237u, 238u, 239u, 239u, 240u, 241u, 241u, 242u, 243u, 243u, 244u, 244u, 245u, 245u, 246u, 246u, 247u, 247u, 247u, 248u, 248u, 249u, 249u, 249u, 249u, 250u, 250u, 250u, 250u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 251u, 250u, 250u, 250u, 250u, 249u, 249u, 249u, 249u, 248u, 248u, 247u, 247u, 247u, 246u, 246u, 245u, 245u, 244u, 244u, 243u, 243u, 242u, 241u, 241u, 240u, 239u, 239u, 238u, 237u, 237u, 236u, 235u, 234u, 233u, 233u, 232u, 231u, 230u, 229u, 228u, 227u, 226u, 225u, 225u, 224u, 223u, 222u, 221u, 219u, 218u, 217u, 216u, 215u, 214u, 213u, 212u, 211u, 209u, 208u, 207u, 206u, 205u, 203u, 202u, 201u, 200u, 198u, 197u, 196u, 195u, 193u, 192u, 191u, 189u, 188u, 186u, 185u, 184u, 182u, 181u, 180u, 178u, 177u, 175u, 174u, 172u, 171u, 169u, 168u, 166u, 165u, 163u, 162u, 160u, 159u, 157u, 156u, 154u, 153u, 151u, 150u, 148u, 147u, 145u, 144u, 142u, 141u, 139u, 137u, 136u, 134u, 133u, 131u, 130u, 128u};
uint8 waveMode = 0;

const char notes[108][3] = {"C0 ", "C#0", "D0 ", "D#0", "E0 ", "F0 ", "F#0", "G0 ", "G#0", "A0 ", "A#0", "B0 ", "C1 ", "C#1", "D1 ", "D#1", "E1 ", "F1 ", "F#1", "G1 ", "G#1", "A1 ", "A#1", "B1 ", "C2 ", "C#2", "D2 ", "D#2", "E2 ", "F2 ", "F#2", "G2 ", "G#2", "A2 ", "A#2", "B2 ", "C3 ", "C#3", "D3 ", "D#3", "E3 ", "F3 ", "F#3", "G3 ", "G#3", "A3 ", "A#3", "B3 ", "C4 ", "C#4", "D4 ", "D#4", "E4 ", "F4 ", "F#4", "G4 ", "G#4", "A4 ", "A#4", "B4 ", "C5 ", "C#5", "D5 ", "D#5", "E5 ", "F5 ", "F#5", "G5 ", "G#5", "A5 ", "A#5", "B5 ", "C6 ", "C#6", "D6 ", "D#6", "E6 ", "F6 ", "F#6", "G6 ", "G#6", "A6 ", "A#6", "B6 ", "C7 ", "C#7", "D7 ", "D#7", "E7 ", "F7 ", "F#7", "G7 ", "G#7", "A7 ", "A#7", "B7 ", "C8 ", "C#8", "D8 ", "D#8", "E8 ", "F8 ", "F#8", "G8 ", "G#8", "A8 ", "A#8", "B8 "};
const uint16 intFrequency[108] = {16, 17, 18, 19, 21, 22, 23, 25, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3730, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5919, 6272, 6645, 7040, 7459, 7902};
const double frequency[108] = {16.35,17.32,18.35,19.45,20.60,21.83,23.12,24.50,25.96,27.50,29.14,30.87,32.70,34.65,36.71,38.89,41.20,43.65,46.25,49.00,51.91,55.00,58.27,61.74,65.41,69.30,73.42,77.78,82.41,87.31,92.50,98.00,103.83,110.00,116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880.00,932.33,987.77,1046.50,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760.00,1864.66,1975.53,2093.00,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520.00,3729.31,3951.07,4186.01,4434.92,4698.63,4978.03,5274.04,5587.65,5919.91,6271.93,6644.88,7040.00,7458.62,7902.13};

volatile uint16 delayMS = 20;
volatile uint8 onOffCount = 0;
char transmitBuffer[100];
char espTransmit[16];
volatile double freq;
volatile uint16 intFreq;
volatile char note[3];
volatile uint8 noteIndex;
volatile uint8 noteIndex2;
volatile uint8 mode = 1;            // set default mode   
volatile uint8 modeFlag = 0;        // flag is set by Timer_Mode, resets after check
volatile uint8 checkingMode = 1;    // set bool if checking mode or not 
volatile uint8 lastMode = 1;
uint16 freqClockDivCounter = START_FREQ_DIV;
volatile uint dice1;
volatile uint dice2;
volatile uint8 toESPviaUARTFlag;
char displayNote[3];
char displayScaleName[40];

volatile uint8 sendDatatoESP = 1;       // enable UART to ESP

volatile uint8 cScaleGroupSelect = 100;                                 // 0 world penta | 1 blues and minors | 2 dominant scales | 3 church modes | 100 chromatic
const uint8 cGROUPS_LENGTH = 6;                                         // scale groups count
volatile uint8 cScaleSelect = 100;                                      // 0-7 depending on group | 100 chromatic
const uint8 cSCALES_LENGTH = 8;                                         // scales per group
volatile uint8 octaveSelect = 1;                                        // switch octaves
volatile uint8 offsetUp = BASS_OFFSET_UP;                               // index 12 is C1
volatile int offset2 = 0;                                             // sub bass

volatile uint8 osz1Select;
volatile uint8 osz2Select;
volatile uint8 waveDAC1running;
volatile uint8 waveDAC2running;
volatile uint8 toggleSettings;


//////////////////////////////////////////////// MODAL MONDIAL
const uint8 cScales[6][8][8] =  {{      // WORLD PENTATONICS                       
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
const char cScaleNames[6][8][40] = {
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
volatile uint16 echoDuration;
volatile uint16 echoDistance;
volatile uint8 echoFlag = 0;        // 0 idle | 1 trig sent | 2 timer value ready
volatile uint16 echoTimerPeriod;
volatile uint16 echoReadCounter;
volatile uint16 echoTuneDelay = 40;


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
    if (button2){
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
        delayMS = (MAX_FREQ_DIV / (2* freqClockDivCounter)) + 20;
        CyDelay(delayMS);    
    }
}

void playRange(uint8 minIndex, uint8 maxIndex, uint16 playRangeDelay){
    if (maxIndex > 107){
        maxIndex = 107;
    }
    if (button1){
        UART_1_PutString("PLAY RANGE \n\r");
        for (uint8 i = minIndex; i <= maxIndex; i++){
            if (button2){
                return;
            }
            freqClockDivCounter = 250000 / intFrequency[i];
            Clock_1_SetDividerValue(freqClockDivCounter);
            sprintf(transmitBuffer, "%c%c%c : %iHz DIV: %i\n\r", notes[i][0],notes[i][1], notes[i][2], intFrequency[i], freqClockDivCounter) ;
            UART_1_PutString(transmitBuffer);
            CyDelay(playRangeDelay);
        }     
    }
}

void distanceEchoPitch(){
    if (analogButFlag){      
        toggleSettings ^= 1;
        Pin_Dice_LED_1_Write(toggleSettings);
        Pin_Dice_LED_2_Write(!toggleSettings);
        analogButFlag = 0;
    }
    if (pitchFlag == 1){   
        if (pitch[0] < 0){
            if (toggleSettings){
                offset2++;
            }
            else{
                offsetUp++;
            }
             pitchFlag = 2;
        }
        else if (pitch[0] > 2){
            if (toggleSettings){
                offset2--;
            }
            else{
                offsetUp--;
            }
             pitchFlag = 2;
        }
         pitchFlag = 2;
    }
    offsetUp = offsetUp > 80 ?  80 : offsetUp;
    offsetUp = offsetUp < 1 ?  BASS_OFFSET_UP : offsetUp;
    offset2 = offset2 > 80 ? 80 : offset2;
     if (button1){
        if (toggleSettings){
            octaveSelect++;
            if (octaveSelect > 4){
               octaveSelect = 1; 
            }
            sprintf(transmitBuffer, "octaveSelect: %i\n\r", octaveSelect);             
            UART_1_PutString(transmitBuffer);
        }
        else{
            echoTuneDelay *= 2;
            if (echoTuneDelay > 300){
               echoTuneDelay = 40; 
            }
            sprintf(transmitBuffer, "echoTuneDelay: %i\n\r", echoTuneDelay);             
            UART_1_PutString(transmitBuffer);
        }
        button1 = 0;
    }
    if (button2){
        if (cScaleGroupSelect == 100){
            cScaleGroupSelect = 0;
            cScaleSelect = 0;
        }
        else if (cScaleGroupSelect == cGROUPS_LENGTH - 1){
            cScaleGroupSelect = 100;
            cScaleSelect = 100;
        }
        else{
            cScaleGroupSelect++;   
        }
        button2 = 0;
        sprintf(transmitBuffer, "cScaleGroup: %i\n\r", cScaleGroupSelect);             
        UART_1_PutString(transmitBuffer);
    }
    if (button3){
        if (cScaleSelect == 100){
            cScaleSelect = 0;
        }
        else if (cScaleSelect == cSCALES_LENGTH - 1){
            cScaleSelect = 0;
        }
        else{
            cScaleSelect++;   
        }
        button3 = 0;
        sprintf(transmitBuffer, "cScale:      %i\n\r", cScaleSelect);             
        UART_1_PutString(transmitBuffer);
    }
    if (echoFlag == 0){
        Pin_EchoTrig_Write(0);
        CyDelayUs(2);
        Pin_EchoTrig_Write(1);
        CyDelayUs(20);
        Pin_EchoTrig_Write(0);
        echoFlag = 1;       
    }
    else if (echoFlag == 2){
        echoDuration = echoTimerPeriod - echoReadCounter;
//        sprintf(transmitBuffer, "EchoDuration: %i\n\r", echoDuration);        
//        UART_1_PutString(transmitBuffer); 
        if (echoDuration < 320 && echoDuration > 10){                
           echoDistance = echoDuration / 5.5;  
        }                 
//        sprintf(transmitBuffer, "echoDistance: %i\n\r", echoDistance);             
//        UART_1_PutString(transmitBuffer); 
        if (cScaleGroupSelect != 100){
            for (int i = 0; i < 8; i++){
                if ((echoDistance + BASS_OFFSET_UP) % 12 == cScales[cScaleGroupSelect][cScaleSelect][i]){
                    noteIndex = echoDistance + offsetUp + (octaveSelect * 12);
                    noteIndex2 = noteIndex + offset2;
                }
            }         
        }
        else{
           noteIndex = echoDistance + offsetUp + (octaveSelect * 12);  
           noteIndex2 = noteIndex + offset2;
        }
        if (noteIndex > 100 || noteIndex < 1){                                  // if out of range
            noteIndex = BASS_OFFSET_UP;                                         // restart bassy
        }
        if (noteIndex2 > 100 || noteIndex < 1){
            noteIndex2 = BASS_OFFSET_UP + offset2;
        }
        sprintf(transmitBuffer, "offsetUP: %i\n\r noteIndex: %i \n\r", offsetUp, noteIndex);              
        UART_1_PutString(transmitBuffer);
       
        Clock_1_SetDividerValue(250000 / intFrequency[noteIndex]); 
        Clock_2_SetDividerValue(250000 / intFrequency[noteIndex2]); 
        echoFlag = 0;
    }
//    sprintf(transmitBuffer, "echoTuneDelay: %i\n\r", button1);             
//    UART_1_PutString(transmitBuffer);
    CyDelay(echoTuneDelay);
}

void noteSelect(int xPit)   {   
    if ((xPit > 100 || xPit < -100) && pitchFlag != 2){
        pitchFlag = 1;                                          // flag set offset select [root note]
//        UART_1_PutString("pitchFlag \n\r");
    }
    else if (xPit < 5 && xPit > -5){
        pitchFlag = 0;                                          // flag reset offset select [root note]
//        UART_1_PutString("pitchFlag cleared \n\r");
    }
}

void switchLEDcheck(){
    osz1Select = Pin_OSZ1_Read();
    osz2Select = Pin_OSZ2_Read();
    if (!osz1Select){
        Pin_OSZ1_LED_Write(1);
    }
    else if (osz1Select){
        Pin_OSZ1_LED_Write(0);
    }
    if (!osz2Select){
        Pin_OSZ2_LED_Write(1);
    }
    else if (osz2Select){
        Pin_OSZ2_LED_Write(0);
    }
}

void voiceSelect(){
    if (!osz1Select && !waveDAC1running){
        WaveDAC8_1_Start();
        waveDAC1running = 1;
    }
    else if (osz1Select && waveDAC1running){   
        WaveDAC8_1_Stop();
        waveDAC1running = 0;
    }
    if (!osz2Select && !waveDAC2running){       
        WaveDAC8_2_Start();
        waveDAC2running = 1;
    }
    else if (osz2Select && waveDAC2running){
        WaveDAC8_2_Stop();
        waveDAC2running = 0;
    }
}


void waveSelect(int yInput)   {
    if(yInput>190 && oldYinput<180)    {
        if(waveMode==4)  {
                waveMode=1;
            }   else    {
                waveMode++;
            }
        }
    if(yInput <-190 && oldYinput>-180)    {
        if(waveMode==0)  {
            waveMode=4;
        }   else    {
            waveMode--;
        }
        switch(waveMode)    {
            case 0:
                WaveDAC8_1_Wave1Setup(sinewave, 502);
                UART_1_PutString("\r\nsinewave");
            break;
            case 1:
                WaveDAC8_1_Wave1Setup(squarewave, 502);
                UART_1_PutString("\r\nsquarewave");
            break;
            case 2:
                WaveDAC8_1_Wave1Setup(trianglewave, 502);
                UART_1_PutString("\r\ntrianglewave");
            break;
            case 3:
                WaveDAC8_1_Wave1Setup(sawtooth, 502);
                UART_1_PutString("\r\nsawtooth");
            break;
            case 4:
                WaveDAC8_1_Wave1Setup(squareXSine, 502);
                UART_1_PutString("\r\nsquareXSine");
            break;
        }
    }
    oldYinput = yInput;
}

int main(){
    CyGlobalIntEnable;
    
    debouncerClock_Start();
    but1_isr_pos_StartEx(but1_isr_pos_vect);
    but1_isr_neg_StartEx(but1_isr_neg_vect);
    but2_isr_pos_StartEx(but2_isr_pos_vect);
    but2_isr_neg_StartEx(but2_isr_neg_vect);
    but3_isr_pos_StartEx(but3_isr_pos_vect);
    but3_isr_neg_StartEx(but3_isr_neg_vect);
    
    analogBut_isr_StartEx(analogBut_isr_vect);
    ADC_isr_StartEx(adc_isr_vect);
    analogMUX_Init(); 
    analogMUX_Select(muxChannel);
    
    analogADC_Start();
    analogADC_StartConvert();
    
    UART_1_Start();
    UART_1_PutString("Hello \n\r");
    
    Timer_Mode_Start();
    Clock_1_Start();
    Clock_2_Start();
    isr_checkMode_StartEx(userModeTimer_ISR);
    
    
    Clock_Echo_Start();
    Timer_Echo_Start();
    isr_Echo_StartEx(userEcho_ISR);
    echoTimerPeriod = Timer_Echo_ReadPeriod();
    
    Timer_Display_Start();
    UART_TOESP_Start();
    isr_updateESP_StartEx(userUpdateESP_ISR);
//    I2COLED_Start();             
//    display_init(DISPLAY_ADDRESS);                    // DISPLAY DOES NOT WORK THIS LINE KILLS LOOP
//    gfx_setTextSize(1);
//    gfx_setTextColor(WHITE);
    
    
    for(;;){
            
// discountinued-----------           
//            display_clear();  
//            display_update(); 
//            gfx_setCursor(2,2);
//            sprintf(displayNote, "%c%c%c", notes[noteIndex][0],notes[noteIndex][1], notes[noteIndex][2]) ;
//            gfx_println("Hello");  // 
//            gfx_setCursor(2,4);
//            gfx_println(cScaleNames[cScaleGroupSelect][cScaleSelect]);
//            gfx_drawRect(10,30,30,30,WHITE);
//            display_update();             
//            CyDelay(90);
// ------------------------------           
        switchLEDcheck();
        if (checkingMode && modeFlag){
            modecheck();
            modeFlag = 0;
        }
        if(adcFlag) {
            int analogRead = analogADC_GetResult16() -810;
//            sprintf(transmitBuffer, "read: %i\n\r", analogRead);             
//            UART_1_PutString(transmitBuffer);
            if(analogRead > 0){
                pitch[muxChannel] =  analogRead/33;
            }else{
                pitch[muxChannel] = analogRead/3.3;
            }
//            sprintf(transmitBuffer, "pitch[0] pitch[1]: V %i : H %i \n\r", pitch[0], pitch[1]);             
//            UART_1_PutString(transmitBuffer);
//            sprintf(transmitBuffer, "channel: C%i \n\r", muxChannel);             
//            UART_1_PutString(transmitBuffer);
            noteSelect(pitch[0]);
            waveSelect(pitch[1]);
            muxChannel ^= 1;
            analogMUX_Select(muxChannel);
            adcFlag = 0;
            analogADC_StartConvert();
        }   
        switch (mode){
            case 0: 
                playRange(noteIndex,90,120); // set min index, max Index, delay [ms]
                longSweep();
                break;
            case 1:
                voiceSelect();
                distanceEchoPitch();        
                break;
            case 2:
                break;
            case 3:
                if(button1){
                    WaveDAC8_1_Start();
                    UART_1_PutString(transmitBuffer);  
                    Clock_1_SetDividerValue(250000 / (intFrequency[button1]+pitch[0]/50));
                }
           
                else if(button2){
                    WaveDAC8_1_Start();
                    UART_1_PutString("\r\n");
                    UART_1_PutChar(notes[button2][0]);
                    Clock_1_SetDividerValue(250000 / (intFrequency[button2]+pitch[0]/50));
                }
                
                else if(button3){
                    WaveDAC8_1_Start();
                    UART_1_PutString("\r\n");
                    UART_1_PutChar(notes[button3][0]);
                    Clock_1_SetDividerValue(250000 / (intFrequency[button3]+pitch[0]/50));
                } else  {
                    WaveDAC8_1_Stop();
                    WaveDAC8_2_Stop();
                    waveDAC1running = 0;
                    waveDAC2running = 0;
                }
                break;
            default:
                break;
        }
        lastMode = mode;

    }
}

CY_ISR(analogBut_isr_vect)    {
    analogButFlag = 1;
//    UART_1_PutString("\r\nanalogbutton pressed");
}

CY_ISR(adc_isr_vect)  {
    adcFlag = 1;
    //UART_1_PutString("\r\nconversion finished");
}

CY_ISR(but1_isr_pos_vect)   {
//    UART_1_PutString("\r\nbutton 1 pressed");
    button1 = 75;
}
CY_ISR(but1_isr_neg_vect)   {
//    UART_1_PutString("\r\nbutton 1 released");
    button1 = 0;
}
CY_ISR(but2_isr_pos_vect)   {
//    UART_1_PutString("\r\nbutton 2 pressed");
    button2 = 85;
}
CY_ISR(but2_isr_neg_vect)   {
//    UART_1_PutString("\r\nbutton 2 released");
    button2 = 0;
}
CY_ISR(but3_isr_pos_vect)   {
//    UART_1_PutString("\r\nbutton 3 pressed");
    button3 = 80;
}
CY_ISR(but3_isr_neg_vect)   {
//    UART_1_PutString("\r\nbutton 3 released");
    button3 = 0;
}
CY_ISR(userEcho_ISR){
    if (echoFlag == 1){
        echoReadCounter = Timer_Echo_ReadCounter();
        echoFlag = 2;    
        Timer_Echo_WriteCounter(0);
        Pin_EchoReturn_ClearInterrupt();
    }
}

CY_ISR(userModeTimer_ISR){ 
    modeFlag = 1;
    Timer_Mode_ReadStatusRegister();
}

CY_ISR(userUpdateESP_ISR){ 
    sprintf(espTransmit, "|%i,%i,%i,%i,%i,|\r\n", offsetUp, noteIndex, offset2, cScaleGroupSelect, cScaleSelect); // fast version
    // sprintf(espTransmit, "|{\"Rt\" : %i, \"Nt\" : %i, \"O2\" : %i, \"Gp\" : %i, \"Sc\" : %i}| \r\n", offsetUp, noteIndex, offset2, cScaleGroupSelect, cScaleSelect); // JSON version, slow
    UART_TOESP_PutString(espTransmit);
    Timer_Display_ReadStatusRegister();
}
/* [] END OF FILE */
