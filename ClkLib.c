#include "ClkLib.h"
/**
   @简介 int Pllcfg(int OSEL,int MDCLK);
      ========== 配置时钟系统的工作模式

   @参数 OSEL :{0x0,0x1}
      - 0 使用外部32KHz晶振
      - 1 使用内部32KHz晶振
        MDCLK ：{0x1,0x3}
      - 0x1 PLL,默认配置
      - 0x3 P0.7引脚上的外部时钟
   @返回值 1 命令成功执行
**/

int Pllcfg(int OSEL,int MDCLK)
{
  PLLKEY1 = 0xAA;
  PLLCON = (OSEL << 5) + MDCLK;
  PLLKEY2 = 0x55;
  return 1;
}
/**
   @简介 int Powcfg(int PC,int CD);
      ========== 配置内核时钟频率及掉电模式

   @参数 PC :{0x0-0x4}
      - 0x0 活动模式
      - 0x1 暂停模式
      - 0x2 浅休眠
      - 0x3 休眠模式 外部中断和定时器2可以唤醒该器件
      - 0x4 停止模式 外部中断可以唤醒该器件
        CD ：{0x0-0x7}
      - 0x0 41.78MHz
      - 0x1 20.89MHz
      - 0X2 10.44MHz
      - 0x3 5.22MHz
      - 0x4 2.61MHz
      - 0x5 1.31MHz
      - 0x6 653kHz
      - 0x7 326kHz
   @返回值 1 命令成功执行
**/

int Powcfg(int PC,int CD)
{
  POWKEY1 = 0x1;
  POWCON = (PC << 5) + CD;
  POWKEY2 = 0xF4;
  return 1;
}
