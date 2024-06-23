// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/SettingsScene.hpp"
#include "Scene/ScoreboardScene.hpp"

#include "Scene/FarmSelectScene.hpp"
#include "Scene/FarmScene.hpp"
#include "Scene/OurGameScene.hpp"
#include "Scene/PotionStoreScene.h"
#include "Scene/SeedStoreScene.h"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    // TODO: [HACKATHON-1-SCENE] (3/4): Register Scenes here
	game.AddNewScene("settings", new SettingsScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
	// Yuli
	game.AddNewScene("start", new StartScene());
	game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("scoreboard", new ScoreboardScene());
	// Yuli
	game.AddNewScene("farm-select", new FarmSelectScene());
	game.AddNewScene("farm", new FarmScene());
	game.AddNewScene("ourgame-scene",new OurGameScene());

	game.AddNewScene("potion-store",new PotionStoreScene());
	game.AddNewScene("seed-store",new SeedStoreScene());
	

	game.Start("start", 60, 1600, 832);
	return 0;
}
