/*
 * stm32f411xx_usart_driver.c
 *
 *  Created on: 03-Jul-2026
 *      Author: Punya
 *
 */

#include "stm32f411xx.h"
#include "USART_driver.h"

extern uint32_t RCC_GetPCLK1Value(void);

static uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t pclk2, SystemClk;
	uint8_t clksrc, temp, ahbp, apb2p;

	clksrc = ((RCC->CFGR >> 2) & 0x3);

	if(clksrc == 0)
	{
		SystemClk = 16000000;   /* HSI = 16 MHz (Black Pill default) */
	}
	else if(clksrc == 1)
	{
		SystemClk = 8000000;    /* HSE = 8 MHz */
	}
	else
	{
		SystemClk = 16000000;

	}

	/* AHB prescaler — CFGR bits [7:4] = HPRE */
	temp = ((RCC->CFGR >> 4) & 0xF);

	if(temp < 8)
	{
		ahbp = 1;
	}
	else
	{
		uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};
		ahbp = AHB_PreScaler[temp - 8];
	}

	/* APB2 prescaler — CFGR bits [15:13] = PPRE2 */
	temp = ((RCC->CFGR >> 13) & 0x7);

	if(temp < 4)
	{
		apb2p = 1;
	}
	else
	{
		uint8_t APB_PreScaler[4] = {2, 4, 8, 16};
		apb2p = APB_PreScaler[temp - 4];
	}

	pclk2 = (SystemClk / ahbp) / apb2p;

	return pclk2;
}

/*********************************************************************
 * @fn      		  - USART_PeriClockControl
 *
 * @brief             - Enables or disables peripheral clock for the given USART
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pUSARTx == USART1)
		{
			USART1_PCLK_EN();
		}
		else if(pUSARTx == USART2)
		{
			USART2_PCLK_EN();
		}
		else if(pUSARTx == USART6)
		{
			USART6_PCLK_EN();
		}
	}
	else
	{
		if(pUSARTx == USART1)
		{
			USART1_PCLK_DI();
		}
		else if(pUSARTx == USART2)
		{
			USART2_PCLK_DI();
		}
		else if(pUSARTx == USART6)
		{
			USART6_PCLK_DI();
		}
	}
}

/*********************************************************************
 * @fn      		  - USART_Init
 *
 * @brief             - Configures CR1/CR2/CR3/BRR based on USART_Config_t
 *                       and enables the peripheral
 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{
	uint32_t tempreg = 0;

	/* 1. Enable the peripheral clock */
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	/* 2. Configure CR1 — mode (TE/RE bits) */
	if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		tempreg |= (1 << USART_CR1_RE);
	}
	else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		tempreg |= (1 << USART_CR1_TE);
	}
	else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		tempreg |= (1 << USART_CR1_TE) | (1 << USART_CR1_RE);
	}

	/* 3. Word length */
	tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M;

	/* 4. Parity control */
	if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
	{
		tempreg |= (1 << USART_CR1_PCE);
		/* PS = 0 for even, no need to explicitly clear, tempreg starts at 0 */
	}
	else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
	{
		tempreg |= (1 << USART_CR1_PCE);
		tempreg |= (1 << USART_CR1_PS);
	}

	pUSARTHandle->pUSARTx->CR1 = tempreg;

	/* 5. CR2 — stop bits */
	tempreg = 0;
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;
	pUSARTHandle->pUSARTx->CR2 = tempreg;

	/* 6. CR3 — hardware flow control */
	tempreg = 0;
	if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		tempreg |= (1 << USART_CR3_CTSE);
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		tempreg |= (1 << USART_CR3_RTSE);
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		tempreg |= (1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE);
	}
	pUSARTHandle->pUSARTx->CR3 = tempreg;

	/* 7. Baud rate */
	USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);

	/* 8. Finally enable the peripheral */
	USART_PeripheralControl(pUSARTHandle->pUSARTx, ENABLE);
}

/*********************************************************************
 * @fn      		  - USART_DeInit
 *
 * @brief             - Resets USARTx registers via RCC reset register
 */
void USART_DeInit(USART_RegDef_t *pUSARTx)
{
	if(pUSARTx == USART1)
	{
		USART1_REG_RESET();
	}
	else if(pUSARTx == USART2)
	{
		USART2_REG_RESET();
	}
	else if(pUSARTx == USART6)
	{
		USART6_REG_RESET();
	}
}

/*********************************************************************
 * @fn      		  - USART_PeripheralControl
 *
 * @brief             - Enables/disables the USART peripheral (UE bit in CR1)
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}
	else
	{
		pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
	}
}

/*********************************************************************
 * @fn      		  - USART_GetFlagStatus / USART_ClearFlag
 *********************************************************************/
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
	if(pUSARTx->SR & (1 << StatusFlagName))
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
{
	pUSARTx->SR &= ~(1 << StatusFlagName);
}

/*********************************************************************
 * @fn      		  - USART_SendData (blocking / polling)
 *
 * @brief             - Sends Len bytes out over pUSARTx, byte by byte,
 *                       waiting on TXE each time and TC after the last byte
 *
 * @note              - IT-driven version needs TxBusyState/TxLen/pTxBuffer
 *                       added to USART_Handle_t — not present in current header
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;

	for(uint32_t i = 0; i < Len; i++)
	{
		/* wait until TXE is set */
		while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_TXE));

		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			/* 9-bit: load 2 bytes from buffer, mask to 9 bits */
			pdata = (uint16_t*)pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				/* parity bit replaces the 9th bit — only 8 data bits from user buffer */
				pTxBuffer++;
			}
		}
		else
		{
			/* 8-bit */
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			pTxBuffer++;
		}
	}

	/* wait until TC is set (last frame fully shifted out) */
	while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_TC));
}

/*********************************************************************
 * @fn      		  - USART_ReceiveData (blocking / polling)
 *
 * @note              - Same limitation as SendData: no IT version without
 *                       expanding USART_Handle_t (RxBusyState/RxLen/pRxBuffer)
 *********************************************************************/
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	for(uint32_t i = 0; i < Len; i++)
	{
		/* wait until RXNE is set */
		while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_RXNE));

		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				/* no parity: all 9 bits are user data */
				*((uint16_t*)pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF);
				pRxBuffer++;
				pRxBuffer++;
			}
			else
			{
				/* parity enabled: 8 bits are user data */
				*pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
				pRxBuffer++;
			}
		}
		else
		{
			/* 8-bit */
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
			}
			else
			{
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F);
			}
			pRxBuffer++;
		}
	}
}
/*********************************************************************
 * @fn      		  - USART_SendDataIT
 *
 * @brief             - Sends data using interrupt mode
 *
 * @param[in]         - pUSARTHandle : USART handle
 * @param[in]         - pTxBuffer    : Pointer to TX buffer
 * @param[in]         - Len          : Length of data
 *
 * @return            - Current TX state
 *
 * @Note              -
 */
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t txstate = pUSARTHandle->TxBusyState;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TxLen = Len;
		pUSARTHandle->pTxBuffer = pTxBuffer;
		pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

		// Enable interrupt for TXE
		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE);

		// Enable interrupt for TC
		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE);
	}

	return txstate;
}


/*********************************************************************
 * @fn      		  - USART_ReceiveDataIT
 *
 * @brief             - Receives data using interrupt mode
 *
 * @param[in]         - pUSARTHandle : USART handle
 * @param[in]         - pRxBuffer    : Pointer to RX buffer
 * @param[in]         - Len          : Length of data
 *
 * @return            - Current RX state
 *
 * @Note              -
 */
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t rxstate = pUSARTHandle->RxBusyState;

	if(rxstate != USART_BUSY_IN_RX)
	{
		pUSARTHandle->RxLen = Len;
		pUSARTHandle->pRxBuffer = pRxBuffer;
		pUSARTHandle->RxBusyState = USART_BUSY_IN_RX;

		// Enable interrupt for RXNE
		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_RXNEIE);
	}

	return rxstate;
}
/*********************************************************************
 * @fn      		  - USART_SetBaudRate
 *
 * @brief             - Standard USARTDIV mantissa/fraction calculation
 *                       per RM0383, split across BRR bits 0-3 (fraction)
 *                       and bits 4-15 (mantissa)
 *********************************************************************/
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
	uint32_t PCLKx;
	uint32_t usartdiv;
	uint32_t M_part, F_part;
	uint32_t tempreg = 0;

	if(pUSARTx == USART1 || pUSARTx == USART6)
	{
		PCLKx = RCC_GetPCLK2Value();
	}
	else
	{
		PCLKx = RCC_GetPCLK1Value();
	}

	if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
	{
		/* OVER8 = 1 */
		usartdiv = ((25 * PCLKx) / (2 * BaudRate));
	}
	else
	{
		/* OVER8 = 0 (default) */
		usartdiv = ((25 * PCLKx) / (4 * BaudRate));
	}

	M_part = usartdiv / 100;
	tempreg |= M_part << USART_BRR_DIV_MANTISSA;

	F_part = usartdiv - (M_part * 100);

	if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
	{
		F_part = (((F_part * 8) + 50) / 100) & (uint8_t)0x07;
	}
	else
	{
		F_part = (((F_part * 16) + 50) / 100) & (uint8_t)0x0F;
	}

	tempreg |= F_part;

	pUSARTx->BRR = tempreg;
}

/*********************************************************************
 * @fn      		  - USART_IRQInterruptConfig / USART_IRQPriorityConfig
 *
 * @brief             - Same NVIC ISER/ICER/IPR pattern as your SPI/I2C driver
 *********************************************************************/
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}

void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

	*(NVIC_PR_BASEADDR + iprx) |= (IRQPriority << shift_amount);
}

/*********************************************************************
 * @fn      		  - USART_IRQHandling
 *
 * @brief             - SKELETON ONLY. Without TxBusyState/RxBusyState/
 *                       pTxBuffer/pRxBuffer/TxLen/RxLen in USART_Handle_t,
 *                       there's nothing for this ISR to actually drive —
 *                       it can clear error flags but can't manage a
 *                       non-blocking transfer. Expand the handle struct
 *                       first (same fields I2C_Handle_t has) if you want
 *                       real IT-based Send/Receive.
 *********************************************************************/
void USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{
	/* placeholder — flag checks for TXE, RXNE, TC, ORE etc. go here
	   once the handle struct supports non-blocking state tracking */
}
