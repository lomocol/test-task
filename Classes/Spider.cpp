#include "Spider.h"

using namespace std;
using namespace cocos2d;

Spider::Spider(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, int mask) : 
	iMonster(filename,_parent, position,mask)
{

}

void Spider::die()
{
}

void Spider::appearance(float time)
{

}
