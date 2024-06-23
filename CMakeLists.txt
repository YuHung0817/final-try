cmake_minimum_required(VERSION 3.27)
project(2024_I2P2_TowerDefense_with_answer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Resource)

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(2024_I2P2_TowerDefense_with_answer
        Engine/Allegro5Exception.cpp
        Engine/Allegro5Exception.hpp
        Engine/AudioHelper.cpp
        Engine/AudioHelper.hpp
        Bullet/Bullet.cpp
        Bullet/Bullet.hpp
        Engine/Collider.cpp
        Engine/Collider.hpp
        UI/Animation/DirtyEffect.cpp
        UI/Animation/DirtyEffect.hpp
        Enemy/Enemy.cpp
        Enemy/Enemy.hpp
        UI/Animation/ExplosionEffect.cpp
        UI/Animation/ExplosionEffect.hpp
        Bullet/FireBullet.cpp
        Bullet/FireBullet.hpp
        Engine/GameEngine.cpp
        Engine/GameEngine.hpp
        Engine/Group.cpp
        Engine/Group.hpp
        Engine/IControl.cpp
        Engine/IControl.hpp
        UI/Component/Image.cpp
        UI/Component/Image.hpp
        UI/Component/ImageButton.cpp
        UI/Component/ImageButton.hpp
        Engine/IObject.cpp
        Engine/IObject.hpp
        Engine/IScene.cpp
        Engine/IScene.hpp
        UI/Component/Label.cpp
        UI/Component/Label.hpp
        Bullet/LaserBullet.cpp
        Bullet/LaserBullet.hpp
        Turret/LaserTurret.cpp
        Turret/LaserTurret.hpp
        Engine/LOG.cpp
        Engine/LOG.hpp
        Scene/LoseScene.cpp
        Scene/LoseScene.hpp
        Turret/MachineGunTurret.cpp
        Turret/MachineGunTurret.hpp
        main.cpp
        Bullet/MissileBullet.cpp
        Bullet/MissileBullet.hpp
        Turret/MissileTurret.cpp
        Turret/MissileTurret.hpp
        UI/Animation/Plane.cpp
        UI/Animation/Plane.hpp
        Enemy/PlaneEnemy.cpp
        Enemy/PlaneEnemy.hpp
        Scene/PlayScene.cpp
        Scene/PlayScene.hpp
        Engine/Point.cpp
        Engine/Point.hpp
        Engine/Resources.cpp
        Engine/Resources.hpp
        UI/Component/Slider.cpp
        UI/Component/Slider.hpp
        Enemy/SoldierEnemy.cpp
        Enemy/SoldierEnemy.hpp
        Engine/Sprite.cpp
        Engine/Sprite.hpp
        Scene/StageSelectScene.cpp
        Scene/StageSelectScene.hpp
        Enemy/TankEnemy.cpp
        Enemy/TankEnemy.hpp
        Turret/Turret.cpp
        Turret/Turret.hpp
        Turret/TurretButton.cpp
        Turret/TurretButton.hpp
        Scene/WinScene.cpp
        Scene/WinScene.hpp

        # TODO: [HACKATHON-1-SCENE] (2/4) Add the new scene source files here
        ## Yuli
        Scene/StartScene.cpp
        Scene/StartScene.h
        Scene/SettingsScene.cpp
        Scene/SettingsScene.hpp
        Scene/ScoreboardScene.cpp
        Scene/ScoreboardScene.hpp
        Enemy/MyEnemy.cpp
        Enemy/MyEnemy.hpp
        Turret/MyTurret.cpp
        Turret/MyTurret.hpp
        Bullet/MyBullet.cpp
        Bullet/MyBullet.hpp

        Bomb/FireEffect.cpp
        Bomb/FireEffect.hpp
        Bomb/HammerEffect.cpp
        Bomb/HammerEffect.hpp
        Bomb/FirearmEffect.hpp
        Bomb/FirearmEffect.cpp

        Scene/FarmScene.cpp
        Scene/FarmScene.hpp
        Scene/FarmSelectScene.cpp
        Scene/FarmSelectScene.hpp
        Plant/Plant.cpp
        Plant/Plant.hpp
        Plant/PlantButton.cpp
        Plant/PlantButton.hpp
        Plant/WheatPlant.cpp
        Plant/WheatPlant.hpp
        Plant/VegetablePlant.cpp
        Plant/VegetablePlant.hpp
        Plant/ApplePlant.cpp
        Plant/ApplePlant.hpp
        Plant/FlowerPlant.cpp
        Plant/FlowerPlant.hpp
        Plant/SicklePlant.hpp
        Plant/SicklePlant.cpp
        ## Yuli
        ##UI/Component/TextInput.cpp
        ##UI/Component/TextInput.hpp

        Scene/OurGameScene.cpp
        Scene/OurGameScene.hpp
        Turret/TurretButton.hpp
        Scene/WinScene.cpp
        Scene/WinScene.hpp
        
        role/Role.cpp
        role/Role.hpp
        role/Role1.cpp
        role/Role1.hpp
        role/Role2.cpp
        role/Role2.hpp
        Bomb/Bomb.cpp
        Bomb/Bomb.hpp
        Bomb/Bomb1.cpp
        Bomb/Bomb1.hpp
        Instrument/Instrument.cpp
        Instrument/Instrument.hpp
        Instrument/Box.cpp
        Instrument/Box.hpp
        Instrument/Firearm.cpp
        Instrument/Firearm.hpp
        Instrument/Bubble.cpp
        Instrument/Bubble.hpp
        Instrument/Hammer.cpp
        Instrument/Hammer.hpp
        Instrument/ToolBomb.cpp
        Instrument/ToolBomb.hpp

        Scene/SeedStoreScene.cpp
        Scene/SeedStoreScene.h
        Scene/PotionStoreScene.cpp
        Scene/PotionStoreScene.h

        UI/Component/Window.h
        UI/Component/Window.cpp
)

IF (WIN32)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC C:/allegro/include)
    target_link_directories(2024_I2P2_TowerDefense_with_answer PUBLIC C:/allegro/lib)
    target_compile_options(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2024_I2P2_TowerDefense_with_answer liballegro_monolith)
ELSE()
    find_package(PkgConfig)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC lib)
    target_include_directories(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_compile_options(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2024_I2P2_TowerDefense_with_answer ${ALLEGRO5_LIBRARIES})
    target_link_directories(2024_I2P2_TowerDefense_with_answer PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
ENDIF()