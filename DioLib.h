#include <ADuC7023.h>
extern int DioCfg(int iPort, unsigned long iMpx);
extern int DioPinCfg(int iPort, int iPin, int iMode);
extern int DioIOen(int iPort, int iIOen);
extern int DioPinIOen(int iPort, int iPin, int iIOen);
extern int DioRd(int iPort);
extern int DioWr(int iPort, int iVal);
extern int DioSet(int iPort, int iVal);
extern int DioClr(int iPort, int iVal);
extern int DioPul(int iPort, unsigned long iPul);
extern int DioPulPin(int iPort, int iPin, int iPul);
