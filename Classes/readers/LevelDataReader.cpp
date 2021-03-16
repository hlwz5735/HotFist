//
// Created by 厉猛 on 2020/4/22.
//

#include "cocostudio/DictionaryHelper.h"
#include "JsonParser.h"
#include "LevelDataReader.h"

using namespace cocostudio;

LevelData LevelDataReader::readDocument(std::string fileName)
{
    auto jsonDoc = getDocumentFromResource(fileName);

//    assert(jsonDoc.HasMember("startPosition"));

    auto levelData = LevelData();
    auto dicHelper = DictionaryHelper::getInstance();

    levelData.setName(dicHelper->getStringValue_json(jsonDoc, "name", ""));
    levelData.setWidth(dicHelper->getFloatValue_json(jsonDoc, "width", 0));
    levelData.setTmxMap(dicHelper->getStringValue_json(jsonDoc, "tmxMap", ""));
    levelData.setBgm(dicHelper->getStringValue_json(jsonDoc, "bgm", "Audio/03-Main.mp3"));

    levelData.setStartPosition(Point(
            dicHelper->getFloatValue_json(jsonDoc["startPosition"], "x", 0),
            dicHelper->getFloatValue_json(jsonDoc["startPosition"], "y", 0)
    ));

    if (jsonDoc.HasMember("enemies")) {
        auto iterator = jsonDoc["enemies"].GetArray().Begin();
        while (iterator != jsonDoc["enemies"].GetArray().End())
        {
            auto type = dicHelper->getStringValue_json(*iterator, "type", "");
            auto position = Point::ZERO;
            if (iterator->HasMember("position"))
            {
                position = Point(
                        dicHelper->getFloatValue_json((*iterator)["position"], "x", 0),
                        dicHelper->getFloatValue_json((*iterator)["position"], "y", 0)
                );
            }

            auto enemyData = EnemyData();
            enemyData.setType(type);
            enemyData.setPosition(position);

            vector<EnemyData> &enemies = levelData.getEnemies();
            enemies.push_back(enemyData);

            iterator++;
        }
    }

    return levelData;
}
