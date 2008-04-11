
#ifndef _declare_H
#define _declare_H 



int Globali=0;
int Global_temps=0;
int Global_freq=0;

u8 I2C0_Global_Buffer_Tx[I2C0_GLOBAL_BUFFER_TX_SIZE][I2C0_LOCAL_BUFFER_SIZE];
u8 I2C0_Local_Buffer_Tx_Size[I2C0_GLOBAL_BUFFER_TX_SIZE];
u8 I2C0_Local_Buffer_Tx_Adress[I2C0_GLOBAL_BUFFER_TX_SIZE];
u8 I2C0_Global_Buffer_Tx_Position = 0;
u8 I2C0_Global_Buffer_Tx_Current = 0;
u8 I2C0_Local_Buffer_Tx_Position = 0;
u8 I2C0_Tx_Idx, I2C0_Rx_Idx, I2C0_Slave_Adress, I2C0_Direction;
u8 I2C0_Buffer_Tx[I2C0_LOCAL_BUFFER_SIZE], I2C0_Buffer_Rx[I2C0_LOCAL_BUFFER_SIZE];
u8 I2C0_Global_Buffer_Tx_Adress[I2C0_GLOBAL_BUFFER_TX_SIZE];

u8 I2C0_State=I2C_FREE;
u8 I2C0_ReadState = 0;
u32 I2C0_ReadTemp;
 
 
type_servo tab_servo[NB_SERVO];



u8 UART0_TxBuffer[10];
u8 UART0_RxBuffer[10];
u8 NbrOfDataToTransfer;
u8 NbrOfDataToRead;

u16 RxCounter;
u16 TxCounter ;
u8 Term_Task;
u8 Term_Command;
u8 UART0_Tx_state = UART_AVAILABLE;

device gMemory[50];
serial_list liste_serial[NB_SERIES];

// Barillet
int CouleurTeam;
int CouleurAdverse;
int CouleurTeam_NbVoulu;
int CouleurTeam_NbCourant;
int CouleurBlanc_NbVoulu;
int CouleurBlanc_NbCourant;
task BarTask_Courant;
int BarListe_Taille;
task BarListe_Task[10]; // Taches en attente
int BarTask_CptTask;	// Utilisé pour donné un numéro à chaque tache. Lien entre le "main" et les interruptions
int BarListe_Available;

int Barillet[5]; // 5 emplacements dans le Barillet

int BarPosition; // Position courante(voulue) du barillet

int BarTask_SaveTime;
int BarTask_TimeOut;
int BarCouleur_Ejecter;

int BarTask_TaskMainNum;
int BarState; // FREE ou BUSY
int Barillet_Mode; // Barillet_AUTOMATIQUE ou Barillet_MANUEL

// PobEye
int PobCouleur;


// PathFinding
u8 Adverse_State; // ADVERSE_PRESENT ou ADVERSE_OUBLIER

// Positions

position PositionsListe[20];


position Position_Depart;
position Position_Destination;
position Position_Adverse;
ListePoints PointPassage[20];


// Stratégie
int Fin_TE=0;

#endif /* _declare_H */

/* End of file declare.h */

