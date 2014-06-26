#ifndef __TXDBIP_H
#define __TXDBIP_H

#include <string>

extern bool TxDbInit();
extern void TxDbClose();
extern bool AddValueToTxIpDb(const std::string &key, const std::string &value);
extern bool GetValueFromTxIpDb(const std::string &key, std::string &value);

#endif //__TXDBIP_H
