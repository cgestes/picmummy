
#include "MEMORY.h"
#include "91x_lib.h"
#include "log.h"

#ifdef LOG_MEMORY
# define log(...) { d(__VA_ARGS__); }
#else
# define log(...) ;
#endif

void init_device(int pMemoryKey,int pValue, u8 pSize)
{
	char i,j;
	for(i=0; i<10; i++)
		gMemory[pMemoryKey].value[i]=pValue;

	if( !(pSize&MEMORY_TAB) ) // On initialise une donnée qui n'est pas un tableau.
	{
		i=pSize&MEMORY_SIZE;
		j=0;
		do
		{
		 	gMemory[pMemoryKey].value[j]=pValue;
			pValue = pValue >> 8;
			i--;
			j++;
		}while(i>0);
	}
	gMemory[pMemoryKey].size = pSize;
	gMemory[pMemoryKey].available=1;
	gMemory[pMemoryKey].updated=0;
}


int acces_Memory(int pMemoryKey, int pWriteData, int pReadWrite, int pIndex) // MEMORY_READ or MEMORY_WRITE
{  // Sémaphore d'exclusion mutuelle entre plusieurs lectures et écritures sur une même donnée dans gMemory

	while(!gMemory[pMemoryKey].available)
	  ;

	gMemory[pMemoryKey].available = 0;

	if(pReadWrite==MEMORY_READ)
		return gMemory[pMemoryKey].value[pIndex]; // lecture
	gMemory[pMemoryKey].value[pIndex] = pWriteData;   // ecriture
	return 0;
}

int read_Memory(int pMemoryKey, int pIndex, int pWait)
{
	int temps;
	while(!gMemory[pMemoryKey].available)
	  ;

	temps = acces_Memory(pMemoryKey, 0, MEMORY_READ, pIndex);
	gMemory[pMemoryKey].updated = 0;
	gMemory[pMemoryKey].available = 1;
	log("Read[%d]: %d\r\n", pIndex, temps);
	return temps;	
}

void write_Memory(int pMemoryKey, int pIndex, int pValue)
{
	while(!gMemory[pMemoryKey].available)
	  ;
	log("Write[%d]: %d\r\n", pIndex, pValue);
	acces_Memory(pMemoryKey, pValue, MEMORY_WRITE, pIndex);
	gMemory[pMemoryKey].updated = 1;
	gMemory[pMemoryKey].available = 1;
}

int read_Memory_Sizeof(int pMemoryKey, int pWait)
{
	int temps=0;
	int i;
	while(!gMemory[pMemoryKey].available)
	  ;
	for(i=0;i<(MEMORY_SIZE&gMemory[pMemoryKey].size);i++)
	{
	 	temps =  (temps<<8) + acces_Memory(pMemoryKey, 0, MEMORY_READ, i);	
	}
	
	gMemory[pMemoryKey].updated = 0;
	gMemory[pMemoryKey].available = 1;
	return temps;	
}

void write_Memory_Sizeof(int pMemoryKey, int pValue)
{
	int i;
	char temps;
	while(!gMemory[pMemoryKey].available)
	  ;
	for(i=0;i<(MEMORY_SIZE&gMemory[pMemoryKey].size);i++)
	{
	 	temps = pValue;
		acces_Memory(pMemoryKey, temps, MEMORY_WRITE, i);
		pValue = pValue>>8;	
	}
	
	gMemory[pMemoryKey].updated = 1;
	gMemory[pMemoryKey].available = 1;
}

int Get_Update_Memory(int pMemoryKey)
{
	while(!gMemory[pMemoryKey].available)
	  ;
	return gMemory[pMemoryKey].updated;
}


