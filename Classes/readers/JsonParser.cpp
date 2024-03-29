﻿#include "cocos2d.h"
#include "JsonParser.h"

using namespace cocos2d;

rapidjson::Document getDocumentFromResource(const std::string& fileName) {
    const std::string contentStr = FileUtils::getInstance()->getStringFromFile(fileName);
    rapidjson::Document jsonDict;
    jsonDict.Parse(contentStr.c_str());
    if (jsonDict.HasParseError())
    {
        CCLOG("GetParseError %d\n", jsonDict.GetParseError());
    }
    return jsonDict;
}
