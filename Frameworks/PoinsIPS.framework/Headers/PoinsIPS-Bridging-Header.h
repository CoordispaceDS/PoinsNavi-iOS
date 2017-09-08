//
//  PoinsIPSSetting.h
//  PrePoinsNavigation
//
//  Created by jeong on 2017. 6. 20..
//  Copyright © 2017년 coordispace. All rights reserved.
//

#ifndef PoinsIPSSetting_h
#define PoinsIPSSetting_h
#include "PoinsIPSCore.h"

// for only iOS
void setBssidList(const long long int bssid[], const int length);
void setLevelList(const int level[], const int length);
void setLinkInfoList(const int links[], const int length);
void setNodeIDList(const int list[], const int length);
void setNodeConnectedNumList(const short list[], const int length);
void setNodeLayerList(const int list[], const int length);
void setNodePositionList(const float list[], const int length);
void setMgnValueList(const short list[], const int length);
void setBSSIDDBList(const long long int list[], const int length, const int maxCount);
void setRSSIDBList(const int list[], const int length, const int maxCount);
    
#endif /* PoinsIPSSetting_h */
