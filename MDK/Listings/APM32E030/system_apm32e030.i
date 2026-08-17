# 1 "..\\Src\\system_apm32e030.c"























 

 
# 1 "..\\Src\\apm32e030.h"

























 

 









 






 











 



 




 


 


 







 



 

 
# 95 "..\\Src\\apm32e030.h"

 



 

 

 

 

 

 




 
typedef enum
{
     
    NonMaskableInt_IRQn         = -14,     
    HardFault_IRQn              = -13,     
    SVC_IRQn                    = -5,      
    PendSV_IRQn                 = -2,      
    SysTick_IRQn                = -1,      

     
    WWDT_IRQn                   =  0,      
    RTC_IRQn                    =  2,      
    FLASH_IRQn                  =  3,      
    RCM_IRQn                    =  4,      
    EINT0_1_IRQn                =  5,      
    EINT2_3_IRQn                =  6,      
    EINT4_15_IRQn               =  7,      
    DMA1_CH1_IRQn               =  9,      
    DMA1_CH2_3_IRQn             = 10,      
    DMA1_CH4_5_IRQn             = 11,      
    ADC1_IRQn                   = 12,      
    TMR1_BRK_UP_TRG_COM_IRQn    = 13,      
    TMR1_CC_IRQn                = 14,      
    TMR3_IRQn                   = 16,      
    TMR6_IRQn                   = 17,      
    TMR14_IRQn                  = 19,      
    TMR15_IRQn                  = 20,      
    TMR16_IRQn                  = 21,      
    TMR17_IRQn                  = 22,      
    I2C1_IRQn                   = 23,      
    I2C2_IRQn                   = 24,      
    SPI1_IRQn                   = 25,      
    SPI2_IRQn                   = 26,      
    USART1_IRQn                 = 27,      
    USART2_IRQn                 = 28,      
} IRQn_Type;

 

 

# 1 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"
 




 
















 










# 1 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
# 27 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











# 46 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
# 216 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



# 241 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











# 305 "C:\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
# 35 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"

















 




 



 

# 1 "..\\Driver\\CMSIS\\Include\\cmsis_version.h"
 




 
















 










 
# 64 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"
 
 









 







# 114 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"

# 1 "..\\Driver\\CMSIS\\Include\\cmsis_compiler.h"
 




 
















 




# 29 "..\\Driver\\CMSIS\\Include\\cmsis_compiler.h"



 
# 1 "..\\Driver\\CMSIS\\Include\\cmsis_armcc.h"
 




 
















 









 













   
   
   

 




 
# 111 "..\\Driver\\CMSIS\\Include\\cmsis_armcc.h"

 





















 



 




 






 







 






 








 






 






 








 








 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int16_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}









 









 








 




__attribute__((always_inline)) static __inline uint32_t __RBIT(uint32_t value)
{
  uint32_t result;
  uint32_t s = (4U   * 8U) - 1U;  

  result = value;                       
  for (value >>= 1U; value != 0U; value >>= 1U)
  {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;                         
  return result;
}








 



# 473 "..\\Driver\\CMSIS\\Include\\cmsis_armcc.h"







 
__attribute__((always_inline)) static __inline int32_t __SSAT(int32_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}







 
__attribute__((always_inline)) static __inline uint32_t __USAT(int32_t val, uint32_t sat)
{
  if (sat <= 31U)
  {
    const uint32_t max = ((1U << sat) - 1U);
    if (val > (int32_t)max)
    {
      return max;
    }
    else if (val < 0)
    {
      return 0U;
    }
  }
  return (uint32_t)val;
}




   


 



 





 
 






 
 





 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}






 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
  __isb(0xF);
}






 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}






 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}






 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}






 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}






 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}






 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}






 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}






 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}






 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}


# 764 "..\\Driver\\CMSIS\\Include\\cmsis_armcc.h"






 
static __inline uint32_t __get_FPSCR(void)
{





   return(0U);

}






 
static __inline void __set_FPSCR(uint32_t fpscr)
{





  (void)fpscr;

}


 


 



 

# 885 "..\\Driver\\CMSIS\\Include\\cmsis_armcc.h"
 


# 35 "..\\Driver\\CMSIS\\Include\\cmsis_compiler.h"




 
# 280 "..\\Driver\\CMSIS\\Include\\cmsis_compiler.h"




# 116 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"

















 
# 160 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"

 






 
# 176 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"

 




 











 



 






 



 
typedef union
{
  struct
  {
    uint32_t _reserved0:28;               
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;

 















 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;

 






 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:15;               
    uint32_t T:1;                         
    uint32_t _reserved1:3;                
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;

 





















 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t _reserved1:30;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 







 



 
typedef struct
{
  volatile uint32_t ISER[1U];                
        uint32_t RESERVED0[31U];
  volatile uint32_t ICER[1U];                
        uint32_t RESERVED1[31U];
  volatile uint32_t ISPR[1U];                
        uint32_t RESERVED2[31U];
  volatile uint32_t ICPR[1U];                
        uint32_t RESERVED3[31U];
        uint32_t RESERVED4[64U];
  volatile uint32_t IP[8U];                  
}  NVIC_Type;

 







 



 
typedef struct
{
  volatile const  uint32_t CPUID;                   
  volatile uint32_t ICSR;                    

  volatile uint32_t VTOR;                    



  volatile uint32_t AIRCR;                   
  volatile uint32_t SCR;                     
  volatile uint32_t CCR;                     
        uint32_t RESERVED1;
  volatile uint32_t SHP[2U];                 
  volatile uint32_t SHCSR;                   
} SCB_Type;

 















 




























 




 















 









 






 



 







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t LOAD;                    
  volatile uint32_t VAL;                     
  volatile const  uint32_t CALIB;                   
} SysTick_Type;

 












 



 



 









 

# 602 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"








 
 







 






 







 


 







 

 














 









 


 



 





 

# 701 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"
 





# 716 "..\\Driver\\CMSIS\\Include\\core_cm0plus.h"




 





 
 












 
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __memory_changed();
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __memory_changed();
  }
}









 
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __dsb(0xF);
    __isb(0xF);
  }
}









 
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}







 
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}










 
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )]  = ((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )]  & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] = ((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
}










 
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[ ( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2)));
  }
  else
  {
    return((uint32_t)(((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2)));
  }
}












 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2)) ? (uint32_t)(2) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(2)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}












 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2)) ? (uint32_t)(2) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(2)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}











 
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{

  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  vectors[(int32_t)IRQn + 16] = vector;




   
}









 
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{

  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  return vectors[(int32_t)IRQn + 16];




}





 
__declspec(noreturn) static __inline void __NVIC_SystemReset(void)
{
  __dsb(0xF);                                                          
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FAUL << 16U) |
                 (1UL << 2U));
  __dsb(0xF);                                                           

  for(;;)                                                            
  {
    __nop();
  }
}

 

 







 





 








 
static __inline uint32_t SCB_GetFPUType(void)
{
    return 0U;            
}


 



 





 













 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);                                                    
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (uint32_t)(ticks - 1UL);                          
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 2) - 1UL);  
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0UL;                                              
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2U) |
                   (1UL << 1U)   |
                   (1UL );                          
  return (0UL);                                                      
}



 










# 158 "..\\Src\\apm32e030.h"
# 1 "..\\Src\\system_apm32e030.h"

























 

 









 



 



 

 



 

 



 

 



 

 
extern uint32_t SystemCoreClock;

 



 

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);







 
 
 
# 159 "..\\Src\\apm32e030.h"
# 160 "..\\Src\\apm32e030.h"



 

typedef enum {FALSE, TRUE} BOOL;

enum {BIT_RESET, BIT_SET};

enum {RESET = 0, SET = !RESET};

enum {DISABLE = 0, ENABLE = !DISABLE};

enum {ERROR = 0, SUCCESS = !ERROR};

# 184 "..\\Src\\apm32e030.h"






#pragma anon_unions


 



 




 

typedef struct
{
     
    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile uint32_t ADCRDYFLG  : 1;
            volatile uint32_t EOSMPFLG   : 1;
            volatile uint32_t EOCFLG     : 1;
            volatile uint32_t EOSEQFLG   : 1;
            volatile uint32_t OVREFLG    : 1;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t AWDFLG     : 1;
            volatile const  uint32_t RESERVED2  : 24;
        } STS_B;
    } ;

     
    union
    {
        volatile uint32_t INT;

        struct
        {
            volatile uint32_t ADCRDYIEN  : 1;
            volatile uint32_t EOSMPIEN   : 1;
            volatile uint32_t EOCIEN     : 1;
            volatile uint32_t EOSEQIEN   : 1;
            volatile uint32_t OVRIEN     : 1;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t AWDIEN     : 1;
            volatile const  uint32_t RESERVED2  : 24;
        } INT_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t ADCEN      : 1;
            volatile uint32_t ADCD       : 1;
            volatile uint32_t STARTCEN   : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t STOPCEN    : 1;
            volatile const  uint32_t RESERVED2  : 26;
            volatile uint32_t CAL        : 1;
        } CTRL_B;
    } ;

     
    union
    {
        volatile uint32_t CFG1;

        struct
        {
            volatile uint32_t DMAEN      : 1;
            volatile uint32_t DMACFG     : 1;
            volatile uint32_t SCANSEQDIR : 1;
            volatile uint32_t DATARESCFG : 2;
            volatile uint32_t DALIGCFG   : 1;
            volatile uint32_t EXTTRGSEL  : 3;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t EXTPOLSEL  : 2;
            volatile uint32_t OVRMAG     : 1;
            volatile uint32_t CMODESEL   : 1;
            volatile uint32_t WAITCEN    : 1;
            volatile uint32_t AOEN       : 1;
            volatile uint32_t DISCEN     : 1;
            volatile const  uint32_t RESERVED2  : 5;
            volatile uint32_t AWDCHEN    : 1;
            volatile uint32_t AWDEN      : 1;
            volatile const  uint32_t RESERVED3  : 2;
            volatile uint32_t AWDCHSEL   : 5;
            volatile const  uint32_t RESERVED4  : 1;
        } CFG1_B;
    } ;

     
    union
    {
        volatile uint32_t CFG2;

        struct
        {
            volatile const  uint32_t RESERVED1  : 30;
            volatile uint32_t CLKCFG     : 2;
        } CFG2_B;
    } ;

     
    union
    {
        volatile uint32_t SMPTIM;

        struct
        {
            volatile uint32_t SMPCYCSEL  : 3;
            volatile const  uint32_t RESERVED1  : 29;
        } SMPTIM_B;
    } ;
    volatile const  uint32_t  RESERVED[2];

     
    union
    {
        volatile uint32_t AWDT;

        struct
        {
            volatile uint32_t AWDLT      : 12;
            volatile const  uint32_t RESERVED1  : 4;
            volatile uint32_t AWDHT      : 12;
            volatile const  uint32_t RESERVED2  : 4;
        } AWDT_B;
    } ;
    volatile const  uint32_t  RESERVED1;

     
    union
    {
        volatile uint32_t CHSEL;

        struct
        {
            volatile uint32_t CH0SEL     : 1;
            volatile uint32_t CH1SEL     : 1;
            volatile uint32_t CH2SEL     : 1;
            volatile uint32_t CH3SEL     : 1;
            volatile uint32_t CH4SEL     : 1;
            volatile uint32_t CH5SEL     : 1;
            volatile uint32_t CH6SEL     : 1;
            volatile uint32_t CH7SEL     : 1;
            volatile uint32_t CH8SEL     : 1;
            volatile uint32_t CH9SEL     : 1;
            volatile uint32_t CH10SEL    : 1;
            volatile uint32_t CH11SEL    : 1;
            volatile uint32_t CH12SEL    : 1;
            volatile uint32_t CH13SEL    : 1;
            volatile uint32_t CH14SEL    : 1;
            volatile uint32_t CH15SEL    : 1;
            volatile uint32_t CH16SEL    : 1;
            volatile uint32_t CH17SEL    : 1;
            volatile const  uint32_t RESERVED1  : 14;
        } CHSEL_B;
    } ;
    volatile const  uint32_t  RESERVED2[5];

     
    union
    {
        volatile const  uint32_t DATA;

        struct
        {
            volatile const  uint32_t DATA       : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } DATA_B;
    } ;
    volatile const  uint32_t  RESERVED3[177];

     
    union
    {
        volatile uint32_t CCFG;

        struct
        {
            volatile const  uint32_t RESERVED1  : 22;
            volatile uint32_t VREFEN     : 1;
            volatile uint32_t TSEN       : 1;
            volatile const  uint32_t RESERVED2  : 8;
        } CCFG_B;
    } ;
} ADC_T;



 

typedef struct
{
     
    union
    {
        volatile uint32_t DATA;

        struct
        {
            volatile uint32_t DATA       : 32;
        } DATA_B;
    } ;

     
    union
    {
        volatile uint32_t INDATA;

        struct
        {
            volatile uint32_t INDATA     : 8;
            volatile const  uint32_t RESERVED1  : 24;
        } INDATA_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t RST        : 1;
            volatile const  uint32_t RESERVED1  : 4;
            volatile uint32_t REVI       : 2;
            volatile uint32_t REVO       : 1;
            volatile const  uint32_t RESERVED2  : 24;
        } CTRL_B;
    } ;
    volatile const  uint32_t  RESERVED;

     
    union
    {
        volatile uint32_t INITVAL;

        struct
        {
            volatile uint32_t VALUE      : 32;
        } INITVAL_B;
    } ;
} CRC_T;



 

typedef struct
{

     
    union
    {
        volatile const  uint32_t IDCODE;

        struct
        {
            volatile const  uint32_t EQR        : 12;
            volatile const  uint32_t RESERVED1  : 4;
            volatile const  uint32_t WVR        : 16;
        } IDCODE_B;
    } ;

     
    union
    {
        volatile uint32_t CFG;

        struct
        {
            volatile const  uint32_t RESERVED1        : 1;
            volatile uint32_t STOP_CLK_STS     : 1;
            volatile uint32_t STANDBY_CLK_STS  : 1;
            volatile const  uint32_t RESERVED2        : 29;
        } CFG_B;
    } ;

     
    union
    {
        volatile uint32_t APB1F;

        struct
        {
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t TMR3_STS   : 1;
            volatile const  uint32_t RESERVED2  : 2;
            volatile uint32_t TMR6_STS   : 1;
            volatile const  uint32_t RESERVED3  : 3;
            volatile uint32_t TMR14_STS  : 1;
            volatile const  uint32_t RESERVED4  : 1;
            volatile uint32_t RTC_STS    : 1;
            volatile uint32_t WWDT_STS   : 1;
            volatile uint32_t IWDT_STS   : 1;
            volatile const  uint32_t RESERVED5  : 8;
            volatile uint32_t I2C1_SMBUS_TIMEOUT_STS : 1;
            volatile const  uint32_t RESERVED6  : 10;
        } APB1F_B;
    } ;

     
    union
    {
        volatile uint32_t APB2F;

        struct
        {
            volatile const  uint32_t RESERVED1  : 11;
            volatile uint32_t TMR1_STS   : 1;
            volatile const  uint32_t RESERVED2  : 4;
            volatile uint32_t TMR15_STS  : 1;
            volatile uint32_t TMR16_STS  : 1;
            volatile uint32_t TMR17_STS  : 1;
            volatile const  uint32_t RESERVED3  : 13;
        } APB2F_B;
    } ;
} DBG_T;



 

typedef struct
{

     
    union
    {
        volatile const  uint32_t INTSTS;

        struct
        {
            volatile const  uint32_t GINTFLG1   : 1;
            volatile const  uint32_t TCFLG1     : 1;
            volatile const  uint32_t HTFLG1     : 1;
            volatile const  uint32_t TERRFLG1   : 1;
            volatile const  uint32_t GINTFLG2   : 1;
            volatile const  uint32_t TCFLG2     : 1;
            volatile const  uint32_t HTFLG2     : 1;
            volatile const  uint32_t TERRFLG2   : 1;
            volatile const  uint32_t GINTFLG3   : 1;
            volatile const  uint32_t TCFLG3     : 1;
            volatile const  uint32_t HTFLG3     : 1;
            volatile const  uint32_t TERRFLG3   : 1;
            volatile const  uint32_t GINTFLG4   : 1;
            volatile const  uint32_t TCFLG4     : 1;
            volatile const  uint32_t HTFLG4     : 1;
            volatile const  uint32_t TERRFLG4   : 1;
            volatile const  uint32_t GINTFLG5   : 1;
            volatile const  uint32_t TCFLG5     : 1;
            volatile const  uint32_t HTFLG5     : 1;
            volatile const  uint32_t TERRFLG5   : 1;
            volatile const  uint32_t RESERVED1  : 12;
        } ISTS_B;
    } ;

     
    union
    {
        volatile  uint32_t INTFCLR;

        struct
        {
            volatile  uint32_t GINTCLR1   : 1;
            volatile  uint32_t TCCLR1     : 1;
            volatile  uint32_t HTCLR1     : 1;
            volatile  uint32_t TERRCLR1   : 1;
            volatile  uint32_t GINTCLR2   : 1;
            volatile  uint32_t TCCLR2     : 1;
            volatile  uint32_t HTCLR2     : 1;
            volatile  uint32_t TERRCLR2   : 1;
            volatile  uint32_t GINTCLR3   : 1;
            volatile  uint32_t TCCLR3     : 1;
            volatile  uint32_t HTCLR3     : 1;
            volatile  uint32_t TERRCLR3   : 1;
            volatile  uint32_t GINTCLR4   : 1;
            volatile  uint32_t TCCLR4     : 1;
            volatile  uint32_t HTCLR4     : 1;
            volatile  uint32_t TERRCLR4   : 1;
            volatile  uint32_t GINTCLR5   : 1;
            volatile  uint32_t TCCLR5     : 1;
            volatile  uint32_t HTCLR5     : 1;
            volatile  uint32_t TERRCLR5   : 1;
            volatile const  uint32_t RESERVED1  : 12;
        } INTFCLR_B;
    } ;

     
    union
    {
        volatile uint32_t CHCFG1;

        struct
        {
            volatile uint32_t CHEN       : 1;
            volatile uint32_t TCINTEN    : 1;
            volatile uint32_t HTINTEN    : 1;
            volatile uint32_t TERRINTEN  : 1;
            volatile uint32_t DIRCFG     : 1;
            volatile uint32_t CIRMODE    : 1;
            volatile uint32_t PERIMODE   : 1;
            volatile uint32_t MIMODE     : 1;
            volatile uint32_t PERSIZE    : 2;
            volatile uint32_t MSIZE      : 2;
            volatile uint32_t CHPL       : 2;
            volatile uint32_t M2MMODE    : 1;
            volatile const  uint32_t RESERVED1  : 17;
        } CHCFG1_B;
    } ;

     
    union
    {
        volatile uint32_t CHNDATA1;

        struct
        {
            volatile uint32_t NDATAT     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CHNDATA1_B;
    } ;

     
    union
    {
        volatile uint32_t CHPADDR1;

        struct
        {
            volatile uint32_t PERADDR    : 32;
        } CHPADDR1_B;
    } ;

     
    union
    {
        volatile uint32_t CHMADDR1;

        struct
        {
            volatile uint32_t MEMADD     : 32;
        } CHMADDR1_B;
    } ;
    volatile const  uint32_t  RESERVED1;

     
    union
    {
        volatile uint32_t CHCFG2;

        struct
        {
            volatile uint32_t CHEN       : 1;
            volatile uint32_t TCINTEN    : 1;
            volatile uint32_t HTINTEN    : 1;
            volatile uint32_t TERRINTEN  : 1;
            volatile uint32_t DIRCFG     : 1;
            volatile uint32_t CIRMODE    : 1;
            volatile uint32_t PERIMODE   : 1;
            volatile uint32_t MIMODE     : 1;
            volatile uint32_t PERSIZE    : 2;
            volatile uint32_t MSIZE      : 2;
            volatile uint32_t CHPL       : 2;
            volatile uint32_t M2MMODE    : 1;
            volatile const  uint32_t RESERVED1  : 17;
        } CHCFG2_B;
    } ;

     
    union
    {
        volatile uint32_t CHNDATA2;

        struct
        {
            volatile uint32_t NDATAT     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CHNDATA2_B;
    } ;

     
    union
    {
        volatile uint32_t CHPADDR2;

        struct
        {
            volatile uint32_t PERADDR    : 32;
        } CHPADDR2_B;
    } ;

     
    union
    {
        volatile uint32_t CHMADDR2;

        struct
        {
            volatile uint32_t MEMADD     : 32;
        } CHMADDR2_B;
    } ;
    volatile const  uint32_t  RESERVED2;

     
    union
    {
        volatile uint32_t CHCFG3;

        struct
        {
            volatile uint32_t CHEN       : 1;
            volatile uint32_t TCINTEN    : 1;
            volatile uint32_t HTINTEN    : 1;
            volatile uint32_t TERRINTEN  : 1;
            volatile uint32_t DIRCFG     : 1;
            volatile uint32_t CIRMODE    : 1;
            volatile uint32_t PERIMODE   : 1;
            volatile uint32_t MIMODE     : 1;
            volatile uint32_t PERSIZE    : 2;
            volatile uint32_t MSIZE      : 2;
            volatile uint32_t CHPL       : 2;
            volatile uint32_t M2MMODE    : 1;
            volatile const  uint32_t RESERVED1  : 17;
        } CHCFG3_B;
    } ;

     
    union
    {
        volatile uint32_t CHNDATA3;

        struct
        {
            volatile uint32_t NDATAT     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CHNDATA3_B;
    } ;

     
    union
    {
        volatile uint32_t CHPADDR3;

        struct
        {
            volatile uint32_t PERADDR    : 32;
        } CHPADDR3_B;
    } ;

     
    union
    {
        volatile uint32_t CHMADDR3;

        struct
        {
            volatile uint32_t MEMADD     : 32;
        } CHMADDR3_B;
    } ;
    volatile const  uint32_t  RESERVED3;

     
    union
    {
        volatile uint32_t CHCFG4;

        struct
        {
            volatile uint32_t CHEN       : 1;
            volatile uint32_t TCINTEN    : 1;
            volatile uint32_t HTINTEN    : 1;
            volatile uint32_t TERRINTEN  : 1;
            volatile uint32_t DIRCFG     : 1;
            volatile uint32_t CIRMODE    : 1;
            volatile uint32_t PERIMODE   : 1;
            volatile uint32_t MIMODE     : 1;
            volatile uint32_t PERSIZE    : 2;
            volatile uint32_t MSIZE      : 2;
            volatile uint32_t CHPL       : 2;
            volatile uint32_t M2MMODE    : 1;
            volatile const  uint32_t RESERVED1  : 17;
        } CHCFG4_B;
    } ;

     
    union
    {
        volatile uint32_t CHNDATA4;

        struct
        {
            volatile uint32_t NDATAT     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CHNDATA4_B;
    } ;

     
    union
    {
        volatile uint32_t CHPADDR4;

        struct
        {
            volatile uint32_t PERADDR    : 32;
        } CHPADDR4_B;
    } ;

     
    union
    {
        volatile uint32_t CHMADDR4;

        struct
        {
            volatile uint32_t MEMADD     : 32;
        } CHMADDR4_B;
    } ;
    volatile const  uint32_t  RESERVED4;

     
    union
    {
        volatile uint32_t CHCFG5;

        struct
        {
            volatile uint32_t CHEN       : 1;
            volatile uint32_t TCINTEN    : 1;
            volatile uint32_t HTINTEN    : 1;
            volatile uint32_t TERRINTEN  : 1;
            volatile uint32_t DIRCFG     : 1;
            volatile uint32_t CIRMODE    : 1;
            volatile uint32_t PERIMODE   : 1;
            volatile uint32_t MIMODE     : 1;
            volatile uint32_t PERSIZE    : 2;
            volatile uint32_t MSIZE      : 2;
            volatile uint32_t CHPL       : 2;
            volatile uint32_t M2MMODE    : 1;
            volatile const  uint32_t RESERVED1  : 17;
        } CHCFG5_B;
    } ;

     
    union
    {
        volatile uint32_t CHNDATA5;

        struct
        {
            volatile uint32_t NDATAT     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CHNDATA5_B;
    } ;

     
    union
    {
        volatile uint32_t CHPADDR5;

        struct
        {
            volatile uint32_t PERADDR    : 32;
        } CHPADDR5_B;
    } ;

     
    union
    {
        volatile uint32_t CHMADDR5;

        struct
        {
            volatile uint32_t MEMADD     : 32;
        } CHMADDR5_B;
    } ;
} DMA_T;



 

typedef struct
{

     
    union
    {
        volatile uint32_t CHCFG;

        struct
        {
            volatile uint32_t CHEN       : 1;
            volatile uint32_t TCINTEN    : 1;
            volatile uint32_t HTINTEN    : 1;
            volatile uint32_t TERRINTEN  : 1;
            volatile uint32_t DIRCFG     : 1;
            volatile uint32_t CIRMODE    : 1;
            volatile uint32_t PERIMODE   : 1;
            volatile uint32_t MIMODE     : 1;
            volatile uint32_t PERSIZE    : 2;
            volatile uint32_t MSIZE      : 2;
            volatile uint32_t CHPL       : 2;
            volatile uint32_t M2MMODE    : 1;
            volatile const  uint32_t RESERVED1  : 17;
        } CHCFG_B;
    } ;

     
    union
    {
        volatile uint32_t CHNDATA;

        struct
        {
            volatile uint32_t NDATAT     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CHNDATA_B;
    } ;

     
    union
    {
        volatile uint32_t CHPADDR;

        struct
        {
            volatile uint32_t PERADDR    : 32;
        } CHPADDR_B;
    } ;

     
    union
    {
        volatile uint32_t CHMADDR;

        struct
        {
            volatile uint32_t MEMADD     : 32;
        } CHMADDR_B;
    } ;
} DMA_CHANNEL_T;



 

typedef struct
{
     
    union
    {
        volatile uint32_t IMASK;

        struct
        {
            volatile uint32_t IMASK0     : 1;
            volatile uint32_t IMASK1     : 1;
            volatile uint32_t IMASK2     : 1;
            volatile uint32_t IMASK3     : 1;
            volatile uint32_t IMASK4     : 1;
            volatile uint32_t IMASK5     : 1;
            volatile uint32_t IMASK6     : 1;
            volatile uint32_t IMASK7     : 1;
            volatile uint32_t IMASK8     : 1;
            volatile uint32_t IMASK9     : 1;
            volatile uint32_t IMASK10    : 1;
            volatile uint32_t IMASK11    : 1;
            volatile uint32_t IMASK12    : 1;
            volatile uint32_t IMASK13    : 1;
            volatile uint32_t IMASK14    : 1;
            volatile uint32_t IMASK15    : 1;
            volatile uint32_t IMASK16    : 1;
            volatile uint32_t IMASK17    : 1;
            volatile uint32_t IMASK18    : 1;
            volatile uint32_t IMASK19    : 1;
            volatile uint32_t IMASK20    : 1;
            volatile uint32_t IMASK21    : 1;
            volatile uint32_t IMASK22    : 1;
            volatile uint32_t IMASK23    : 1;
            volatile uint32_t IMASK24    : 1;
            volatile uint32_t IMASK25    : 1;
            volatile uint32_t IMASK26    : 1;
            volatile uint32_t IMASK27    : 1;
            volatile uint32_t IMASK28    : 1;
            volatile uint32_t IMASK29    : 1;
            volatile uint32_t IMASK30    : 1;
            volatile uint32_t IMASK31    : 1;
        } IMASK_B;
    } ;

     
    union
    {

        volatile uint32_t EMASK;

        struct
        {
            volatile uint32_t EMASK0     : 1;
            volatile uint32_t EMASK1     : 1;
            volatile uint32_t EMASK2     : 1;
            volatile uint32_t EMASK3     : 1;
            volatile uint32_t EMASK4     : 1;
            volatile uint32_t EMASK5     : 1;
            volatile uint32_t EMASK6     : 1;
            volatile uint32_t EMASK7     : 1;
            volatile uint32_t EMASK8     : 1;
            volatile uint32_t EMASK9     : 1;
            volatile uint32_t EMASK10    : 1;
            volatile uint32_t EMASK11    : 1;
            volatile uint32_t EMASK12    : 1;
            volatile uint32_t EMASK13    : 1;
            volatile uint32_t EMASK14    : 1;
            volatile uint32_t EMASK15    : 1;
            volatile uint32_t EMASK16    : 1;
            volatile uint32_t EMASK17    : 1;
            volatile uint32_t EMASK18    : 1;
            volatile uint32_t EMASK19    : 1;
            volatile uint32_t EMASK20    : 1;
            volatile uint32_t EMASK21    : 1;
            volatile uint32_t EMASK22    : 1;
            volatile uint32_t EMASK23    : 1;
            volatile uint32_t EMASK24    : 1;
            volatile uint32_t EMASK25    : 1;
            volatile uint32_t EMASK26    : 1;
            volatile uint32_t EMASK27    : 1;
            volatile uint32_t EMASK28    : 1;
            volatile uint32_t EMASK29    : 1;
            volatile uint32_t EMASK30    : 1;
            volatile uint32_t EMASK31    : 1;
        } EMASK_B;
    } ;

    union
    {
        volatile uint32_t RTEN;

        struct
        {
            volatile uint32_t RTEN0      : 1;
            volatile uint32_t RTEN1      : 1;
            volatile uint32_t RTEN2      : 1;
            volatile uint32_t RTEN3      : 1;
            volatile uint32_t RTEN4      : 1;
            volatile uint32_t RTEN5      : 1;
            volatile uint32_t RTEN6      : 1;
            volatile uint32_t RTEN7      : 1;
            volatile uint32_t RTEN8      : 1;
            volatile uint32_t RTEN9      : 1;
            volatile uint32_t RTEN10     : 1;
            volatile uint32_t RTEN11     : 1;
            volatile uint32_t RTEN12     : 1;
            volatile uint32_t RTEN13     : 1;
            volatile uint32_t RTEN14     : 1;
            volatile uint32_t RTEN15     : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t RTEN17     : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t RTEN19     : 1;
            volatile const  uint32_t RESERVED3  : 12;
        } RTEN_B;
    } ;

     
    union
    {
        volatile uint32_t FTEN;

        struct
        {
            volatile uint32_t FTEN0      : 1;
            volatile uint32_t FTEN1      : 1;
            volatile uint32_t FTEN2      : 1;
            volatile uint32_t FTEN3      : 1;
            volatile uint32_t FTEN4      : 1;
            volatile uint32_t FTEN5      : 1;
            volatile uint32_t FTEN6      : 1;
            volatile uint32_t FTEN7      : 1;
            volatile uint32_t FTEN8      : 1;
            volatile uint32_t FTEN9      : 1;
            volatile uint32_t FTEN10     : 1;
            volatile uint32_t FTEN11     : 1;
            volatile uint32_t FTEN12     : 1;
            volatile uint32_t FTEN13     : 1;
            volatile uint32_t FTEN14     : 1;
            volatile uint32_t FTEN15     : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t FTEN17     : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t FTEN19     : 1;
            volatile const  uint32_t RESERVED3  : 12;
        } FTEN_B;
    } ;

     
    union
    {
        volatile uint32_t SWINTE;

        struct
        {
            volatile uint32_t SWINTE0    : 1;
            volatile uint32_t SWINTE1    : 1;
            volatile uint32_t SWINTE2    : 1;
            volatile uint32_t SWINTE3    : 1;
            volatile uint32_t SWINTE4    : 1;
            volatile uint32_t SWINTE5    : 1;
            volatile uint32_t SWINTE6    : 1;
            volatile uint32_t SWINTE7    : 1;
            volatile uint32_t SWINTE8    : 1;
            volatile uint32_t SWINTE9    : 1;
            volatile uint32_t SWINTE10   : 1;
            volatile uint32_t SWINTE11   : 1;
            volatile uint32_t SWINTE12   : 1;
            volatile uint32_t SWINTE13   : 1;
            volatile uint32_t SWINTE14   : 1;
            volatile uint32_t SWINTE15   : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t SWINTE17   : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t SWINTE19   : 1;
            volatile const  uint32_t RESERVED3  : 12;
        } SWINTE_B;
    } ;

     
    union
    {
        volatile uint32_t IPEND;

        struct
        {
            volatile uint32_t IPEND0     : 1;
            volatile uint32_t IPEND1     : 1;
            volatile uint32_t IPEND2     : 1;
            volatile uint32_t IPEND3     : 1;
            volatile uint32_t IPEND4     : 1;
            volatile uint32_t IPEND5     : 1;
            volatile uint32_t IPEND6     : 1;
            volatile uint32_t IPEND7     : 1;
            volatile uint32_t IPEND8     : 1;
            volatile uint32_t IPEND9     : 1;
            volatile uint32_t IPEND10    : 1;
            volatile uint32_t IPEND11    : 1;
            volatile uint32_t IPEND12    : 1;
            volatile uint32_t IPEND13    : 1;
            volatile uint32_t IPEND14    : 1;
            volatile uint32_t IPEND15    : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t IPEND17    : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t IPEND19    : 1;
            volatile const  uint32_t RESERVED3  : 12;
        } IPEND_B;
    } ;
} EINT_T;



 

typedef struct
{

     
    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t WS         : 3;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t PBEN       : 1;
            volatile const  uint32_t PBSF       : 1;
            volatile const  uint32_t RESERVED3  : 26;
        } CTRL1_B;
    } ;

     
    union
    {
        volatile  uint32_t KEY;

        struct
        {
            volatile  uint32_t KEY        : 32;
        } KEY_B;
    } ;

     
    union
    {
        volatile  uint32_t OBKEY;

        struct
        {
            volatile  uint32_t OBKEY      : 32;
        } OBKEY_B;
    } ;

     
    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile const  uint32_t BUSYF      : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t PEF        : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t WPEF       : 1;
            volatile uint32_t OCF        : 1;
            volatile const  uint32_t RESERVED3  : 26;
        } STS_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t PG         : 1;
            volatile uint32_t PAGEERA    : 1;
            volatile uint32_t MASSERA    : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t OBP        : 1;
            volatile uint32_t OBE        : 1;
            volatile uint32_t STA        : 1;
            volatile uint32_t LOCK       : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t OBWEN      : 1;
            volatile uint32_t ERRIE      : 1;
            volatile const  uint32_t RESERVED3  : 1;
            volatile uint32_t OCIE       : 1;
            volatile uint32_t OBLOAD     : 1;
            volatile const  uint32_t RESERVED4  : 18;
        } CTRL2_B;
    } ;

     
    union
    {
        volatile  uint32_t ADDR;

        struct
        {
            volatile  uint32_t ADDR       : 32;
        } ADDR_B;
    } ;
    volatile const  uint32_t  RESERVED;

     
    union
    {
        volatile const  uint32_t OBCS;

        struct
        {
            volatile const  uint32_t OBE        : 1;
            volatile const  uint32_t READPROT   : 2;
            volatile const  uint32_t RESERVED1  : 5;
            volatile const  uint32_t WDTSEL     : 1;
            volatile const  uint32_t RSTSTOP    : 1;
            volatile const  uint32_t RSTSTDB    : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile const  uint32_t nBOOT1     : 1;
            volatile const  uint32_t VDDAMONI   : 1;
            volatile const  uint32_t SRAMPARITY : 1;
            volatile const  uint32_t RESERVED3  : 1;
            volatile const  uint32_t DATA0      : 8;
            volatile const  uint32_t DATA1      : 8;
        } OBCS_B;
    } ;

     
    union
    {
        volatile const  uint32_t WRTPROT;

        struct
        {
            volatile const  uint32_t WRTPROT    : 32;
        } WRTPROT_B;
    } ;
} FMC_T;



 

typedef struct
{
     
    union
    {
        volatile uint32_t MODE;

        struct
        {
            volatile uint32_t MODE0      : 2;
            volatile uint32_t MODE1      : 2;
            volatile uint32_t MODE2      : 2;
            volatile uint32_t MODE3      : 2;
            volatile uint32_t MODE4      : 2;
            volatile uint32_t MODE5      : 2;
            volatile uint32_t MODE6      : 2;
            volatile uint32_t MODE7      : 2;
            volatile uint32_t MODE8      : 2;
            volatile uint32_t MODE9      : 2;
            volatile uint32_t MODE10     : 2;
            volatile uint32_t MODE11     : 2;
            volatile uint32_t MODE12     : 2;
            volatile uint32_t MODE13     : 2;
            volatile uint32_t MODE14     : 2;
            volatile uint32_t MODE15     : 2;
        } MODE_B;
    } ;

     
    union
    {
        volatile uint32_t OMODE;

        struct
        {
            volatile uint32_t OMODE0     : 1;
            volatile uint32_t OMODE1     : 1;
            volatile uint32_t OMODE2     : 1;
            volatile uint32_t OMODE3     : 1;
            volatile uint32_t OMODE4     : 1;
            volatile uint32_t OMODE5     : 1;
            volatile uint32_t OMODE6     : 1;
            volatile uint32_t OMODE7     : 1;
            volatile uint32_t OMODE8     : 1;
            volatile uint32_t OMODE9     : 1;
            volatile uint32_t OMODE10    : 1;
            volatile uint32_t OMODE11    : 1;
            volatile uint32_t OMODE12    : 1;
            volatile uint32_t OMODE13    : 1;
            volatile uint32_t OMODE14    : 1;
            volatile uint32_t OMODE15    : 1;
            volatile uint32_t RESERVED1  : 16;
        } OMODE_B;
    } ;

     
    union
    {
        volatile uint32_t OSSEL;

        struct
        {
            volatile uint32_t OSSEL0     : 2;
            volatile uint32_t OSSEL1     : 2;
            volatile uint32_t OSSEL2     : 2;
            volatile uint32_t OSSEL3     : 2;
            volatile uint32_t OSSEL4     : 2;
            volatile uint32_t OSSEL5     : 2;
            volatile uint32_t OSSEL6     : 2;
            volatile uint32_t OSSEL7     : 2;
            volatile uint32_t OSSEL8     : 2;
            volatile uint32_t OSSEL9     : 2;
            volatile uint32_t OSSEL10    : 2;
            volatile uint32_t OSSEL11    : 2;
            volatile uint32_t OSSEL12    : 2;
            volatile uint32_t OSSEL13    : 2;
            volatile uint32_t OSSEL14    : 2;
            volatile uint32_t OSSEL15    : 2;
        } OSSEL_B;
    } ;

     
    union
    {
        volatile uint32_t PUPD;

        struct
        {
            volatile uint32_t PUPD0      : 2;
            volatile uint32_t PUPD1      : 2;
            volatile uint32_t PUPD2      : 2;
            volatile uint32_t PUPD3      : 2;
            volatile uint32_t PUPD4      : 2;
            volatile uint32_t PUPD5      : 2;
            volatile uint32_t PUPD6      : 2;
            volatile uint32_t PUPD7      : 2;
            volatile uint32_t PUPD8      : 2;
            volatile uint32_t PUPD9      : 2;
            volatile uint32_t PUPD10     : 2;
            volatile uint32_t PUPD11     : 2;
            volatile uint32_t PUPD12     : 2;
            volatile uint32_t PUPD13     : 2;
            volatile uint32_t PUPD14     : 2;
            volatile uint32_t PUPD15     : 2;
        } PUPD_B;
    } ;

     
    union
    {
        volatile const  uint32_t IDATA;

        struct
        {
            volatile const  uint32_t IDATA0       : 1;
            volatile const  uint32_t IDATA1       : 1;
            volatile const  uint32_t IDATA2       : 1;
            volatile const  uint32_t IDATA3       : 1;
            volatile const  uint32_t IDATA4       : 1;
            volatile const  uint32_t IDATA5       : 1;
            volatile const  uint32_t IDATA6       : 1;
            volatile const  uint32_t IDATA7       : 1;
            volatile const  uint32_t IDATA8       : 1;
            volatile const  uint32_t IDATA9       : 1;
            volatile const  uint32_t IDATA10      : 1;
            volatile const  uint32_t IDATA11      : 1;
            volatile const  uint32_t IDATA12      : 1;
            volatile const  uint32_t IDATA13      : 1;
            volatile const  uint32_t IDATA14      : 1;
            volatile const  uint32_t IDATA15      : 1;
            volatile const  uint32_t RESERVED1  : 16;
        } IDATA_B;
    } ;

     
    union
    {
        volatile uint32_t ODATA;

        struct
        {
            volatile uint32_t ODATA0      : 1;
            volatile uint32_t ODATA1      : 1;
            volatile uint32_t ODATA2      : 1;
            volatile uint32_t ODATA3      : 1;
            volatile uint32_t ODATA4      : 1;
            volatile uint32_t ODATA5      : 1;
            volatile uint32_t ODATA6      : 1;
            volatile uint32_t ODATA7      : 1;
            volatile uint32_t ODATA8      : 1;
            volatile uint32_t ODATA9      : 1;
            volatile uint32_t ODATA10     : 1;
            volatile uint32_t ODATA11     : 1;
            volatile uint32_t ODATA12     : 1;
            volatile uint32_t ODATA13     : 1;
            volatile uint32_t ODATA14     : 1;
            volatile uint32_t ODATA15     : 1;
            volatile uint32_t RESERVED1  : 16;
        } ODATA_B;
    } ;

     
    union
    {
        volatile  uint32_t BSC;

        struct
        {
            volatile  uint32_t BS0        : 1;
            volatile  uint32_t BS1        : 1;
            volatile  uint32_t BS2        : 1;
            volatile  uint32_t BS3        : 1;
            volatile  uint32_t BS4        : 1;
            volatile  uint32_t BS5        : 1;
            volatile  uint32_t BS6        : 1;
            volatile  uint32_t BS7        : 1;
            volatile  uint32_t BS8        : 1;
            volatile  uint32_t BS9        : 1;
            volatile  uint32_t BS10       : 1;
            volatile  uint32_t BS11       : 1;
            volatile  uint32_t BS12       : 1;
            volatile  uint32_t BS13       : 1;
            volatile  uint32_t BS14       : 1;
            volatile  uint32_t BS15       : 1;
            volatile  uint32_t BC0        : 1;
            volatile  uint32_t BC1        : 1;
            volatile  uint32_t BC2        : 1;
            volatile  uint32_t BC3        : 1;
            volatile  uint32_t BC4        : 1;
            volatile  uint32_t BC5        : 1;
            volatile  uint32_t BC6        : 1;
            volatile  uint32_t BC7        : 1;
            volatile  uint32_t BC8        : 1;
            volatile  uint32_t BC9        : 1;
            volatile  uint32_t BC10       : 1;
            volatile  uint32_t BC11       : 1;
            volatile  uint32_t BC12       : 1;
            volatile  uint32_t BC13       : 1;
            volatile  uint32_t BC14       : 1;
            volatile  uint32_t BC15       : 1;
        } BSC_B;
    } ;

     
    union
    {
        volatile uint32_t LOCK;

        struct
        {
            volatile uint32_t LOCK0      : 1;
            volatile uint32_t LOCK1      : 1;
            volatile uint32_t LOCK2      : 1;
            volatile uint32_t LOCK3      : 1;
            volatile uint32_t LOCK4      : 1;
            volatile uint32_t LOCK5      : 1;
            volatile uint32_t LOCK6      : 1;
            volatile uint32_t LOCK7      : 1;
            volatile uint32_t LOCK8      : 1;
            volatile uint32_t LOCK9      : 1;
            volatile uint32_t LOCK10     : 1;
            volatile uint32_t LOCK11     : 1;
            volatile uint32_t LOCK12     : 1;
            volatile uint32_t LOCK13     : 1;
            volatile uint32_t LOCK14     : 1;
            volatile uint32_t LOCK15     : 1;
            volatile uint32_t LOCKKEY    : 1;
            volatile uint32_t RESERVED1  : 15;
        } LOCK_B;
    } ;

     
    union
    {
        volatile uint32_t ALFL;

        struct
        {
            volatile uint32_t AF0        : 4;
            volatile uint32_t AF1        : 4;
            volatile uint32_t AF2        : 4;
            volatile uint32_t AF3        : 4;
            volatile uint32_t AF4        : 4;
            volatile uint32_t AF5        : 4;
            volatile uint32_t AF6        : 4;
            volatile uint32_t AF7        : 4;
        } ALFL_B;
    } ;

     
    union
    {
        volatile uint32_t ALFH;

        struct
        {
            volatile uint32_t AF0        : 4;
            volatile uint32_t AF1        : 4;
            volatile uint32_t AF2        : 4;
            volatile uint32_t AF3        : 4;
            volatile uint32_t AF4        : 4;
            volatile uint32_t AF5        : 4;
            volatile uint32_t AF6        : 4;
            volatile uint32_t AF7        : 4;
        } ALFH_B;
    } ;

     
    union
    {
        volatile  uint32_t BR;

        struct
        {
            volatile  uint32_t BR0        : 1;
            volatile  uint32_t BR1        : 1;
            volatile  uint32_t BR2        : 1;
            volatile  uint32_t BR3        : 1;
            volatile  uint32_t BR4        : 1;
            volatile  uint32_t BR5        : 1;
            volatile  uint32_t BR6        : 1;
            volatile  uint32_t BR7        : 1;
            volatile  uint32_t BR8        : 1;
            volatile  uint32_t BR9        : 1;
            volatile  uint32_t BR10       : 1;
            volatile  uint32_t BR11       : 1;
            volatile  uint32_t BR12       : 1;
            volatile  uint32_t BR13       : 1;
            volatile  uint32_t BR14       : 1;
            volatile  uint32_t BR15       : 1;
            volatile  uint32_t RESERVED1  : 16;
        } BR_B;
    } ;
} GPIO_T;




 

typedef struct
{
     
    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t I2CEN      : 1;
            volatile uint32_t TXIEN      : 1;
            volatile uint32_t RXIEN      : 1;
            volatile uint32_t SADDRMIEN  : 1;
            volatile uint32_t NACKRXIEN  : 1;
            volatile uint32_t STOPIEN    : 1;
            volatile uint32_t TXCIEN     : 1;
            volatile uint32_t ERRIEN     : 1;
            volatile uint32_t DNFCFG     : 4;
            volatile uint32_t ANFD       : 1;
            volatile  uint32_t SWRST      : 1;
            volatile uint32_t DMATXEN    : 1;
            volatile uint32_t DMARXEN    : 1;
            volatile uint32_t SBCEN      : 1;
            volatile uint32_t CLKSTRETCHD : 1;
            volatile uint32_t WUPEN      : 1;
            volatile uint32_t RBEN       : 1;
            volatile uint32_t HADDREN    : 1;
            volatile uint32_t DEADDREN   : 1;
            volatile uint32_t ALTEN      : 1;
            volatile uint32_t PECEN      : 1;
            volatile const  uint32_t RESERVED2  : 8;
        } CTRL1_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t SADDR0     : 1;
            volatile uint32_t SADDR1     : 7;
            volatile uint32_t SADDR8     : 2;
            volatile uint32_t TXDIR      : 1;
            volatile uint32_t SADDRLEN   : 1;
            volatile uint32_t ADDR10     : 1;
            volatile uint32_t START      : 1;
            volatile uint32_t STOP       : 1;
            volatile uint32_t NACKEN     : 1;
            volatile uint32_t NUMBYT     : 8;
            volatile uint32_t RELOADEN   : 1;
            volatile uint32_t ENDCFG     : 1;
            volatile uint32_t PEC        : 1;
            volatile uint32_t RESERVED1  : 5;
        } CTRL2_B;
    } ;

     
    union
    {
        volatile uint32_t ADDR1;

        struct
        {
            volatile uint32_t ADDR0      : 1;
            volatile uint32_t ADDR1      : 7;
            volatile uint32_t ADDR8      : 2;
            volatile uint32_t ADDR1LEN   : 1;
            volatile const  uint32_t RESERVED1  : 4;
            volatile uint32_t ADDR1EN    : 1;
            volatile const  uint32_t RESERVED2  : 16;
        } ADDR1_B;
    } ;

     
    union
    {
        volatile uint32_t ADDR2;

        struct
        {
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t ADDR2      : 7;
            volatile uint32_t ADDR2MSK   : 3;
            volatile const  uint32_t RESERVED2  : 4;
            volatile uint32_t ADDR2EN    : 1;
            volatile const  uint32_t RESERVED3  : 16;
        } ADDR2_B;
    } ;

     
    union
    {
        volatile uint32_t TIMING;

        struct
        {
            volatile uint32_t SCLL       : 8;
            volatile uint32_t SCLH       : 8;
            volatile uint32_t DATAHT     : 4;
            volatile uint32_t DATAT      : 4;
            volatile const  uint32_t RESERVED1  : 4;
            volatile uint32_t TIMINGPSC  : 4;
        } TIMING_B;
    } ;

     
    union
    {
        volatile uint32_t TIMEOUT;

        struct
        {
            volatile uint32_t TIMEOUTA   : 12;
            volatile uint32_t IDLECLKTO  : 1;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t CLKTOEN    : 1;
            volatile uint32_t TIMEOUTB   : 12;
            volatile const  uint32_t RESERVED2  : 3;
            volatile uint32_t EXCLKTOEN  : 1;
        } TIMEOUT_B;
    } ;

     
    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile uint32_t TXBEFLG    : 1;
            volatile uint32_t TXINTFLG   : 1;
            volatile const  uint32_t RXBNEFLG   : 1;
            volatile const  uint32_t ADDRMFLG   : 1;
            volatile const  uint32_t NACKFLG    : 1;
            volatile const  uint32_t STOPFLG    : 1;
            volatile const  uint32_t TXCFLG     : 1;
            volatile const  uint32_t TXCRFLG    : 1;
            volatile const  uint32_t BERRFLG    : 1;
            volatile const  uint32_t ALFLG      : 1;
            volatile const  uint32_t OVRURFLG   : 1;
            volatile const  uint32_t PECEFLG    : 1;
            volatile const  uint32_t TTEFLG     : 1;
            volatile const  uint32_t SMBALTFLG  : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile const  uint32_t BUSBSYFLG  : 1;
            volatile const  uint32_t TXDIRFLG   : 1;
            volatile const  uint32_t ADDRCMFLG  : 7;
            volatile const  uint32_t RESERVED2  : 8;
        } STS_B;
    } ;

     
    union
    {
        volatile  uint32_t INTFCLR;

        struct
        {
            volatile const  uint32_t RESERVED1  : 3;
            volatile  uint32_t ADDRMCLR   : 1;
            volatile  uint32_t NACKCLR    : 1;
            volatile  uint32_t STOPCLR    : 1;
            volatile const  uint32_t RESERVED2  : 2;
            volatile  uint32_t BERRCLR    : 1;
            volatile  uint32_t ALCLR      : 1;
            volatile  uint32_t OVRURCLR   : 1;
            volatile  uint32_t PECECLR    : 1;
            volatile  uint32_t TTECLR     : 1;
            volatile  uint32_t SMBALTCLR  : 1;
            volatile const  uint32_t RESERVED3  : 18;
        } INTFCLR_B;
    } ;

     
    union
    {
        volatile const  uint32_t PEC;

        struct
        {
            volatile const  uint32_t PEC        : 8;
            volatile const  uint32_t RESERVED1  : 24;
        } PEC_B;
    } ;

     
    union
    {
        volatile const  uint32_t RXDATA;

        struct
        {
            volatile const  uint32_t RXDATA     : 8;
            volatile const  uint32_t RESERVED1  : 24;
        } RXDATA_B;
    } ;

     
    union
    {
        volatile uint32_t TXDATA;

        struct
        {
            volatile uint32_t TXDATA     : 8;
            volatile uint32_t RESERVED1  : 24;
        } TXDATA_B;
    } ;
} I2C_T;



 

typedef struct
{

     
    union
    {
        volatile  uint32_t KEY;

        struct
        {
            volatile  uint32_t KEY        : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } KEY_B;
    } ;

     
    union
    {
        volatile uint32_t PSC;

        struct
        {
            volatile uint32_t PSC        : 3;
            volatile const  uint32_t RESERVED1  : 29;
        } PSC_B;
    } ;

     
    union
    {
        volatile uint32_t CNTRLD;

        struct
        {
            volatile uint32_t CNTRLD     : 12;
            volatile const  uint32_t RESERVED1  : 20;
        } CNTRLD_B;
    } ;

     
    union
    {
        volatile const  uint32_t STS;

        struct
        {
            volatile const  uint32_t PSCUFLG    : 1;
            volatile const  uint32_t CNTUFLG    : 1;
            volatile const  uint32_t WINUFLG    : 1;
            volatile const  uint32_t RESERVED1  : 29;
        } STS_B;
    } ;

     
    union
    {
        volatile uint32_t WIN;

        struct
        {
            volatile uint32_t WIN        : 12;
            volatile const  uint32_t RESERVED1  : 20;
        } WIN_B;
    } ;
} IWDT_T;



 

typedef struct
{

     
    union
    {
        volatile uint16_t READPROT;

        struct
        {
            volatile uint16_t READPROT   : 8;
            volatile uint16_t nREADPROT  : 8;
        } READPORT_B;
    } ;

     
    union
    {
        volatile uint16_t USER;

        struct
        {
            volatile uint16_t WDTSEL     : 1;
            volatile uint16_t RSTSTOP    : 1;
            volatile uint16_t RSTSTDBY   : 1;
            volatile const  uint16_t RESERVED1  : 1;
            volatile uint16_t BOT1       : 1;
            volatile uint16_t VDDAMON    : 1;
            volatile uint16_t RPC        : 1;
            volatile const  uint16_t RESERVED2  : 1;
            volatile uint16_t nUSER      : 8;
        } USER_B;
    } ;

     
    union
    {
        volatile uint16_t DATA0;

        struct
        {
            volatile uint16_t DATA0      : 8;
            volatile uint16_t nDATA0     : 8;
        } DATA0_B;
    } ;

     
    union
    {
        volatile uint16_t DATA1;

        struct
        {
            volatile uint16_t DATA1      : 8;
            volatile uint16_t nDATA1     : 8;
        } DATA1_B;
    } ;

     
    union
    {
        volatile uint16_t WRTPROT0;

        struct
        {
            volatile uint16_t WRTPROT0   : 8;
            volatile uint16_t nWRTPROT0  : 8;
        } WRTPROT0_B;
    } ;

     
    union
    {
        volatile uint16_t WRTPROT1;

        struct
        {
            volatile uint16_t WRTPROT1   : 8;
            volatile uint16_t nWRTPROT1  : 8;
        } WRTPROT1_B;
    } ;
} OB_T;



 

typedef struct
{
     
    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t LPDSCFG    : 1;
            volatile uint32_t PDDSCFG    : 1;
            volatile uint32_t WUFLGCLR   : 1;
            volatile uint32_t SBFLGCLR   : 1;
            volatile const  uint32_t RESERVED1  : 4;
            volatile uint32_t BPWEN      : 1;
            volatile const  uint32_t RESERVED2  : 23;

        } CTRL_B;
    } ;

     
    union
    {
        volatile uint32_t CSTS;

        struct
        {
            volatile const  uint32_t WUEFLG     : 1;
            volatile const  uint32_t SBFLG      : 1;
            volatile const  uint32_t RESERVED1  : 6;
            volatile uint32_t WKUPCFG1   : 1;
            volatile uint32_t WKUPCFG2   : 1;
            volatile const  uint32_t RESERVED2  : 22;
        } CSTS_B;
    } ;
} PMU_T;



 

typedef struct
{
     
    union
    {
         
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t HSIEN      : 1;
            volatile const  uint32_t HSIRDYFLG  : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t HSITRM     : 5;
            volatile const  uint32_t HSICAL     : 8;
            volatile uint32_t HSEEN      : 1;
            volatile const  uint32_t HSERDYFLG  : 1;
            volatile uint32_t HSEBCFG    : 1;
            volatile uint32_t CSSEN      : 1;
            volatile const  uint32_t RESERVED2  : 4;
            volatile uint32_t PLLEN      : 1;
            volatile const  uint32_t PLLRDYFLG  : 1;
            volatile const  uint32_t RESERVED3  : 6;
        } CTRL1_B;
    } ;

     
    union
    {
        volatile uint32_t CFG1;

        struct
        {
            volatile uint32_t SCLKSEL    : 2;
            volatile const  uint32_t SCLKSWSTS  : 2;
            volatile uint32_t AHBPSC     : 4;
            volatile uint32_t APB1PSC    : 3;
            volatile const  uint32_t RESERVED1  : 5;
            volatile uint32_t PLLSRCSEL  : 1;
            volatile uint32_t PLLHSEPSC  : 1;
            volatile uint32_t PLLMULCFG  : 4;
            volatile const  uint32_t RESERVED3  : 2;
            volatile uint32_t MCOSEL     : 4;
            volatile const  uint32_t RESERVED4  : 4;
        } CFG1_B;
    } ;

     
    union
    {
        volatile uint32_t INT;

        struct
        {
            volatile const  uint32_t LSIRDYFLG   : 1;
            volatile const  uint32_t LSERDYFLG   : 1;
            volatile const  uint32_t HSIRDYFLG   : 1;
            volatile const  uint32_t HSERDYFLG   : 1;
            volatile const  uint32_t PLLRDYFLG   : 1;
            volatile const  uint32_t HSI14RDYFLG : 1;
            volatile const  uint32_t RESERVED1   : 1;
            volatile const  uint32_t CSSFLG      : 1;
            volatile uint32_t LSIRDYEN    : 1;
            volatile uint32_t LSERDYEN    : 1;
            volatile uint32_t HSIRDYEN    : 1;
            volatile uint32_t HSERDYEN    : 1;
            volatile uint32_t PLLRDYEN    : 1;
            volatile uint32_t HSI14RDYEN  : 1;
            volatile const  uint32_t RESERVED2   : 2;
            volatile  uint32_t LSIRDYCLR   : 1;
            volatile  uint32_t LSERDYCLR   : 1;
            volatile  uint32_t HSIRDYCLR   : 1;
            volatile  uint32_t HSERDYCLR   : 1;
            volatile  uint32_t PLLRDYCLR   : 1;
            volatile  uint32_t HSI14RDYCLR : 1;
            volatile const  uint32_t RESERVED3   : 1;
            volatile  uint32_t CSSCLR      : 1;
            volatile const  uint32_t RESERVED4   : 8;
        } INT_B;
    } ;

     
    union
    {
        volatile uint32_t APBRST2;

        struct
        {
            volatile uint32_t SYSCFGRST     : 1;
            volatile const  uint32_t RESERVED1     : 8;
            volatile uint32_t ADCRST        : 1;
            volatile const  uint32_t RESERVED2     : 1;
            volatile uint32_t TMR1RST       : 1;
            volatile uint32_t SPI1RST       : 1;
            volatile const  uint32_t RESERVED3     : 1;
            volatile uint32_t USART1RST     : 1;
            volatile const  uint32_t RESERVED4     : 1;
            volatile uint32_t TMR15RST      : 1;
            volatile uint32_t TMR16RST      : 1;
            volatile uint32_t TMR17RST      : 1;
            volatile const  uint32_t RESERVED5     : 3;
            volatile uint32_t DBGRST        : 1;
            volatile const  uint32_t RESERVED6     : 9;
        } APBRST2_B;
    } ;

     
    union
    {
        volatile uint32_t APBRST1;

        struct
        {
            volatile const  uint32_t RESERVED1     : 1;
            volatile uint32_t TMR3RST       : 1;
            volatile const  uint32_t RESERVED2     : 2;
            volatile uint32_t TMR6RST       : 1;
            volatile const  uint32_t RESERVED3     : 3;
            volatile uint32_t TMR14RST      : 1;
            volatile const  uint32_t RESERVED4     : 2;
            volatile uint32_t WWDTRST       : 1;
            volatile const  uint32_t RESERVED5     : 2;
            volatile uint32_t SPI2RST       : 1;
            volatile const  uint32_t RESERVED6     : 2;
            volatile uint32_t USART2RST     : 1;
            volatile const  uint32_t RESERVED7     : 3;
            volatile uint32_t I2C1RST       : 1;
            volatile uint32_t I2C2RST       : 1;
            volatile const  uint32_t RESERVED8     : 5;
            volatile uint32_t PMURST        : 1;
            volatile const  uint32_t RESERVED9     : 3;
        } APBRST1_B;
    } ;

     
    union
    {
        volatile uint32_t AHBCLKEN;

        struct
        {
            volatile uint32_t DMA1EN       : 1;
            volatile const  uint32_t RESERVED1    : 1;
            volatile uint32_t SRAMEN       : 1;
            volatile const  uint32_t RESERVED2    : 1;
            volatile uint32_t FMCEN        : 1;
            volatile const  uint32_t RESERVED3    : 1;
            volatile uint32_t CRCEN        : 1;
            volatile const  uint32_t RESERVED4    : 10;
            volatile uint32_t PAEN         : 1;
            volatile uint32_t PBEN         : 1;
            volatile uint32_t PCEN         : 1;
            volatile uint32_t PDEN         : 1;
            volatile const  uint32_t RESERVED5    : 1;
            volatile uint32_t PFEN         : 1;
            volatile const  uint32_t RESERVED6    : 9;
        } AHBCLKEN_B;
    } ;

    union
    {
        volatile uint32_t APBCLKEN2;

        struct
        {
            volatile uint32_t SYSCFGEN     : 1;
            volatile const  uint32_t RESERVED1    : 8;
            volatile uint32_t ADCEN        : 1;
            volatile const  uint32_t RESERVED2    : 1;
            volatile uint32_t TMR1EN       : 1;
            volatile uint32_t SPI1EN       : 1;
            volatile const  uint32_t RESERVED3    : 1;
            volatile uint32_t USART1EN     : 1;
            volatile const  uint32_t RESERVED4    : 1;
            volatile uint32_t TMR15EN      : 1;
            volatile uint32_t TMR16EN      : 1;
            volatile uint32_t TMR17EN      : 1;
            volatile const  uint32_t RESERVED5    : 3;
            volatile uint32_t DBGEN        : 1;
            volatile const  uint32_t RESERVED6    : 9;
        } APBCLKEN2_B;
    } ;

     
    union
    {
        volatile uint32_t APBCLKEN1;

        struct
        {
            volatile const  uint32_t RESERVED1    : 1;
            volatile uint32_t TMR3EN       : 1;
            volatile const  uint32_t RESERVED2    : 2;
            volatile uint32_t TMR6EN       : 1;
            volatile const  uint32_t RESERVED3    : 3;
            volatile uint32_t TMR14EN      : 1;
            volatile const  uint32_t RESERVED4    : 2;
            volatile uint32_t WWDTEN       : 1;
            volatile const  uint32_t RESERVED5    : 2;
            volatile uint32_t SPI2EN       : 1;
            volatile const  uint32_t RESERVED6    : 2;
            volatile uint32_t USART2EN     : 1;
            volatile const  uint32_t RESERVED7    : 3;
            volatile uint32_t I2C1EN       : 1;
            volatile uint32_t I2C2EN       : 1;
            volatile const  uint32_t RESERVED8    : 5;
            volatile uint32_t PMUEN        : 1;
            volatile const  uint32_t RESERVED9    : 3;
        } APBCLKEN1_B;
    } ;

     
    union
    {
        volatile uint32_t BDCTRL;

        struct
        {
            volatile uint32_t LSEEN      : 1;
            volatile const  uint32_t LSERDYFLG  : 1;
            volatile uint32_t LSEBCFG    : 1;
            volatile uint32_t LSEDRVCFG  : 2;
            volatile const  uint32_t RESERVED1  : 3;
            volatile uint32_t RTCSRCSEL  : 2;
            volatile const  uint32_t RESERVED2  : 5;
            volatile uint32_t RTCCLKEN   : 1;
            volatile uint32_t BDRST      : 1;
            volatile const  uint32_t RESERVED3  : 15;
        } BDCTRL_B;
    } ;

     
    union
    {
        volatile uint32_t CSTS;

        struct
        {
            volatile uint32_t LSIEN      : 1;
            volatile const  uint32_t LSIRDYFLG  : 1;
            volatile const  uint32_t RESERVED1  : 21;
            volatile const  uint32_t PWRRSTFLG  : 1;
            volatile uint32_t RSTFLGCLR  : 1;
            volatile const  uint32_t OBRSTFLG   : 1;
            volatile const  uint32_t PINRSTFLG  : 1;
            volatile const  uint32_t PODRSTFLG  : 1;
            volatile const  uint32_t SWRSTFLG   : 1;
            volatile const  uint32_t IWDTRSTFLG : 1;
            volatile const  uint32_t WWDTRSTFLG : 1;
            volatile const  uint32_t LPWRRSTFLG : 1;
        } CSTS_B;
    } ;

     
    union
    {
        volatile uint32_t AHBRST;

        struct
        {
            volatile const  uint32_t RESERVED1  : 17;
            volatile uint32_t PARST      : 1;
            volatile uint32_t PBRST      : 1;
            volatile uint32_t PCRST      : 1;
            volatile uint32_t PDRST      : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t PFRST      : 1;
            volatile const  uint32_t RESERVED3  : 9;
        } AHBRST_B;
    } ;

     
    union
    {
        volatile uint32_t CFG2;

        struct
        {
            volatile uint32_t PLLDIVCFG  : 4;
            volatile const  uint32_t RESERVED1  : 28;
        } CFG2_B;
    } ;

     
    union
    {
        volatile uint32_t CFG3;

        struct
        {
            volatile uint32_t USART1SEL  : 2;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t I2C1SEL    : 1;
            volatile const  uint32_t RESERVED2  : 3;
            volatile uint32_t ADCSEL     : 1;
            volatile const  uint32_t RESERVED3  : 23;
        } CFG3_B;
    } ;

    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t HSI14EN    : 1;
            volatile const  uint32_t HSI14RDFLG : 1;
            volatile uint32_t HSI14TO    : 1;
            volatile uint32_t HSI14TRM   : 5;
            volatile const  uint32_t HSI14CAL   : 8;
            volatile const  uint32_t RESERVED1  : 16;
        } CTRL2_B;
    } ;
} RCM_T;



 

typedef struct
{

     
    union
    {
        volatile uint32_t TIME;

        struct
        {
            volatile uint32_t SECU       : 4;
            volatile uint32_t SECT       : 3;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t MINU       : 4;
            volatile uint32_t MINT       : 3;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t HRU        : 4;
            volatile uint32_t HRT        : 2;
            volatile uint32_t TIMEFCFG   : 1;
            volatile const  uint32_t RESERVED3  : 9;
        } TIME_B;
    } ;

     
    union
    {
        volatile uint32_t DATE;

        struct
        {
            volatile uint32_t DAYU       : 4;
            volatile uint32_t DAYT       : 2;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t MONU       : 4;
            volatile uint32_t MONT       : 1;
            volatile uint32_t WEEKSEL    : 3;
            volatile uint32_t YRU        : 4;
            volatile uint32_t YRT        : 4;
            volatile const  uint32_t RESERVED2  : 8;
        } DATE_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile const  uint32_t RESERVED1  : 3;
            volatile uint32_t TSETECFG   : 1;
            volatile uint32_t RCLKDEN    : 1;
            volatile uint32_t RCMCFG     : 1;
            volatile uint32_t TIMEFCFG   : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile uint32_t ALREN      : 1;
            volatile const  uint32_t RESERVED3  : 2;
            volatile uint32_t TSEN       : 1;
            volatile uint32_t ALRIEN     : 1;
            volatile const  uint32_t RESERVED4  : 2;
            volatile uint32_t TSIEN      : 1;
            volatile  uint32_t STCCFG     : 1;
            volatile  uint32_t WTCCFG     : 1;
            volatile uint32_t BAKP       : 1;
            volatile uint32_t CALOSEL    : 1;
            volatile uint32_t POLCFG     : 1;
            volatile uint32_t OUTSEL     : 2;
            volatile uint32_t CALOEN     : 1;
            volatile const  uint32_t RESERVED5  : 8;
        } CTRL_B;
    } ;

     
    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile const  uint32_t ALRWFLG    : 1;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t SOPFLG     : 1;
            volatile const  uint32_t INITSFLG   : 1;
            volatile uint32_t RSFLG      : 1;
            volatile const  uint32_t RINITFLG   : 1;
            volatile uint32_t INITEN     : 1;
            volatile uint32_t ALRAFLG    : 1;
            volatile const  uint32_t RESERVED2  : 2;
            volatile uint32_t TSFLG      : 1;
            volatile uint32_t TSOVRFLG   : 1;
            volatile uint32_t TP1FLG     : 1;
            volatile uint32_t TP2FLG     : 1;
            volatile const  uint32_t TP3FLG     : 1;
            volatile const  uint32_t RCALPFLG   : 1;
            volatile const  uint32_t RESERVED3  : 15;
        } STS_B;
    } ;

     
    union
    {
        volatile uint32_t PSC;

        struct
        {
            volatile uint32_t SPSC       : 15;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t APSC       : 7;
            volatile const  uint32_t RESERVED2  : 9;
        } PSC_B;
    } ;

    volatile const  uint32_t  RESERVED[2];

     
    union
    {
        volatile uint32_t ALRMA;

        struct
        {
            volatile uint32_t SECU       : 4;
            volatile uint32_t SECT       : 3;
            volatile uint32_t SECMEN     : 1;
            volatile uint32_t MINU       : 4;
            volatile uint32_t MINT       : 3;
            volatile uint32_t MINMEN     : 1;
            volatile uint32_t HRU        : 4;
            volatile uint32_t HRT        : 2;
            volatile uint32_t TIMEFCFG   : 1;
            volatile uint32_t HRMEN      : 1;
            volatile uint32_t DAYU       : 4;
            volatile uint32_t DAYT       : 2;
            volatile uint32_t WEEKSEL    : 1;
            volatile uint32_t DATEMEN    : 1;
        } ALRMA_B;
    } ;

    volatile const  uint32_t  RESERVED1;

     
    union
    {
        volatile  uint32_t WRPROT;

        struct
        {
            volatile  uint32_t KEY        : 8;
            volatile const  uint32_t RESERVED1  : 24;
        } WRPROT_B;
    } ;

     
    union
    {
        volatile const  uint32_t SUBSEC;

        struct
        {
            volatile const  uint32_t SUBSEC     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } SUBSEC_B;
    } ;

     
    union
    {
        volatile  uint32_t SHIFT;

        struct
        {
            volatile  uint32_t SFSEC      : 15;
            volatile const  uint32_t RESERVED1  : 16;
            volatile  uint32_t ADD1SECEN  : 1;
        } SHIFT_B;
    } ;

     
    union
    {
        volatile const  uint32_t TSTIME;

        struct
        {
            volatile const  uint32_t SECU       : 4;
            volatile const  uint32_t SECT       : 3;
            volatile const  uint32_t RESERVED1  : 1;
            volatile const  uint32_t MINU       : 4;
            volatile const  uint32_t MINT       : 3;
            volatile const  uint32_t RESERVED2  : 1;
            volatile const  uint32_t HRU        : 4;
            volatile const  uint32_t HRT        : 2;
            volatile const  uint32_t TIMEFCFG   : 1;
            volatile const  uint32_t RESERVED3  : 9;
        } TSTIME_B;
    } ;

     
    union
    {
        volatile const  uint32_t TSDATE;

        struct
        {
            volatile const  uint32_t DAYU       : 4;
            volatile const  uint32_t DAYT       : 2;
            volatile const  uint32_t RESERVED1  : 2;
            volatile const  uint32_t MONU       : 4;
            volatile const  uint32_t MONT       : 1;
            volatile const  uint32_t WEEKSEL    : 3;
            volatile const  uint32_t RESERVED2  : 16;
        } TSDATE_B;
    } ;

     
    union
    {
        volatile const  uint32_t TSSUBSEC;

        struct
        {
            volatile const  uint32_t SUBSEC     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } TSSUBSEC_B;
    } ;

     
    union
    {
        volatile uint32_t CAL;

        struct
        {
            volatile uint32_t RECALF     : 9;
            volatile const  uint32_t RESERVED1  : 4;
            volatile uint32_t CAL16CFG   : 1;
            volatile uint32_t CAL8CFG    : 1;
            volatile uint32_t ICALFEN    : 1;
            volatile const  uint32_t RESERVED2  : 16;
        } CAL_B;
    } ;

     
    union
    {
        volatile uint32_t TACFG;

        struct
        {
            volatile uint32_t TP1EN      : 1;
            volatile uint32_t TP1ALCFG   : 1;
            volatile uint32_t TPIEN      : 1;
            volatile uint32_t TP2EN      : 1;
            volatile uint32_t TP2ALCFG   : 1;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t TPTSEN     : 1;
            volatile uint32_t TPSFSEL    : 3;
            volatile uint32_t TPFCSEL    : 2;
            volatile uint32_t TPPRDUSEL  : 2;
            volatile uint32_t TPPUDIS    : 1;
            volatile const  uint32_t RESERVED2  : 2;
            volatile uint32_t PC13VAL    : 1;
            volatile uint32_t PC13EN     : 1;
            volatile uint32_t PC14VAL    : 1;
            volatile uint32_t PC14EN     : 1;
            volatile uint32_t PC15VAL    : 1;
            volatile uint32_t PC15EN     : 1;
            volatile const  uint32_t RESERVED3  : 8;
        } TACFG_B;
    } ;

     
    union
    {
        volatile uint32_t ALRMASS;

        struct
        {
            volatile uint32_t SUBSEC     : 15;
            volatile const  uint32_t RESERVED1  : 9;
            volatile uint32_t MASKSEL    : 4;
            volatile const  uint32_t RESERVED2  : 4;
        } ALRMASS_B;
    } ;

    volatile const  uint32_t RESERVED2[2];

    union
    {
        volatile uint32_t BAKP0;

        struct
        {
            volatile uint32_t BAKP       : 32;
        } BAKP0_B;
    } ;

    union
    {
        volatile uint32_t BAKP1;

        struct
        {
            volatile uint32_t BAKP       : 32;
        } BAKP1_B;
    } ;
    union
    {
        volatile uint32_t BAKP2;

        struct
        {
            volatile uint32_t BAKP       : 32;
        } BAKP2_B;
    } ;
    union
    {
        volatile uint32_t BAKP3;

        struct
        {
            volatile uint32_t BAKP       : 32;
        } BAKP3_B;
    } ;
    union
    {
        volatile uint32_t BAKP4;

        struct
        {
            volatile uint32_t BAKP       : 32;
        } BAKP4_B;
    } ;
} RTC_T;



 

typedef struct
{
     
    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t CPHA       : 1;
            volatile uint32_t CPOL       : 1;
            volatile uint32_t MSMCFG     : 1;
            volatile uint32_t BRSEL      : 3;
            volatile uint32_t SPIEN      : 1;
            volatile uint32_t LSBSEL     : 1;
            volatile uint32_t ISSEL      : 1;
            volatile uint32_t SSEN       : 1;
            volatile uint32_t RXOMEN     : 1;
            volatile uint32_t CRCLSEL    : 1;
            volatile uint32_t CRCNXT     : 1;
            volatile uint32_t CRCEN      : 1;
            volatile uint32_t BMOEN      : 1;
            volatile uint32_t BMEN       : 1;
            volatile const  uint32_t RESERVED1  : 16;
        } CTRL1_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t RXDEN      : 1;
            volatile uint32_t TXDEN      : 1;
            volatile uint32_t SSOEN      : 1;
            volatile uint32_t NSSPEN     : 1;
            volatile uint32_t FRFCFG     : 1;
            volatile uint32_t ERRIEN     : 1;
            volatile uint32_t RXBNEIEN   : 1;
            volatile uint32_t TXBEIEN    : 1;
            volatile uint32_t DSCFG      : 4;
            volatile uint32_t FRTCFG     : 1;
            volatile uint32_t LDRX       : 1;
            volatile uint32_t LDTX       : 1;
            volatile const  uint32_t RESERVED1  : 17;
        } CTRL2_B;
    } ;

     
    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile const  uint32_t RXBNEFLG   : 1;
            volatile const  uint32_t TXBEFLG    : 1;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t CRCEFLG    : 1;
            volatile const  uint32_t MEFLG      : 1;
            volatile const  uint32_t OVRFLG     : 1;
            volatile const  uint32_t BSYFLG     : 1;
            volatile const  uint32_t FREFLG     : 1;
            volatile const  uint32_t FRLSEL     : 2;
            volatile const  uint32_t FTLSEL     : 2;
            volatile const  uint32_t RESERVED2  : 19;
        } STS_B;
    } ;

     
    union
    {
        volatile uint32_t DATA;

        struct
        {
            volatile uint32_t DATA       : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } DATA_B;
    } ;

     
    union
    {
        volatile uint32_t CRCPOLY;

        struct
        {
            volatile uint32_t CRCPOLY    : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CRCPOLY_B;
    } ;

     
    union
    {

        volatile const  uint32_t RXCRC;

        struct
        {
            volatile const  uint32_t RXCRC      : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } RXCRC_B;
    } ;

     
    union
    {

        volatile const  uint32_t TXCRC;

        struct
        {
            volatile const  uint32_t TXCRC      : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } TXCRC_B;
    } ;
} SPI_T;



 

typedef struct
{
     
    union
    {
        volatile uint32_t CFG1;

        struct
        {
            volatile uint32_t MMSEL        : 2;
            volatile const  uint32_t RESERVED1    : 6;
            volatile uint32_t ADCDMARMP    : 1;
            volatile uint32_t USART1TXRMP  : 1;
            volatile uint32_t USART1RXRMP  : 1;
            volatile uint32_t TMR16DMARMP  : 1;
            volatile uint32_t TMR17DMARMP  : 1;
            volatile const  uint32_t RESERVED2    : 3;
            volatile uint32_t I2CPB6FMP    : 1;
            volatile uint32_t I2CPB7FMP    : 1;
            volatile uint32_t I2CPB8FMP    : 1;
            volatile uint32_t I2CPB9FMP    : 1;
            volatile uint32_t I2C1FMP      : 1;
            volatile const  uint32_t RESERVED3    : 1;
            volatile uint32_t I2CPA9FMP    : 1;
            volatile uint32_t I2CPA10FMP   : 1;
            volatile const  uint32_t RESERVED4    : 8;
        } CFG1_B;
    } ;
    volatile const  uint32_t  RESERVED;

     
    union
    {

        volatile uint32_t EINTCFG1;

        struct
        {
            volatile uint32_t EINT0      : 4;
            volatile uint32_t EINT1      : 4;
            volatile uint32_t EINT2      : 4;
            volatile uint32_t EINT3      : 4;
            volatile const  uint32_t RESERVED1  : 16;
        } EINTCFG1_B;
    } ;

     
    union
    {
        volatile uint32_t EINTCFG2;

        struct
        {
            volatile uint32_t EINT4      : 4;
            volatile uint32_t EINT5      : 4;
            volatile uint32_t EINT6      : 4;
            volatile uint32_t EINT7      : 4;
            volatile const  uint32_t RESERVED1  : 16;
        } EINTCFG2_B;
    } ;

     
    union
    {
        volatile uint32_t EINTCFG3;

        struct
        {
            volatile uint32_t EINT8      : 4;
            volatile uint32_t EINT9      : 4;
            volatile uint32_t EINT10     : 4;
            volatile uint32_t EINT11     : 4;
            volatile const  uint32_t RESERVED1  : 16;
        } EINTCFG3_B;
    } ;

     
    union
    {
        volatile uint32_t EINTCFG4;

        struct
        {
            volatile uint32_t EINT12     : 4;
            volatile uint32_t EINT13     : 4;
            volatile uint32_t EINT14     : 4;
            volatile uint32_t EINT15     : 4;
            volatile const  uint32_t RESERVED1  : 16;
        } EINTCFG4_B;
    } ;

     
    union
    {
        volatile uint32_t CFG2;

        struct
        {
            volatile uint32_t LOCK       : 1;
            volatile uint32_t SRAMLOCK   : 1;
            volatile const  uint32_t RESERVED1  : 6;
            volatile uint32_t SRAMEFLG   : 1;
            volatile const  uint32_t RESERVED2  : 23;
        } CFG2_B;
    } ;
} SYSCFG_T;



 

typedef struct
{
     
    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t CNTEN      : 1;
            volatile uint32_t UD         : 1;
            volatile uint32_t URSSEL     : 1;
            volatile uint32_t SPMEN      : 1;
            volatile uint32_t CNTDIR     : 1;
            volatile uint32_t CAMSEL     : 2;
            volatile uint32_t ARPEN      : 1;
            volatile uint32_t CLKDIV     : 2;
            volatile const  uint32_t RESERVED1  : 22;
        } CTRL1_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t CCPEN      : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t CCUSEL     : 1;
            volatile uint32_t CCDSEL     : 1;
            volatile uint32_t MMSEL      : 3;
            volatile uint32_t TI1SEL     : 1;
            volatile uint32_t OC1OIS     : 1;
            volatile uint32_t OC1NOIS    : 1;
            volatile uint32_t OC2OIS     : 1;
            volatile uint32_t OC2NOIS    : 1;
            volatile uint32_t OC3OIS     : 1;
            volatile uint32_t OC3NOIS    : 1;
            volatile uint32_t OC4OIS     : 1;
            volatile const  uint32_t RESERVED2  : 17;
        } CTRL2_B;
    } ;

     
    union
    {
        volatile uint32_t SMCTRL;

        struct
        {
            volatile uint32_t SMFSEL     : 3;
            volatile uint32_t OCCSEL     : 1;
            volatile uint32_t TRGSEL     : 3;
            volatile uint32_t MSMEN      : 1;
            volatile uint32_t ETFCFG     : 4;
            volatile uint32_t ETPCFG     : 2;
            volatile uint32_t ECEN       : 1;
            volatile uint32_t ETPOL      : 1;
            volatile const  uint32_t RESERVED1  : 16;
        } SMCTRL_B;
    } ;

     
    union
    {
        volatile uint32_t DIEN;

        struct
        {
            volatile uint32_t UIEN       : 1;
            volatile uint32_t CC1IEN     : 1;
            volatile uint32_t CC2IEN     : 1;
            volatile uint32_t CC3IEN     : 1;
            volatile uint32_t CC4IEN     : 1;
            volatile uint32_t COMIEN     : 1;
            volatile uint32_t TRGIEN     : 1;
            volatile uint32_t BRKIEN     : 1;
            volatile uint32_t UDIEN      : 1;
            volatile uint32_t CC1DEN     : 1;
            volatile uint32_t CC2DEN     : 1;
            volatile uint32_t CC3DEN     : 1;
            volatile uint32_t CC4DEN     : 1;
            volatile uint32_t COMDEN     : 1;
            volatile uint32_t TRGDEN     : 1;
            volatile const  uint32_t RESERVED1  : 17;
        } DIEN_B;
    } ;

     
    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile uint32_t UIFLG      : 1;
            volatile uint32_t CC1IFLG    : 1;
            volatile uint32_t CC2IFLG    : 1;
            volatile uint32_t CC3IFLG    : 1;
            volatile uint32_t CC4IFLG    : 1;
            volatile uint32_t COMIFLG    : 1;
            volatile uint32_t TRGIFLG    : 1;
            volatile uint32_t BRKIFLG    : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t CC1RCFLG   : 1;
            volatile uint32_t CC2RCFLG   : 1;
            volatile uint32_t CC3RCFLG   : 1;
            volatile uint32_t CC4RCFLG   : 1;
            volatile const  uint32_t RESERVED2  : 19;
        } STS_B;
    } ;

     
    union
    {
        volatile  uint32_t CEG;

        struct
        {
            volatile  uint32_t UEG        : 1;
            volatile  uint32_t CC1EG      : 1;
            volatile  uint32_t CC2EG      : 1;
            volatile  uint32_t CC3EG      : 1;
            volatile  uint32_t CC4EG      : 1;
            volatile  uint32_t COMG       : 1;
            volatile  uint32_t TEG        : 1;
            volatile  uint32_t BEG        : 1;
            volatile const  uint32_t RESERVED1  : 24;
        } CEG_B;
    } ;

    union
    {
         
        union
        {
            volatile uint32_t CCM1_OUTPUT;

            struct
            {
                volatile uint32_t CC1SEL     : 2;
                volatile uint32_t OC1FEN     : 1;
                volatile uint32_t OC1PEN     : 1;
                volatile uint32_t OC1MOD     : 3;
                volatile uint32_t OC1CEN     : 1;
                volatile uint32_t CC2SEL     : 2;
                volatile uint32_t OC2FEN     : 1;
                volatile uint32_t OC2PEN     : 1;
                volatile uint32_t OC2MOD     : 3;
                volatile uint32_t OC2CEN     : 1;
                volatile const  uint32_t RESERVED1  : 16;
            } CCM1_OUTPUT_B;
        } ;

         
        union
        {
            volatile uint32_t CCM1_INPUT;

            struct
            {
                volatile uint32_t CC1SEL     : 2;
                volatile uint32_t IC1PSC     : 2;
                volatile uint32_t IC1F       : 4;
                volatile uint32_t CC2SEL     : 2;
                volatile uint32_t IC2PSC     : 2;
                volatile uint32_t IC2F       : 4;
                volatile const  uint32_t RESERVED1  : 16;
            } CCM1_INPUT_B;
        } ;
    };

    union
    {
         
        union
        {
            volatile uint32_t CCM2_OUTPUT;

            struct
            {
                volatile uint32_t CC3SEL     : 2;
                volatile uint32_t OC3FEN     : 1;
                volatile uint32_t OC3PEN     : 1;
                volatile uint32_t OC3MOD     : 3;
                volatile uint32_t OC3CEN     : 1;
                volatile uint32_t CC4SEL     : 2;
                volatile uint32_t OC4FEN     : 1;
                volatile uint32_t OC4PEN     : 1;
                volatile uint32_t OC4MOD     : 3;
                volatile uint32_t OC4CEN     : 1;
                volatile const  uint32_t RESERVED1  : 16;
            } CCM2_OUTPUT_B;
        } ;

         
        union
        {
            volatile uint32_t CCM2_INPUT;

            struct
            {
                volatile uint32_t CC3SEL     : 2;
                volatile uint32_t IC3PSC     : 2;
                volatile uint32_t IC3F       : 4;
                volatile uint32_t CC4SEL     : 2;
                volatile uint32_t IC4PSC     : 2;
                volatile uint32_t IC4F       : 4;
                volatile const  uint32_t RESERVED1  : 16;
            } CCM2_INPUT_B;
        } ;
    };

     
    union
    {
        volatile uint32_t CCEN;

        struct
        {
            volatile uint32_t CC1EN      : 1;
            volatile uint32_t CC1POL     : 1;
            volatile uint32_t CC1NEN     : 1;
            volatile uint32_t CC1NPOL    : 1;
            volatile uint32_t CC2EN      : 1;
            volatile uint32_t CC2POL     : 1;
            volatile uint32_t CC2NEN     : 1;
            volatile uint32_t CC2NPOL    : 1;
            volatile uint32_t CC3EN      : 1;
            volatile uint32_t CC3POL     : 1;
            volatile uint32_t CC3NEN     : 1;
            volatile uint32_t CC3NPOL    : 1;
            volatile uint32_t CC4EN      : 1;
            volatile uint32_t CC4POL     : 1;
            volatile const  uint32_t RESERVED1  : 18;
        } CCEN_B;
    } ;

     
    union
    {
        volatile uint32_t CNT;

        struct
        {
            volatile uint32_t CNT        : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CNT_B;
    } ;

     
    union
    {
        volatile uint32_t PSC;

        struct
        {
            volatile uint32_t PSC        : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } PSC_B;
    } ;

     
    union
    {
        volatile uint32_t AUTORLD;

        struct
        {
            volatile uint32_t AUTORLD    : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } AUTORLD_B;
    } ;

     
    union
    {
        volatile uint32_t REPCNT;

        struct
        {
            volatile uint32_t REPCNT     : 8;
            volatile const  uint32_t RESERVED1  : 24;
        } REPCNT_B;
    } ;

     
    union
    {
        volatile uint32_t CC1;

        struct
        {
            volatile uint32_t CC1        : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CC1_B;
    } ;

     
    union
    {
        volatile uint32_t CC2;

        struct
        {
            volatile uint32_t CC2        : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CC2_B;
    } ;

     
    union
    {
        volatile uint32_t CC3;

        struct
        {
            volatile uint32_t CC3        : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CC3_B;
    } ;

     
    union
    {
        volatile uint32_t CC4;

        struct
        {
            volatile uint32_t CC4        : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } CC4_B;
    } ;

     
    union
    {
        volatile uint32_t BDT;

        struct
        {
            volatile uint32_t DTS        : 8;
            volatile uint32_t LOCKCFG    : 2;
            volatile uint32_t IMOS       : 1;
            volatile uint32_t RMOS       : 1;
            volatile uint32_t BRKEN      : 1;
            volatile uint32_t BRKPOL     : 1;
            volatile uint32_t AOEN       : 1;
            volatile uint32_t MOEN       : 1;
            volatile const  uint32_t RESERVED1  : 16;
        } BDT_B;
    } ;

     
    union
    {
        volatile uint32_t DCTRL;

        struct
        {
            volatile uint32_t DBADDR     : 5;
            volatile const  uint32_t RESERVED1  : 3;
            volatile uint32_t DBLEN      : 5;
            volatile const  uint32_t RESERVED2  : 19;
        } DCTRL_B;
    } ;

     
    union
    {
        volatile uint32_t DMADDR;

        struct
        {
            volatile uint32_t DMADDR     : 16;
            volatile const  uint32_t RESERVED1  : 16;
        } DMADDR_B;
    } ;

     
    union
    {
        volatile uint32_t OPT;

        struct
        {
            volatile uint32_t RMPSEL     : 2;
            volatile const  uint32_t RESERVED1  : 30;
        } OPT_B;
    } ;
} TMR_T;



 

typedef struct
{
     
    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t UEN        : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t RXEN       : 1;
            volatile uint32_t TXEN       : 1;
            volatile uint32_t IDLEIEN    : 1;
            volatile uint32_t RXBNEIEN   : 1;
            volatile uint32_t TXCIEN     : 1;
            volatile uint32_t TXBEIEN    : 1;
            volatile uint32_t PEIEN      : 1;
            volatile uint32_t PCFG       : 1;
            volatile uint32_t PCEN       : 1;
            volatile uint32_t WUPMCFG    : 1;
            volatile uint32_t DBLCFG0    : 1;
            volatile uint32_t RXMUTEEN   : 1;
            volatile uint32_t CMIEN      : 1;
            volatile uint32_t OSMCFG     : 1;
            volatile uint32_t DDLTEN     : 5;
            volatile uint32_t DLTEN      : 5;
            volatile uint32_t RXTOIEN    : 1;
            volatile const  uint32_t RESERVED2  : 1;
            volatile const  uint32_t RESERVED3  : 4;
        } CTRL1_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile const  uint32_t RESERVED1  : 4;
            volatile uint32_t ADDRLEN    : 1;
            volatile const  uint32_t RESERVED2  : 3;
            volatile uint32_t LBCPOEN    : 1;
            volatile uint32_t CPHA       : 1;
            volatile uint32_t CPOL       : 1;
            volatile uint32_t CLKEN      : 1;
            volatile uint32_t STOPCFG    : 2;
            volatile const  uint32_t RESERVED3  : 1;
            volatile uint32_t SWAPEN     : 1;
            volatile uint32_t RXINVEN    : 1;
            volatile uint32_t TXINVEN    : 1;
            volatile uint32_t BINVEN     : 1;
            volatile uint32_t MSBFEN     : 1;
            volatile uint32_t ABRDEN     : 1;
            volatile uint32_t ABRDCFG    : 2;
            volatile uint32_t RXTODEN    : 1;
            volatile uint32_t ADDRL      : 4;
            volatile uint32_t ADDRH      : 4;
        } CTRL2_B;
    } ;

     
    union
    {
        volatile uint32_t CTRL3;

        struct
        {
            volatile uint32_t ERRIEN     : 1;
            volatile const  uint32_t RESERVED1  : 2;
            volatile uint32_t HDEN       : 1;
            volatile const  uint32_t RESERVED2  : 2;
            volatile uint32_t DMARXEN    : 1;
            volatile uint32_t DMATXEN    : 1;
            volatile uint32_t RTSEN      : 1;
            volatile uint32_t CTSEN      : 1;
            volatile uint32_t CTSIEN     : 1;
            volatile uint32_t SAMCFG     : 1;
            volatile uint32_t OVRDEDIS   : 1;
            volatile uint32_t DDISRXEEN  : 1;
            volatile uint32_t DEN        : 1;
            volatile uint32_t DPCFG      : 1;
            volatile const  uint32_t RESERVED3  : 16;
        } CTRL3_B;
    } ;

     
    union
    {
        volatile uint32_t BR;

        struct
        {
            volatile uint32_t FBR        : 4;
            volatile uint32_t IBR        : 12;
            volatile const  uint32_t RESERVED1  : 16;
        } BR_B;
    } ;

    volatile const  uint32_t  RESERVED1;
     
    union
    {
        volatile uint32_t RXTO;

        struct
        {
            volatile uint32_t RXTO       : 24;
            volatile const  uint32_t RESERVED1  : 8;
        } RXTO_B;
    } ;

     
    union
    {
        volatile uint32_t REQUEST;

        struct
        {
            volatile uint32_t ABRDQ      : 1;
            volatile uint32_t TXBFQ      : 1;
            volatile uint32_t MUTEQ      : 1;
            volatile uint32_t RXDFQ      : 1;
            volatile const  uint32_t RESERVED1  : 28;
        } REQUEST_B;
    } ;

     
    union
    {
        volatile const  uint32_t STS;

        struct
        {
            volatile const  uint32_t PEFLG      : 1;
            volatile const  uint32_t FEFLG      : 1;
            volatile const  uint32_t NEFLG      : 1;
            volatile const  uint32_t OVREFLG    : 1;
            volatile const  uint32_t IDLEFLG    : 1;
            volatile const  uint32_t RXBNEFLG   : 1;
            volatile const  uint32_t TXCFLG     : 1;
            volatile const  uint32_t TXBEFLG    : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile const  uint32_t CTSFLG     : 1;
            volatile const  uint32_t CTSCFG     : 1;
            volatile const  uint32_t RXTOFLG    : 1;
            volatile const  uint32_t RESERVED2  : 2;
            volatile const  uint32_t ABRDEFLG   : 1;
            volatile const  uint32_t ABRDFLG    : 1;
            volatile const  uint32_t BSYFLG     : 1;
            volatile const  uint32_t CMFLG      : 1;
            volatile const  uint32_t TXBFFLG    : 1;
            volatile const  uint32_t RXWFMUTE   : 1;
            volatile const  uint32_t RESERVED3  : 12;
        } STS_B;
    } ;

     
    union
    {
        volatile uint32_t INTFCLR;

        struct
        {
            volatile uint32_t PECLR      : 1;
            volatile uint32_t FECLR      : 1;
            volatile uint32_t NECLR      : 1;
            volatile uint32_t OVRECLR    : 1;
            volatile uint32_t IDLECLR    : 1;
            volatile const  uint32_t RESERVED1  : 1;
            volatile uint32_t TXCCLR     : 1;
            volatile const  uint32_t RESERVED2  : 2;
            volatile uint32_t CTSCLR     : 1;
            volatile const  uint32_t RESERVED3  : 1;
            volatile uint32_t RXTOCLR    : 1;
            volatile const  uint32_t RESERVED4  : 5;
            volatile uint32_t CMCLR      : 1;
            volatile const  uint32_t RESERVED6  : 14;
        } INTFCLR_B;
    } ;

     
    union
    {
        volatile const  uint32_t RXDATA;

        struct
        {
            volatile const  uint32_t RXDATA     : 9;
            volatile const  uint32_t RESERVED1  : 23;
        } RXDATA_B;
    } ;

     
    union
    {
        volatile uint32_t TXDATA;

        struct
        {
            volatile uint32_t TXDATA     : 9;
            volatile const  uint32_t RESERVED1  : 23;
        } TXDATA_B;
    } ;
} USART_T;



 

typedef struct
{
    union
    {
         
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t CNT        : 7;
            volatile uint32_t WWDTEN     : 1;
            volatile const  uint32_t RESERVED1  : 24;
        } CTRL_B;
    } ;

    union
    {
         
        volatile uint32_t CFG;

        struct
        {
            volatile uint32_t WIN        : 7;
            volatile uint32_t TBPSC      : 2;
            volatile uint32_t EWIEN      : 1;
            volatile const  uint32_t RESERVED1  : 22;
        } CFG_B;
    } ;

    union
    {
         
        volatile uint32_t STS;

        struct
        {
            volatile uint32_t EWIFLG     : 1;
            volatile const  uint32_t RESERVED1  : 31;
        } STS_B;
    } ;
} WWDT_T;


 



 

 

 

 

 


 




# 3586 "..\\Src\\apm32e030.h"

# 3597 "..\\Src\\apm32e030.h"

# 3604 "..\\Src\\apm32e030.h"












 



 

# 3640 "..\\Src\\apm32e030.h"

# 3647 "..\\Src\\apm32e030.h"







# 3661 "..\\Src\\apm32e030.h"

 



 

 
# 3701 "..\\Src\\apm32e030.h"















 







 
 
# 28 "..\\Src\\system_apm32e030.c"
# 1 "..\\Driver\\APM32E030_StdPeriphDriver\\inc\\apm32e030_fmc.h"























 

 







 
# 36 "..\\Driver\\APM32E030_StdPeriphDriver\\inc\\apm32e030_fmc.h"



 



 



 

 

 


 






 



 
 
# 84 "..\\Driver\\APM32E030_StdPeriphDriver\\inc\\apm32e030_fmc.h"

 



 




 



 
typedef enum
{
    FMC_LATENCY_0,                            
    FMC_LATENCY_1,                            
    FMC_LATENCY_2                             
} FMC_LATENCY_T;



 
typedef enum
{
    FMC_FLAG_BUSY = ((uint8_t)0x01),          
    FMC_FLAG_PE   = ((uint8_t)0x04),          
    FMC_FLAG_WPE  = ((uint8_t)0x10),          
    FMC_FLAG_OC   = ((uint8_t)0x20),          
} FMC_FLAG_T;



 
typedef enum
{
    FMC_STATE_COMPLETE = ((uint8_t)0),        
    FMC_STATE_BUSY     = ((uint8_t)1),        
    FMC_STATE_PG_ERR   = ((uint8_t)2),        
    FMC_STATE_WRP_ERR  = ((uint8_t)3),        
    FMC_STATE_TIMEOUT  = ((uint8_t)4),        
} FMC_STATE_T;



 
typedef enum
{
    FMC_INT_ERROR = ((uint32_t)0x400),        
    FMC_INT_COMPLETE  = ((uint32_t)0x1000),   
} FMC_INT_T;



 
typedef enum
{
    FMC_RDP_LEVEL_0 = ((uint8_t)0xAA),        
    FMC_RDP_LEVEL_1 = ((uint8_t)0xBB),        
} FMC_RDP_T;



 
typedef enum
{
    FMC_OB_IWDT_HW    = ((uint8_t)0X00),      
    FMC_OB_IWDT_SW    = ((uint8_t)0X01),      
} FMC_OB_IWDT_T;



 
typedef enum
{
    FMC_OB_STOP_RESET = ((uint8_t)0X00),      
    FMC_OB_STOP_NRST  = ((uint8_t)0X02),      
} FMC_OB_STOP_T;



 
typedef enum
{
    FMC_OB_STDBY_RESET = ((uint8_t)0X00),     
    FMC_OB_STDBY_NRST  = ((uint8_t)0X04),     
} FMC_OB_STDBY_T;



 
typedef enum
{
    FMC_OB_BOOT0_RESET  = ((uint8_t)0X00),    
    FMC_OB_BOOT0_SET = ((uint8_t)0X08),       
} FMC_OB_BOOT0_T;



 
typedef enum
{
    FMC_OB_BOOT1_RESET    = ((uint8_t)0X00),  
    FMC_OB_BOOT1_SET      = ((uint8_t)0X10),  
} FMC_OB_BOOT1_T;



 
typedef enum
{
    FMC_OB_VDDA_ANALOG_OFF = ((uint8_t)0X00),  
    FMC_OB_VDDA_ANALOG_ON  = ((uint8_t)0X20),  
} FMC_OB_VDDA_ANALOG_T;



 
typedef enum
{
    FMC_OB_SRAM_PARITY_SET    = ((uint8_t)0X00),  
    FMC_OB_SRAM_PARITY_RESET  = ((uint8_t)0X40),  
} FMC_OB_SRAM_PARITY_T;



 
typedef enum
{
    FMC_OB_BOOT0_SW   = ((uint8_t)0X00),      
    FMC_OB_BOOT0_HW   = ((uint8_t)0X80),      
} FMC_OB_BOOT0SW_T;

 



 



 
typedef struct
{
    FMC_OB_IWDT_T  iwdtSw;
    FMC_OB_STOP_T  stopce;
    FMC_OB_STDBY_T stdbyce;
} FMC_UserConfig_T;

 



 

 



 

 

 
void FMC_SetLatency(FMC_LATENCY_T latency);

 
void FMC_EnablePrefetchBuffer(void);
void FMC_DisablePrefetchBuffer(void);
uint8_t FMC_ReadPrefetchBufferStatus(void);

 
void FMC_Unlock(void);
void FMC_Lock(void);

 
FMC_STATE_T FMC_ErasePage(uint32_t pageAddr);
FMC_STATE_T FMC_EraseAllPages(void);

FMC_STATE_T FMC_ProgramWord(uint32_t addr, uint32_t data);
FMC_STATE_T FMC_ProgramHalfWord(uint32_t addr, uint16_t data);

 
void FMC_UnlockOptionByte(void);
void FMC_LockOptionByte(void);
void FMC_LaunchOptionByte(void);
FMC_STATE_T FMC_EraseOptionByte(void);
FMC_STATE_T FMC_EnableWriteProtection(uint32_t page);
FMC_STATE_T FMC_ConfigReadOutProtection(FMC_RDP_T rdp);
FMC_STATE_T FMC_ConfigOptionByteUser(FMC_UserConfig_T* userConfig);
FMC_STATE_T FMC_EnableOptionByteBOOT(void);
FMC_STATE_T FMC_DisableOptionByteBOOT(void);
FMC_STATE_T FMC_EnableOptionByteVDDA(void);
FMC_STATE_T FMC_DisableOptionByteVDDA(void);
FMC_STATE_T FMC_EnableOptionByteSRAMParity(void);
FMC_STATE_T FMC_DisableOptionByteSRAMParity(void);
FMC_STATE_T FMC_WriteOptionByteUser(uint8_t ob_user);
FMC_STATE_T FMC_ProgramOptionByteData(uint32_t addr, uint8_t data);
uint8_t FMC_ReadOptionByteUser(void);
uint32_t FMC_ReadOptionByteWriteProtection(void);
uint8_t FMC_GetReadProtectionStatus(void);

 
void FMC_EnableInterrupt(uint32_t interrupt);
void FMC_DisableInterrupt(uint32_t interrupt);
uint8_t FMC_ReadStatusFlag(FMC_FLAG_T flag);
void FMC_ClearStatusFlag(uint8_t flag);

 
FMC_STATE_T FMC_ReadState(void);
FMC_STATE_T FMC_WaitForReady(uint32_t timeOut);







 
 
 
# 29 "..\\Src\\system_apm32e030.c"



 



 



 

 


 






 




 



 

 



 

 



 

# 84 "..\\Src\\system_apm32e030.c"
    uint32_t SystemCoreClock         = (72000000);




static void SystemClockConfig(void);

# 100 "..\\Src\\system_apm32e030.c"
    static void SystemClock72M(void);



 



 









 
void SystemInit(void)
{
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL1_B.HSIEN = BIT_SET;
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1 &= (uint32_t)0x08FFB80CU;
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL1 &= (uint32_t)0xFEF6FFFFU;
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL1_B.HSEBCFG = BIT_RESET;
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1 &= (uint32_t)0xFFC0FFFFU;
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1 &= (uint32_t)0xFFFFFFF0U;
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG3 &= (uint32_t)0xFFFFFEAC;
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL2_B.HSI14EN = BIT_RESET;
     
    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->INT = 0x00000000U;

    SystemClockConfig();




    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR = ((uint32_t)0x08000000) | 0x00;

}










 
void SystemCoreClockUpdate(void)
{
    uint32_t sysClock, pllMull, pllSource, Prescaler;
    uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

     
    sysClock = ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.SCLKSWSTS;

    switch (sysClock)
    {
        case 0:
            SystemCoreClock = ((uint32_t)8000000);
            break;

         
        case 1:
            SystemCoreClock = ((uint32_t)8000000);
            break;

         
        case 2:
            pllMull = ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.PLLMULCFG + 2;
            pllSource = ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.PLLSRCSEL;

             
            if (pllSource == 1)
            {
                SystemCoreClock = ((uint32_t)8000000) * pllMull;

                 
                if (((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.PLLHSEPSC)
                {
                    SystemCoreClock >>= 1;
                }
            }
             
            else
            {
                SystemCoreClock = (((uint32_t)8000000) >> 1) * pllMull;
            }

            break;

        default:
            SystemCoreClock  = ((uint32_t)8000000);
            break;
    }

    Prescaler = AHBPrescTable[(((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.AHBPSC)];
    SystemCoreClock >>= Prescaler;
}








 
static void SystemClockConfig(void)
{
# 230 "..\\Src\\system_apm32e030.c"
    SystemClock72M();

}

# 451 "..\\Src\\system_apm32e030.c"









 
static void SystemClock72M(void)
{
    uint32_t i;

    ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL1_B.HSEEN = BIT_SET;

    for (i = 0; i < ((uint32_t)0x10000); i++)
    {
        if (((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL1_B.HSERDYFLG)
        {
            break;
        }
    }

    if (((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL1_B.HSERDYFLG)
    {
         
        ((FMC_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00002000))->CTRL1_B.PBEN = BIT_SET;
         
        do{((FMC_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00002000))->CTRL1_B . WS = 1; ((FMC_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00002000))->CTRL1_B . WS = 2;}while(0);

         
        ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.AHBPSC = 0X00;

         
        ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.APB1PSC = 0X00;

         
        ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.PLLSRCSEL = 1;
        ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.PLLMULCFG = 7;

         
        ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL1_B.PLLEN = 1;

         
        while (((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CTRL1_B.PLLRDYFLG == BIT_RESET);

         
        ((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.SCLKSEL = 2;

         
        while (((RCM_T*) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFG1_B.SCLKSWSTS != 0x02);
    }
}



 
 
 
