#include "ImageManager.h"

using namespace std;
using namespace cocos2d;

void ImageManager::addTexture(const std::string& filename, cocos2d::Size size)
{

	// Original image
	auto backOrig = Sprite::create(filename);
	if (backOrig == nullptr)
		throw new exception("Image was not found");
	auto oWidth = backOrig->getContentSize().width;
	auto oHeight = backOrig->getContentSize().height;
	backOrig->setFlippedY(true);
	backOrig->setScale(size.width / oWidth, size.height / oHeight); // backOrig scaled to screen size
	backOrig->setPosition(size.width / 2, size.height / 2);

	// Create new texture with background in the exact size of the screen
	
	RenderTexture* renderTexture = RenderTexture::create(size.width,size.height, Texture2D::PixelFormat::RGBA8888);
	renderTexture->begin();
	backOrig->visit();
	renderTexture->end();
	//textures = 
	textures[filename] = renderTexture->getSprite()->getTexture();
	renderTexture->getSprite()->getTexture()->retain();

}

ImageManager::ImageManager()
{
	addTexture(PLAYER_IMAGE,PLAYER_SIZE);
	addTexture(PLAYER_DEAD_IMAGE,PLAYER_SIZE);

	addTexture(HEALTH_IMAGE,BONUS_SIZE);
	addTexture(PROTECTION_IMAGE,BONUS_SIZE);
	addTexture(FIREBALL_IMAGE,BONUS_SIZE);
	addTexture(BLOCK_IMAGE,BONUS_SIZE);
	addTexture(SHIELD_IMAGE,BONUS_SIZE);
}

ImageManager::~ImageManager()
{
	for (auto & p : textures)
	{
		p.second->release();
	}
}

cocos2d::Texture2D *  ImageManager::getTexture(const std::string& filename)
{
	auto it = textures.find(filename);
	if (it != textures.end())
	{
		return it->second;
	}
	else
		return nullptr;
}


