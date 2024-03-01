#ifndef __TABLEVIEWTESTSCENE_H__
#define __TABLEVIEWTESTSCENE_H__

#include "cocos2d.h"
#include "GUI/ScrollView/TableView.h"

USING_NS_AX;
USING_NS_AX_EXT;

class TableViewTestLayer : public Layer, public TableViewDataSource, public TableViewDelegate {
public:
    virtual bool init() override;

    CREATE_FUNC(TableViewTestLayer);

    virtual void tableCellTouched(TableView *table, TableViewCell *cell) override;

    virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx) override;
    virtual Size cellSizeForTable(TableView *table) override;
    virtual ssize_t numberOfCellsInTableView(TableView *table) override;
    virtual TableViewCell *tableCellAtIndex(TableView *table, ssize_t idx) override;

private:
    int cellWidth = 120;
};

#endif // __TABLEVIEWTESTSCENE_H__
