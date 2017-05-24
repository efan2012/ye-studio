#include <ADuC7023.h>
#define MASTER 0
#define SLAVE 1
#define DISABLE 0
#define ENABLE 1

extern int I2cMCfg(int iChannel, int iIntSources, int iConfig);
extern int I2cSCfg(int iChannel, int iIntSources, int iConfig);
extern int I2cFifoFlush(int iChannel,int iMode, int iFlush);
extern int I2cRx(int iChannel,int iMode);
extern int I2cTx(int iChannel,int iMode, int iTx);
extern int I2cBaud(int iChannel,int iHighPeriod, int iLowPeriod);
extern int I2cMWrCfg(int iChannel,unsigned int uiDevAddr);
extern int I2C0SIDCfg(int iChannel,int iSlaveID0, int iSlaveID1,int iSlaveID2,int iSlaveID3);
extern int I2cSta(int iChannel,int iMode);
