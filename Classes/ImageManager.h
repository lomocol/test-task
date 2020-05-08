#pragma once

#include "settings.h"
#include "cocos2d.h"
#include <map>

class ImageManager
{

public:
	static ImageManager& instance()
	{
		static ImageManager imageManager;
		return imageManager;
	}

	void addTexture(const std::string & filename, cocos2d::Size size);
	cocos2d::Texture2D * getTexture(const std::string& filename);
private:
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator = (const ImageManager&) = delete;
	ImageManager();
	~ImageManager();
	

//private:
	std::map<std::string, cocos2d::Texture2D*> textures;

};

