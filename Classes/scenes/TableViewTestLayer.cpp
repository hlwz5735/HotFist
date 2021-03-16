#include "TableViewTestLayer.h"
#include "SceneFactory.h"

USING_NS_CC;
USING_NS_CC_EXT;

// on "init" you need to initialize your instance
bool TableViewTestLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    TableView *tableView = TableView::create(this, visibleSize);
    tableView->setDirection(ScrollView::Direction::HORIZONTAL);
    tableView->setPosition(0, visibleSize.height / 2 - 50);
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();

    MenuItemImage *btnReturn = MenuItemImage::create("returnMenu.png", "returnMenu.png");
    btnReturn->setCallback([](Ref* pSender){
        Director::getInstance()->popScene();
    });
    btnReturn->setPosition(visibleSize.width - 64, visibleSize.height - 64);
    auto menu = Menu::create(btnReturn, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    return true;
}

void TableViewTestLayer::tableCellTouched(TableView *table, TableViewCell *cell) {
    CCLOG("cell touched at index: %i", (int) cell->getIdx());
    switch (cell->getIdx()) {
        case 0:
            Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, SceneFactory::loadLevel("01")));
            break;
        case 1:
            Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, SceneFactory::loadLevel("02")));
            break;
        case 2:
            Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, SceneFactory::loadLevel("03")));
            break;
        case 3:
            Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, SceneFactory::loadLevel("04")));
            break;
        default:
            Director::getInstance()->replaceScene(SceneFactory::storyEnd());
            break;
    }
}

Size TableViewTestLayer::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    return Size(this->cellWidth, 120);
}

Size TableViewTestLayer::cellSizeForTable(TableView *table) {
    return Size(this->cellWidth, 120);
}

ssize_t TableViewTestLayer::numberOfCellsInTableView(TableView *table) {
    return 4;
}

TableViewCell *TableViewTestLayer::tableCellAtIndex(TableView *table, ssize_t idx) {
    int normalIdx = static_cast<int>(idx + 1);
    auto string = StringUtils::format("%d", normalIdx);

    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = TableViewCell::create();

        Sprite *sprite = Sprite::create("HelloWorld.png");
        sprite->setScale(0.2f);
        sprite->setPosition(Point(this->cellWidth / 2, 60));
        sprite->setTag(123);
        cell->addChild(sprite);

        auto label = Label::createWithTTF(string, "fonts/arial.ttf", 20.0);
        label->setPosition(this->cellWidth / 2, 10);
        label->setTag(456);
        cell->addChild(label);
    } else {
        Label *label = (Label *) cell->getChildByTag(456);
        label->setString(string);
    }
    return cell;
}
