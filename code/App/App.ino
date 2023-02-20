/* Includes ------------------------------------------------------------------*/
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>
#include "Excuses.h"

//int buttonPin = 16;  // GPIO 4 (D2) for ESP8266 https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
int buttonPin = 0;  // GPIO 4 (D2) for ESP8266 https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

int cigaretteCounter = 0;
char input; // for serial

bool buttonPressed = false;
bool pButtonPressed = false;

UBYTE *BlackImage;

unsigned long seed = 0;

void setup() {
    Serial.begin(115200);
  //randomSeed(randomSeed);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  printf("Smoke Break v1 \r\n");
  DEV_Module_Init();

  printf("e-Paper Init and Clear...\r\n");
  EPD_1IN54_V2_Init();
  EPD_1IN54_V2_Clear();
  DEV_Delay_ms(500);

  //Create a new image cache
  /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
  UWORD Imagesize = ((EPD_1IN54_V2_WIDTH % 8 == 0) ? (EPD_1IN54_V2_WIDTH / 8) : (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while (1)
      ;
  }
  printf("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);

  Paint_SetRotate(0);
  showTitle();
  //showNextExcuse();
  //EPD_1IN54_V2_Sleep();

}

void showTitle() {
  cigaretteCounter = 0;

  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  
  //Paint_DrawString_EN(5, 85, "SMOKE BREAK", &Font24, WHITE, BLACK);

  Paint_DrawString_EN(55, 85 - Font16.Height, "SMOKE", &Font24, WHITE, BLACK);
  Paint_DrawString_EN(55, 85 + Font16.Height, "BREAK", &Font24, WHITE, BLACK);

  EPD_1IN54_V2_Display(BlackImage);
  //DEV_Delay_ms(2000);

}

void showDayCounter() {

  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  Paint_DrawString_EN(5, 5, "Days without smoking 1", &Font20, WHITE, BLACK);

  EPD_1IN54_V2_Display(BlackImage);
  DEV_Delay_ms(1000);
  //EPD_1IN54_V2_Sleep();
}

void showNextExcuse() {
  cigaretteCounter++;
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  int idx = random(n_excuses);
  excuse ex = excuses[idx];
  Paint_DrawString_EN(5, 5, ex.message, &Font20, WHITE, BLACK);
  char s [20];
  sprintf (s, "Cigarettes %d", cigaretteCounter);
  
  Paint_DrawString_EN(5, EPD_1IN54_V2_HEIGHT - 5 - Font16.Height, s, &Font16, WHITE, BLACK);

  EPD_1IN54_V2_Display(BlackImage);
  DEV_Delay_ms(1000);
  //EPD_1IN54_V2_Sleep();
}

void loop() {
  int buttonValue = digitalRead(buttonPin);
  //int buttonValue = analogRead(buttonPin);
  //Serial.println("loop");
  //Serial.println(buttonValue);
  //Serial.println(buttonValue);
  buttonPressed = buttonValue == HIGH;
  //buttonPressed = true; 

  if(Serial.available()){
        input = Serial.read();
        if (input == 'm') {
          showNextExcuse();
        }

        if (input == 'q') {
          showDayCounter();
        }

        if (input == 'h') {
          showTitle();
        }
  }

  bool onButtonUp = pButtonPressed && !buttonPressed;

  if (onButtonUp) {
    //Serial.println("click");
    showNextExcuse();
  }

  pButtonPressed = buttonPressed;

  digitalWrite(LED_BUILTIN, buttonValue);  // Built in LED feedback

  delay(1);

  //delay(100);
/*
    digitalWrite(LED_BUILTIN, HIGH);  // Built in LED feedback
delay(100);
    digitalWrite(LED_BUILTIN, LOW);  // Built in LED feedback
*/
}

/*
#if 0  // Drawing on the image
    printf("Drawing\r\n");
    
    //1.Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    // 2.Drawing on the image
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 10, 20, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(170, 15, 170, 55, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(150, 35, 190, 35, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(85, 10, 130, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawCircle(170, 35, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(170, 85, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(5, 85, "waveshare", &Font20, BLACK, WHITE);
    Paint_DrawNum(5, 110, 123456789, &Font20, BLACK, WHITE);

    Paint_DrawString_CN(5, 135,"你好abc", &Font12CN, BLACK, WHITE);
    Paint_DrawString_CN(5, 155, "微雪电子", &Font24CN, WHITE, BLACK);

    EPD_1IN54_V2_Display(BlackImage);
    DEV_Delay_ms(2000);
#endif
*/

/*
#if 0   //show image for array    
    printf("show image for array\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(gImage_1in54);

    EPD_1IN54_V2_Display(BlackImage);
    DEV_Delay_ms(2000);
#endif

// Fonts are 8, 12, 16, 20, 24
*/

//EPD_1IN54_V2_Sleep();
//free(BlackImage);
//BlackImage = NULL;

/*
    printf("Clear...\r\n");
    EPD_1IN54_V2_Init();
    EPD_1IN54_V2_Clear();

    printf("Goto Sleep...\r\n");
    EPD_1IN54_V2_Sleep();
    free(BlackImage);
    BlackImage = NULL;
  */

/*
#if 0   //Partial refresh, example shows time    
    // The image of the previous frame must be uploaded, otherwise the
    // first few seconds will display an exception.
    EPD_1IN54_V2_Init();
    EPD_1IN54_V2_DisplayPartBaseImage(BlackImage);
    EPD_1IN54_V2_Init_Partial();
    printf("Partial refresh\r\n");
    Paint_SelectImage(BlackImage);
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 20;
    for (;;) {
        sPaint_time.Sec = sPaint_time.Sec + 1;
        if (sPaint_time.Sec == 60) {
            sPaint_time.Min = sPaint_time.Min + 1;
            sPaint_time.Sec = 0;
            if (sPaint_time.Min == 60) {
                sPaint_time.Hour =  sPaint_time.Hour + 1;
                sPaint_time.Min = 0;
                if (sPaint_time.Hour == 24) {
                    sPaint_time.Hour = 0;
                    sPaint_time.Min = 0;
                    sPaint_time.Sec = 0;
                }
            }
        }
        Paint_ClearWindows(15, 65, 15 + Font20.Width * 7, 65 + Font20.Height, WHITE);
        Paint_DrawTime(15, 65, &sPaint_time, &Font20, WHITE, BLACK);
        num = num - 1;
        if(num == 0) {
            break;
        }
        EPD_1IN54_V2_DisplayPart(BlackImage);
        DEV_Delay_ms(500);//Analog clock 1s
    }
#endif

  */
