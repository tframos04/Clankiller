#pragma once

#include "Base.h"

template <typename T>
class AssetStore
{
public:
	~AssetStore()
	{
		unloadAll();
	}

	void load(const std::string& name, const std::string& path);
	void unloadAll();

	T& get(const std::string& name)
	{
		if (resources.find(name) == resources.end())
		{
			throw std::runtime_error("Asset not found: " + name);
		}

		return resources.at(name);
	}

private:
	std::map<std::string, T> resources;
};

template<>
inline void AssetStore<Model>::load(const std::string& name, const std::string& path) {
	if (resources.find(name) == resources.end()) {
		resources[name] = LoadModel(path.c_str());
	}
}

template<>
inline void AssetStore<Model>::unloadAll() {
	for (auto const& [name, model] : resources) {
		UnloadModel(model);
	}
	resources.clear();
}

template<>
inline void AssetStore<Sound>::load(const std::string& name, const std::string& path) {
	if (resources.find(name) == resources.end()) {
		resources[name] = LoadSound(path.c_str());
	}
}

template<>
inline void AssetStore<Sound>::unloadAll() {
	for (auto const& [name, sound] : resources) {
		UnloadSound(sound);
	}
	resources.clear();
}
