﻿#ifndef HOTFISTREMASTER_JSONPARSER_H
#define HOTFISTREMASTER_JSONPARSER_H

#include "external/json/document.h"
#include <string>

rapidjson::Document getDocumentFromResource(std::string fileName);


#endif //HOTFISTREMASTER_JSONPARSER_H
