//
// Created by IRIS0817 on 2024/6/11.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_OURGAMESCENE_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_OURGAMESCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "role/Role.hpp"
#include "role/Role1.hpp"
#include "role/Role2.hpp"
#include "Bomb/Bomb.hpp"
#include "Bomb/FireEffect.hpp"
#include "Bomb/HammerEffect.hpp"
#include "Bomb/FirearmEffect.hpp"
#include "Instrument/Instrument.hpp"
#include "Instrument/Box.hpp"
#include "Instrument/Firearm.hpp"
#include "Instrument/Bubble.hpp"
#include "Instrument/Hammer.hpp"
#include "Instrument/ToolBomb.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"

namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}  // namespace Engine

class OurGameScene final : public Engine::IScene {
private:
    Role1* role1;
    Role2* role2;
    enum TileType {
        TILE_FLOOR,
        TILE_WALL,
        TILE_OCCUPIED,
        TILE_TOOL_BOMB,
        TILE_TOOL_FIREARM,
        TILE_TOOL_HAMMER,
        TILE_BLOCK
    };
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
    std::array<bool, ALLEGRO_KEY_MAX> keys;
protected:
    int SpeedMult;
public:
    static float timer;
    static bool DebugMode;
    static const std::vector<Engine::Point> directions;
    static const int MapWidth, MapHeight;
    static const int BlockSize;
    static const Engine::Point SpawnGridPoint;
    static const Engine::Point EndGridPoint;
    static const std::vector<int> code;
    float ticks;
    float deathCountDown;

    static Box* mapBox[25][13];
    static Firearm* mapFirearm[25][13];
    static Bubble* mapBubble[25][13];
    static Hammer* mapHammer[25][13];
    static ToolBomb* mapToolBomb[25][13];
    // Map tiles.
    Group* TileMapGroup;
    Group* GroundEffectGroup;
    Group* DebugIndicatorGroup;
    Group* BombGroup;
    Group* FireEffectGroup;
    Group* FirearmEffectGroup;
    Group* HammerEffectGroup;
    Group* RoleGroup;
    Group* InstrumentGroup;
    Group* EffectGroup;
    Group* UIGroup;
    Engine::Image* imgTarget;
    Engine::Sprite* dangerIndicator;
    std::vector<std::vector<TileType>> mapState;
    std::vector<std::vector<bool>> ValidState;
    std::list<int> keyStrokes;
    static Engine::Point GetClientSize();
    explicit OurGameScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void PutBomb(int x,int y);
    void ClearBomb(int x,int y,int radius);
    /******/
    /*******/
    void OnKeyUp(int keyCode) override;
    void OnKeyDown(int keyCode) override;
    void Hit();
    void ReadMap();
    void ConstructUI();
    void UIBtnClicked(int id);
    bool CheckSpaceValid(int x, int y);
    void TakeTool(Role* role);
    void CheckDie(int i,int j);
    void firearmEffect(int x,int y,Role* r);
    void hammerEffect(int x,int y,Role* r);
    // void ModifyReadMapTiles();
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_OURGAMESCENE_HPP
