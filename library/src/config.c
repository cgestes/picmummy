/*
* File Name          : config.c
* Author             : Xt-6
* Date First Issued  : 03/02/2008 : Version 1.0
* Description        : regroupe les fonctions de configurations de la carte
********************************************************************************
* History:
*
*******************************************************************************/
#include "91x_lib.h"


 GPIO_InitTypeDef GPIO_InitStructure;
 ADC_InitTypeDef   ADC_InitStructure;
 TIM_InitTypeDef	TIM_InitStructure;
 UART_InitTypeDef UART_InitStructure;
 I2C_InitTypeDef	I2C_InitStructure;

void GPIO_config (void)
{
/* GPIO Configuration --------------------------------------------------------*/
  
  // GPIO 4
  GPIO_DeInit(GPIO4); // Haut parleur
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Disable;
  GPIO_InitStructure.GPIO_Alternate=GPIO_OutputAlt1;
  GPIO_Init (GPIO4, &GPIO_InitStructure);

  GPIO_ANAPinConfig(GPIO_ANAChannel5, ENABLE); // Potentiomètre
  GPIO_ANAPinConfig(GPIO_ANAChannel4, ENABLE); // Joystick
  GPIO_ANAPinConfig(GPIO_ANAChannel0, ENABLE); // SHARP
  GPIO_ANAPinConfig(GPIO_ANAChannel1, ENABLE); // SHARP
  GPIO_ANAPinConfig(GPIO_ANAChannel2, ENABLE); // SHARP
  GPIO_ANAPinConfig(GPIO_ANAChannel3, ENABLE); // SHARP


  // GPIO 6
  GPIO_DeInit(GPIO6); // Ecran
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Disable;
  GPIO_InitStructure.GPIO_Alternate=GPIO_OutputAlt1;
  GPIO_Init (GPIO6, &GPIO_InitStructure);

  // GPIO 5
	/* UART0  */
  GPIO_DeInit(GPIO5);
  /*Configure UART0_Rx pin GPIO5.1*/
  GPIO_InitStructure.GPIO_Direction = GPIO_PinInput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_Alternate = GPIO_InputAlt1;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Enable;
  GPIO_Init (GPIO5, &GPIO_InitStructure);

  /*Configure UART0_Tx pin GPIO5.0*/
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt3;
  GPIO_Init (GPIO5, &GPIO_InitStructure);

  // GPIO 3
	/* UART2  */
  GPIO_DeInit(GPIO3);
  /*Configure UART2_Rx pin GPIO3.1*/
  GPIO_InitStructure.GPIO_Direction = GPIO_PinInput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_Alternate = GPIO_InputAlt1;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Enable;
  GPIO_Init (GPIO3, &GPIO_InitStructure);

  /*Configure UART2_Tx pin GPIO3.0*/
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt2;
  GPIO_Init (GPIO3, &GPIO_InitStructure);

	/* LCD */
  // Gonfigure SSP1_CLK, SSP1_MOSI
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Enable;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt2;
  GPIO_Init (GPIO3, &GPIO_InitStructure);

  //Configure SSP1_MISO pin
  GPIO_InitStructure.GPIO_Direction = GPIO_PinInput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Enable;
  GPIO_InitStructure.GPIO_Alternate = GPIO_InputAlt1  ;
  GPIO_Init (GPIO3, &GPIO_InitStructure);


  // GPIO 2
    /* I2C 0 */
   GPIO_DeInit(GPIO2);
  /*Configure SCL*/
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt2;
  GPIO_Init (GPIO2, &GPIO_InitStructure);
  
  /*Configure SDA*/
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_OpenCollector;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt2;
  GPIO_Init (GPIO2, &GPIO_InitStructure);

  /*Bouton départ/couleur*/
  GPIO_InitStructure.GPIO_Direction = GPIO_PinInput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;  // PullUp Cablée
  GPIO_InitStructure.GPIO_Alternate = GPIO_InputAlt1;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Disable;
  GPIO_Init (GPIO2, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Direction = GPIO_PinInput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ; // PullUp Cablée
  GPIO_InitStructure.GPIO_Alternate = GPIO_InputAlt1;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Disable;
  GPIO_Init (GPIO2, &GPIO_InitStructure);

}


 void ADC_config (void)
 {
/* ADC Structure Initialization */
  ADC_StructInit(&ADC_InitStructure);

  /* Configure the ADC in continuous mode conversion */
  ADC_InitStructure.ADC_Channel_5_Mode = ADC_NoThreshold_Conversion;
  ADC_InitStructure.ADC_Channel_4_Mode = ADC_NoThreshold_Conversion;
  ADC_InitStructure.ADC_Channel_0_Mode = ADC_NoThreshold_Conversion;
  ADC_InitStructure.ADC_Channel_1_Mode = ADC_NoThreshold_Conversion;
  ADC_InitStructure.ADC_Channel_2_Mode = ADC_NoThreshold_Conversion;
  ADC_InitStructure.ADC_Channel_3_Mode = ADC_NoThreshold_Conversion;
  ADC_InitStructure.ADC_Scan_Mode = ENABLE;
  ADC_InitStructure.ADC_Conversion_Mode = ADC_Continuous_Mode;

  /* Enable the ADC */
  ADC_Cmd(ENABLE);

  /* Prescaler config */
  ADC_PrescalerConfig(0x0);

  /* Configure the ADC */
  ADC_Init(&ADC_InitStructure);

  /* Start the conversion */
  ADC_ConversionCmd(ADC_Conversion_Start);

}

void configuration_I2C (void)
{
   I2C_DeInit(I2C0);

   I2C_InitStructure.I2C_CLKSpeed = 90000; // 100k
   I2C_InitStructure.I2C_OwnAddress = I2C_MyAdress;
   I2C_InitStructure.I2C_GeneralCall = I2C_GeneralCall_Disable;
   I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;

   I2C_Init(I2C0, &I2C_InitStructure);
   I2C_Cmd(I2C0, ENABLE);
   I2C0_ReadState = 0; // utilisé dans les interruption
}


void configuration_UART (void)
{

	// UART0
  UART_InitStructure.UART_WordLength = UART_WordLength_8D;
  UART_InitStructure.UART_StopBits = UART_StopBits_1;
  UART_InitStructure.UART_Parity = UART_Parity_No ;
  UART_InitStructure.UART_BaudRate = 115200;   
  UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
  UART_InitStructure.UART_Mode = UART_Mode_Tx_Rx;
  UART_InitStructure.UART_FIFO = UART_FIFO_Enable;
  UART_InitStructure.UART_TxFIFOLevel = UART_FIFOLevel_1_8; /* FIFO size 16 bytes, FIFO level 8 bytes */
  UART_InitStructure.UART_RxFIFOLevel = UART_FIFOLevel_1_8; /* FIFO size 16 bytes, FIFO level 8 bytes */
  
  

  UART_DeInit(UART0);
  UART_ITConfig (UART0, UART_IT_Receive, ENABLE);
  UART_Init(UART0, &UART_InitStructure);

  /* Enable the UART0 */
  UART_Cmd(UART0, ENABLE);

  	// UART2
  UART_InitStructure.UART_WordLength = UART_WordLength_8D;
  UART_InitStructure.UART_StopBits = UART_StopBits_1;
  UART_InitStructure.UART_Parity = UART_Parity_No ;
  UART_InitStructure.UART_BaudRate = 115200;   
  UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
  UART_InitStructure.UART_Mode = UART_Mode_Tx_Rx;
  UART_InitStructure.UART_FIFO = UART_FIFO_Disable;
  //UART_InitStructure.UART_TxFIFOLevel = UART_FIFOLevel_1_8; /* FIFO size 16 bytes, FIFO level 8 bytes */
  //UART_InitStructure.UART_RxFIFOLevel = UART_FIFOLevel_1_8; /* FIFO size 16 bytes, FIFO level 8 bytes */
 
 // UART_InitStructure.UART_Mode = UART_Mode_Tx_Rx;
 // UART_InitStructure.UART_FIFO = UART_FIFO_Enable;
 // UART_InitStructure.UART_TxFIFOLevel = UART_FIFOLevel_1_8; /* FIFO size 16 bytes, FIFO level 8 bytes */
 // UART_InitStructure.UART_RxFIFOLevel = UART_FIFOLevel_1_8; /* FIFO size 16 bytes, FIFO level 8 bytes */
  
  

  UART_DeInit(UART2);
  UART_ITConfig (UART2, UART_IT_Receive, ENABLE);
  UART_Init(UART2, &UART_InitStructure);

  /* Enable the UART2 */
  UART_Cmd(UART2, ENABLE);
  
}


void config_timer0 (void)
{
  /* Timer 0 en interrution */
  TIM_DeInit(TIM0);

  TIM_InitStructure.TIM_Clock_Source = TIM_CLK_APB;
  TIM_InitStructure.TIM_Prescaler = 240;
  TIM_InitStructure.TIM_Mode = TIM_OCM_CHANNEL_1;
  TIM_InitStructure.TIM_Pulse_Length_1= 20000; // 0,1 sec
  TIM_InitStructure.TIM_OC1_Modes = TIM_TIMING;
  TIM_ITConfig(TIM0, TIM_IT_OC1, ENABLE);
  TIM_Init(TIM0, &TIM_InitStructure);
  TIM_CounterCmd(TIM0, TIM_START);
}



void config_interruption (void)
{
 /* Interrutpions du timer 0*/
  VIC_DeInit();

  // Timer0
  VIC_Config(TIM0_ITLine, VIC_IRQ, 0);
  VIC_ITCmd(TIM0_ITLine, ENABLE);


  //interruption UART 
  VIC_Config(UART0_ITLine, VIC_IRQ, 3);
  VIC_ITCmd(UART0_ITLine, ENABLE);

  VIC_Config(UART2_ITLine, VIC_IRQ, 2);
  VIC_ITCmd(UART2_ITLine, ENABLE);

  //I2C
  VIC_Config(I2C0_ITLine,VIC_IRQ , 1);
  VIC_ITCmd(I2C0_ITLine, ENABLE);

}



void Activer_PLL(void)
{
	// Configure la PLL pour une fréquence de 96MHz, avec un quartz de 25MHz
	SCU_MCLKSourceConfig(SCU_MCLK_OSC); // horloge cablée sur Quartz
	SCU_FMICLKDivisorConfig(SCU_FMICLK_Div2); // Flash Memory Interface Clock Driver = RCLK / 2 (needed for PLL at 96MHz)
	SCU_PCLKDivisorConfig(SCU_PCLK_Div2); // PCLK_Div2 pour le APB est de 48Mhz max
	SCU_HCLKDivisorConfig(SCU_HCLK_Div1);
	SCU_PLLFactorsConfig(192, 25, 2); // Configure la PLL à 96MHz
	SCU_PLLCmd(ENABLE); // Active la PLL
	SCU_MCLKSourceConfig(SCU_MCLK_PLL); // horloge cablée sur la PLL
	SCU_RCLKDivisorConfig(SCU_RCLK_Div1 ); 
	
}


void Desactiver_PLL(void)
{
	// Configure un quartz de 25MHz
	SCU_MCLKSourceConfig(SCU_MCLK_OSC); // horloge cablée sur Quartz
	SCU_PCLKDivisorConfig(SCU_PCLK_Div1); // PCLK_Div2 pour le APB est de 48Mhz max
	SCU_HCLKDivisorConfig(SCU_HCLK_Div1);
	SCU_RCLKDivisorConfig(SCU_RCLK_Div1);
	SCU_FMICLKDivisorConfig(SCU_FMICLK_Div1); // Flash Memory Interface Clock Driver = RCLK / 2 (needed for PLL at 96MHz)
	SCU_PLLCmd(DISABLE);
}

/*******************************************************************************
* Function Name  : SCU_Configuration
* Description    : Configures the system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SCU_Configuration(void)
{
  // Enable the __GPIO0  //(CS_LCD)
  SCU_APBPeriphClockConfig(__GPIO0 ,ENABLE);
  // Enable the __GPIO3  //(SSP1 + UART2)
  SCU_APBPeriphClockConfig(__GPIO3 ,ENABLE);
  // Enable the __GPIO4 
  SCU_APBPeriphClockConfig(__GPIO4 ,ENABLE);
  // Enable the __GPIO6
  SCU_APBPeriphClockConfig(__GPIO6 ,ENABLE);
  
  SCU_APBPeriphClockConfig(__SSP1 ,ENABLE);
  
  SCU_APBPeriphClockConfig(__ADC, ENABLE);    // Enable the clock for the ADC 
  ADC_DeInit();                               // ADC Deinitialization 

    // Enable the UART0 Clock 
  SCU_APBPeriphClockConfig(__UART0, ENABLE);
  SCU_APBPeriphClockConfig(__UART2, ENABLE);

  // Enable the GPIO5 Clock
  SCU_APBPeriphClockConfig(__GPIO5, ENABLE);
   	
  // Timer 0 
  //SCU_TIMCLKSourceConfig(SCU_TIM01, SCU_TIMCLK_INT); // timer01 sur horloge interne
  //SCU_TIMPresConfig(SCU_TIM01, 9600 ); // Prescaler sur Fmaster(96Mhz) 9600=>  TE=0,1ms
  // On utilise Pclk comme entrée d'horloge
  SCU_APBPeriphClockConfig(__TIM01, ENABLE);

  SCU_AHBPeriphClockConfig(__VIC, ENABLE);
  SCU_AHBPeriphReset(__VIC, DISABLE);

  SCU_AHBPeriphClockConfig(__FMI, ENABLE);
  SCU_AHBPeriphReset(__FMI, DISABLE);

  SCU_APBPeriphClockConfig(__VIC, ENABLE);
  SCU_APBPeriphReset(__VIC, DISABLE);

    /* I2C */
  SCU_APBPeriphClockConfig(__GPIO2 ,ENABLE);
  SCU_APBPeriphClockConfig(__I2C0 ,ENABLE);

}

void config_FMI(void)
{
	/* -------------------------------------------------------------------------- */
	/*                Configure bank 0 as 512KB and bank 1 as 32KB                */
	/*        Configure bank 0 at address 0x0 and bank 1 at address 0x80000       */
	/* -------------------------------------------------------------------------- */
	
	  FMI_BankRemapConfig(0x4, 0x2, 0x0, 0x80000);
	
	/* -------------------------------------------------------------------------- */
	/*             Disable the Write protection for sector 0 of bank 1            */
	/* -------------------------------------------------------------------------- */
	
	  FMI_WriteProtectionCmd(FMI_B1S0, DISABLE);
	
	/* -------------------------------------------------------------------------- */
	/*                        Erase the sector 0 of bank 1                        */
	/* -------------------------------------------------------------------------- */
	
	  //FMI_EraseSector(FMI_B1S0); On ne veut pas effacer la mémoire !!
	  //FMI_Timeout_Status = FMI_WaitForLastOperation(FMI_BANK_1);
}

void initialisation (void)
{

 	SCU_Configuration();/* Configure the system clocks */
	Activer_PLL();
//  Desactiver_PLL();	
	GPIO_config ()  ; //configuration du GPIO
	ADC_config ()	; //configuration ADC
	configuration_UART () ;	//configuration UART
	config_timer0 ();  // config timer
	configuration_I2C();
	config_FMI();


	GPIO_WriteBit(GPIO6,GPIO_Pin_4,Bit_SET); // allume l'écran
	InitLCD();
	LCDSettings();
	//réinitialisation des variables
	Globali=0;
	Global_temps=0;

	// Global memory
	init_device(SERVO_0_KEY,0,MEMORY_SIZE_8); //init_device(int pMemoryKey,int pValue, u8 pSize)
	init_device(SERVO_1_KEY,0,MEMORY_SIZE_8);
	init_device(SERVO_2_KEY,0,MEMORY_SIZE_8);
	init_device(SERVO_3_KEY,0,MEMORY_SIZE_8);
	init_device(SERVO_4_KEY,0,MEMORY_SIZE_8);
	init_device(SERVO_5_KEY,0,MEMORY_SIZE_8);
	init_device(SERVO_6_KEY,0,MEMORY_SIZE_8);
	init_device(SERVO_7_KEY,0,MEMORY_SIZE_8);
	init_device(SERVO_8_KEY,0,MEMORY_SIZE_8);
	init_device(SERVO_9_KEY,0,MEMORY_SIZE_8);

	//init_device(int pMemoryKey,int pValue, u8 pSize)
	init_device(BARILLET_KEY,0,MEMORY_SIZE_8);
	init_device(BARILLET_RETURN_KEY,0,MEMORY_SIZE_8);
   	write_Memory_Sizeof(BARILLET_KEY, 128);
 	
	// Barillet
	init_device(BARILLET_POSITION_KEY,0,MEMORY_SIZE_8);
	init_device(BARILLET_TASK_KEY,0,MEMORY_SIZE_8);
	init_device(BARILLET_POSITION_KEY,0,MEMORY_SIZE_8);
	init_device(BARILLET_BLOQUER_ENTREE_KEY,0,MEMORY_SIZE_8);
	init_device(NBBALLE_TOTAL_KEY,0,MEMORY_SIZE_8);
	init_device(NBBALLE_BLANCHE_KEY,0,MEMORY_SIZE_8);
	init_device(NBBALLE_TEAM_KEY,0,MEMORY_SIZE_8);
	init_device(NBBALLE_ADVERSE_KEY,0,MEMORY_SIZE_8);

	// Asservissement
	init_device(ASS_WRITE_KEY,0,MEMORY_TAB+5);
	init_device(ASS_POINT1_X_KEY,0,MEMORY_SIZE_16);
	init_device(ASS_POINT1_Y_KEY,0,MEMORY_SIZE_16);
	init_device(ASS_POINT2_X_KEY,0,MEMORY_SIZE_16);
	init_device(ASS_POINT2_Y_KEY,0,MEMORY_SIZE_16);
	init_device(ASS_CONSIGNE_KEY,0,MEMORY_SIZE_16);
	init_device(ASS_READ_KEY,0,MEMORY_TAB+5);
	init_device(ASS_COORDONEES_X_KEY,0,MEMORY_SIZE_16);
	init_device(ASS_COORDONEES_Y_KEY,0,MEMORY_SIZE_16);
	init_device(ASS_ORIENTATION_KEY,0,MEMORY_SIZE_16);

	// Capteur infrarouges
	init_device(IR_C_KEY,0,MEMORY_TAB+5);

	// Camera PobEye
	init_device(POBEYE_BALLE_KEY,0,MEMORY_SIZE_8);
	init_device(POBEYE_TERRAIN_KEY,0,MEMORY_SIZE_8);

	LCD_Debug_String("Load Settings...");
	load_all_servos();
	LCD_Debug_String("Load successful");
	
	// void I2C0_Add_message(int pSlave, int RW,int pRepeat,int pCommand,int pMemoryKey)
	//I2C0_Add_message(I2C_ServoAdress, SERIAL_WRITE, SERIAL_REPEAT_ON ,0 ,SERVO_0_KEY);
	//I2C0_Add_message(I2C_ServoAdress, SERIAL_WRITE, SERIAL_REPEAT_ON ,1 ,SERVO_1_KEY);
	//I2C0_Add_message(I2C_ServoAdress, SERIAL_WRITE, SERIAL_REPEAT_ON ,2 ,SERVO_2_KEY);
	
	//I2C0_Add_message(I2C_BarilletAdress, SERIAL_WRITE, SERIAL_REPEAT_ON ,COM_BARILLET_WRITE ,BARILLET_KEY);
	I2C0_Add_message(I2C_BarilletAdress, SERIAL_READ, SERIAL_REPEAT_ON ,COM_BARILLET_READ ,BARILLET_RETURN_KEY);
	

//	I2C0_Add_message(54, SERIAL_WRITE, SERIAL_REPEAT_ON ,3 ,SERVO_3_KEY);
//	I2C0_Add_message(54, SERIAL_WRITE, SERIAL_REPEAT_ON ,4 ,SERVO_4_KEY);
//	I2C0_Add_message(54, SERIAL_WRITE, SERIAL_REPEAT_ON ,5 ,SERVO_5_KEY);
//	I2C0_Add_message(54, SERIAL_WRITE, SERIAL_REPEAT_ON ,6 ,SERVO_6_KEY);
//	I2C0_Add_message(54, SERIAL_WRITE, SERIAL_REPEAT_ON ,7 ,SERVO_7_KEY);
//	I2C0_Add_message(54, SERIAL_WRITE, SERIAL_REPEAT_ON ,8 ,SERVO_8_KEY);
//	I2C0_Add_message(54, SERIAL_WRITE, SERIAL_REPEAT_ON ,9 ,SERVO_9_KEY);

	Init_PathFinding();
	Init_Pobeye();
	Init_Barillet();
	Init_Strategie();

	config_interruption ();	 // Lance le Timer, l'I2C ...
}

/* End of file config.c */
