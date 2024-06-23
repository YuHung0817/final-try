//
// Created by janet on 2024/6/11.
//

#ifndef POTIONSTORESCENE_H
#define POTIONSTORESCENE_H
#include "Engine/IScene.hpp"

class Plant;
namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}  // namespace Engine

class PotionStoreScene final : public Engine::IScene {
protected:
    int money1, money2;
    int table[3][5]={0};
    PotionStoreScene* getPotionScene();
public:
    void Initialize() override;
    void NextOnClick(int stage);
    void BuyOnClick(int player, int money, int potion);
    //void OnMouseDown(int button, int mx, int my) override;
    //void OnMouseUp(int button, int mx, int my) override;
    void ReadMoney();//get money
    void CostPotion(int player, int potion) const;
    int GetPotionNumber(int player, int potion) const;


};
#endif //POTIONSTORESCENE_H
