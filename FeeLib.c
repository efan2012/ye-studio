#include "FeeLib.h"
/**
   @简介 int FeeSR(unsigned long ulAddr);
      ========== 读取指定地址的16位数据

   @参数 ulAddr :{0x00080000-0x0008ffff}
      - 指定读取数据的地址
   @返回值 0 FLASH/EE控制器忙
          1 命令成功执行
**/

int FeeSR(unsigned long ulAddr)
{
  if((FEESTA&0x4)!=0) return 0;
  FEEADR = ulAddr;
  FEECON = 0x1;
  return FEEDAT;
}

/**
   @简介 int FeeSW(int iData,unsigned long ulAddr);
      ========== 单次写入16位数据到指定地址

   @参数 ulAddr :{0x00080000-0x0008ffff}
      - 指定写入数据的地址
   @返回值 0 FLASH/EE控制器忙
          1 命令成功执行
**/

int FeeSW(int iData, unsigned long ulAddr)
{
  if((FEESTA&0x4)!=0) return 0;
  FEEDAT = iData;
  FEEADR = ulAddr;
  FEEMOD |= 0x8;
  FEECON = 0x2;
  return 1;
}

/**
   @简介 int FeeEW(int iData,unsigned long ulAddr);
      ========== 擦除指定地址的数据后，单次写入16位数据到指定地址

   @参数 ulAddr :{0x00080000-0x0008ffff}
      - 指定写入数据的地址
   @返回值 0 FLASH/EE控制器忙
          1 命令成功执行
**/

int FeeEW(int iData, unsigned long ulAddr)
{
  if((FEESTA&0x4)!=0) return 0;
  FEEDAT = iData;
  FEEADR = ulAddr;
  FEEMOD |= 0x8;
  FEECON = 0x3;
  return 1;
}

/**
   @简介 int FeeSV(int iData,unsigned long ulAddr);
      ========== 验证指定地址的数据
   @参数 ulAddr :{0x00080000-0x0008ffff}
      - 指定写入数据的地址
   @返回值 0 FLASH/EE控制器忙
          1 数据无误
          2 数据有误
**/

int FeeSV(int iData, unsigned long ulAddr)
{
  if((FEESTA&0x4)!=0) return 0;
  FEEDAT = iData;
  FEEADR = ulAddr;
  FEECON = 0x4;
  if ((FEESTA&0X1)!=0)
  {
    return 1;
  } else {
    return 2;
  }
}

/**
   @简介 int FeePErs(unsigned long ulAddr);
      ========== 擦除指定地址所在的页

   @参数 ulAddr :{0x00080000-0x0008ffff}
      - 指定擦除数据的地址
   @返回值 0 FLASH/EE控制器忙
          1 命令成功执行
**/

int FeePErs(unsigned long ulAddr)
{
  if((FEESTA&0x4)!=0) return 0;
  FEEADR = ulAddr;
  FEEMOD |= 0x8;
  FEECON = 0x05;
  return 1;
}

/**
   @简介 int FeeMErs(void);
      ========== 执行块擦除操作

   @返回值 0 FLASH/EE控制器忙
          1 命令成功执行
**/

int FeeMErs(void)
{
  if((FEESTA&0x4)!=0) return 0;
  FEEDAT = 0x3cff;
  FEEADR = 0xffc3;
  FEEMOD |= 0x8;
  FEECON = 0x06;
  return 1;
}

/**
   @简介 int FeeSta(void);
      ========== 读取FEESTA寄存器值

   @返回值 FEESTA 寄存器值
**/

int FeeSta(void)
{
  return FEESTA;
}

/**
   @简介 int FeeSta(void);
      ========== 开启/关闭 FLASH/EE 中断使能开关
   @参数 iEnable :{0x0-0x1}
         - 1 开启中断使能开关
         - 0 关闭中断使能开关
   @返回值 1 命令成功执行
**/

int FeeIntCfg(int iEnable)
{
  if (iEnable)
  {
    FEEMOD |= 0x10;
  } else {
    FEEMOD &= 0xef;
  }
  return 1;
}
/**
   @简介 int FeePro(int iMode,int iPage);
      ========== 执行页保护的操作
   @参数 iMode :{0x0-0x2}
         - 0x0 临时保护指定页
         - 0x1 采用密钥保护模式保护指定页
         - 0x2 特定密钥永久保护闪存中数据
         iPage :{0x0-0x123}
         - 指定保护的页
   @返回值 1 命令成功执行
**/
int FeePro(int iMode, int iPage)
{
  int a = iPage/4;
  switch (iMode){
    case 0:
    FEEHIDE &= ~(0x1 << a); //31位清0，保护所有代码 0-30位清零页写保护，每位保护4页
    break;

    case 1: break;
    case 2: break;
    default : break;
  }
  return 1;
}
