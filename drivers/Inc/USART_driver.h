/*
 * USART_driver.h
 *
 *  Created on: 02-Jul-2026
 *      Author: Punya
 */

#ifndef INC_USART_DRIVER_H_
#define INC_USART_DRIVER_H_
/*
 * Configuration structure for USARTx peripheral
 */
typedef struct
{
	uint8_t USART_Mode;
	uint32_t USART_Baud;
	uint8_t USART_NoOfStopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
}USART_Config_t;

/*
 * Handle structure for USARTx peripheral
 */
typedef struct
{
    USART_RegDef_t *pUSARTx;
    USART_Config_t USART_Config;

    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;

    uint32_t TxLen;
    uint32_t RxLen;

    uint8_t TxBusyState;
    uint8_t RxBusyState;

}USART_Handle_t;

/*
 * USART Application States
 */
#define USART_READY         0
#define USART_BUSY_IN_RX    1
#define USART_BUSY_IN_TX    2

#define USART_MODE_ONLY_TX  0
#define USART_MODE_ONLY_RX  1
#define USART_MODE_TXRX     2

/*
 * @USART_Baud
 * Possible options for USART_Baud
 */
#define USART_STD_BAUD_1200      1200
#define USART_STD_BAUD_2400      2400
#define USART_STD_BAUD_9600      9600
#define USART_STD_BAUD_19200     19200
#define USART_STD_BAUD_38400     38400
#define USART_STD_BAUD_57600     57600
#define USART_STD_BAUD_115200    115200
#define USART_STD_BAUD_230400    230400
#define USART_STD_BAUD_460800    460800
#define USART_SR_PE       0   // Parity Error
#define USART_SR_FE       1   // Framing Error
#define USART_SR_NE       2   // Noise Flag
#define USART_SR_ORE      3   // Overrun Error
#define USART_SR_IDLE     4   // IDLE line detected
#define USART_SR_RXNE     5   // Read Data Register Not Empty
#define USART_SR_TC       6   // Transmission Complete
#define USART_SR_TXE      7   // Transmit Data Register Empty
#define USART_SR_LBD      8   // LIN Break Detection
#define USART_SR_CTS      9   // CTS flag
/*
 * Define for Baud Rate Generation under BRR
 */
#define USART_BRR_DIV_FRACTION   0   // bits 0-3
#define USART_BRR_DIV_MANTISSA   4   // bits 4-15

/*
 * Define for CR1
 */
#define USART_CR1_SBK       0    // Send Break
#define USART_CR1_RWU       1    // Receiver wakeup
#define USART_CR1_RE        2    // Receiver Enable
#define USART_CR1_TE         3    // Transmitter Enable
#define USART_CR1_IDLEIE    4    // IDLE Interrupt Enable
#define USART_CR1_RXNEIE    5    // RXNE Interrupt Enable
#define USART_CR1_TCIE      6    // Transmission Complete Interrupt Enable
#define USART_CR1_TXEIE     7    // TXE Interrupt Enable
#define USART_CR1_PEIE      8    // PE Interrupt Enable
#define USART_CR1_PS        9    // Parity Selection
#define USART_CR1_PCE       10   // Parity Control Enable
#define USART_CR1_WAKE      11   // Wakeup method
#define USART_CR1_M         12   // Word length
#define USART_CR1_UE        13   // USART Enable
// bit 14 reserved
#define USART_CR1_OVER8     15   // Oversampling mode
/*
 * For CR2
 */
#define USART_CR2_ADD        0    // bits 0-3: Address of USART node
// bit 4 reserved
#define USART_CR2_LBDL        5    // LIN break detection length
#define USART_CR2_LBDIE       6    // LIN break detection interrupt enable
// bit 7 reserved
#define USART_CR2_LBCL        8    // Last bit clock pulse
#define USART_CR2_CPHA         9    // Clock phase
#define USART_CR2_CPOL         10   // Clock polarity
#define USART_CR2_CLKEN        11   // Clock enable
#define USART_CR2_STOP         12   // bits 12-13: STOP bits
#define USART_CR2_LINEN        14   // LIN mode enable
// bit 15 reserved

/*
 * For CR2
 */
#define USART_CR3_EIE       0    // Error Interrupt Enable
#define USART_CR3_IREN      1    // IrDA mode Enable
#define USART_CR3_IRLP      2    // IrDA Low-Power
#define USART_CR3_HDSEL     3    // Half-Duplex Selection
#define USART_CR3_NACK      4    // Smartcard NACK Enable
#define USART_CR3_SCEN      5    // Smartcard Mode Enable
#define USART_CR3_DMAR      6    // DMA Enable Receiver
#define USART_CR3_DMAT      7    // DMA Enable Transmitter
#define USART_CR3_RTSE      8    // RTS Enable
#define USART_CR3_CTSE      9    // CTS Enable
#define USART_CR3_CTSIE     10   // CTS Interrupt Enable
// bits 11-31 reserved

/*
 * For GTPR
*/
#define USART_GTPR_PSC       0    // bits 0-7: Prescaler value
#define USART_GTPR_GT        8    // bits 8-15: Guard time value


/*
 * @USART_ParityControl
 */
#define USART_PARITY_DISABLE     0
#define USART_PARITY_EN_EVEN     1
#define USART_PARITY_EN_ODD      2

/*
 * @USART_WordLength
 */
#define USART_WORDLEN_8BITS      0
#define USART_WORDLEN_9BITS      1

/*
 * @USART_NoOfStopBits
 */
#define USART_STOPBITS_1         0
#define USART_STOPBITS_0_5       1
#define USART_STOPBITS_2         2
#define USART_STOPBITS_1_5       3

/*
 * @USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE       0
#define USART_HW_FLOW_CTRL_CTS        1
#define USART_HW_FLOW_CTRL_RTS        2
#define USART_HW_FLOW_CTRL_CTS_RTS    3

/*
 * Flag status (same pattern as SPI/I2C)
 */
#define FLAG_RESET    0
#define FLAG_SET      1

/*
/ * PROTOTYPES to the APIs Deployment section
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);

void USART_IRQHandling(USART_Handle_t *pUSARTHandle);

/*****************************************************************
 * 				APIs Deployment
 *****************************************************************/
/* implemented APIs by taking reference from I2C or SPI driver */

void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName);
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
#endif /* INC_USART_DRIVER_H_ */
