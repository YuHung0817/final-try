//
// Created by IRIS0817 on 2024/6/12.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ROLE1_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ROLE1_HPP
#include "Role.hpp"

class Role1 : public Role {
public:
    static int offset;
    static int frameIndex;
    static int dir;
    static bool change;
    int bombRange=1;
    int live=1;
    int speedMult=1;
    void SetDir(int i);
    int ReturnDir() override;
    //void gettool(std::string type) override;
    Role1(int x, int y);
    virtual void Draw() const override;
    void init();

};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_ROLE1_HPP
