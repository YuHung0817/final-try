#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Bullet/MyBullet.hpp"
#include "MyTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int MyTurret::Price = 150;
MyTurret::MyTurret(float x, float y) :
	Turret("play/tower-base.png", "play/MyTurret.png", x, y, 500, Price, 1) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}

void MyTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new MyBullet(Position + normalized * 36, diff, rotation, this));
	//getPlayScene()->BulletGroup->AddNewObject(new MyBullet(Position + normalized * 36, diff, rotation, this));
	AudioHelper::PlayAudio("a.wav");
}
