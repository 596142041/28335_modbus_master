#include "CAN_APP.h"
#include "LED.h"
#include "Flash.h"
#include "timer.h"
#include "os.h"
#include "modbus_master.h"
#include "port.h"
#include "modbus_master.h"
int i = 0;
void Modbus_Data_Init(void);
void task_10ms(void);
void task_50ms(void);
uint16_t  Input_Result[2] = {0,0};
uint8_t result =0;
u8 test = 0;
u8 test_send = 0;
void main(void)
{
	InitSysCtrl();
	LED_GPIO_Config();
	CAN_GPIO_Config(CANA);
	taskinit();
	DINT;
	DRTM;
	CsmUnlock();
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);
	MemCopy(&Flash28_API_LoadStart, &Flash28_API_LoadEnd,&Flash28_API_RunStart);
	InitFlash();
	FlashAPI_Init();
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.ECAN1INTA = &Ecana_isr1;
	PieVectTable.XINT13    = &CPU_timer1_isr;
	PieVectTable.TINT0     = &cpu_timer0_isr;
	PieVectTable.SCIRXINTC = &serial_Rx_isr;
	PieVectTable.SCITXINTC = &serial_Tx_isr;
	EDIS;
	//LED_Timer_Config();
	CPU_timer1_init();
	ModbusMaster_begin();
	xMBPortSerialInit(9600);
 	vMBPortSerialEnable(1,1);
	xMBPortTimersInit(20);
	vMBPortTimersEnable();

	CAN_Config(CANA);
	CAN_Rx_Config();
	CAN_Rx_IT_Concig();

	//配置中断
	PieCtrlRegs.PIEIER9.bit.INTx6 = 1; //CANA的中断1
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	//使能CPU定时器0的中断

	IER |= M_INT9;
	IER |= M_INT13;
	IER |= M_INT8;
	IER |= M_INT1;

	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM

   while(1)
   {
	   if(test == 1)
	   {

		   result = ModbusMaster_readInputRegisters(0x01,0x2, 2);
		   		if (result == 0x00)
		   		{
		   			Input_Result[0] = ModbusMaster_getResponseBuffer(0x00);
		   			Input_Result[1] = ModbusMaster_getResponseBuffer(0x01);
		   		}
	   }
	   if(test_send == 1)
	   {
		   test_send = 0;
		   xMBPortSerialPutByte('A');
	   }
		for(i = 0;i<TASKNUM;i++)
		{
			if(tasktimer[i].flag != 0)
			{
				switch (i)
				{
					case TASK10MS:
					{
						task_10ms();
					}
					break;
					case TASK50MS:
					{
						task_50ms();
					}
					break;
				}
			}
		}
   }
}
/*

 */
void task_10ms(void)
{
	;
}
void task_50ms(void)
{
	if(can_rx_msg.rx_update == UPDATE)
	{
		can_rx_msg.rx_update = NON_CHANGE;
		CAN_BOOT_ExecutiveCommand(&can_rx_msg);
	}
}
