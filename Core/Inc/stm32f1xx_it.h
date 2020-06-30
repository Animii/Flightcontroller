/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_IT_H__
#define __STM32L1xx_IT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
//void EXTI15_10_IRQHandler(void);

void TIM21_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1xx_IT_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
