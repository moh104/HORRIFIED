#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "monstercard.hpp"
#include "perk.hpp"

class Game
{
    private:
        std::vector<MonsterCard> monsterCards;
        std::array<std::unique_ptr<Hero> , 2> heroes;
        std::array<Villager, 7> villagers = {
            Villager(VillagerName::DRCRANLY, Location::LABORATORY, Location::PRECINCT),
            Villager(VillagerName::DRREAD, Location::INSTITUTE, Location::CAMP),
            Villager(VillagerName::PROFPEARSON, Location::CAVE, Location::MUSEUM),
            Villager(VillagerName::MALEVA, Location::CAMP, Location::SHOP),
            Villager(VillagerName::FRITZ, Location::TOWER, Location::INSTITUTE),
            Villager(VillagerName::WILBURANDCHICK, Location::SHOP, Location::DUNGEON),
            Villager(VillagerName::MARIA, Location::BARN, Location::CAMP)
        };
        std::array<std::unique_ptr<Monster> , 2> monsters; // 0: Dracula  1:Invisible Man
        std::array<Item , 35> items = {
            Item("Flower", ItemType::YELLOW, 2, Location::DOCKS),
            Item("Tarot Deck", ItemType::YELLOW, 3, Location::CAMP),
            Item("Garlic", ItemType::YELLOW, 2, Location::INN),
            Item("Mirrred Box", ItemType::YELLOW, 3, Location::MANSION),
            Item("Stake", ItemType::YELLOW, 3, Location::ABBEY),
            Item("Scroll of Thoth", ItemType::YELLOW, 4, Location::MUSEUM),
            Item("Violin", ItemType::YELLOW, 3, Location::CAMP),
            Item("Tablet", ItemType::YELLOW, 3, Location::MUSEUM),
            Item("Wilfsbane", ItemType::YELLOW, 4, Location::CAMP),
            Item("Charm", ItemType::YELLOW, 4, Location::CAMP),
            
            Item("Dart", ItemType::RED, 2, Location::INN),
            Item("Fire Poker", ItemType::RED, 3, Location::MANSION),
            Item("Rapier", ItemType::RED, 5, Location::THEATRE),
            Item("Shovel", ItemType::RED, 2, Location::GRAVEYARD),
            Item("Torch", ItemType::RED, 5, Location::BARN),
            Item("Pitchfork", ItemType::RED, 4, Location::BARN),
            Item("Rifle", ItemType::RED, 6, Location::BARN),
            Item("Silver Cane", ItemType::RED, 6, Location::SHOP),
            Item("Knife", ItemType::RED, 3, Location::DOCKS),
            Item("Pistol", ItemType::RED, 6, Location::PRECINCT),
            Item("Bear Trap", ItemType::RED, 4, Location::SHOP),
            Item("Speargun", ItemType::RED, 4, Location::INSTITUTE),
            
            Item("Anatomy Text", ItemType::BLUE, 1, Location::INSTITUTE),
            Item("Centrifuge", ItemType::BLUE, 1, Location::LABORATORY),
            Item("Kite", ItemType::BLUE, 1, Location::TOWER),
            Item("Research", ItemType::BLUE, 2, Location::TOWER),
            Item("Telescope", ItemType::BLUE, 2, Location::MANSION),
            Item("Searchlight", ItemType::BLUE, 2, Location::PRECINCT),
            Item("Experiment", ItemType::BLUE, 2, Location::LABORATORY),
            Item("Analysis", ItemType::BLUE, 2, Location::INSTITUTE),
            Item("Rotenone", ItemType::BLUE, 3, Location::INSTITUTE),
            Item("Casmic Ray Diffuser", ItemType::BLUE, 3, Location::TOWER),
            Item("Nebularium", ItemType::BLUE, 3, Location::TOWER),
            Item("Monocane Mixture", ItemType::BLUE, 3, Location::INN),
            Item("Fossil", ItemType::BLUE, 3, Location::CAMP)
        };
        std::array<Perk, 20> AllPerks = {
            Perk(Name::Late_into_the_Night, 1),
            Perk(Name::Late_into_the_Night, 1),
            Perk(Name::Late_into_the_Night, 1),
            
            Perk(Name::Break_of_Dawn, 1),
            Perk(Name::Break_of_Dawn, 1),
            Perk(Name::Break_of_Dawn, 1),
            
            Perk(Name::Overstock, 1),
            Perk(Name::Overstock, 1),
            Perk(Name::Overstock, 1),
            Perk(Name::Overstock, 1),
            
            Perk(Name::Visit_from_the_Detective, 1),
            Perk(Name::Visit_from_the_Detective, 1),
            Perk(Name::Visit_from_the_Detective, 1),
            Perk(Name::Visit_from_the_Detective, 1),
            
            Perk(Name::Repel, 1),
            Perk(Name::Repel, 1),
            Perk(Name::Repel, 1),
            
            Perk(Name::Hurry, 1),
            Perk(Name::Hurry, 1),
            Perk(Name::Hurry, 1)
        };
        size_t frenzyIndex{0}; // 0: Dracula , 1: InvisibleMan
        Hero* currentHero = nullptr;
        bool skipNextMonsterPhase = false;
        unsigned outGameItems = 70;
        struct DiceResult{
            unsigned attackIcons{0};
            unsigned powerIcons{0};
        };

        void placeRandomItems(int count);
        void doEvent(MonsterCardName);
        void doMonsterStrikes(const MonsterCard& card);
        DiceResult throwDice(int numberOfDice) const noexcept;
        int getIntNumber(std::string output) const noexcept;
        void refreshDiscardedItems();
        void initMonsterCards();
        void initMonsters();
        void initHeros();

        
        void Visit_from_the_Detective(Monster* monster);
        void Break_of_Dawn();
        void Overstock();
        void Late_into_the_Night( Hero* hero);
        void Repel( Monster* dracula , Monster* invisibleman );
        void Hurry(Hero* hero);
        void displayHelp();

    public:
        Game();
        void run();
};

#endif 