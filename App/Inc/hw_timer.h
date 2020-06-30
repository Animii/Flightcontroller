/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "hw.h"

    void HW_TIMER_Init(void);

    void HW_TIMER_IoInit(void);

    //void HW_TIMER_PWM_Init(void);

    void HW_TIMER_PWM_ChangeDuty(uint32_t duty);

    void HW_TIMER_EnableClk(TIM_HandleTypeDef *htim_base);
#ifdef __cplusplus
}
#endif

#endif //__HW_TIMER_H__
