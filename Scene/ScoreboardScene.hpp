#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
// Yu start
#include <vector>
#include <string>
#include <tuple>
using namespace std;
// Yu end

class ScoreboardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    explicit ScoreboardScene() = default;
    void Initialize() override;
	void Terminate() override;
    void BackOnClick(int stage);

    // Yu start
    void ReadScoreRecord();
    vector<tuple<string, int, string>> ScoreData;
    //vector<tuple<int, string>> ScoreData;
    struct compareScore {
        bool operator() (const tuple<string, int, string>& d1, const tuple<string, int, string>& d2) const {
            if (std::get<1>(d1) > std::get<1>(d2)) {
                return true;
            } else if (std::get<1>(d1) == std::get<1>(d2)) {
                return false;
            } else {
                return false;
            }
        }
    };
    void PrevOnClick(int stage);
    void NextOnClick(int stage);
    // Yu end
};

#endif // SCOREBOARDSCENE_HPP