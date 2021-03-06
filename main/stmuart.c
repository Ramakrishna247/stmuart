#include "stm32f401xe.h"
#include "stm32f4xx.h"


int main( )
{
RCC->APB2ENR |=RCC_APB2ENR_USART1EN;
	
RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;

GPIOA->AFR[1]=0X00000770;  //ALTERNATE FUNCTION HIGH REGISTER IS SELECTED FOR UART1 , AF[0]-ARFL,AF[1]-ARFH
GPIOA->MODER |=GPIO_MODER_MODE9_1;
GPIOA->MODER &=~(GPIO_MODER_MODE9_0);   //PA9 is Tx 
GPIOA->MODER |=GPIO_MODER_MODE10_1;
GPIOA->MODER &=~(GPIO_MODER_MODE10_0);	 //PA10 is Rx
GPIOA->OTYPER &=~(GPIO_OTYPER_OT9);
GPIOA->PUPDR &=~(GPIO_PUPDR_PUPD9_0);	
GPIOA->PUPDR &=~(GPIO_PUPDR_PUPD9_1);		
	
GPIOA->OTYPER |=GPIO_OTYPER_OT10;
GPIOA->PUPDR &=~(GPIO_PUPDR_PUPD10_0);	
GPIOA->PUPDR &=~(GPIO_PUPDR_PUPD10_1);			
	
USART1->BRR =0X683; //0X683 IS THE VALUE TO SELECT BAUDRATE 9600
	
USART1->CR1 |=USART_CR1_UE; //USART PERIPHERAL ENABLE
USART1->CR1 |=USART_CR1_TE;	//USART1 TRANSMIT ENABLE
USART1->CR1 |=USART_CR1_RE;	//USART1 RECEIVE ENABLE

int i=0;

unsigned char a[10]="kittu";

for(i=0;i<5;i++)
{
	
USART1->DR =a[i];
while (!(USART1->SR & USART_SR_TXE));

}


}
