#include <ADuC7023.h>
extern int FeeSR(unsigned long ulAddr);
extern int FeeSW(int iData, unsigned long ulAddr);
extern int FeeEW(int iData, unsigned long ulAddr);
extern int FeeSV(int iData, unsigned long ulAddr);
extern int FeePErs(unsigned long ulAddr);
extern int FeeMErs(void);
extern int FeeSta(void);
extern int FeeIntCfg(int iEnable);
extern int FeePro(int iMode, int iPage);
