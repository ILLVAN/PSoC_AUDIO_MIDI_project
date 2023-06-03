/*******************************************************************************
* File: main.c      
*
*******************************************************************************/

#include <project.h>
#include <stdio.h>
#include <stdlib.h>

// Clock divider and offset for sweep
#define START_FREQ_DIV 1000
#define MAX_FREQ_DIV 8000
#define BASS_OFFSET_UP 12

// 8 bit waveforms
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
uint8 waveMode = 0;                             // selector for waves

const char notes[108][3] = {"C0 ", "C#0", "D0 ", "D#0", "E0 ", "F0 ", "F#0", "G0 ", "G#0", "A0 ", "A#0", "B0 ", "C1 ", "C#1", "D1 ", "D#1", "E1 ", "F1 ", "F#1", "G1 ", "G#1", "A1 ", "A#1", "B1 ", "C2 ", "C#2", "D2 ", "D#2", "E2 ", "F2 ", "F#2", "G2 ", "G#2", "A2 ", "A#2", "B2 ", "C3 ", "C#3", "D3 ", "D#3", "E3 ", "F3 ", "F#3", "G3 ", "G#3", "A3 ", "A#3", "B3 ", "C4 ", "C#4", "D4 ", "D#4", "E4 ", "F4 ", "F#4", "G4 ", "G#4", "A4 ", "A#4", "B4 ", "C5 ", "C#5", "D5 ", "D#5", "E5 ", "F5 ", "F#5", "G5 ", "G#5", "A5 ", "A#5", "B5 ", "C6 ", "C#6", "D6 ", "D#6", "E6 ", "F6 ", "F#6", "G6 ", "G#6", "A6 ", "A#6", "B6 ", "C7 ", "C#7", "D7 ", "D#7", "E7 ", "F7 ", "F#7", "G7 ", "G#7", "A7 ", "A#7", "B7 ", "C8 ", "C#8", "D8 ", "D#8", "E8 ", "F8 ", "F#8", "G8 ", "G#8", "A8 ", "A#8", "B8 "};             // array of notes
const uint16 intFrequency[108] = {16, 17, 18, 19, 21, 22, 23, 25, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3730, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5919, 6272, 6645, 7040, 7459, 7902};       // array  of frequencys
//const double frequency[108] = {16.35,17.32,18.35,19.45,20.60,21.83,23.12,24.50,25.96,27.50,29.14,30.87,32.70,34.65,36.71,38.89,41.20,43.65,46.25,49.00,51.91,55.00,58.27,61.74,65.41,69.30,73.42,77.78,82.41,87.31,92.50,98.00,103.83,110.00,116.54,123.47,130.81,138.59,146.83,155.56,164.81,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440.00,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880.00,932.33,987.77,1046.50,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760.00,1864.66,1975.53,2093.00,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520.00,3729.31,3951.07,4186.01,4434.92,4698.63,4978.03,5274.04,5587.65,5919.91,6271.93,6644.88,7040.00,7458.62,7902.13};

const uint8 DISPLAY_ADDRESS = 0x3C;             // 011110+SA0+RW - 0x3C or 0x3D 

CY_ISR_PROTO(userModeTimer_ISR);                // timer for frequent mode check
CY_ISR_PROTO(userEcho_ISR);                     // interrupt to when Echo sensor is done
CY_ISR_PROTO(userUpdateESP_ISR);                // interrupt to refresh display

// Interrupts for Buttons
CY_ISR_PROTO(but1_isr_neg_vect);
CY_ISR_PROTO(but1_isr_pos_vect);
CY_ISR_PROTO(but2_isr_neg_vect);
CY_ISR_PROTO(but2_isr_pos_vect);
CY_ISR_PROTO(but3_isr_neg_vect);
CY_ISR_PROTO(but3_isr_pos_vect);
CY_ISR_PROTO(analogBut_isr_vect);

CY_ISR_PROTO(adc_isr_vect);                     // interrupt when joystick adc is done

// variables for the buttons
volatile uint8 button1 = 0;
volatile uint8 button2 = 0;
volatile uint8 button3 = 0;
uint8 analogButFlag = 0;

// Joystick and its ADC
volatile uint8 muxChannel = 0;                  // switching between 0 and 1 to select which axis to read
volatile uint8 adcFlag = 0;                     // flag for when adc is done
int pitch[2] = {0,0};                           // variable for adc reading for each axis
int oldYinput = 0;                              // old input for edge recognition
int oldXinput = 0;                              
uint8 pitchFlag;                                // flag for if there is a new pitch

volatile uint16 delayMS = 20;                   // variable to make the dac switch low frequencies faster
char transmitBuffer[100];                       // buffer for uart via usb
char espTransmit[16];                           // buffer for uart with ESP32
volatile double freq;                           // for better conversion of the frequencies
volatile uint16 intFreq;                        // variable for frequencies
volatile uint8 noteIndex;                       // indexes for the two notes
volatile uint8 noteIndex2;
volatile uint8 mode = 1;                        // set default mode   
volatile uint8 modeFlag = 1;                    // flag is set by Timer_Mode, resets after check
volatile uint8 checkingMode = 1;                // set bool if checking mode or not 
volatile uint8 lastMode = 1;                    // variable to check if the mode changed
uint16 freqClockDivCounter = START_FREQ_DIV;    // variable for the frequency divider
volatile uint8 dice1;                            // variables for the KY-027 Magic Light Cup sensor
volatile uint8 dice2;

volatile uint8 cScaleGroupSelect = 100;         // 0 world penta | 1 blues and minors | 2 dominant scales | 3 church modes | 100 chromatic
const uint8 cGROUPS_LENGTH = 6;                 // scale groups count
volatile uint8 cScaleSelect = 100;              // 0-7 depending on group | 100 chromatic
const uint8 cSCALES_LENGTH = 8;                 // scales per group
volatile uint8 octaveSelect = 1;                // switch octaves
volatile uint8 offsetUp = BASS_OFFSET_UP;       // index 12 is C1
volatile int offset2 = 0;                       // sub bass

volatile uint8 osz1Select;                      // switch oscillator 1 on off
volatile uint8 osz2Select;                      // switch oscillator 2 on off
volatile uint8 waveDAC1running;                 // indicates if osc1 is running
volatile uint8 waveDAC2running;                 // indicates if osc2 is running   
volatile uint8 toggleSettings;                  // switch between 2 settings pages


//////////////////////////////////////////////// MODAL MONDIAL: JAZZ SCALES
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
volatile uint16 echoDuration;               // duration between send and receive fo the echo sensor
volatile uint16 echoDistance;               // calculated distance
volatile uint8 echoFlag = 0;                // 0 idle | 1 trig sent | 2 timer value ready
volatile uint16 echoTimerPeriod;            // the cycle length depending on input clock
volatile uint16 echoReadCounter;            // length of echo pulse
volatile uint16 echoTuneDelay = 40;         // controlling responsivness of distance sensor
volatile uint16 songPosition = 0;           // counted from start
volatile uint8 bar;                         // current bar
volatile uint16 songLength = 96 * 13;       // wedding march theme length, 13 bars
volatile uint8 songRepeatCounter = 0;       // count number of repeats
volatile uint8 songDelayMs = 9;             // song speed^-1

// MODECHECK FUNCTION checks mode on 4 state cube
void modecheck(){
    dice1 = Pin_Dice_1_Read();                              // reading orientation of dice pins
    dice2 = Pin_Dice_2_Read();
    
    // Check if dice orientation corresponds to MODE 0
    if(dice1 == 0 && dice2 == 0 && mode != 0){
        mode = 0;
        Pin_Dice_LED_1_Write(0);                            // Turn off LED 1
        Pin_Dice_LED_2_Write(0);                            // Turn off LED 2
        UART_1_PutString("MODE 0 \n\r");                    // Send "MODE 0" message via UART
    }
    // Check if dice orientation corresponds to MODE 1
    else if(dice1 == 0 && dice2 == 1 && mode != 1){
        mode = 1;
        Pin_Dice_LED_1_Write(0);                            // Turn off LED 1
        Pin_Dice_LED_2_Write(1);                            // Turn on LED 2
        UART_1_PutString("MODE 1 \n\r");                    // Send "MODE 1" message via UART
    }
    // Check if dice orientation corresponds to MODE 2
    else if(dice1 == 1 && dice2 == 0 && mode != 2){
        mode = 2;
        Pin_Dice_LED_1_Write(1);                            // Turn on LED 1
        Pin_Dice_LED_2_Write(0);                            // Turn off LED 2
        UART_1_PutString("MODE 2 \n\r");                    // Send "MODE 2" message via UART
    }
    // Check if dice orientation corresponds to MODE 3
    else if(dice1 == 1 && dice2 == 1 && mode != 3){
        mode = 3;
        Pin_Dice_LED_1_Write(1);                            // Turn on LED 1
        Pin_Dice_LED_2_Write(1);                            // Turn on LED 2
        UART_1_PutString("MODE 3 \n\r");                    // Send "MODE 3" message via UART
    }
}

void longSweep(){ // FREQ SWEEP 6kHz to 30Hz SHOWING FREQS AND DIV VIA UART
    if (button2){
        if (freqClockDivCounter > MAX_FREQ_DIV){
            freqClockDivCounter = START_FREQ_DIV;
        }
        freq = 250000 / freqClockDivCounter;
        intFreq = freq;
        
        // Iterate over the elements of intFrequency array
        for (uint16 i=0; i < sizeof(intFrequency)/sizeof(intFrequency[0]); i++){
            if (intFreq == intFrequency[i]){
                noteIndex = i;
                // Create a formatted string with frequency, divider value, and note information
                sprintf(transmitBuffer, "%c%c%c : %iHz DIV: %i\n\r", notes[noteIndex][0],notes[noteIndex][1], notes[noteIndex][2], intFreq, freqClockDivCounter) ;
                UART_1_PutString(transmitBuffer); // Send the formatted string via UART
            }
        }
        
        Clock_1_SetDividerValue(freqClockDivCounter); // Set the clock divider value
        
        freqClockDivCounter++; // Increment the frequency clock divider counter
        
        // Calculate the delay based on the current frequency clock divider counter
        delayMS = (MAX_FREQ_DIV / (2* freqClockDivCounter)) + 20;
        CyDelay(delayMS); // Delay execution for the calculated delay in milliseconds
    }
}

void playRange(uint8 minIndex, uint8 maxIndex, uint16 playRangeDelay){
    if (maxIndex > 107){
        maxIndex = 107;
    }
    
    if (button1){
        UART_1_PutString("PLAY RANGE \n\r"); // Send "PLAY RANGE" message via UART
        
        // Iterate over the range of notes specified by minIndex and maxIndex
        for (uint8 i = minIndex; i <= maxIndex; i++){
            if (button2){
                return; // If button2 is pressed, exit the function
            }
            
            freqClockDivCounter = 250000 / intFrequency[i]; // Calculate the frequency clock divider value
            
            Clock_1_SetDividerValue(freqClockDivCounter); // Set the clock divider value
            
            // Create a formatted string with frequency, divider value, and note information
            sprintf(transmitBuffer, "%c%c%c : %iHz DIV: %i\n\r", notes[i][0],notes[i][1], notes[i][2], intFrequency[i], freqClockDivCounter) ;
            UART_1_PutString(transmitBuffer); // Send the formatted string via UART
            
            CyDelay(playRangeDelay); // Delay execution for the specified playRangeDelay
        }     
    }
}

void setWaveDACnotes(uint8 n1, uint8 n2){
    freqClockDivCounter = 250000 / intFrequency[n1]; // Calculate the frequency clock divider value for note n1
    Clock_1_SetDividerValue(freqClockDivCounter); // Set the clock divider value for Clock_1
    
    freqClockDivCounter = 250000 / intFrequency[n2]; // Calculate the frequency clock divider value for note n2
    Clock_2_SetDividerValue(freqClockDivCounter); // Set the clock divider value for Clock_2
    
    WaveDAC8_1_Start(); // Start WaveDAC1
    WaveDAC8_2_Start(); // Start WaveDAC2
    
    waveDAC1running = 1; // Set waveDAC1running flag to indicate WaveDAC1 is running
    waveDAC2running = 1; // Set waveDAC2running flag to indicate WaveDAC2 is running
}

void stopBothDACs(){
    WaveDAC8_1_Stop(); // Stop WaveDAC1
    WaveDAC8_2_Stop(); // Stop WaveDAC2
    
    waveDAC1running = 0; // Set waveDAC1running flag to indicate WaveDAC1 is stopped
    waveDAC2running = 0; // Set waveDAC2running flag to indicate WaveDAC2 is stopped
}

void weddingMarchMendelssohnBartholdy(){
    if (songPosition >= songLength || (songPosition == 0 && songRepeatCounter == 0)){ 
       songPosition = 0;                                                            // Reset the song position if it reaches the end or if it's the first iteration
       sprintf(transmitBuffer, "songRepeatCounter %i\n\r", songRepeatCounter);      // Format the string to be transmitted
       UART_1_PutString(transmitBuffer);                                            // Transmit the formatted string
       switch(songRepeatCounter){
            case 0: WaveDAC8_1_Wave1Setup(sawtooth, 502); // Set up WaveDAC1 with sawtooth waveform and frequency 502
                    WaveDAC8_2_Wave1Setup(sinewave, 502); // Set up WaveDAC2 with sine waveform and frequency 502
                    break;
            case 1: WaveDAC8_1_Wave1Setup(squareXSine, 502); // Set up WaveDAC1 with squareXSine waveform and frequency 502
                    WaveDAC8_2_Wave1Setup(sinewave, 502); // Set up WaveDAC2 with sine waveform and frequency 502
                    break;
            case 2: WaveDAC8_1_Wave1Setup(squarewave, 502); // Set up WaveDAC1 with squarewave waveform and frequency 502
                    WaveDAC8_2_Wave1Setup(sinewave, 502); // Set up WaveDAC2 with sine waveform and frequency 502
                    break;
            case 3: WaveDAC8_1_Wave1Setup(sawtooth, 502); // Set up WaveDAC1 with sawtooth waveform and frequency 502
                    WaveDAC8_2_Wave1Setup(squareXSine, 502); // Set up WaveDAC2 with squareXSine waveform and frequency 502
                    break;
            case 4: WaveDAC8_1_Wave1Setup(sinewave, 502); // Set up WaveDAC1 with sine waveform and frequency 502
                    WaveDAC8_2_Wave1Setup(squareXSine, 502); // Set up WaveDAC2 with squareXSine waveform and frequency 502
                    break;
            case 5: WaveDAC8_1_Wave1Setup(trianglewave, 502); // Set up WaveDAC1 with trianglewave waveform and frequency 502
                    WaveDAC8_2_Wave1Setup(sinewave, 502); // Set up WaveDAC2 with sine waveform and frequency 502
                    break;    
            default:  break;
        }
        songRepeatCounter++; // Increment the songRepeatCounter
        songDelayMs--; // Decrement the songDelayMs
        songDelayMs = songDelayMs < 1 ? 9 : songDelayMs; // If songDelayMs is less than 1, set it to 9
        songRepeatCounter = songRepeatCounter > 5 ? 0 : songRepeatCounter; // If songRepeatCounter is greater than 5, set it to 0
    }
    else{
        bar = (songPosition) / 96 + 1; // Calculate the current bar number based on the song position
        songPosition++; // Increment the song position
//        sprintf(transmitBuffer, "songPos %i\n\r", songPosition);             
//        UART_1_PutString(transmitBuffer);      
//        sprintf(transmitBuffer, "bar %i\n\r", bar);             
//        UART_1_PutString(transmitBuffer);   
        switch(bar){                                        // bars
            case 1: switch(songPosition){                   // bar 1
                        case 72:  setWaveDACnotes(72, 48) ; break;
                        case 78:  WaveDAC8_1_Stop(); break;
                        case 80:  WaveDAC8_1_Start(); break;
                        case 86:  WaveDAC8_1_Stop(); break;
                        case 88:  WaveDAC8_1_Start(); break;
                        case 94:  WaveDAC8_1_Stop(); break;
                        default:  break;
                    }; break;    
            case 2: switch(songPosition - 96){              // bar 2
                        case 1:   WaveDAC8_1_Start(); break;
                        case 46:  WaveDAC8_1_Stop(); break;
                        case 72:  WaveDAC8_1_Start(); break;
                        case 78:  WaveDAC8_1_Stop(); break;
                        case 80:  WaveDAC8_1_Start(); break;
                        case 86:  WaveDAC8_1_Stop(); break;
                        case 88:  WaveDAC8_1_Start(); break;
                        case 94:  WaveDAC8_1_Stop(); break;
                        default:  break;
                    }; break;
            case 3: switch(songPosition - 2 * 96){             
                        case 1:   WaveDAC8_1_Start(); break;
                        case 46:  WaveDAC8_1_Stop(); break;
                        case 72:  WaveDAC8_1_Start(); break;
                        case 78:  WaveDAC8_1_Stop(); break;
                        case 80:  WaveDAC8_1_Start(); break;
                        case 86:  WaveDAC8_1_Stop(); break;
                        case 88:  WaveDAC8_1_Start(); break;
                        case 94:  WaveDAC8_1_Stop(); break;
                        default:  break;
                    }; break;
            case 4: switch(songPosition - 3 * 96){          // bar 4
                        case 1:   setWaveDACnotes(72, 76); break;
                        case 22:  stopBothDACs(); break;
                        case 24:  WaveDAC8_1_Start();
                                  WaveDAC8_2_Start(); break;
                        case 30:  stopBothDACs(); break;        
                        case 32:  WaveDAC8_1_Start();
                                  WaveDAC8_2_Start(); break;
                        case 38:  stopBothDACs(); break; 
                        case 40:  WaveDAC8_1_Start();
                                  WaveDAC8_2_Start(); break;
                        case 46:  stopBothDACs(); break;
                        case 48:  WaveDAC8_1_Start();
                                  WaveDAC8_2_Start(); break;
                        case 70:  stopBothDACs(); break;                                 
                        case 72:  WaveDAC8_1_Start(); 
                                  WaveDAC8_2_Start(); break;
                        case 78:  stopBothDACs(); break;
                        case 80:  WaveDAC8_1_Start(); 
                                  WaveDAC8_2_Start(); break;
                        case 86:  stopBothDACs(); break;
                        case 88:  WaveDAC8_1_Start();
                                  WaveDAC8_2_Start(); break;
                        case 94:  stopBothDACs(); break;
                        default:  break;
                    }; break;                  
            case 5:  switch(songPosition - 4 * 96){          // bar 5
                        case 1:   setWaveDACnotes(72, 79); break;
                        case 22:  stopBothDACs(); break;
                        case 24:  setWaveDACnotes(72, 79);; break;
                        case 30:  stopBothDACs(); break;        
                        case 32:  setWaveDACnotes(72, 79);; break;
                        case 38:  stopBothDACs(); break; 
                        case 40:  setWaveDACnotes(72, 79);; break;
                        case 46:  stopBothDACs(); break;
                        case 48:  setWaveDACnotes(72, 79);; break;
                        case 70:  stopBothDACs(); break;                                 
                        case 72:  setWaveDACnotes(72, 84); break;
                        case 78:  stopBothDACs(); break;
                        case 80:  setWaveDACnotes(76, 88); break;
                        case 86:  stopBothDACs(); break;
                        case 88:  setWaveDACnotes(79, 91); break;
                        case 94:  stopBothDACs(); break;
                        default:  break;
                    }; break;   
            case 6: switch(songPosition - 5 * 96){          // bar 6
                        case 1:   setWaveDACnotes(69, 96); break;
                        case 46:  stopBothDACs(); break;
                        case 48:  setWaveDACnotes(71, 95); break;
                        case 82:  stopBothDACs(); break;                                 
                        case 84:  setWaveDACnotes(71, 90); break;
                        case 94:  stopBothDACs(); break;
                        default:  break;
                    }; break;   
            case 7: switch(songPosition - 6 * 96){          // bar 7
                        case 1:   setWaveDACnotes(76, 93); break;
                        case 22:  WaveDAC8_2_Stop(); break;
                        case 24:  setWaveDACnotes(76, 91); break;
                        case 46:  stopBothDACs(); break;                                 
                        case 48:  setWaveDACnotes(77, 89); break;
                        case 70:  stopBothDACs(); break;
                        case 72:  setWaveDACnotes(65, 86);
                                  WaveDAC8_2_Start(); break;     
                        case 94:  stopBothDACs(); break;                                   
                        default:  break;
                    }; break;   
            case 8: switch(songPosition - 7 * 96){          // bar 8
                        case 1:   setWaveDACnotes(67, 84); break;
                        case 34:  WaveDAC8_2_Stop(); break;
                        case 36:  freqClockDivCounter = 250000 / intFrequency[83];
                                  Clock_2_SetDividerValue(freqClockDivCounter);
                                  WaveDAC8_2_Start(); break;
                        case 40:  WaveDAC8_2_Stop(); break;                                 
                        case 42:  freqClockDivCounter = 250000 / intFrequency[84];
                                  Clock_2_SetDividerValue(freqClockDivCounter);
                                  WaveDAC8_2_Start(); break;
                        case 46:  stopBothDACs(); break;
                        case 48:  setWaveDACnotes(67, 86); break;    
                        case 70:  WaveDAC8_2_Stop(); break;  
                        case 72:  freqClockDivCounter = 250000 / intFrequency[79];
                                  Clock_2_SetDividerValue(freqClockDivCounter);
                                  WaveDAC8_2_Start(); break;
                        case 88: WaveDAC8_2_Stop(); break;                                
                        case 90:  freqClockDivCounter = 250000 / intFrequency[86];
                                  Clock_2_SetDividerValue(freqClockDivCounter);
                                  WaveDAC8_2_Start(); break;
                        case 94:  stopBothDACs(); break;                               
                        default:  break;
                    }; break;  
            case 9: switch(songPosition - 8 * 96){          // bar 9
                        case 1:   setWaveDACnotes(72, 88); break;
                        case 22:  WaveDAC8_1_Stop(); break;    
                        case 24:  setWaveDACnotes(60, 72); break; 
                        case 34:  stopBothDACs(); break;
                        case 36:  setWaveDACnotes(64, 76); break; 
                        case 46:  stopBothDACs(); break;
                        case 48:  setWaveDACnotes(67, 79); break; 
                        case 58:  stopBothDACs(); break;
                        case 60:  setWaveDACnotes(72, 84); break; 
                        case 70:  stopBothDACs(); break;                       
                        case 72:  setWaveDACnotes(76, 88); break;
                        case 82:  stopBothDACs(); break;  
                        case 84:  setWaveDACnotes(79, 91); break;
                        case 94:  stopBothDACs(); break;                                      
                        default:  break;
                    }; break; 
            case 10: switch(songPosition - 9 * 96){          // bar 10
                        case 1:   setWaveDACnotes(69, 96); break;
                        case 46:  WaveDAC8_1_Stop(); 
                                  WaveDAC8_2_Stop(); break;
                        case 48:  setWaveDACnotes(71, 95); break;
                        case 82:  stopBothDACs(); break;                                 
                        case 84:  setWaveDACnotes(71, 90); break;
                        case 94:  stopBothDACs(); break;
                        default:  break;
                    }; break;   
            case 11: switch(songPosition - 10 * 96){          // bar 11
                        case 1:   setWaveDACnotes(76, 93); break;
                        case 22:  WaveDAC8_2_Stop(); break;
                        case 24:  setWaveDACnotes(76, 91); break;
                        case 46:  stopBothDACs(); break;                                 
                        case 48:  setWaveDACnotes(77, 89); break;
                        case 70:  stopBothDACs(); break;
                        case 72:  setWaveDACnotes(65, 86); break;     
                        case 94:  stopBothDACs(); break;                                   
                        default:  break;
                    }; break;    
            case 12: switch(songPosition - 11 * 96){          // bar 12
                        case 1:   setWaveDACnotes(67, 84); break;
                        case 34:  WaveDAC8_2_Stop(); break;
                        case 36:  setWaveDACnotes(74, 83); break;
                        case 40:  stopBothDACs(); break;                                 
                        case 42:  setWaveDACnotes(76, 84); break;
                        case 46:  stopBothDACs(); break;     
                        case 48:  setWaveDACnotes(79, 88); break;    
                        case 70:  stopBothDACs(); break;  
                        case 72:  setWaveDACnotes(77, 84); break;
                        case 88:  stopBothDACs(); break;                                
                        case 90:  setWaveDACnotes(79, 88); break;
                        case 94:  stopBothDACs(); break;                               
                        default:  break;
                    }; break;  
            case 13: switch(songPosition - 12 * 96){          // bar 13
                        case 1:   setWaveDACnotes(67, 86); break;
                        case 46:  stopBothDACs(); break;
                        case 48:  setWaveDACnotes(72, 84); break;   
                        case 70:  stopBothDACs(); break;                               
                        default:  break;
                    }; break;          
            default: break;
        }
        CyDelay(songDelayMs);       // controls song speed
    }
}

void distanceEchoPitch(){
    if (analogButFlag){
        // Toggle the settings flag
        toggleSettings ^= 1;
        // Update LED states based on toggleSettings
        Pin_Dice_LED_1_Write(toggleSettings);
        Pin_Dice_LED_2_Write(!toggleSettings);
        // Reset analogButFlag
        analogButFlag = 0;
    }
    
    if (pitchFlag == 1){
        // Increment offset2 or offsetUp based on toggleSettings
        if (toggleSettings){
            offset2++;
        }
        else{
            offsetUp++;
        }
        // Reset pitchFlag
        pitchFlag = 0;
    }
    else if (pitchFlag == 2){
        // Decrement offset2 or offsetUp based on toggleSettings
        if (toggleSettings){
            offset2--;
        }
        else{
            offsetUp--;
        }
        // Reset pitchFlag
        pitchFlag = 0;
    }
    
    // Ensure offsetUp stays within the range [1, 80]
    offsetUp = offsetUp > 80 ?  80 : offsetUp;
    offsetUp = offsetUp < 1 ?  BASS_OFFSET_UP : offsetUp;
    
    // Ensure offset2 stays within the range [0, 80]
    offset2 = offset2 > 80 ? 80 : offset2;
    
    if (button1){
        if (toggleSettings){
            // Increment octaveSelect with a maximum value of 4
            octaveSelect++;
            if (octaveSelect > 4){
                octaveSelect = 1;
            }
            // Print octaveSelect value
            sprintf(transmitBuffer, "octaveSelect: %i\n\r", octaveSelect);
            UART_1_PutString(transmitBuffer);
        }
        else{
            // Double echoTuneDelay with a maximum value of 300
            echoTuneDelay *= 2;
            if (echoTuneDelay > 300){
                echoTuneDelay = 40;
            }
            // Print echoTuneDelay value
            sprintf(transmitBuffer, "echoTuneDelay: %i\n\r", echoTuneDelay);
            UART_1_PutString(transmitBuffer);
        }
        // Reset button1
        button1 = 0;
    }
    
    if (button2){
        if (cScaleGroupSelect == 100){
            // Reset cScaleGroupSelect and cScaleSelect
            cScaleGroupSelect = 0;
            cScaleSelect = 0;
        }
        else if (cScaleGroupSelect == cGROUPS_LENGTH - 1){
            // Set cScaleGroupSelect and cScaleSelect to special values
            cScaleGroupSelect = 100;
            cScaleSelect = 100;
        }
        else{
            // Increment cScaleGroupSelect
            cScaleGroupSelect++;
        }
        // Reset button2
        button2 = 0;
        // Print cScaleGroupSelect value
        sprintf(transmitBuffer, "cScaleGroup: %i\n\r", cScaleGroupSelect);
        UART_1_PutString(transmitBuffer);
    }
    
    if (button3){
        if (cScaleSelect == 100){
            // Reset cScaleSelect
            cScaleSelect = 0;
        }
        else if (cScaleSelect == cSCALES_LENGTH - 1){
            // Reset cScaleSelect to the beginning of the scale
            cScaleSelect = 0;
        }
        else{
            // Increment cScaleSelect
            cScaleSelect++;
        }
        // Reset button3
        button3 = 0;
        // Print cScaleSelect value
        sprintf(transmitBuffer, "cScale:      %i\n\r", cScaleSelect);
        UART_1_PutString(transmitBuffer);
    }
    
    if (echoFlag == 0){
        // Trigger an echo by setting and resetting a pin
        Pin_EchoTrig_Write(0);
        CyDelayUs(2);
        Pin_EchoTrig_Write(1);
        CyDelayUs(20);
        Pin_EchoTrig_Write(0);
        // Set echoFlag
        echoFlag = 1;
    }
    else if (echoFlag == 2){
        // Calculate echo duration based on counters
        echoDuration = echoTimerPeriod - echoReadCounter;
        
        if (echoDuration < 320 && echoDuration > 10){
            // Calculate echo distance based on echo duration
            echoDistance = echoDuration / 5.5;
        }
        
        if (cScaleGroupSelect != 100){
            for (int i = 0; i < 8; i++){
                // Check if echoDistance + BASS_OFFSET_UP matches a value in the scale
                if ((echoDistance + BASS_OFFSET_UP) % 12 == cScales[cScaleGroupSelect][cScaleSelect][i]){
                    // Calculate noteIndex and noteIndex2 based on offsets and octaveSelect
                    noteIndex = echoDistance + offsetUp + (octaveSelect * 12);
                    noteIndex2 = noteIndex + offset2;
                }
            }
        }
        else{
            // Calculate noteIndex and noteIndex2 based on offsets and octaveSelect
            noteIndex = echoDistance + offsetUp + (octaveSelect * 12);
            noteIndex2 = noteIndex + offset2;
        }
        
        // Check if note indices are out of range
        if (noteIndex > 100 || noteIndex < 1){
            // Reset noteIndex to a specific value
            noteIndex = BASS_OFFSET_UP;
        }
        
        if (noteIndex2 > 100 || noteIndex < 1){
            // Reset noteIndex2 to a specific value
            noteIndex2 = BASS_OFFSET_UP + offset2;
        }
        
        // Print offsetUp and noteIndex values
        sprintf(transmitBuffer, "offsetUP: %i\n\r noteIndex: %i \n\r", offsetUp, noteIndex);
        UART_1_PutString(transmitBuffer);
       
        // Set clock divider values based on noteIndex and noteIndex2
        Clock_1_SetDividerValue(250000 / intFrequency[noteIndex]);
        Clock_2_SetDividerValue(250000 / intFrequency[noteIndex2]);
        
        // Reset echoFlag
        echoFlag = 0;
    }
    
    // Delay the execution of the function based on echoTuneDelay
    CyDelay(echoTuneDelay);
}

void noteSelect(int xPit) {
    if (xPit > 230 && oldXinput < 200) {
        // If xPit is above a threshold and oldXinput is below a threshold,
        // indicating a rising edge in the pitch control
        pitchFlag = 2;  // Set pitchFlag to 2 for pitch increase
    }
    if (xPit < -160 && oldXinput > -130) {
        // If xPit is below a threshold and oldXinput is above a threshold,
        // indicating a falling edge in the pitch control
        pitchFlag = 1;  // Set pitchFlag to 1 for pitch decrease
    }
    if (xPit < 150 && xPit > -100) {
        // If xPit is within a small range around zero,
        // indicating the pitch control is centered
        pitchFlag = 0;  // Set pitchFlag to 0 for no pitch change
    }
    oldXinput = xPit;  // Update the oldXinput with the current xPit value for reference
}

void switchLEDcheck() {
    osz1Select = Pin_OSZ1_Read();  // Read the state of Pin_OSZ1
    osz2Select = Pin_OSZ2_Read();  // Read the state of Pin_OSZ2

    if (!osz1Select) {
        // If Pin_OSZ1 is not selected
        Pin_OSZ1_LED_Write(1);  // Turn on Pin_OSZ1_LED
    } else if (osz1Select) {
        // If Pin_OSZ1 is selected
        Pin_OSZ1_LED_Write(0);  // Turn off Pin_OSZ1_LED
    }

    if (!osz2Select) {
        // If Pin_OSZ2 is not selected
        Pin_OSZ2_LED_Write(1);  // Turn on Pin_OSZ2_LED
    } else if (osz2Select) {
        // If Pin_OSZ2 is selected
        Pin_OSZ2_LED_Write(0);  // Turn off Pin_OSZ2_LED
    }
}

void voiceSelect(){
    if (!osz1Select && !waveDAC1running){
        // Start WaveDAC1 if it is not running and osz1Select is not set
        WaveDAC8_1_Start();
        waveDAC1running = 1;
    }
    else if (osz1Select && waveDAC1running){
        // Stop WaveDAC1 if it is running and osz1Select is set
        WaveDAC8_1_Stop();
        waveDAC1running = 0;
    }
    
    if (!osz2Select && !waveDAC2running){
        // Start WaveDAC2 if it is not running and osz2Select is not set
        WaveDAC8_2_Start();
        waveDAC2running = 1;
    }
    else if (osz2Select && waveDAC2running){
        // Stop WaveDAC2 if it is running and osz2Select is set
        WaveDAC8_2_Stop();
        waveDAC2running = 0;
    }
}

void waveSelect(int yInput) {
    if (yInput > 230 && oldYinput < 200) {
        // If yInput is above a threshold and oldYinput is below a threshold,
        // indicating a rising edge in the joystick movement
        if (waveMode == 4) {
            // If waveMode is already at the maximum value, wrap around to 0
            waveMode = 0;
        } else {
            // Increment waveMode to select the next waveform
            waveMode++;
        }
    }
    if (yInput < -160 && oldYinput > -130) {
        // If yInput is below a threshold and oldYinput is above a threshold,
        // indicating a falling edge in the joystick movement
        if (waveMode == 0) {
            // If waveMode is already at the minimum value, wrap around to 4
            waveMode = 4;
        } else {
            // Decrement waveMode to select the previous waveform
            waveMode--;
        }
    }
    switch (waveMode) {
        case 0:
            // Set up WaveDAC1 for a sine wave using the sinewave array 
            WaveDAC8_1_Wave1Setup(sinewave, 502);
            break;
        case 1:
            // Set up WaveDAC1 for a square wave using the squarewave array 
            WaveDAC8_1_Wave1Setup(squarewave, 502);
            break;
        case 2:
            // Set up WaveDAC1 for a triangle wave using the trianglewave array 
            WaveDAC8_1_Wave1Setup(trianglewave, 502);
            break;
        case 3:
            // Set up WaveDAC1 for a sawtooth wave using the sawtooth array
            WaveDAC8_1_Wave1Setup(sawtooth, 502);
            break;
        case 4:
            // Set up WaveDAC1 for a squareXsine wave using the squareXSine array
            WaveDAC8_1_Wave1Setup(squareXSine, 502);
            break;
    }
    // Update the oldYinput with the current yInput for edge recognition in the next iteration
    oldYinput = yInput;
}


int main(){
    CyGlobalIntEnable;  // Enable global interrupts

    // Start debouncer clock and configure interrupt service routines (ISRs) for buttons
    debouncerClock_Start();
    but1_isr_pos_StartEx(but1_isr_pos_vect);
    but1_isr_neg_StartEx(but1_isr_neg_vect);
    but2_isr_pos_StartEx(but2_isr_pos_vect);
    but2_isr_neg_StartEx(but2_isr_neg_vect);
    but3_isr_pos_StartEx(but3_isr_pos_vect);
    but3_isr_neg_StartEx(but3_isr_neg_vect);

    analogBut_isr_StartEx(analogBut_isr_vect);  // Start ISR for analog button
    ADC_isr_StartEx(adc_isr_vect);              // Start ISR for ADC
    analogMUX_Init();                            // Initialize analog multiplexer
    analogMUX_Select(muxChannel);                // Select the desired multiplexer channel

    analogADC_Start();              // Start the ADC
    analogADC_StartConvert();       // Start ADC conversion

    UART_1_Start();                 // Start UART communication
    UART_1_PutString("Hello \n\r");  // Send a greeting message

    Timer_Mode_Start();             // Start mode timer
    Clock_1_Start();                 // Start DAC 1 clock
    Clock_2_Start();                 // Start DAC 2 clock
    isr_checkMode_StartEx(userModeTimer_ISR);  // Start ISR for mode checking

    Clock_Echo_Start();             // Start echo clock
    Timer_Echo_Start();             // Start echo timer
    isr_Echo_StartEx(userEcho_ISR);  // Start ISR for echo processing
    echoTimerPeriod = Timer_Echo_ReadPeriod();  // Read the period of the echo timer

    Timer_Display_Start();          // Start display timer
    UART_TOESP_Start();             // Start UART communication with ESP32 module
    isr_updateESP_StartEx(userUpdateESP_ISR);  // Start ISR for ESP module update

    WaveDAC8_1_Stop();              // Stop WaveDAC1
    WaveDAC8_2_Stop();              // Stop WaveDAC2

// discountinued-----------   
//    I2COLED_Start();             
//    display_init(DISPLAY_ADDRESS);                    // DISPLAY DOES NOT WORK THIS LINE KILLS LOOP
//    gfx_setTextSize(1);
//    gfx_setTextColor(WHITE);
// ------------------------------  
    
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
    switchLEDcheck();               // Check and update the status of the LEDs
    if (checkingMode && modeFlag) {
        modecheck();                // Check the mode and perform corresponding actions
        modeFlag = 0;
    }
    if (adcFlag) {
        int analogRead = analogADC_GetResult16() - 810;  // Read analog input and adjust the value
        if (analogRead > 0) {
            pitch[muxChannel] = analogRead / 33;         // Adjust pitch based on analog reading
        } else {
            pitch[muxChannel] = analogRead / 3.3;
        }
        sprintf(transmitBuffer, "x: %i y: %i\n\r", pitch[0], pitch[1]);             
       // UART_1_PutString(transmitBuffer);     
        noteSelect(pitch[0]);                            // Select the note based on pitch
        waveSelect(pitch[1]);                            // Select the waveform based on pitch
        muxChannel ^= 1;                                 // Toggle multiplexer channel
        analogMUX_Select(muxChannel);
        adcFlag = 0;                                     // Reset ADC flag
        analogADC_StartConvert();                        // Start ADC conversion
    }

    switch (mode) {
        case 0:
            playRange(noteIndex, 90, 120);  // Play notes within the specified range
              UART_1_PutString("mode 0");
            longSweep();                    // Perform a long sweep action
            break;
        case 1:
            voiceSelect();                  // Select the voice based on input
            distanceEchoPitch();            // Perform distance-based echo pitch
            break;
        case 2:
            weddingMarchMendelssohnBartholdy();  // Perform the wedding march action
            break;
        case 3:
            if (button1) {
                WaveDAC8_1_Start();
                UART_1_PutString("but1");
                Clock_1_SetDividerValue(250000 / (intFrequency[button1] + pitch[0] / 50));
            } else if (button2) {
                WaveDAC8_1_Start();
                UART_1_PutString("\r\n");
                UART_1_PutChar(notes[button2][0]);
                Clock_1_SetDividerValue(250000 / (intFrequency[button2] + pitch[0] / 50));
            } else if (button3) {
                WaveDAC8_1_Start();
                UART_1_PutString("\r\n");
                UART_1_PutChar(notes[button3][0]);
                Clock_1_SetDividerValue(250000 / (intFrequency[button3] + pitch[0] / 50));
            } else {
                WaveDAC8_1_Stop();
                WaveDAC8_2_Stop();
                waveDAC1running = 0;
                waveDAC2running = 0;
            }
            break;
        default:
            break;
    }

    lastMode = mode;  // Update the last mode value
}
}
CY_ISR(analogBut_isr_vect) {
    analogButFlag = 1;      // Set the analog button flag
}

CY_ISR(adc_isr_vect) {
    adcFlag = 1;            // Set the ADC flag
}

CY_ISR(but1_isr_pos_vect) {
    button1 = 75;           // Set the button1 value
}

CY_ISR(but1_isr_neg_vect) {
    button1 = 0;            // Reset the button1 value
}

CY_ISR(but2_isr_pos_vect) {
    button2 = 85;           // Set the button2 value
}

CY_ISR(but2_isr_neg_vect) {
    button2 = 0;            // Reset the button2 value
}

CY_ISR(but3_isr_pos_vect) {
    button3 = 80;           // Set the button3 value
}

CY_ISR(but3_isr_neg_vect) {
    button3 = 0;            // Reset the button3 value
}

CY_ISR(userEcho_ISR) {
    if (echoFlag == 1) {
        echoReadCounter = Timer_Echo_ReadCounter();    // Read the echo counter
        echoFlag = 2;
        Timer_Echo_WriteCounter(0);                     // Reset the echo counter
        Pin_EchoReturn_ClearInterrupt();                // Clear the echo return interrupt
    }
}

CY_ISR(userModeTimer_ISR) {
    modeFlag = 1;                       // Set the mode flag
    Timer_Mode_ReadStatusRegister();    // Read the status register of the mode timer
}

CY_ISR(userUpdateESP_ISR) {
    sprintf(espTransmit, "|%i,%i,%i,%i,%i,|\r\n", offsetUp, noteIndex, offset2, cScaleGroupSelect, cScaleSelect);  // Create the ESP transmission string
    // sprintf(espTransmit, "|{\"Rt\" : %i, \"Nt\" : %i, \"O2\" : %i, \"Gp\" : %i, \"Sc\" : %i}| \r\n", offsetUp, noteIndex, offset2, cScaleGroupSelect, cScaleSelect); // JSON version, slow
    UART_TOESP_PutString(espTransmit);  // Send the ESP transmission string
    Timer_Display_ReadStatusRegister(); // Read the status register of the display timer
}

/* [] END OF FILE */
