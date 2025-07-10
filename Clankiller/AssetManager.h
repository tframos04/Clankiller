#pragma once

#include "AssetStore.h"

class AssetManager
{
public:
	AssetManager(AssetManager const&) = delete;
	void operator=(AssetManager const&) = delete;

	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}

	void unloadAllAssets()
	{
		models.unloadAll();
		sounds.unloadAll();
	}

	AssetStore<Model> models;
	AssetStore<Sound> sounds;

private:
	AssetManager() = default;
};