/******************** (C) COPYRIGHT 2006 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Date First Issued  : 05/18/2006 : Version 1.0
* Description        : Main program body
********************************************************************************
* History:
* 05/22/2007 : Version 1.2
* 05/24/2006 : Version 1.1
* 05/18/2006 : Version 1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "91x_lib.h"
#include "lcd_STR912.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
  
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

#define COEF_SON 3.43
#define DO_0   524280/264*COEF_SON
#define DO_0d  524280/280*COEF_SON
#define RE_0   524280/297*COEF_SON
#define RE_0d  524280/315*COEF_SON
#define MI_0   524280/330*COEF_SON
#define FA_0   524280/352*COEF_SON
#define FA_0d  524280/372*COEF_SON
#define SOL_0  524280/396*COEF_SON
#define SOL_0d 524280/420*COEF_SON
#define LA_0   524280/440*COEF_SON
#define LA_0d  524280/466*COEF_SON
#define SI_0   524280/495*COEF_SON

#define DO_1   524280/528*COEF_SON
#define DO_1d  524280/559*COEF_SON
#define RE_1   524280/594*COEF_SON
#define RE_1d  524280/629*COEF_SON
#define MI_1   524280/660*COEF_SON
#define FA_1   524280/704*COEF_SON
#define FA_1d  524280/745*COEF_SON
#define SOL_1  524280/792*COEF_SON
#define SOL_1d 524280/839*COEF_SON
#define LA_1   524280/880*COEF_SON
#define LA_1d  524280/932*COEF_SON
#define SI_1   524280/990*COEF_SON





#define REF_TPS 52428*COEF_SON // 1/10 sec

  GPIO_InitTypeDef GPIO_InitStructure;
  u8 a;
/* Private function prototypes -----------------------------------------------*/
  void SCU_Configuration(void);
  static void Delay(u32 nCount);
  void Jouer_note(u32 freq, u32 duree);
  void Activer_PLL(void);
  void Desactiver_PLL(void);
    
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main()
{
  #ifdef DEBUG
    debug();
  #endif

  /* Configure the system clocks */
  SCU_Configuration();


/* GPIO Configuration --------------------------------------------------------*/

				 /*
  GPIO_DeInit(GPIO0); // Pin for LCD_CS (P0.1)
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Disable;
  GPIO_InitStructure.GPIO_Alternate=GPIO_OutputAlt1;
  GPIO_Init (GPIO0, &GPIO_InitStructure);
  
  GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_RESET);	*/

  /*
  GPIO_DeInit(GPIO3);
  //Configure SSP1_MISO pin
  GPIO_InitStructure.GPIO_Direction = GPIO_PinInput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Enable;
  GPIO_InitStructure.GPIO_Alternate = GPIO_InputAlt1  ;
  GPIO_Init (GPIO3, &GPIO_InitStructure);

  //Configure SSP1_CLK, SSP1_MOSI, SSP1_nSS pins 
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Disable;
  GPIO_InitStructure.GPIO_Alternate = GPIO_OutputAlt2  ;
  GPIO_Init (GPIO3, &GPIO_InitStructure);
										*/
  
  GPIO_DeInit(GPIO4); // Haut parleur
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Disable;
  GPIO_InitStructure.GPIO_Alternate=GPIO_OutputAlt1;
  GPIO_Init (GPIO4, &GPIO_InitStructure);

  GPIO_DeInit(GPIO6); // Ecran
  GPIO_InitStructure.GPIO_Direction = GPIO_PinOutput;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Type = GPIO_Type_PushPull ;
  GPIO_InitStructure.GPIO_IPConnected = GPIO_IPConnected_Disable;
  GPIO_InitStructure.GPIO_Alternate=GPIO_OutputAlt1;
  GPIO_Init (GPIO6, &GPIO_InitStructure);



  //Activer_PLL();
  Desactiver_PLL();




  GPIO_WriteBit(GPIO6,GPIO_Pin_4,Bit_SET); // allume l'écran
  InitLCD();
  LCDSettings();
  LCDWrite130x130bmp();
  LCDSetLine(10,10,100,100, RED);

  while(1)
  {	
	//mission impossible
	Jouer_note(LA_0,8);
	Delay(1*REF_TPS);
	Jouer_note(LA_0,8);
	Delay(1*REF_TPS);
	Jouer_note(DO_1,6);
	Jouer_note(RE_1,6);
	Jouer_note(LA_0,8);
	Delay(1*REF_TPS);
	Jouer_note(LA_0,8);
	Delay(1*REF_TPS);
	Jouer_note(SOL_0,6);
	Jouer_note(SOL_0d,6);
	Jouer_note(LA_0,12);

	Delay(500000);
  }
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
  /* Enable the __GPIO0 */ //(CS_LCD)
  SCU_APBPeriphClockConfig(__GPIO0 ,ENABLE);
  /* Enable the __GPIO3 */ //(SSP1)
  SCU_APBPeriphClockConfig(__GPIO3 ,ENABLE);
  /* Enable the __GPIO4 */
  SCU_APBPeriphClockConfig(__GPIO4 ,ENABLE);
  /* Enable the __GPIO6 */
  SCU_APBPeriphClockConfig(__GPIO6 ,ENABLE);
  
  SCU_APBPeriphClockConfig(__SSP1 ,ENABLE);
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
	
}

void Desactiver_PLL(void)
{
	// Configure la PLL pour une fréquence de 96MHz, avec un quartz de 25MHz
	SCU_PCLKDivisorConfig(SCU_PCLK_Div1); // PCLK_Div2 pour le APB est de 48Mhz max
	SCU_FMICLKDivisorConfig(SCU_FMICLK_Div1);
	SCU_MCLKSourceConfig(SCU_MCLK_OSC); // horloge cablée sur Quartz
	SCU_FMICLKDivisorConfig(SCU_FMICLK_Div1); // Flash Memory Interface Clock Driver = RCLK / 2 (needed for PLL at 96MHz)
	
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Output         : None
* Return         : None
*******************************************************************************/
static void Delay(u32 nCount)
{
  u32 j = 0;

  for(j = nCount; j != 0; j--);
}


void Jouer_note(u32 freq, u32 duree)
{
	u32 i = 0;
	u32 fin = duree*REF_TPS;
	
	if(GPIO_ReadBit(GPIO6,GPIO_Pin_4) == Bit_SET)
		{
			GPIO_WriteBit(GPIO6,GPIO_Pin_4,Bit_RESET);
		}
	else
		{
			GPIO_WriteBit(GPIO6,GPIO_Pin_4,Bit_SET);
		}
	
	do
	{
		Delay(freq);
		GPIO_WriteBit(GPIO4,GPIO_Pin_6,Bit_SET);
		Delay(freq);
		GPIO_WriteBit(GPIO4,GPIO_Pin_6,Bit_RESET);
		i=i+freq*2;
	} while (i<fin);
}

/******************* (C) COPYRIGHT 2006 STMicroelectronics *****END OF FILE****/
