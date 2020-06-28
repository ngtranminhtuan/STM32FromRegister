#include "stm32f10x.h"
#include "stm32f10x_flash.h"

void WriteFlash(void);
void ReadFlash(void);

static uint16_t datasave[101];
static uint16_t dataread[101];

int main(){
	
}

void WriteFlash(){
	unsigned char i;
	// Mo khoa Flash cho phep xoa du lieu
	FLASH_Unlock();
	
	//Xoa cac co bao trang thai cua Flash
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	//Xoa page can ghi
	FLASH_ErasePage(0x0807F800);
	
	for(i=0;i<100;i++){
		//Ghi 100 so 16 bit vao Flash
		FLASH_ProgramHalfWord(0x0807F800 + i*2, datasave[i]);
	}
	//Khoa Flash de cam xoa
	FLASH_Lock();
}

void ReadFlash(){
	unsigned char i;
	for(i=0;i<100;i++){
		//Doc 100 so 16 bit tu Flash ve
		dataread[i] = *(uint16_t *)(0x0807F800 + i*2);
	}
}
