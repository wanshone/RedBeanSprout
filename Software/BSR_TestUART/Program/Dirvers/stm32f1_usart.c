/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_usart.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendByte
**功能 : 發送 1Byte 資料
**輸入 : USARTx, *SendData
**輸出 : None
**使用 : UART_SendByte(USART1, 'A');
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendByte( USART_TypeDef* USARTx, int8_t* SendData )
{
  USART_SendData(USARTx, *SendData);
  while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByte
**功能 : 接收 1Byte 資料
**輸入 : USARTx, *RecvByte
**輸出 : None
**使用 : UART_RecvByte(USART1, RecvData);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvByte( USART_TypeDef* USARTx, int8_t* RecvData )
{
  while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
  *RecvData = USART_ReceiveData(USARTx);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByteWTO
**功能 : 接收 1Byte 資料, 並加入 Timeout 功能
**輸入 : USARTx, *RecvByte, TimeoutMs
**輸出 : State
**使用 : UART_RecvByteWTO(USART1, RecvData, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t UART_RecvByteWTO( USART_TypeDef* USARTx, int8_t* RecvData, int32_t TimeoutMs )
{
  while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET) {
    if(TimeoutMs >= 0) {
      TimeoutMs--;
      Delay_1ms(1);
    }
    else {
      return ERROR; // timeout
    }
  }
  *RecvData = USART_ReceiveData(USARTx);

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendData
**功能 : 發送資料
**輸入 : USARTx, *SendData, DataLen
**輸出 : None
**使用 : UART_SendByte(USART1, SendData, DataLen);
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendData( USART_TypeDef* USARTx, int8_t* SendData, uint16_t DataLen )
{
  do {
    UART_SendByte(USARTx, SendData);
    SendData++;
  } while(--DataLen);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvData
**功能 : 接收資料
**輸入 : USARTx, *RecvData, DataLen
**輸出 : None
**使用 : UART_RecvData(USART1, RecvData, DataLen);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvData( USART_TypeDef* USARTx, int8_t* RecvData, uint16_t DataLen )
{
  do {
    UART_RecvByte(USARTx, RecvData++);
  } while(--DataLen);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvDataWTO
**功能 : 接收資料, 並加入 Timeout 功能
**輸入 : USARTx, *RecvByte, DataLen, TimeoutMs
**輸出 : State
**使用 : UART_RecvDataWTO(USART1, RecvData, DataLen, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t UART_RecvDataWTO( USART_TypeDef* USARTx, int8_t* RecvData, uint16_t DataLen, int32_t TimeoutMs )
{
  int8_t State = ERROR;

  do {
    State = UART_RecvByteWTO(USARTx, RecvData++, TimeoutMs);
    if(State == ERROR)
      return ERROR;
  } while(--DataLen);

  return State;
}
/*====================================================================================================*/
/*====================================================================================================*/
