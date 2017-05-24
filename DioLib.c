#include "DioLib.h"
/**
   @简介 int DioCfg(int iPort,unsigned lone ulMpx);
      ========== 设置端口引脚功能
   @参数 iPort :{0x0-0x4}
      - 指定端口
        ulAddr :{0x00000000-0xffffffff}
      - 设置端口引脚功能
   @返回值 1 命令成功执行
**/

int DioCfg(int iPort, unsigned long ulMpx)
{
  GPIO->Control[iPort] = ulMpx;
  return 1;
}

/**
   @简介 int DioPinCfg(int iPort, int iPin,int iMode);
      ========== 设置端口引脚功能
   @参数 iPort :{0x0-0x4}
      - 指定端口
        iPin :{0x0-0x7}
      - 指定引脚
        iMode :{0x0-0x3}
      - 设置端口引脚功能
   @返回值 1 命令成功执行
**/

int DioPinCfg(int iPort, int iPin, int iMode)
{
  unsigned long a = GPIO->Control[iPort];
  a &= (0xffffffff - (0x3 << (4 * iPin)));
  a += (iMode << (4 * iPin));
  GPIO->Control[iPort] = a;
  return 1;
}

/**
   @简介 int DioIOen(int iPort, int iIOen);
      ========== 设置端口引脚输入/输出模式
   @参数 iPort :{0x0-0x4}
      - 指定端口
        iIOen :{0x00-0xff}
      - 设置端口引脚输入/输出模式
   @返回值 1 命令成功执行
**/

int DioIOen(int iPort, int iIOen)
{
  unsigned long a = GPIO->Port[iPort].Data;
  a &= 0x00ffffff;
  a += (iIOen << 24);
  GPIO->Port[iPort].Data = a;
  return 1;
}

/**
   @简介 int DioPinIOen(int iPort, int iPin,int iIOen);
      ========== 设置端口引脚输入/输出模式
   @参数 iPort :{0x0-0x4}
      - 指定端口
        iPin :{0x0-0x7}
      - 指定引脚
        iIOen :{0x0-0x1}
      - 设置端口引脚输入/输出模式
   @返回值 1 命令成功执行
**/

int DioPinIOen(int iPort, int iPin, int iIOen)
{
  unsigned long a = GPIO->Port[iPort].Data;
  a &= 0xffffffff - (0x1 << (iPin + 24));
  a += (iIOen << (24 + iPin));
  GPIO->Port[iPort].Data = a;
  return 1;
}

/**
   @简介 int DioRd(int iPort);
      ========== 读取输入数据
   @参数 iPort :{0x0-0x4}
      - 指定端口
   @返回值 a 返回输入数据
**/

int DioRd(int iPort)
{
  unsigned char a = GPIO->Port[iPort].Data;
  return a;
}

/**
   @简介 int DioWr(int iPort, int iVal);
      ========== 指定输出数据
   @参数 iPort :{0x0-0x4}
      - 指定端口
        iVal:{0x0-0x255}
      -指定输出数据
   @返回值 b 返回输出数据
**/

int DioWr(int iPort, int iVal)
{
  unsigned long a = GPIO->Port[iPort].Data;
  a &= 0xff00ffff;
  a += (iVal << 16);
  GPIO->Port[iPort].Data = a;
  unsigned char b = (GPIO->Port[iPort].Data >> 16); //取输出数据
  return b;
}

/**
   @简介 int DioSet(int iPort, int iVal);
      ========== 指定输出引脚置1
   @参数 iPort :{0x0-0x4}
      - 指定端口
        iVal:{0x0-0x255}
      -指定输出引脚置1
   @返回值 b 返回输出数据
**/

int DioSet(int iPort, int iVal)
{
  unsigned long a = GPIO->Port[iPort].Set;
  a &= 0xff00ffff;
  a += (iVal << 16);
  GPIO->Port[iPort].Set = a;
  unsigned char b = (GPIO->Port[iPort].Data >> 16); //取输出数据
  return b;
}


/**
   @简介 int DioClr(int iPort, int iVal);
      ========== 指定输出引脚清零
   @参数 iPort :{0x0-0x4}
      - 指定端口
        iVal:{0x0-0x255}
      -指定输出引脚清零
   @返回值 b 返回输出数据
**/

int DioClr(int iPort, int iVal)
{
  unsigned long a = GPIO->Port[iPort].Clear;
  a &= 0xff00ffff;
  a += (iVal << 16);
  GPIO->Port[iPort].Clear = a;
  unsigned char b = (GPIO->Port[iPort].Data >> 16); //取输出数据
  return b;
}

/**
   @简介 int DioPul(int iPort, unsigned long ulPul);
      ========== 设置端口引脚是否禁用上拉电阻
   @参数 iPort :{0x0-0x4}
      - 指定端口
        iVal:{0x0-0x255}
      - 设置端口引脚是否禁用上拉电阻
   @返回值 1 命令成功执行
**/

int DioPul(int iPort, unsigned long ulPul)
{
  if (iPort) {
    GP0PAR = ulPul;
  } else {
    GP1PAR = ulPul;
  }
  return 1;
}

/**
   @简介 int DioPulPin(int iPort, int iPin, int iPul);
      ==========  设置端口引脚是否禁用上拉电阻
   @参数 iPort :{0x0-0x4}
      - 指定端口
      iPin :{0x0-0x7}
      - 指定引脚
        iVal:{0x0-0x1}
      - 0x0 启用上拉电阻
        0x1 禁用上拉电阻
   @返回值 1 命令成功执行
**/

int DioPulPin(int iPort, int iPin, int iPul)
{
  if (iPort) {
    unsigned long a = GP0PAR;
    a &= (0xffffffff - (0x1 << ( 4 * iPin )));
    a += (iPul << 4 * iPin);
    GP0PAR = a;
  } else {
    unsigned long a = GP1PAR;
    a &= (0xffffffff - (0x1 << ( 4 * iPin )));
    a += (iPul << 4 * iPin);
    GP1PAR = a;
  }
  return 1;
}
