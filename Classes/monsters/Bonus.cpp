#include "Bonus.h"

using namespace std;
using namespace cocos2d;

Bonus::Bonus(cocos2d::Size size, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo, BonusType _type):
	iMonster(size,_parent,position,bodyInfo), type(_type)
{
    Texture2D* texture = nullptr;
	switch (_type)
	{
    case BonusType::Health:
        texture = ImageManager::instance().getTexture("bonus/health.png");
        break;
    case BonusType::Protection:
        texture = ImageManager::instance().getTexture("bonus/protection.png");
        break;
    case BonusType::FireBall:
        texture = ImageManager::instance().getTexture("bonus/fireball.png");
        break;
    case BonusType::Block:
        texture = ImageManager::instance().getTexture("bonus/block.png");
        break;
    case BonusType::Shield:
        texture = ImageManager::instance().getTexture("bonus/shield.png");
        break;
    default:
        throw exception("Unknown BonusType");
        break;
	}
    if (texture == nullptr)
        throw exception("image for this BonusType was not added");

    sprite->setTexture(texture);
}
