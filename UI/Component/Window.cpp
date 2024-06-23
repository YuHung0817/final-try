#include "Window.h"

#include <functional>
#include "Engine/Group.hpp"
#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Image.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include <string>
#include <fstream>
#include "Engine/LOG.hpp"
#include "Scene/SeedStoreScene.h"
#include "Scene/PotionStoreScene.h"
#include "UI/Component/Label.hpp"

namespace Engine {

    SeedStoreScene* getSeedScene() {
        return dynamic_cast<SeedStoreScene*>(Engine::GameEngine::GetInstance().GetScene("seed-store"));
    }
    PotionStoreScene* getPotionScene() {
        return dynamic_cast<PotionStoreScene*>(Engine::GameEngine::GetInstance().GetScene("potion-store"));
    }

    Window::Window(int scene, std::string img, std::string wd, std::string message, float x, float y, float w, float h, float anchorX, float anchorY)
        : sc(scene), Image(img, x, y, w, h, anchorX, anchorY), message(message), imgBitmap(Resources::GetInstance().GetBitmap(img)), background(wd) {

    }

    void Window::OnMouseMove(int mx, int my) {
        mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), imgBitmap);
        if (mouseIn) {
            DrawWindow();
        }
        else if(!mouseIn && Drew) {

            if(sc==1)getSeedScene()->RemoveObject(imageObject->GetObjectIterator());
            else if(sc==2)getPotionScene()->RemoveObject(imageObject->GetObjectIterator());
            if(sc==1)Engine::GameEngine::GetInstance().ChangeScene("seed-store");
            else GameEngine::GetInstance().ChangeScene("potion-store");
            //Engine::LOG(Engine::DEBUGGING) <<"Delete";
            Drew=false;

        }
    }

    void Window::DrawWindow() {
        //Engine::LOG(Engine::DEBUGGING) <<"Draw";
        if(sc==1)getSeedScene()->AddNewObject(imageObject=new Engine::Image(background, Position.x,  Position.y-130, 0, 0, 0.5, 0.5));
        if(sc==1)getSeedScene()->AddNewObject(new Engine::Label(message, "pirulen.ttf", 20, Position.x,  Position.y-175, 0, 0, 0, 255, 0.5, 0.5));
        if(sc==2)getPotionScene()->AddNewObject(imageObject=new Engine::Image(background, Position.x,  Position.y-130, 0, 0, 0.5, 0.5));
        if(sc==2)getPotionScene()->AddNewObject(new Engine::Label(message, "pirulen.ttf", 20, Position.x,  Position.y-175, 0, 0, 0, 255, 0.5, 0.5));
        Drew = true;
    }
}