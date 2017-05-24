#include <ADuC7023.h>
extern int AdcGo(int iTEN, int iSpeed, int iTime, int iStart, int iPower, int iMode, int iType);
extern int AdcPin(int iInN, int iInP);
extern int AdcCal(int iGain, int iOffset);
extern int AdcRd(void);
extern int AdcRst(int iReset);
extern int AdcRESet(void);
