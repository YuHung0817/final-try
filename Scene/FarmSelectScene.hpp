#ifndef FARMSELECTSCENE_HPP
#define FARMSELECTSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class FarmSelectScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit FarmSelectScene() = default;
	void Initialize() override;
	void Terminate() override;
	void PlayerOnClick(int player);
	void BackOnClick(int player);
};

#endif // FARMSELECTSCENE_HPP
