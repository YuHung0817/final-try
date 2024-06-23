

#ifndef SEEDSTORESCENE_H
#define SEEDSTORESCENE_H
#include <allegro5/allegro_audio.h>

#include "Engine/IScene.hpp"

class Plant;
namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}  // namespace Engine

class SeedStoreScene final : public Engine::IScene {
private:
    ALLEGRO_SAMPLE_ID bgmId;
    int position_x[3][2];
    int position_y[2];
protected:
    int money1, money2;
    int table[3][4]={0};
    SeedStoreScene* getSeedScene();
public:
    Group* MarkGroup;
    void Initialize() override;
    void NextOnClick(int stage);
    void BuyOnClick(int player, int money);
    //void OnMouseDown(int button, int mx, int my) override;
    //void OnMouseUp(int button, int mx, int my) override;
    void ReadMoney();//get money
    int GetSeedNumber(int player, int seed);
    void CostMoney(int player, int seed);

};

#endif //SEEDSTORESCENE_H
