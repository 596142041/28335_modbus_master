#ifndef _PORT_H
#define _PORT_H

#include "bsp_board.h"
#include <inttypes.h>
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }
#define assert(e) ((e) ? (void)0 :  1)
void __assert(const char * x1, const char * x2, int x3);


//数据类型定义
typedef unsigned char UCHAR;
typedef char CHAR;
typedef UCHAR BOOL;
typedef unsigned short int USHORT;
typedef short int SHORT;
typedef unsigned long int ULONG;
typedef long int LONG;
//485 接口宏定义
#define USER_RS485_Port 0
#define RS485_Pin GpioDataRegs.GPADAT.bit.GPIO0
#define TX_EN 1
#define RX_EN 0
#define ENTER_CRITICAL_SECTION()   INTX_DISABLE() //关总中断
#define EXIT_CRITICAL_SECTION()    INTX_ENABLE() //开总中断
#ifndef TRUE
#define TRUE            1
#endif
#ifndef FALSE
#define FALSE           0
#endif
void INTX_DISABLE(void);
void  INTX_ENABLE(void);
__interrupt void serial_Rx_isr(void);
__interrupt void serial_Tx_isr(void);
__interrupt void cpu_timer0_isr(void);
void vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable );
BOOL xMBPortSerialInit(ULONG ulBaudRate);
BOOL xMBPortSerialGetByte( UCHAR * pucByte );
BOOL xMBPortSerialPutByte( UCHAR ucByte );
BOOL xMBPortTimersInit( USHORT usTim1Timerout50us );
void vMBPortTimersEnable(void);
void vMBPortTimersDisable(void);
extern __IO uint32_t uwTick;

#endif
