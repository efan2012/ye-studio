#include "UrtLib.h"
int UrtCfg(int iChan, int iBaud, int iBits, int iFormat)
{
  if (iChan) //选择模式1引脚
  {
    GP0CON &= 0x0fffffff;
    GP0CON |= 0x20000000;
    GP2CON &= 0xfffffff0;
    GP2CON |= 0x00000002;
  } else { //选择模式0引脚
    GP1CON &= 0xffffff00;
    GP1CON |= 0x00000011;
  }
  switch ()
  {
    case

  }
  COMCON0 = (iFormat&0x3c)|(iBits&3);
}

/**
   @简介 int UrtLinSta(void);
      ========== 读取UART线路状态

   @返回值 CMSTA0的值
   - 0x1 =  数据就绪
   - (0x1 << 1) =  溢出错误
   - (0x1 << 2) =  奇偶校验错误
   - (0x1 << 3) =  帧错误
   - (0x1 << 4) =  断开错误，SIN保持低电平超过最大字长
   - (0x1 << 5) =  COMTX 寄存器空状态
   - (0x1 << 6) =  COMTX和移位寄存器空状态
 @警告	检查状态前需要配置好UART
**/

int UrtLinSta(void)
{
	return	COMSTA0;
}

/**
	@简要 int UrtTx(int iTx)；
			==========Write 8 bits of iTx to the UART.

	@参数 iTx :{0-255}
		- 发送的字节
	@return 1 成功发送
  0 TX 缓冲已满
	@警告
		 写入数据前UART必须被配置，如果TX缓冲已满，数据丢失
**/

int UrtTx(int iTx)
{
	if(COMSTA0 & (0x1 << 5))
	{
		COMTX = iTx;
		return 1;
	}
  return 0;
}

/**
	@简介 int UrtRx(void)；
			==========读取UART数据
	@返回值 在RX缓冲的字节 (COMRX)
	@标注
		- 不会等待新的接收到的数据
**/

int UrtRx(void)
{
	return COMRX;
}

/**
	@简介 int UrtModSta(void)；
			========== 读取调制解调器状态寄存器
	@返回值  COMMSR寄存器值:
		- (0x1 << 7) = 数据载波检测
		- (0x1 << 6) = 响铃指示
		- (0x1 << 5) = 数据准备就绪
		- (0x1 << 4) = 清除发送
		- (0x1 << 3) = 三角波DCD
		- (0x1 << 2) = 下降沿RI
		- (0x1 << 1) = 三角波DSR
		- 0x1 = 三角波 CTS
	@警告	检查状态前UART必须被配置
**/

int UrtModSta(void)
{
	return	COMSTA1;
}

/**
	@简介 int UrtIntCfg(int iIrq)；
			==========开启/关闭UART中断使能

	@参数 iIrq :{COMIEN_ERBFI| COMIEN_ETBEI| COMIEN_ELSI| COMIEN_EDSSI| COMIEN_EDMAT| COMIEN_EDMAR}
		- 0 to select none of the options.
		Or set to the bitwise or combination of
		- COMIEN_ERBFI to enable UART RX IRQ.
		- COMIEN_ETBEI to enable UART TX IRQ.
		- COMIEN_ELSI to enable UART Status IRQ.
		- COMIEN_EDSSI to enable UART Modem status IRQ.
		- COMIEN_EDMAT to enable UART DMA Tx IRQ.
		- COMIEN_EDMAR to enable UART DMA Rx IRQ.
	@return 1.
**/

int UrtIntCfg(int iIrq)
{
	COMIEN0 = iIrq;
	return 1;
}

/**
	@简介 int UrtIntSta(void);
			==========返回UART中断状态
  @返回值 COMIIR.
**/

int UrtIntSta(void)
{
	return COMIID0;
}
