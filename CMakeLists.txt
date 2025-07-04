cmake_minimum_required(VERSION 3.10)

project(horrified LANGUAGES CXX)

set(SOURCES
    main.cpp
    archaeologist.cpp
    dracula.cpp
    game.cpp
    hero.cpp
    invisibleman.cpp
    item.cpp
    map.cpp
    mayor.cpp
    monster.cpp
    monstercard.cpp
    perk.cpp
    villager.cpp)

set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app ${SOURCES})