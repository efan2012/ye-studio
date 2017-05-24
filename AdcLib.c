#include "AdcLib.h"
/**
   @简介 AdcGo(int iTEN, int iSpeed, int iTime, int iStart, int iPower, int iMode, int iType);
         ========== 设置ADC采样配置，包括转换模式\转换类型\采样时间\时钟速率等
   @参数 iTEN :{0x0,0x1}
        - 0x0 正常采样转换
        - 0x1 温度采样转换和单次采样软件转换
        iSpeed :{0-5}
        - ADC时钟速率
        - 0 fadc/1
        - 1 fadc/2
        - 2 fadc/4
        - 3 fadc/8
        - 4 fadc/16
        - 5 fadc/32
        iTime :{0-3}
        - 采集时间
        - 0 2个时钟
        - 1 4个时钟
        - 2 8个时钟
        - 3 16个时钟
        iStart :{0x0,0x1}
        - 转换启动使能
        - 0x0 禁用转换启动
        - 0x1 启动任意类型的启动
        iPower :{0x0,0x1}
        - ADC电源控制
        - 0x0 掉电模式
        - 0x1 正常模式
        iMode :{0-3}
        - 转换模式
        - 0 单端模式
        - 1 差分模式
        - 2 伪差分模式 保留
        - 3 保留
        iType :{0-5}
        - 转换类型
        - 0 CONVSTART 引脚作为转换使能信号
        - 1 定时器1输出作为转换使能信号
        - 2 定时器0输出作为转换使能信号
        - 3 单次软件转换 转换后设为000，即CONVSTART 引脚再一次触发转换
        - 4 连续软件转换
        - 5 PLA转换
   @返回值 1 命令成功执行
**/

int AdcGo(int iTEN, int iSpeed, int iTime, int iStart, int iPower, int iMode, int iType)
{
  int i = 0;
  i += (iTEN << 13);
  i += (iSpeed << 10);
  i += (iTime << 8);
  i += (iStart << 7);
  i += (iPower << 5);
  i += (iMode << 3);
  i += iType;
  ADCCON = i;
  return 1;
}

/**
   @简介 int AdcPin(int iInN, int iInP);
         ========== ADC通道选择
   @参数 iInN :{0-19} 具体范围视芯片类型而定
   - 反向通道选择位
   - 0 ADC0
   - 1 ADC1
   - 2 ADC2
   - 3 ADC3
   - 4 ADC4
   - 5 ADC5
   - 6 ADC6
   - 7 ADC7
   - 8 ADC8
   - 9 ADC9
   - 10 ADC10
   - 11 ADC11 保留
   - 12 ADC12
   - 13 ADC13 保留
   - 14 ADC14 保留
   - 15 DAC1
   - 16 温度传感器
   - 17 AGND (自诊断特性)
   - 18 内部基准电压(自诊断特性)

         iInP :{0-19}
   - 正向通道选择位
   - 0 ADC0
   - 1 ADC1
   - 2 ADC2
   - 3 ADC3
   - 4 ADC4
   - 5 ADC5
   - 6 ADC6
   - 7 ADC7
   - 8 ADC8
   - 9 ADC9
   - 10 ADC10
   - 11 ADC11 保留
   - 12 ADC12
   - 13 ADC13 保留
   - 14 DAC0
   - 15 DAC1
   - 16 温度传感器
   - 17 AGND (自诊断特性)
   - 18 内部基准电压(自诊断特性)
   - 19 AVDD/2

   @返回值 1 命令成功执行
**/

int AdcPin(int iInN, int iInP)
{
   ADCCN = iInN;
   ADCCP = iInP;
   return 1;
}

/**
   @简介 int AdcCal(int iGain, int iOffset);
         ========== ADC采样校准
   @参数 iGain :{0-1024}
      - 增益校准
        iOffset :{0-1024}
      - 失调校准
   @返回值 1 命令成功执行
**/

int AdcCal(int iGain, int iOffset)
{
   ADCGN = iGain;
   ADCOF = iOffset;
   return 1;
}

/**
   @简介 int AdcRd(void);
         ========== 读取采样值
   @返回值 ADCDAT
**/

int AdcRd(void)
{
   return ADCDAT;
 }

 /**
    @简介 int AdcRst(int iReset);
          ========== 重置ADC采样
    @参数 iReset :{}
        - 任意值，重置ADC采样
    @返回值 1 命令执行成功
 **/

 int AdcRst(int iReset)
 {
   ADCRST = iReset;
   return 1;
 }

int AdcRESet(void)
{
  REFCON = 0x1;
  return 1;
}
