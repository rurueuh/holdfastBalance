#include "Balance.hpp"
/**
 * CONSTRUCTOR
*/

Balance::Balance()
{
}

Balance::~Balance()
{
}

/**
 * INPUT
*/
void Balance::input()
{
    std::ifstream file(FILEPATHINPUT);
    std::string line;


    if (!file.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        exit(84);
    }

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        if (line.at(0) == '#')
            continue;
        std::string name;
        int nbPlayer;
        bool spe[4] = {false, false, false, false};
        int oldSpeCount = 0;

        std::istringstream iss(line);
        std::string word;
        int i = 0;
        while (std::getline(iss, word, ',')) {
            if (i == 0)
                name = word;
            else if (i == 1)
                nbPlayer = std::stoi(word);
            else if (i == 2) {
                if (word == "1") 
                    spe[0] = true;
            } else if (i == 3) {
                if (word == "1") 
                    spe[1] = true;
            } else if (i == 4) {
                if (word == "1") 
                    spe[2] = true;
            } else if (i == 5) {
                if (word == "1") 
                    spe[3] = true;
            } else if (i == 6) {
                oldSpeCount = std::stoi(word);
            }
            i++;
        }
        Speciality *wantedSpeciality = new Speciality(spe[0], spe[1], spe[2], spe[3]);
        Regiment *regiment = new Regiment(name, nbPlayer, wantedSpeciality);
        regiment->_oldSpeCount = oldSpeCount;
        _regiments.push_back(regiment);
    }
}

void Balance::init()
{
    input();
}

/**
 * CALCULATE
*/

void Balance::calculate()
{
    std::vector<int> calculator(this->_regiments.size(), 0);
    while (1) {
        bool isOnlyOne = true;
        for (int i = 0; i < calculator.size(); i++) {
            if (calculator[i] != 1) {
                isOnlyOne = false;
                break;
            }
        }
        if (isOnlyOne)
            break;
        for (int i = calculator.size() - 1; i >= 0; i--) {
            if (calculator[i] == 0) {
                calculator[i] = 1;
                break;
            } else {
                calculator[i] = 0;
            }
        }
        std::vector<Regiment *> regimentsRed;
        std::vector<Regiment *> regimentsBlue;
        for (int i = 0; i < calculator.size(); i++) {
            if (calculator[i] == 0)
                regimentsRed.push_back(this->_regiments[i]);
            else
                regimentsBlue.push_back(this->_regiments[i]);
        }
        const int safeCPU = 500000;
        static int countsafe = 0;
        countsafe++;
        if (countsafe > safeCPU) {
            Printer::file << "safe CPU usage only " + std::to_string(safeCPU) + " games possible to count" << std::endl;
            break;
        }
        Game *game = new Game(regimentsRed, regimentsBlue);
        game->giveSpeciality();
        this->_games.push_back(game);
    }
    Printer::file << "Number of games possible : " << this->_games.size() << std::endl;
    std::vector<Game *> InvalidGames = {}; // can't be invalid but can be save with give dual speciality
    for (auto game : this->_games) {
        bool invalid = game->invalidGame();
        if (invalid) {
            InvalidGames.push_back(game);
        }
    }
    std::sort(this->_games.begin(), this->_games.end(), [](Game *a, Game *b) {
        return a->numberOfSpeciality() > b->numberOfSpeciality();
    });
    std::sort(InvalidGames.begin(), InvalidGames.end(), [](Game *a, Game *b) {
        return a->numberOfSpeciality() > b->numberOfSpeciality();
    });
    for (auto game : InvalidGames) {
        if (!(this->_games.at(0)->numberOfSpeciality() < game->numberOfSpeciality() && game->numberOfSpeciality() % 2 == 0))
            this->_games.erase(std::remove(this->_games.begin(), this->_games.end(), game), this->_games.end());
    }
    
}

/**
 * DISPLAY
*/

void Balance::sort()
{
    for (auto game : this->_games) {
        game->calculateRatio();
    }
    std::vector<Game *> maxSpeciality = {};
    int max = 0;
    for (auto game : this->_games) {
        if (game->numberOfSpeciality() > max) {
            max = game->numberOfSpeciality();
            maxSpeciality = {};
            maxSpeciality.push_back(game);
        } else if (game->numberOfSpeciality() == max) {
            maxSpeciality.push_back(game);
        }
    }
    _games = maxSpeciality;
    std::sort(this->_games.begin(), this->_games.end(), [](Game *a, Game *b) {
        return a->_ratio > b->_ratio;
    });
}

void Balance::display()
{
    if (_games.size() == 0) {
        Printer::file << "No solution found" << std::endl;
        return;
    } else if (_games.size() >= 1000) {
        Printer::file << "Multiple solution found, write only 1000 first of them" << std::endl;

        for (int i = 0; i < 1000; i++) {
            this->_games[i]->display();
        }
    } else {
        for (auto game : this->_games) {
            game->display();
        }
    }
}