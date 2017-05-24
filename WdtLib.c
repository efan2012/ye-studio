#include "I2cLib.h"
/**
   @简介 int WdtLd(int iTld);
      ========== 设定定时器的重载值

   @参数 iTld :{0-0xffff}
      - 计时器重载值
   @返回值 1 命令成功执行
**/

int WdtLd(int iTld)
{
   T2LD = iTld;
   return 1;
}

/**
   @简介 int WdtVal(void);
         ========== 读取定时器值
   @返回值 计时器值 T3VAL.
**/

int WdtVal(void)
{
   return T2VAL;
}

/**
   @简介 int WdtCfg(int iMod, int iPre, int iInt, int iPd);
         ========== 配置定时器3的配置寄存器
   @参数 iCount :{}
        -
        iEnable :{}
        -
        iMod :{}
        iWMod :{}
        iSecu :{}
        iPre :{}
        iInt :{}

   @返回值 1 命令成功执行
**/

int WdtCfg(int iCount, int iEnable, int iMod, int iWMod,int iSecu, int iPre, int iInt)
{
   int	i1;
   i1 |= iCount;
   i1 |= iEnable;
   i1 |= iMod;
   i1 |= iWMod;
   i1 |= iSecu;
   i1 |= iPre;
   i1 |= iInt;
   T2CON = i1;
   return 1;
}
