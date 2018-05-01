/**
 * @file dma.c
 * @brief Implementation of the dma.h file
 *
 * This source file holds implementations for dma memory abstraction functions from the dma.h file
 *
 * @author Girish Narayanswamy & Karros Huang
 * @date April 1, 2018
 * @version 1.0
 *
 */

#include "dma.h"
#include "MKL25Z4.h"
#include "timer.h"

uint8_t dmaTransfer;

uint8_t dmaInit(uint8_t * src, uint8_t * dst, size_t length, uint8_t size, uint8_t srcInc)
{
	/* error and exception checking */
	if(src == NULL || dst == NULL) return -1; /* checking for bad pointer access */
	if(length > DMAMAXBYTENUM) return -1; /* data transfer too large */

	/* clock gating to enable DMA and DMA mux modules */
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK; /* DMA mux */
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK; /* DMA */

	/* enable dma interrupts */
	NVIC_EnableIRQ(DMA0_IRQn); /* enable DMA0 interrupts */

	/* DMA mux reg cleared */
	DMAMUX0->CHCFG[0] = 0x00; /* clear all info in DMA mux reg */

	/* Byte count reg settings */
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE(0x01); /* clear pending transfer flag, clear reg */
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_BCR(length); /* set byte count to num of bytes to transfer, clears all status bits */

	/* Source and destination reg settings */
	DMA0->DMA[0].SAR = (uint32_t) src; /* source address */
	DMA0->DMA[0].DAR = (uint32_t) dst; /* destination address */

	/* DMA control reg settings */
	DMA0->DMA[0].DCR = 0x0000;

	DMA0->DMA[0].DCR |= DMA_DCR_EINT(0x01); /* int enabled on transfer completion */
	DMA0->DMA[0].DCR |= DMA_DCR_ERQ(0x00); /* peripheral requests ignored */
	DMA0->DMA[0].DCR |= DMA_DCR_CS(0x00); /* continuous read/writes until BCR == 0 */
	DMA0->DMA[0].DCR |= DMA_DCR_SINC(srcInc); /* src increments after each transfer */
	DMA0->DMA[0].DCR |= DMA_DCR_SSIZE(size); /* src size value */
	DMA0->DMA[0].DCR |= DMA_DCR_DINC(0x01); /* dst increments after each transfer */
	DMA0->DMA[0].DCR |= DMA_DCR_DSIZE(size); /* dst size value */

	dmaTransfer = 0x00; /* dma available/ready */

	return 0;
}

uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length, uint8_t size)
{
	/* error and exception checking */
	if(src == NULL || dst == NULL) return NULL; /* checking for bad pointer access */
	if(length > DMAMAXBYTENUM) return NULL; /* data transfer too large */

	/* dma transfer scenarios */
	if(src > dst) /* no overlap condition */
	{
		dmaInit(src, dst, length, size, INCREMENT); /* init dma */
		dmaTransfer = 0x01; /* dma busy */
		DMA0->DMA[0].DCR |= DMA_DCR_START(0x01); /* start data transfer */
	}

	else if(dst > src) /* overlap condition is most likely significantly slower than std mem move */
	{
		if(src + length > dst) /* overlap case */ /* still need to finish this Girish */
		{
			size_t i;
			for(i = 0; i < length; i++)
			{
				dmaInit(src + length - i - 1, dst + length - i - 1, 0x01, size, INCREMENT);
				dmaTransfer = 0x01; /* dma busy */
				DMA0->DMA[0].DCR |= DMA_DCR_START(0x01); /* start data transfer */
				while(dmaTransfer); /* wait for transfer to finish */
			}
		}

		else /* non over lap case */
		{
			dmaInit(src, dst, length, size, INCREMENT); /* init dma */
			dmaTransfer = 0x01; /* dma busy */
			DMA0->DMA[0].DCR |= DMA_DCR_START(0x01); /* start data transfer */
		}
	}

	return dst;
}

uint8_t * memset_dma(uint8_t * mem, size_t length, uint8_t value)
{
	/* error and exception checking */
	if(mem == NULL) return NULL; /* checking for bad pointer access */
	if(length > DMAMAXBYTENUM) return NULL; /* data transfer too large */

	/* dma transfer init and start */
	dmaInit(&value, mem, length, DMASIZE8, NONINCREMENT); /* dma init */
	dmaTransfer = 0x01; /* dma busy */
	DMA0->DMA[0].DCR |= DMA_DCR_START(0x01); /* start data transfer */

	return mem;
}

void DMA0_IRQHandler(void)
{
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE(0x01); /* clear pending transfer flag, clear reg */
	dmaTransfer = 0x00; /* dma available/ready */
	return;
}
