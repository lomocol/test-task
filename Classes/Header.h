#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "ui/CocosGUI.h"
#include "monsters/bonus.h"

const static float buttonWidthPercent = 0.2f;
const static float buttonHeightPercent = 0.5f;
const static std::string fireBallButtonFileName = "buttons/fireball.png";
const static std::string fireBallButtonUnavailableFileName = "buttons/fireball_unavailable.png";
const static std::string blockButtonFileName = "buttons/block.png";
const static std::string blockButtonUnavailableFileName = "buttons/block_unavailable.png";
const static std::string shieldButtonFileName = "buttons/shield.png";
const static std::string shieldButtonUnavailableFileName = "buttons/shield_unavailable.png";

class Header
{
public:
	Header(cocos2d::Node* _parent);
	void changeHealth(float newHealth);
	void changeProtection(float newProtection);
	void changeSkillButton(BonusType type,int count);
	~Header() ;
private:
	void createBars();
	void createButtons();
	void createLabels();
	void setBackground();
	void addButton(BonusType type,const std::string & normalImageFileName,
		const std::string& unavailableImageFileName,const cocos2d::Vec2 position, const cocos2d::Size buttonSize);
private:
	cocos2d::Sprite* background;
	cocos2d::Size headerSize;
	cocos2d::Node* parent;
	cocos2d::Node* buttonNode;
	cocos2d::Node* barNode;
	cocos2d::ui::LoadingBar* healthBar;
	cocos2d::ui::LoadingBar* protectionBar;

	std::map<BonusType, cocos2d::ui::Button*>buttons;
	std::map<BonusType, cocos2d::Label*>labels;
};

