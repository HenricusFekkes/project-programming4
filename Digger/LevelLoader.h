#pragma once
#include<Singleton.h>
#include <string>

namespace dae
{
	class Scene;
	class LevelLoader final : public Singleton<LevelLoader>
	{
	public:
		Scene* ReadFile(const std::string& filename, const std::string& sceneName);

	private:
		void LoadTunnel(std::stringstream& ss, Scene* pScene);
		void LoadPlayer(std::stringstream& ss, Scene* pScene);
		void LoadRock(std::stringstream& ss, Scene* pScene);
		void LoadEmerald(std::stringstream& ss, Scene* pScene);
		void LoadSpawner(std::stringstream& ss, Scene* pScene);
	};
}


