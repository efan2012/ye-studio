#include "I2cLib.h"
/**
   @简介 int I2cMCfg(int iChannel, int iIntSources, int iConfig);
      ========== 配置I2C主机通道

   @参数 iChannel :{0x0,0x1}
        -0x0 I2C0通道
        -0x0 I2C1通道
      iIntSources :{0|I2CMCON_IENCMP_EN|I2CMCON_IENACK_EN|I2CMCON_IENALOST_EN|I2CMCON_IENMTX_EN|I2CMCON_IENMRX_EN}
        - 0 默认值禁用所有的中断源
        - (0x1 << 8) 传输完成时产生中断
        - (0x1 << 7) 主机没有收到应答时产生中断
        - (0x1 << 6) 主机失去对I2C总线的控制时产生中断
        - (0x1 << 5)  主机传输一个字节时产生中断
        - (0x1 << 4)  主机接收数据时产生中断
      iConfig :{0|I2CMCON_LOOPBACK_EN|I2CMCON_COMPETE_EN|I2CMCON_MASEN_EN}
        - 0 by default.
        - (0x1 << 2) 开启回环测试模式
        - (0x1 << 1) 允许设备抢占总线的控制
        - 0x1  开启I2C主机模式

   @返回值 1 命令成功执行
**/

int I2cMCfg(int iChannel, int iIntSources, int iConfig)
{
  int i1;
  i1 |= iIntSources;
  i1 |= iConfig;
  if (iChannel)
  {
    I2C1MCON = i1;
  } else {
    I2C0MCON = i1;
  }
  return 1;
}

/**
	@简介 int I2cSCfg(int iChannel, int iIntSources, int iConfig);
			========== 配置I2C从机通道
   @参数 iChannel :{0x0,0x1}
		- 0x0  I2C0通道
		- 0x1  I2C1通道
         iIntSources :{0|I2CSCON_IENREPST_EN|I2CSCON_IENSTX_EN|I2CSCON_IENSRX_EN|I2CSCON_IENSTOP_EN}
		- 0 by default to disable all interrupt sources. 0 默认禁用所有的中断源
		- I2CSCON_IENREPST_EN to enable interrupts when a repeated Start condition is detected. I2CSCON_IENREPST_DIS by default.从机传输1字节数据时产生中断
		- I2CSCON_IENSTX_EN to enable Transmit interrupts. I2CSCON_IENSTX_DIS by default. 从机接收数据时产生中断
		- I2CSCON_IENSRX_EN to enable Receive interrupts. I2CSCON_IENSRX_DIS by default. 检测到传输完成，即停止信号时产生中断
		- I2CSCON_IENSTOP_EN to enable interrupts when Stop condition is detected. I2CSCON_IENSTOP_DIS by default.
	       iConfig :{0|I2CSCON_NACK_EN|I2CSCON_EARLYTXR_EN|I2CSCON_GCSBCLR_EN|I2CSCON_HGCEN_EN|I2CSCON_GCEN_EN|I2CSCON_ADR10EN_EN|I2CSCON_SLVEN_EN}
		- 0 by default.
		- I2CSCON_NACK_EN to force NACK after next byte. I2CSCON_NACK_DIS by default.
		- I2CSCON_EARLYTXR_EN to enable early transmit request. I2CSCON_EARLYTXR_DIS by default.
		- I2CSCON_GCSBCLR_EN to clear general call status register.
		- I2CSCON_HGCEN_EN to enable Hardware general calls. I2CSCON_HGCEN_DIS by default.
		- I2CSCON_GCEN_EN to enable general calls. I2CSCON_GCEN_DIS by default.
		- I2CSCON_ADR10EN_EN to enable 10-bit addresses. I2CSCON_ADR10EN_DIS by default.
		- I2CSCON_SLVEN_EN to enable Slave mode. I2CSCON_SLVEN_DIS by default.
**/

int I2cSCfg(int iChannel, int iIntSources, int iConfig)
{
  int i1;
  i1 |= iIntSources;
  i1 |= iConfig;
  if (iChannel){
  I2C1SCON = i1;
  } else {
  I2C0SCON = i1;
  }

  return 1;
}

/**
   @简介 int I2cFifoFlush(int iChannel,int iMode, int iFlush);
      ==========  清除主机模式 或 从机模式 Tx FIFO

   @参数 iChannel :{0x0,0x1}
      - 指定I2C通道 0x0 I2C0通道
                   0x1 I2C1通道
         iMode :{0x0,0x1}
      - 0X0 主机模式
      - 0x1 从机模式
      iFlush :{0x0,0x1}
      - 0x0 不清除Tx FIFO
      - 0x1  清除Tx FIFO
   @返回值 1 命令成功执行
**/

int I2cFifoFlush(int iChannel,int iMode, int iFlush)
{
  if (iMode == 1) // slave从机模式
  {
    if (iChannel)
    {
      if (iFlush == 1)
          I2C1FSTA |= 0x100;
      else
        I2C1FSTA &= 0xEFF;
    } else {
      if (iFlush == 1)
        I2C0FSTA |= 0x100;
      else
        I2C0FSTA &= 0xEFF;
    }
  } else      // master主机模式
    {
    if (iChannel)
    {
    if (iFlush == 1)
      I2C1FSTA |= 0x200;
    else
      I2C1FSTA &= 0xDFF;
    } else {
      if (iFlush == 1)
        I2C0FSTA |= 0x200;
      else
        I2C0FSTA &= 0xDFF;
    }
  }
  return 1;
}

/**
   @简介 int I2cRx(int iChannel,int iMode);
      ========== 从I2CxSRX或I2CxMRX读取8位数据

   @参数 iChannel :{0x0,0x1}
      - 指定I2C通道 0x0 I2C0通道
                   0x1 I2C1通道
         iMode :{0x0,0x1}
      - 0X0 主机模式
      - 0x1 从机模式
   @返回值 I2CxSRX或I2CxMRX 接收的字节
**/

int I2cRx(int iChannel,int iMode)
{
  int i1;

  i1 = iMode;
  if (iChannel)
  {
    if (i1 == 1)
    {
      return I2C1SRX;
    } else {
      return I2C1MRX;
    }
  } else {
    if (i1 == 1)
    {
      return I2C0SRX;
    }  else {
      return I2C0MRX;
    }
  }
}

/**
   @简介 int I2cTx(int iChannel,int iMode, int iTx);
      ========== 写8位的数据到I2CxMTX或I2CxSTX

   @参数 iChannel :{0x0,0x1}
      - 指定I2C通道 0x0 I2C0通道
                   0x1 I2C1通道
         iMode :{0x0,0x1}
      - 0X0 主机模式
      - 0x1 从机模式
          iTx :{0-255}
      - 传送的字节
   @返回值 1 命令成功执行
**/

int I2cTx(int iChannel,int iMode, int iTx)
{
  unsigned int i1;

  i1 = iTx;
    if (iChannel)
    {
      if (iMode == 1)
        I2C1STX = i1;
      else
        I2C1MTX = i1;
      return 1;
    } else {
      if (iMode == 1)
        I2C0STX = i1;
      else
        I2C0MTX = i1;
      return 1;
    }
}

/**
   @简介 int I2cBaud(int iChannel,int iHighPeriod, int iLowPeriod);
      ========== 配置主机模式时的时钟速率
                  100kHz iHighPeriod=iLowPeriod=0xCF
                  400kHz iHighPeriod=0x28 iLowPeriod=0x3C;
   @参数 iChannel :{0x0,0x1}
      - 指定I2C通道  0x0 为I2C0
                    0X1 为I2C1
      iHighPeriod :{0-255}
      - 主机时钟线"高"时间段
      iLowPeriod :{0-255}
      - 主机时钟线"高"时间段
   @返回值  1 命令成功执行
**/

int I2cBaud(int iChannel,int iHighPeriod, int iLowPeriod)
{
  unsigned int i1;

  i1 =  iLowPeriod;
  i1 |= (iHighPeriod << 8);
  if (iChannel)
  {
    I2C1DIV = i1;
  } else {
    I2C0DIV = i1;
  }
  return 1;
}

/**
   @简介 int I2cMWrCfg(int iChannel,unsigned int uiDevAddr);
      ========== 配置设备地址寄存器值
   @参数 iChannel :{0x0,0x1}
      - 指定I2C通道  0x0 为I2C0
                    0X1 为I2C1
        uiDevAddr :{0-1023}
      - 设定设备地址及读写位
   @返回值  1 命令成功执行
**/

int I2cMWrCfg(int iChannel,unsigned int uiDevAddr)
{
  if (iChannel)
  {
    uiDevAddr &= 0xFFFE;		// Ensure write bit is configured确保读/写位清零
    if (uiDevAddr > 0xFF)  	// Check for 10-bit address
    {
      I2C1ADR1 = (uiDevAddr & 0xFF);
      I2C1ADR0	= ((uiDevAddr >> 7) & 0x6) | 0xF0;
    }
    else //7-bit 地址
    {
      I2C1ADR0 = uiDevAddr & 0xFF;
      I2C1ADR1 = 0x00;
    }
  } else {
    uiDevAddr &= 0xFFFE;		// Ensure write bit is configured确保读/写位清零
    if (uiDevAddr > 0xFF)  	// Check for 10-bit address
    {
      I2C0ADR1 = (uiDevAddr & 0xFF);
      I2C0ADR0	= ((uiDevAddr >> 7) & 0x6) | 0xF0;
    }
    else //7-bit 地址
    {
      I2C0ADR0 = uiDevAddr & 0xFF;
      I2C0ADR1 = 0x00;
    }
  }
  return 1;
}

int I2C0SIDCfg(int iChannel,int iSlaveID0, int iSlaveID1,int iSlaveID2,int iSlaveID3)
{
  if (iChannel)
  {
    I2C1ID0 = iSlaveID0;
    I2C1ID1 = iSlaveID1;
    I2C1ID2 = iSlaveID2;
    I2C1ID3 = iSlaveID3;
  } else {
    I2C0ID0 = iSlaveID0;
    I2C0ID1 = iSlaveID1;
    I2C0ID2 = iSlaveID2;
    I2C0ID3 = iSlaveID3;
  }
  return 1;
}

/**
	@简介 int I2cSta(int iChannel,int iMode);
			========== 读取I2C主机或从机状态
	@参数 iChannel :{0x0,0x1}
		- 0x0 I2C0通道
		- 0x1 I2C1通道
   @param iMode :{MASTER, SLAVE}
		- 0 或 MASTER 主机模式
		- 1 或 SLAVE 从机模式
	@return value of I2CSSTA:
		- I2CSSTA.0 = Tx FIFO 状态
		- I2CSSTA.1 = I2C Tx FIFO 下溢(收到主机读命令，但FIFO为空)
		- I2CSSTA.2 = I2C Tx 请求
		- I2CSSTA.3 = I2C Rx 请求
		- I2CSSTA.4 = I2C Rx FIFO 上溢
		- I2CSSTA.5 = I2C 从机无数据传输确认
		- I2CSSTA.6 = I2C 从机忙
		- I2CSSTA.7 = I2C 通常请求中断
		- I2CSSTA.9:8 = I2C 通常请求号
		- I2CSSTA.10 = I2C 停止状态检测
		- I2CSSTA.12:11 = 指示I2C匹配ID
		- I2CSSTA.13 = I2C 重复开始状态检测
		- I2CSSTA.14 = I2C 开始及匹配地址检测
	@return value of I2CMSTA:
		- I2CMSTA.1:0 = Tx FIFO 状态
		- I2CMSTA.2 = I2C Tx 请求
		- I2CMSTA.3 = I2C Rx 请求
		- I2CMSTA.4 = I2C 没有收到来自从机地址的确认
		- I2CMSTA.5 = I2C  失去对I2C总线的仲裁
		- I2CMSTA.6 = I2C  主机忙
		- I2CMSTA.7 = I2C  没有收到数据传输的确认
		- I2CMSTA.8 = I2C 传输完成
		- I2CMSTA.9 = Rx  接收溢出
		- I2CMSTA.10 = I2C 总线忙
**/

int I2cSta(int iChannel,int iMode)
{
  if (iChannel)
  {
    if (iMode == 1)
      return I2C1SSTA;
    else
      return I2C1MSTA;
  } else {
    if (iMode == 1)
      return I2C0SSTA;
    else
      return I2C0MSTA;
  }
}
