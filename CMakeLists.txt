cmake_minimum_required(VERSION 3.21)
project(Project_2 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(PlaneWar main.c Plane.c Plane.h Config.h Resource.c Resource.h PlayerControl.c PlayerControl.h EnemyControl.c EnemyControl.h BulletsControl.c BulletsControl.h CheckCollision.c CheckCollision.h Data.c Data.h Props.c Props.h)
target_link_libraries(PlaneWar mingw32)
target_link_libraries(PlaneWar SDL2main)
target_link_libraries(PlaneWar SDL2)
target_link_libraries(PlaneWar SDL2_image)
target_link_libraries(PlaneWar SDL2_ttf)