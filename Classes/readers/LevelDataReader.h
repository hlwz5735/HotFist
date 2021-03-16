//
// Created by 厉猛 on 2020/4/22.
//

#ifndef HOTFISTREMASTER_LEVELDATAREADER_H
#define HOTFISTREMASTER_LEVELDATAREADER_H

#include "LevelData.h"

class LevelDataReader
{
public:
    static LevelData readDocument(std::string fileName);
};


#endif //HOTFISTREMASTER_LEVELDATAREADER_H
