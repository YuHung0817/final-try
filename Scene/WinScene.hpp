#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"

class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
public:
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
	// Yu start
	int w;
	int h;
	int halfW;
	int halfH;
	std::string winnerName;
	void Draw() const override;
	void OnKeyDown(int keyCode) override;
	// Yu end
};

#endif // WINSCENE_HPP
