/* Includes ------------------------------------------------------------------*/
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>

/* Entry point ----------------------------------------------------------------*/
void setup()
{
  printf("EPD_2IN13B_V4_test Demo\r\n");
  DEV_Module_Init();

  printf("e-Paper Init and Clear...\r\n");
  EPD_2IN13B_V4_Init();
  EPD_2IN13B_V4_Clear();
  DEV_Delay_ms(500);

  //Create a new image cache named IMAGE_BW and fill it with white
  UBYTE *BlackImage, *RYImage; // Red or Yellow
  UWORD Imagesize = ((EPD_2IN13B_V4_WIDTH % 8 == 0) ? (EPD_2IN13B_V4_WIDTH / 8 ) : (EPD_2IN13B_V4_WIDTH / 8 + 1)) * EPD_2IN13B_V4_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while (1);
  }
  if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for red memory...\r\n");
    while (1);
  }
  printf("NewImage:BlackImage and RYImage\r\n");
  Paint_NewImage(BlackImage, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, 270, WHITE);
  Paint_NewImage(RYImage, EPD_2IN13B_V4_WIDTH, EPD_2IN13B_V4_HEIGHT, 270, WHITE);

  //Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_SelectImage(RYImage);
  Paint_Clear(WHITE);

#if 1   // show image for array    
  printf("show image for array\r\n");
  EPD_2IN13B_V4_Display(gImage_2in13b_V4b, gImage_2in13b_V4r);
  DEV_Delay_ms(2000);
#endif

#if 1   // Drawing on the image
  /*Horizontal screen*/
  //1.Draw black image
  printf("Draw black image\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawPoint(5, 70, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  Paint_DrawPoint(5, 80, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  Paint_DrawLine(20, 70, 50, 100, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(50, 70, 20, 100, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawRectangle(60, 70, 90, 100, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawCircle(125, 85, 15, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawString_CN(5, 15, "你好abc", &Font12CN, WHITE, BLACK);

  //2.Draw red image
  printf("Draw red image\r\n");
  Paint_SelectImage(RYImage);
  Paint_Clear(WHITE);
  Paint_DrawPoint(5, 90, RED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  Paint_DrawPoint(5, 100, RED, DOT_PIXEL_4X4, DOT_STYLE_DFT);
  Paint_DrawLine(125, 70, 125, 100, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawLine(110, 85, 140, 85, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawRectangle(20, 70, 50, 100, RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(165, 85, 15, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(5, 0, "waveshare Electronics", &Font12, BLACK, WHITE);
  Paint_DrawNum(5, 50, 987654321, &Font16, WHITE, RED);

  printf("EPD_Display\r\n");
  EPD_2IN13B_V4_Display(BlackImage, RYImage);
  DEV_Delay_ms(2000);
#endif

  printf("Clear...\r\n");
  EPD_2IN13B_V4_Clear();

  printf("Goto Sleep...\r\n");
  EPD_2IN13B_V4_Sleep();
  free(BlackImage);
  free(RYImage);
  BlackImage = NULL;
  RYImage = NULL;


}

/* The main loop -------------------------------------------------------------*/
void loop()
{
  //
}
