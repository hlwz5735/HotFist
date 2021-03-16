#include "cocos/2d/CCNode.h"
using namespace cocos2d;

namespace hotfist {

class GuiReader
{
public:
    static Node* readDocument(std::string fileName);
};

}
