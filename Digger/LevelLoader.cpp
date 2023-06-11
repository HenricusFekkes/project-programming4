#include "LevelLoader.h"
#include "Scene.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "LevelScene.h"

using namespace dae;

Scene* LevelLoader::ReadFile(const std::string& filename, const std::string& sceneName)
{
	LevelScene* pScene = new LevelScene(sceneName);


	if (std::ifstream file{ filename }; file.is_open()) {
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			std::string command{};
			std::stringstream ss{ line };
			ss >> command;
		}
	}
	return pScene;
}

void LevelLoader::LoadTunnel(std::stringstream& ss, Scene* pScene)
{
	int x, y, w, h;
	ss >> x >> y >> w >> h;
	pScene;
}

void LevelLoader::LoadPlayer(std::stringstream& ss, Scene* pScene)
{
	ss;
	pScene;
}

void LevelLoader::LoadRock(std::stringstream& ss, Scene* pScene)
{
	ss;
	pScene;
}

void LevelLoader::LoadEmerald(std::stringstream& ss, Scene* pScene)
{
	ss;
	pScene;
}

void LevelLoader::LoadSpawner(std::stringstream& ss, Scene* pScene)
{
	ss;
	pScene;
}