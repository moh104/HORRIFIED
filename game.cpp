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

void Game::monsterPhase()
{
    cout<<"\n--- Monster Phase ---\n";

    size_t index = rand() % monsterCards.size();
    MonsterCard card = monsterCards[index];
    std::swap(monsterCards[index], monsterCards.back());
    monsterCards.pop_back();

    cout << "Monster Card " << monsterCardToString(card.getName()) << " was executed\n";

    try
    {
        placeRandomItems(card.getNewItems());
        doEvent(card.getName());
        doMonsterStrikes(card);
    }
    catch (const invalid_argument& e)
    {
        cerr << "(ERROR) " << e.what() << '\n';
    }
    catch (const logic_error& e)
    {
        cerr << "(ERROR) " << e.what() << '\n';
    }
    

}

void Game::doEvent(MonsterCardName cardName)
{
    switch(cardName)
    {
        case MonsterCardName::FORMOFTHEBAT:
            monsters[0]->setLocation(currentHero->getLocation());
            break;

        case MonsterCardName::SUNRISE:
            monsters[0]->setLocation(Location::CRYPT);
            break;

        case MonsterCardName::THIEF:
        {
            Location location = Map::findLocationWithMostItems(items);
            monsters[1]->setLocation(location);
            for (auto& item : items)
            {
                if (item.getLocation() == location && item.getItemStatus() == ItemStatus::ON_BOARD)
                {
                    item.removeItem();
                }
            }
            break;
        }

        case MonsterCardName::THEDELIVERY:
            for (auto& villager : villagers)
            {
                if (villager.getName() == VillagerName::WILBURANDCHICK)
                {
                    villager.setLocation(Location::DOCKS);
                    villager.activate();
                    break;
                }
            }
            break;

        case MonsterCardName::FORTUNETELLER:
            for (auto& villager : villagers)
            {
                if (villager.getName() == VillagerName::MALEVA)
                {
                    villager.setLocation(Location::CAMP);
                    villager.activate();
                    break;
                }
            }
            break;

        case MonsterCardName::FORMEREMPLOYER:
            for (auto& villager : villagers)
            {
                if (villager.getName() == VillagerName::DRCRANLY)
                {
                    villager.setLocation(Location::LABORATORY);
                    villager.activate();
                    break;
                }
            }
            break;

        case MonsterCardName::HURRIEDASSISTANT:
            for (auto& villager : villagers)
            {
                if (villager.getName() == VillagerName::FRITZ)
                {
                    villager.setLocation(Location::TOWER);
                    villager.activate();
                    break;
                }
            }
            break;

        case MonsterCardName::THEINNOCENT:
            for (auto& villager : villagers)
            {
                if (villager.getName() == VillagerName::MARIA)
                {
                    villager.setLocation(Location::BARN);
                    villager.activate();
                    break;
                }
            }
            break;

        case MonsterCardName::EGYPTIANEXPERT:
            for (auto& villager : villagers)
            {
                if (villager.getName() == VillagerName::PROFPEARSON)
                {
                    villager.setLocation(Location::CAVE);
                    villager.activate();
                    break;
                }
            }
            break;

        case MonsterCardName::THEICHTHYOLOGIST:
            for (auto& villager : villagers)
            {
                if (villager.getName() == VillagerName::DRREAD)
                {
                    villager.setLocation(Location::INSTITUTE);
                    villager.activate();
                    break;
                }
            }
            break;

        case MonsterCardName::HYPNOTICGAZE:
        {
            Location draculaLocation = monsters[0]->getLocation();
            auto [hero , villager] = Map::findNearestTarget(draculaLocation , villagers , heroes);
            if (hero)
            {
                hero->movement(1 , draculaLocation);
            }
            else if (villager)
            {
                villager->movement(1 , draculaLocation);
            }
            break;
        }

        case MonsterCardName::ONTHEMOVE:
            frenzyIndex = 1 - frenzyIndex;
            for(auto &villager : villagers)
            {
                villager.movement(1 , villager.getSafeLocation());
            }
            break;
    }
}

void Game::doMonsterStrikes(const MonsterCard& card)
{
    unsigned invisibleManPowerCount = 0;
    monsters[1]->clearMarkedVillager();
    auto order = card.getStrikeOrder();

    for (auto monsterName : order)
    {
        Monster* monster = nullptr;
        if (monsterName == MonsterName::FRENZY)
        {
            monster = monsters[frenzyIndex].get();
        }
        else
        {
            monster = (monsterName == MonsterName::DRACULA ? monsters[0].get() : monsters[1].get());
        }
        if (!monster->isActive())
        {
            continue;
        }

        auto [hero , villager] = Map::findNearestTarget(monster->getLocation(), villagers , heroes);
        Location target = (hero ? hero->getLocation() : villager->getLocation());
        monster->movement(card.getStrikeMove(), target);

        DiceResult result = throwDice(card.getStrikeDice());
        if (result.attackIcons > 0)
        {
            if (hero && hero->getLocation() == monster->getLocation())
            {
                if (monster->attack(hero , nullptr))
                {
                    return;
                }
            }
            else if (villager && villager->getLocation() == monster->getLocation())
            {
                if (monster->attack(nullptr, villager))
                {
                    return;
                }
            }
        }

        if (monster->getName() == MonsterName::INVISIBLEMAN && result.powerIcons > 0)
        {
            invisibleManPowerCount += result.powerIcons;
        }
        else if (monster->getName() == MonsterName::DRACULA && result.powerIcons > 0)
        {
            monster->power(villagers , currentHero);
        }
    }

    for (unsigned i = 0 ; i < invisibleManPowerCount ; ++i)
    {
        try
        {
            monsters[0]->power(villagers , currentHero);
        }
        catch (const logic_error& e)
        {
            return;
        }
    }
}

Game::DiceResult Game::throwDice(int numberOfDice) const noexcept
{
    DiceResult result;
    for (int i = 0; i < numberOfDice; ++i)
    {
        int diceResult = rand() % 6;
        if(diceResult < 4){}
        else if(diceResult == 4)
            ++result.powerIcons;
        else if(diceResult == 5)
            ++result.attackIcons;
    }
    return result;
}

void Game::placeRandomItems(int count)
{
    if (count < 0)
    {
        throw invalid_argument("The number of new items cannot be negative");
    }

    if (count > outGameItems)
    {
        refreshDiscardedItems();
        if (count > outGameItems)
        {
            throw logic_error("There are not enough items outside the game");
        }
    }
    int numberOfItems = static_cast<int>(items.size());
    int placed = 0;
    while (placed < count)
    {
        Item& item = items[rand() % numberOfItems];
        if (item.getItemStatus() == ItemStatus::OUT_GAME)
        {
            item.activate();
            ++placed;
            --outGameItems;
        }
    }
}

void Game::run()
{
    size_t current;
    array<string , 2> playerNames;
    while (true)
    {
        cout << "Player 1 Enter your name: ";
        getline(cin, playerNames[0]);
        cout << "Player 2 Enter your name: ";
        getline(cin, playerNames[1]);
        if (playerNames[1] == playerNames[0])
        {
            cerr << "The names of the players cannot be the same" << endl;
            continue;
        }
        cout << playerNames[0];
        int time0 = getIntNumber(", how many days ago did you eat garlic? ");
        cout << playerNames[1];
        int time1 = getIntNumber(", how many days ago did you eat garlic? ");
        if (time0 < 0 || time1 < 0)
        {
            cerr << "Duration cannot be negative" << endl;
            continue;
        }
        current = (time0 < time1 ? 0 : 1);
        break;
    }
    while (true)
    {
        cout << playerNames[current] << ", Choose your hero:\n"
                << "1) " << heroes[0]->heroNameToString(heroes[0]->getName()) << '\n'
                << "2) " << heroes[1]->heroNameToString(heroes[1]->getName()) << '\n';
        int choice = getIntNumber("");
        if (choice != 1 && choice != 2)
        {
            cerr << "Invalid choice entered, please try again\n";
            continue;
        }
        try
        {
            heroes[choice - 1]->setOwner(playerNames[current]);
            heroes[1 - (choice - 1)]->setOwner(playerNames[1 - current]);
        }
        catch (const invalid_argument& e)
        {
            cerr << "(ERROR) " << e.what();
            continue;
        }
        currentHero = heroes[choice - 1].get();
        break;
    }

    try
    {
        placeRandomItems(12);
    }
    catch (const invalid_argument& e)
    {
        cerr << "(ERROR) " << e.what() << '\n';
    }
    catch (const logic_error& e)
    {
        cerr << "(ERROR) " << e.what() << '\n';
    }
    

    while (true)
    {
        cout << "\n===== Play " << currentHero->getOwner() << ",  it's turn (" << currentHero->heroNameToString(currentHero->getName()) << ") =====\n";
        heroPhase();
        if (!monsters[0]->isActive() && !monsters[1]->isActive())
        {
            std::cout << "\n HEROES WIN! All monsters defeated.\n";
            return;
        }

        if (skipNextMonsterPhase)
        {
            cout << "[Monster Phase skipped]\n";
            skipNextMonsterPhase = false;
        }
        else
        {
            monsterPhase();
        }
        if (monsterCards.empty())
        {
            cout << "\n MONSTERS WIN! No monster cards left.\n";
            return;
        }
        if (Map::getHorroLevel() >= 5)
        {
            cout << "\nMONSTERS WIN! horror reached 5.\n";
            return;
        }

        current = 1 - current;
        currentHero = heroes[current].get();
    }
}

int Game::getIntNumber(string output) noexcept
{
    string input;
    int value;
    

    while (true)
    {
        cout << output;
        getline(cin , input);
        try
        {
            size_t pos = 0;
            value = stoi(input , &pos);

            if (pos == input.size())
            {
                return value;
            }
            else
            {
                cout << "Invalid input! Please enter only a integer number without extra characters.\n";
            }
        }
        catch(...)
        {
            cout << "Invalid input! Please enter a valid integer number.\n";
        }
    }
}

void Game::refreshDiscardedItems()
{
    for (auto& item : items)
    {
        if (item.getItemStatus() == ItemStatus::DISCARDED)
        {
            item.setItemStatus(ItemStatus::OUT_GAME);
            ++outGameItems;
        }
    }
}

// void Game::ClearScreen() {
//     #ifdef _WIN32
//         system("cls"); 
//     #else
//         system("clear");  
//     #endif
// }

void Game::Visit_from_the_Detective(Monster* monster)
{
    if (monster->getName() == MonsterName::INVISIBLEMAN)
    {
        std::cout << "Location that monster can go :" << std::endl;
        std::cout << "1.DOCKS\n2.CAMP\n3.INN\n4.MANSION\n5.ABBEY\n6.MUSEUM\n7.THEATRE\n"
                  << "8.GRAVEYARD\n9.BARN\n10.SHOP\n11.PRECINCT\n12.INSTITUTE\n13.LABORATORY\n"
                  << "14.TOWER\n15.CAVE\n16.DUNGEON\n17.CRYPT\n18.CHURCH\n19.HOSPITAL\n";
        std::cout << "Enter where the monster you want to go : ";
        int loc;
        std::cin >> loc;
        monster->setLocation(static_cast<Location> ( loc - 1));
    }
    else
    {
        return;
    }
    
}

void Game::Break_of_Dawn()
{
    skipNextMonsterPhase = true;
}

void Game::Overstock()
{
    placeRandomItems(2);
}

void Game::Late_into_the_Night( Hero* hero)
{
    int a = hero->getActionsLeft();
    a +=2 ;
    hero->setActionsLeft(a) ;
}

void Game::Repel( Monster* dracula , Monster* invisibleman )
{
    std::vector <Location> nearMonster = Map::getNeighboringPlaces(dracula->getLocation());
    std::cout << "Location that Dracula can go :" << std::endl;
    int a = 1;
    for (size_t i = 0; i < nearMonster.size(); i++)
    {
        std::cout << a << ". " << Map::locationToString(nearMonster[i]) << std::endl ;
        a++;
    }
    std::cout << "Enter where the monster you want to go : ";
    int loc;
    std::cin >> loc;
    dracula->movement(1 , nearMonster[loc-1]);
    nearMonster.clear();

    nearMonster = Map::getNeighboringPlaces(dracula->getLocation());
    std::cout << "Location that Dracula can go :" << std::endl;
    a = 1;
    for (size_t i = 0; i < nearMonster.size(); i++)
    {
        std::cout << a << ". " << Map::locationToString(nearMonster[i]) << std::endl ;
        a++;
    }
    std::cout << "Enter where the monster you want to go : ";
    std::cin >> loc;
    dracula->movement(1 , nearMonster[loc-1]);
    nearMonster.clear();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    nearMonster = Map::getNeighboringPlaces(invisibleman->getLocation());
    std::cout << "Location that Invisible Man can go :" << std::endl;
    a = 1;
    for (size_t i = 0; i < nearMonster.size(); i++)
    {
        std::cout << a << ". " << Map::locationToString(nearMonster[i]) << std::endl ;
        a++;
    }
    std::cout << "Enter where the monster you want to go : ";
    std::cin >> loc;
    invisibleman->movement(1 , nearMonster[loc-1]);
    nearMonster.clear();

    nearMonster = Map::getNeighboringPlaces(invisibleman->getLocation());
    std::cout << "Location that Invisible Man can go :" << std::endl;
    a = 1;
    for (size_t i = 0; i < nearMonster.size(); i++)
    {
        std::cout << a << ". " << Map::locationToString(nearMonster[i]) << std::endl ;
        a++;
    }
    std::cout << "Enter where the monster you want to go : ";
    std::cin >> loc;
    invisibleman->movement(1 , nearMonster[loc-1]);
    nearMonster.clear();
}

void Game::Hurry(Hero* hero)
{
    std::vector <Location> nearHero = Map::getNeighboringPlaces(hero->getLocation());
    std::cout << "Location that hero can go :" << std::endl;
    int a = 1;
    for (size_t i = 0; i < nearHero.size(); i++)
    {
        std::cout << a << ". " << Map::locationToString(nearHero[i]) << std::endl ;
        a++;
    }
    std::cout << "Enter where the hero you want to go : ";
    int loc;
    std::cin >> loc;
    hero->move(nearHero[loc-1]);

    nearHero = Map::getNeighboringPlaces(hero->getLocation());
    std::cout << "Location that hero can go :" << std::endl;
    a = 1;
    for (size_t i = 0; i < nearHero.size(); i++)
    {
        std::cout << a << ". " << Map::locationToString(nearHero[i]) << std::endl ;
        a++;
    }
    std::cout << "Enter where the hero you want to go : ";
    std::cin >> loc;
    hero->move(nearHero[loc-1]);
}

void Game::heroPhase() {

    
    while (currentHero->getActionsLeft() > 0) {
        // ClearScreen();
        Map::draw(items , monsters , villagers , heroes);
        std::string action;
        std::cout << "Actions:\nMove    Guide    PickUp    Advance    Defeat    Perk    Help    Quit\n";
        std::cout << "Choose action for " << currentHero->heroNameToString(currentHero->getName()) << ": ";
        std::cin >> action;

        if (action == "Move") {
            // ClearScreen();
            std::cout << "Do you want to move villager with hero?[Y/N]";
            std::string ans;
            std::cin >> ans;
            if (ans == "N")
            {
                std::vector <Location> nearlocations = Map::getNeighboringPlaces(currentHero->getLocation());
                std::cout << "There is the locations you can go :" << std::endl;
                int a = 1;
                for (size_t i = 0 ; i < nearlocations.size() ; ++i){
                    std::cout << a << ". " << Map::locationToString(nearlocations[i]) << std::endl; 
                    a++;
                }
                int newLocation;
                newLocation = getIntNumber("Enter location to move to: ");
                // std::cout << "Enter location to move to: ";
                // std::cin >> newLocation;
                
                
                if (newLocation > static_cast<int>(nearlocations.size()))
                {
                    std::cout << "Enter a correct location to move to: ";
                    std::cin >> newLocation;
                }

                currentHero->move(nearlocations[newLocation - 1]);
            }

            if (ans == "Y")
            {
                std::vector <Location> nearlocations = Map::getNeighboringPlaces(currentHero->getLocation());
                std::cout << "There is the locations you can go :" << std::endl;
                int a = 1;
                for (size_t i = 0 ; i < nearlocations.size() ; i ++){
                    std::cout << a << ". " << Map::locationToString(nearlocations[i]) << std::endl; 
                    a++;
                }
                int newLocation;
                newLocation = getIntNumber("Enter location to move to: ");
                // int newLocation;
                // std::cout << "Enter location to move to: ";
                // std::cin >> newLocation;
                
                if (newLocation > static_cast<int>(nearlocations.size()))
                {
                    std::cout << "Enter a correct location to move to: ";
                    std::cin >> newLocation;
                }
                std::array <Villager* , 7> all ;
                for (size_t i = 0; i < villagers.size(); ++i) {
                    all[i] = &villagers[i];
                }
                for (size_t i = 0; i < all.size(); i++)
                {
                    if (all[i]->isActive() && all[i]->getLocation() == currentHero->getLocation())
                    {
                        all[i]->setLocation(nearlocations[newLocation - 1]);
                        std::cout << Map::locationToString(all[i]->getLocation()) << std::endl;
                        if (all[i]->getLocation() == all[i]->getSafeLocation())
                        {
                            std::array<Perk , 20 > P = AllPerks;
                            time_t randomPerk = rand() % 20 + 1;
                            currentHero->HavePerkCard(P[randomPerk]);
                            all[i]->DisActive();
                        }
                        
                    }
                }
                currentHero->move(nearlocations[newLocation - 1]);
            }
            
        }

        else if (action == "Guide")
        {
            // ClearScreen();
            std::array <Villager* , 7> all ;
            for (size_t i = 0; i < villagers.size(); ++i) {
                all[i] = &villagers[i];
            }
            std::vector < Villager* > near;
            for (size_t i = 0; i < all.size(); i++)
            {
                if (all[i]->isActive())
                {
                    near.push_back(all[i]);
                }
            }
            currentHero->guide( near);
            for (size_t i = 0; i < all.size(); i++)
            {
                if (all[i]->getLocation() == all[i]->getSafeLocation() )
                {
                    std::array<Perk , 20 > P = AllPerks;
                    time_t randomPerk = rand() % 20 + 1;
                    currentHero->HavePerkCard(P[randomPerk]);
                    all[i]->DisActive();
                }
                
            }
            
        }

        else if (action == "PickUp")
        {
            std::array <Item* , 70> All ;
            for (size_t i = 0; i < All.size(); ++i) {
                All[i] = &items[i];
            }
            currentHero->pickUpItem( All );
        }

        else if (action == "Advance")
        {
            // ClearScreen();
            if (currentHero->getLocation() == Location::CAVE || currentHero->getLocation() == Location::GRAVEYARD || currentHero->getLocation() == Location::CRYPT || currentHero->getLocation() == Location::DUNGEON)
            {
                currentHero->advanceTask(monsters[0].get());
            }
            if (currentHero->getLocation() == Location::PRECINCT)
            {
                currentHero->advanceTask(monsters[1].get());
            }
            
        }

        else if (action == "Defeat")
        {
            // ClearScreen();
            if (currentHero->getLocation() == monsters[0]->getLocation())
            {
                currentHero->defeatMonster(monsters[0].get());
            }
            if (currentHero->getLocation() == monsters[1]->getLocation())
            {
                currentHero->defeatMonster(monsters[1].get());
            }
            
        }
        
        else if(action == "Perk"){
            // ClearScreen();
            std::vector<Perk>perkCards = currentHero->GetPerk();
            if (!perkCards.empty()) {

            std::cout << "You can use this perks:" << std::endl;
            int a = 1;
            for (Perk& perk : perkCards)
            {
                std::cout << a << ". " << perk.NameToString(perk.getName()) << std::endl;
                a++;
            }
            int choise;
            choise = getIntNumber("Enter the perk you want to use :");

            // std::cout << "Enter the perk you want to use :" ;
            //std::cin >> choise;

            if (choise > static_cast<int>(perkCards.size()))
            {
                std::cout << "Enter the correct choice :" ;
                std::cin >> choise;
            }

            if(perkCards[choise-1].getName() == Name::Late_into_the_Night){
                Late_into_the_Night(currentHero);
                perkCards.erase(perkCards.begin() + choise - 1);
            }
            else if(perkCards[choise-1].getName() == Name::Break_of_Dawn){
                Break_of_Dawn();
                perkCards.erase(perkCards.begin() + choise - 1);
            }
            else if(perkCards[choise-1].getName() == Name::Overstock){
                Overstock();
                perkCards.erase(perkCards.begin() + choise - 1);
            }
            else if(perkCards[choise-1].getName() == Name::Visit_from_the_Detective){
                Visit_from_the_Detective(monsters[1].get());
                perkCards.erase(perkCards.begin() + choise - 1);
            }
            else if(perkCards[choise-1].getName() == Name::Repel){
                Repel(monsters[0].get() , monsters[1].get());
                perkCards.erase(perkCards.begin() + choise - 1);
            }
            else if(perkCards[choise-1].getName() == Name::Hurry){
                Hurry(currentHero);
                perkCards.erase(perkCards.begin() + choise - 1);
            }


            } 
            else {
                std::cout << currentHero->heroNameToString(currentHero->getName()) << " has no perk cards to use!" << std::endl;
            }
            
             
        }

        else if (action == "Help")
        {
            // ClearScreen();
            displayHelp();
        }

        else if(action == "Quit"){
            // ClearScreen();
            return;
        }

        else{
            std::cout << "Enter correct action :";
        }
        
        if (heroes[0]->getActionsLeft() == 0)
        {
            heroes[0]->setActionsLeft(4);
            return;
        }
        
        if (heroes[1]->getActionsLeft() == 0)
        {
            heroes[1]->setActionsLeft(5);
            return;
        }

    }
}


void Game::displayHelp() {
    std::cout << "\nAvailable Actions:\n"
        << "1. Move - Move to adjacent location\n"
        << "2. Guide - Move a villager\n"
        << "3. PickUp - Collect items\n"
        << "4. Advance - Work on monster task\n"
        << "5. Defeat - Attempt to defeat monster\n"
        << "6. Perk - Use perk card\n"
        << "7. Status - Show game state\n"
        << "8. End - Finish turn\n"
        << "9. Help - Show this message\n"
        << "0. Quit - Exit game\n";
        std::cout <<"Enter the action you want to help (Number) : ";
        int num;
        std::cin >> num;
        switch (num)
        {
        case 1:
           std::cout << "Move to adjacent location\n";
        case 2:
           std::cout << "Move a villager\n";
        case 3:
           std::cout << "Collect items\n";
        case 4:
           std::cout << "Work on monster task\n";
        case 5:
           std::cout << "Attempt to defeat monster\n";
        case 6:
           std::cout << "Use perk card\n";
        case 7:
           std::cout << "Show game state\n";
        case 8:
           std::cout << "Finish turn\n";
        case 9:
           std::cout << "Show this message\n";
        case 0:
           std::cout << "Exit game";
         
        default:
           break;
        }
}