
#ifndef WINDOW_H
#define WINDOW_H
#include <allegro5/bitmap.h>
#include <functional>
#include <string>
#include "Engine/Sprite.hpp"
#include "Engine/IControl.hpp"
#include "Image.hpp"
#include "Engine/LOG.hpp"



namespace Engine {

    class Window : public Image, public IControl {
    private:
        int sc;
        bool mouseIn = false;
        std::string background;
        std::shared_ptr<ALLEGRO_BITMAP> imgBitmap;
        std::string message;
        std::function<void()> OnClickCallback;

    protected:
        Engine::Image* imageObject = nullptr;
    public:
        bool Drew = false;

        Window(int scene, std::string img, std::string wd, std::string message, float x, float y, float w, float h, float anchorX, float anchorY);
        void DrawWindow();
        void OnMouseMove(int mx, int my);
    };

} // namespace Engine
#endif //WINDOW_H
