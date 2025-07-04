#include "game.hpp"
#include "dracula.hpp"
#include "invisibleman.hpp"
#include "archaeologist.hpp"
#include "mayor.hpp"
#include "perk.hpp"

using namespace std;

Game::Game()
{
    srand(static_cast<unsigned>(time(nullptr)));
    initMonsterCards();
    initMonsters();
    initHeros();
    std::array<Perk , 20 > P = AllPerks;
    time_t randomPerk1 = rand() % 20 + 1;
    time_t randomPerk2 = rand() % 20 + 1;
    heroes[0]->HavePerkCard(P[randomPerk1]);
    heroes[1]->HavePerkCard(P[randomPerk2]);
}

void Game::initMonsterCards()
{
    monsterCards.reserve(12);
    monsterCards.emplace_back(MonsterCardName::FORMOFTHEBAT , 3 , 2 , 1 , 2 , vector<MonsterName>{MonsterName::INVISIBLEMAN});
    monsterCards.emplace_back(MonsterCardName::SUNRISE , 3 , 0 , 1 , 2 , vector<MonsterName>{MonsterName::INVISIBLEMAN , MonsterName::FRENZY});
    monsterCards.emplace_back(MonsterCardName::THIEF , 5 , 2 , 1 , 3 , vector<MonsterName>{MonsterName::INVISIBLEMAN , MonsterName::DRACULA});
    monsterCards.emplace_back(MonsterCardName::THEDELIVERY , 1 , 3 , 1 , 3 , vector<MonsterName>{MonsterName::FRENZY});
    monsterCards.emplace_back(MonsterCardName::FORTUNETELLER , 1 , 3 , 1 , 2 , vector<MonsterName>{MonsterName::FRENZY});
    monsterCards.emplace_back(MonsterCardName::FORMEREMPLOYER , 1 , 3 , 1 , 2 , vector<MonsterName>{MonsterName::INVISIBLEMAN , MonsterName::FRENZY});
    monsterCards.emplace_back(MonsterCardName::HURRIEDASSISTANT , 1 , 3 , 2 , 3 , vector<MonsterName>{MonsterName::DRACULA});
    monsterCards.emplace_back(MonsterCardName::THEINNOCENT , 1 , 3 , 1 , 3 , vector<MonsterName>{MonsterName::FRENZY , MonsterName::DRACULA , MonsterName::INVISIBLEMAN});
    monsterCards.emplace_back(MonsterCardName::EGYPTIANEXPERT , 1 , 3 , 2 , 2 , vector<MonsterName>{MonsterName::DRACULA , MonsterName::FRENZY});
    monsterCards.emplace_back(MonsterCardName::THEICHTHYOLOGIST , 1 , 3 , 1 , 2 , vector<MonsterName>{MonsterName::FRENZY});
    monsterCards.emplace_back(MonsterCardName::HYPNOTICGAZE , 2 , 2 , 1 , 2 , vector<MonsterName>{MonsterName::INVISIBLEMAN});
    monsterCards.emplace_back(MonsterCardName::ONTHEMOVE , 2 , 3 , 3 , 2 , vector<MonsterName>{MonsterName::FRENZY});
}

void Game::initHeros()
{
    heroes[0] = make_unique<Archaeologist>();
    heroes[1] = make_unique<Mayor>();
}

void Game::initMonsters()
{
    monsters[0] = make_unique<Dracula>(Location::CRYPT);
    monsters[1] = make_unique<InvisibleMan>(Location::INSTITUTE);
}