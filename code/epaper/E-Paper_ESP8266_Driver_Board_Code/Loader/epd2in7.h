/**
  ******************************************************************************
  * @file    edp2in7.h
  * @author  Waveshare Team
  * @version V1.0.0
  * @date    23-January-2018
  * @brief   This file describes initialisation of 2.7 and 2.7b e-Papers
  *
  ******************************************************************************
  */
unsigned char lut_dc_2in7[] = 
{
    0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x05, 0x00, 0x32, 0x32, 
    0x00, 0x00, 0x02, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x05, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R21H
unsigned char lut_ww_2in7[] = 
{
    0x50, 0x0F, 0x0F, 0x00, 0x00, 0x05, 0x60, 0x32, 0x32, 0x00, 0x00, 0x02, 0xA0, 0x0F, 
    0x0F, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R22H    r
unsigned char lut_bw_2in7[] =
{
    0x50, 0x0F, 0x0F, 0x00, 0x00, 0x05, 0x60, 0x32, 0x32, 0x00, 0x00, 0x02, 0xA0, 0x0F, 
    0x0F, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R24H    b
unsigned char lut_bb_2in7[] =
{
    0xA0, 0x0F, 0x0F, 0x00, 0x00, 0x05, 0x60, 0x32, 0x32, 0x00, 0x00, 0x02, 0x50, 0x0F, 
    0x0F, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//R23H    w
unsigned char lut_wb_2in7[] =
{
    0xA0, 0x0F, 0x0F, 0x00, 0x00, 0x05, 0x60, 0x32, 0x32, 0x00, 0x00, 0x02, 0x50, 0x0F, 
    0x0F, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

int EPD_Init_2in7() 
{
    EPD_Reset();
    
    EPD_SendCommand(0x01);//POWER_SETTING
    EPD_SendData(0x03);   // VDS_EN, VDG_EN
    EPD_SendData(0x00);   // VCOM_HV, VGHL_LV[1], VGHL_LV[0]
    EPD_SendData(0x2b);   // VDH
    EPD_SendData(0x2b);   // VDL
    EPD_SendData(0x09);   // VDHR
    
    EPD_Send_3(0x06, 0x07, 0x07, 0x17);//BOOSTER_SOFT_START
    
    // Power optimization
    EPD_Send_2(0xF8, 0x60, 0xA5);
    EPD_Send_2(0xF8, 0x89, 0xA5);
    EPD_Send_2(0xF8, 0x90, 0x00);
    EPD_Send_2(0xF8, 0x93, 0x2A);
    EPD_Send_2(0xF8, 0xA0, 0xA5);
    EPD_Send_2(0xF8, 0xA1, 0x00);
    EPD_Send_2(0xF8, 0x73, 0x41);
    
    EPD_Send_1(0x16, 0x00);//PARTIAL_DISPLAY_REFRESH
    EPD_SendCommand(0x04);//POWER_ON
    EPD_WaitUntilIdle();

    EPD_Send_1(0x00, 0xAF);//PANEL_SETTING: KW-BF, KWR-AF, BWROTP 0f
    EPD_Send_1(0x30, 0x3A);//PLL_CONTROL: 3A 100HZ, 29 150Hz, 39 200HZ, 31 171HZ
    EPD_Send_1(0x82, 0x12);//VCM_DC_SETTING_REGISTER
    delay(2);

    EPD_lut(0x20,44,&lut_dc_2in7[0]);// LUT_FOR_VCOM
    EPD_lut(0x21,42,&lut_ww_2in7[0]);// LUT_WHITE_TO_WHITE   
    EPD_lut(0x22,42,&lut_bw_2in7[0]);// LUT_BLACK_TO_WHITE
    EPD_lut(0x23,42,&lut_wb_2in7[0]);// LUT_WHITE_TO_BLACK
    EPD_lut(0x24,42,&lut_bb_2in7[0]);// LUT_BLACK_TO_BLACK

    EPD_SendCommand(0x10);//DATA_START_TRANSMISSION_1  
    delay(2);
    for(int i = 0; i < 176*264; i++)EPD_SendData(0xFF);//Red channel

    EPD_SendCommand(0x13);//DATA_START_TRANSMISSION_2
    delay(2);
    return 0;
}

int EPD_2IN7_V2_Init(void)
{
    EPD_Reset();
    EPD_WaitUntilIdle_high();

    EPD_SendCommand(0x12); //SWRESET
    EPD_WaitUntilIdle_high();

    EPD_SendCommand(0x45); //set Ram-Y address start/end position          
    EPD_SendData(0x00);
    EPD_SendData(0x00);
    EPD_SendData(0x07); //0x0107-->(263+1)=264
    EPD_SendData(0x01);

    EPD_SendCommand(0x4F);   // set RAM y address count to 0;    
    EPD_SendData(0x00);
    EPD_SendData(0x00);

    EPD_SendCommand(0x11);   // data entry mode
    EPD_SendData(0x03);

    EPD_SendCommand(0x24);
    delay(2);
	return 0;
}

void EPD_2IN7_V2_Show(void)
{
    EPD_SendCommand(0x22);  //Display Update Control
    EPD_SendData(0XF7);
    EPD_SendCommand(0x20);  //Activate Display Update Sequence
    EPD_WaitUntilIdle_high();
    delay(2);
    Serial.print("EPD_2IN7_V2_Show END\r\n");
    EPD_SendCommand(0X07);  	//deep sleep
    EPD_SendData(0xA5);
}

unsigned char lut_dc_2in7b[] =
{
    0x00, 0x00, 0x00, 0x1A, 0x1A, 0x00, 0x00, 0x01, 0x00, 0x0A, 0x0A, 
    0x00, 0x00, 0x08, 0x00, 0x0E, 0x01, 0x0E, 0x01, 0x10, 0x00, 0x0A, 
    0x0A, 0x00, 0x00, 0x08, 0x00, 0x04, 0x10, 0x00, 0x00, 0x05, 0x00, 
    0x03, 0x0E, 0x00, 0x00, 0x0A, 0x00, 0x23, 0x00, 0x00, 0x00, 0x01    
};

//R21H
unsigned char lut_ww_2in7b[] =
{
    0x90, 0x1A, 0x1A, 0x00, 0x00, 0x01, 0x40, 0x0A, 0x0A, 0x00, 0x00, 0x08, 0x84, 0x0E, 
    0x01, 0x0E, 0x01, 0x10, 0x80, 0x0A, 0x0A, 0x00, 0x00, 0x08, 0x00, 0x04, 0x10, 0x00, 
    0x00, 0x05, 0x00, 0x03, 0x0E, 0x00, 0x00, 0x0A, 0x00, 0x23, 0x00, 0x00, 0x00, 0x01
};

//R22H    r
unsigned char lut_bw_2in7b[] =
{
    0xA0, 0x1A, 0x1A, 0x00, 0x00, 0x01, 0x00, 0x0A, 0x0A, 0x00, 0x00, 0x08, 0x84, 0x0E, 
    0x01, 0x0E, 0x01, 0x10, 0x90, 0x0A, 0x0A, 0x00, 0x00, 0x08, 0xB0, 0x04, 0x10, 0x00, 
    0x00, 0x05, 0xB0, 0x03, 0x0E, 0x00, 0x00, 0x0A, 0xC0, 0x23, 0x00, 0x00, 0x00, 0x01
};

//R23H    w
unsigned char lut_bb_2in7b[] =
{
    0x90, 0x1A, 0x1A, 0x00, 0x00, 0x01, 0x40, 0x0A, 0x0A, 0x00, 0x00, 0x08, 0x84, 0x0E, 
    0x01, 0x0E, 0x01, 0x10, 0x80, 0x0A, 0x0A, 0x00, 0x00, 0x08, 0x00, 0x04, 0x10, 0x00,
    0x00, 0x05, 0x00, 0x03, 0x0E, 0x00, 0x00, 0x0A, 0x00, 0x23, 0x00, 0x00, 0x00, 0x01
};

//R24H    b
unsigned char lut_wb_2in7b[] =
{
    0x90, 0x1A, 0x1A, 0x00, 0x00, 0x01, 0x20, 0x0A, 0x0A, 0x00, 0x00, 0x08, 0x84, 0x0E, 
    0x01, 0x0E, 0x01, 0x10, 0x10, 0x0A, 0x0A, 0x00, 0x00, 0x08, 0x00, 0x04, 0x10, 0x00, 
    0x00, 0x05, 0x00, 0x03, 0x0E, 0x00, 0x00, 0x0A, 0x00, 0x23, 0x00, 0x00, 0x00, 0x01
};

int EPD_Init_2in7b() 
{
    EPD_Reset();

    EPD_SendCommand(0x04);//POWER_ON
    EPD_WaitUntilIdle();

    EPD_Send_1(0x00, 0xAF);//PANEL_SETTING
    EPD_Send_1(0x30,0x3A);//PLL_CONTROL: 3A 100HZ, 29 150Hz, 39 200HZ, 31 171HZ
    EPD_Send_5(0x01,0x03,0x00,0x2B,0x2B,0x09);//POWER_SETTING    
    EPD_Send_3(0x06,0x07,0x07,0x17);//BOOSTER_SOFT_START

    // Power optimization
    EPD_Send_2(0xF8,0x60,0xA5);
    EPD_Send_2(0xF8,0x89,0xA5);
    EPD_Send_2(0xF8,0x90,0x00);
    EPD_Send_2(0xF8,0x93,0x2A);
    EPD_Send_2(0xF8,0x73,0x41);

    EPD_Send_1(0x82,0x2E);// VCM_DC_SETTING_REGISTER
    EPD_Send_1(0x50,0xA7);// VCOM_AND_DATA_INTERVAL_SETTING
    
    EPD_lut(0x20,44,&lut_dc_2in7b[0]);// LUT_FOR_VCOM
    EPD_lut(0x21,42,&lut_ww_2in7b[0]);// LUT_WHITE_TO_WHITE   
    EPD_lut(0x22,42,&lut_bw_2in7b[0]);// LUT_BLACK_TO_WHITE
    EPD_lut(0x23,42,&lut_wb_2in7b[0]);// LUT_WHITE_TO_BLACK
    EPD_lut(0x24,42,&lut_bb_2in7b[0]);// LUT_BLACK_TO_BLACK

    EPD_Send_4(0x61, 0, 176, 1, 8);// TCON_RESOLUTION: HI(W), LO(W), HI(H), LO(H)
    EPD_Send_1(0x16, 0x00);//PARTIAL_DISPLAY_REFRESH); 

    EPD_SendCommand(0x10);//DATA_START_TRANSMISSION_1
    delay(2);
   
    return 0;
}

int EPD_Init_2in7b_V2(void)
{
	EPD_Reset();
	
	EPD_WaitUntilIdle_high();
	EPD_SendCommand(0x12);
	EPD_WaitUntilIdle_high();
	
	EPD_Send_3(0x00, 0x27, 0x01, 0x00);
	EPD_Send_1(0x11, 0x03);
	
	EPD_Send_2(0x44, 0x00, 0x15);
	EPD_Send_4(0x45, 0x00, 0x00, 0x7, 0x1);
	
	EPD_Send_1(0x4e, 0x00);
	EPD_Send_2(0x4f, 0x00, 0x00);
	
	EPD_SendCommand(0x24);
	return 0;
}

void EPD_Show_2in7b_V2(void)
{
	EPD_SendCommand(0x20);
	EPD_WaitUntilIdle_high();
	
	delay(200);
	EPD_Send_1(0x10, 0x01);
}
