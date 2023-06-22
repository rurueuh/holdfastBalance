#include "Game.hpp"

Game::Game()
{
    static int id = 0;
    id++;
    _id = id;
}

Game::~Game()
{
}

void Game::calculateRatioSplit()
{
    uint objectiveSplit = 0;
    int diff = 0;
    for (auto &regiment : _regimentsBlue)
        objectiveSplit += regiment->_nbPlayer;
    for (auto &regiment : _regimentsRed)
        objectiveSplit += regiment->_nbPlayer;
    objectiveSplit /= 2;

    diff = _nbPlayerBlue - objectiveSplit;
    if (diff < 0)
        diff *= -1;
    _ratio += ratioPlayerSplit - (ratioPlayerSplit * (float)diff / (float)objectiveSplit);
}

void Game::calculateRatioNewRegimentSpeciality()
{
    int diff = 0;
    int diffReg[6] = {0, 0, 0, 0, 0, 0};
    const float diffMalusMult = 0.9f;
    for (auto &regiment : _regimentsBlue) {
        if (regiment == this->blueSpe[0]) {
            diffReg[0] = regiment->_oldSpeCount;
            continue;
        } else if (regiment == this->blueSpe[1]) {
            diffReg[1] = regiment->_oldSpeCount;
            continue;
        } else if (regiment == this->blueSpe[2]) {
            diffReg[2] = regiment->_oldSpeCount;
            continue;
        }
    }
    for (auto &regiment : _regimentsBlue) {
        if (regiment == this->blueSpe[0] || regiment == this->blueSpe[1] || regiment == this->blueSpe[2])
            continue;
        if (regiment->wantedSpeciality->arty == 1)
            diff += std::max(diffReg[3] - regiment->_oldSpeCount, 0);
        if (regiment->wantedSpeciality->skirm == 1)
            diff += std::max(diffReg[4] - regiment->_oldSpeCount, 0);
        if (regiment->wantedSpeciality->cav == 1)
            diff += std::max(diffReg[5] - regiment->_oldSpeCount, 0);
    }
    for (auto &regiment : _regimentsRed) {
        if (regiment == this->redSpe[0]) {
            diffReg[3] = regiment->_oldSpeCount;
            continue;
        } else if (regiment == this->redSpe[1]) {
            diffReg[4] = regiment->_oldSpeCount;
            continue;
        } else if (regiment == this->redSpe[2]) {
            diffReg[5] = regiment->_oldSpeCount;
            continue;
        }
    }
    for (auto &regiment : _regimentsRed) {
        if (regiment == this->redSpe[0] || regiment == this->redSpe[1] || regiment == this->redSpe[2])
            continue;
        if (regiment->wantedSpeciality->arty == 1)
            diff += std::max(diffReg[0] - regiment->_oldSpeCount, 0);
        if (regiment->wantedSpeciality->skirm == 1)
            diff += std::max(diffReg[1] - regiment->_oldSpeCount, 0);
        if (regiment->wantedSpeciality->cav == 1)
            diff += std::max(diffReg[2] - regiment->_oldSpeCount, 0);
    }
    _diffSpecialityOld = diff;
    float ratioAdd = ratioNewRegimentSpeciality;
    for (int i = 0; i < diff; i++)
        ratioAdd *= diffMalusMult;
    _ratio += ratioAdd;
}

void Game::calculateRatio()
{
    calculateRatioSplit();
    calculateRatioNewRegimentSpeciality();
}

void Game::giveSpeciality(void)
{
    int numberOfRegWantArtyRed = 0;
    int numberOfRegWantSkirmRed = 0;
    int numberOfRegWantCavalryRed = 0;
    int numberOfRegWantArtyBlue = 0;
    int numberOfRegWantSkirmBlue = 0;
    int numberOfRegWantCavalryBlue = 0;

    for (auto &regiment : _regimentsBlue) {
        if (regiment->wantedSpeciality->arty == 1)
            numberOfRegWantArtyBlue++;
        if (regiment->wantedSpeciality->skirm == 1)
            numberOfRegWantSkirmBlue++;
        if (regiment->wantedSpeciality->cav == 1)
            numberOfRegWantCavalryBlue++;
        _nbPlayerBlue += regiment->_nbPlayer;
    }
    for (auto &regiment : _regimentsRed) {
        if (regiment->wantedSpeciality->arty == 1)
            numberOfRegWantArtyRed++;
        if (regiment->wantedSpeciality->skirm == 1)
            numberOfRegWantSkirmRed++;
        if (regiment->wantedSpeciality->cav == 1)
            numberOfRegWantCavalryRed++;
        _nbPlayerRed += regiment->_nbPlayer;
    }

    int totalArty = numberOfRegWantArtyBlue + numberOfRegWantArtyRed;
    int totalSkirm = numberOfRegWantSkirmBlue + numberOfRegWantSkirmRed;
    int totalCavalry = numberOfRegWantCavalryBlue + numberOfRegWantCavalryRed;
    if (totalArty == 0)
        totalArty = -1;
    if (totalSkirm == 0)
        totalSkirm = -1;
    if (totalCavalry == 0)
        totalCavalry = -1;

    for (int i = 0; i < 3; i++) {
        if (totalArty <= totalSkirm && totalArty <= totalCavalry) {
            if (numberOfRegWantArtyBlue > 0 && numberOfRegWantArtyRed > 0) {
                giveArtillery();
            }
            totalArty = __INT32_MAX__;
            continue;
        }
        if (totalSkirm <= totalArty && totalSkirm <= totalCavalry) {
            if (numberOfRegWantSkirmBlue > 0 && numberOfRegWantSkirmRed > 0) {
                giveSkirm();
            }
            totalSkirm = __INT32_MAX__;
            continue;
        }
        if (totalCavalry <= totalArty && totalCavalry <= totalSkirm) {
            if (numberOfRegWantCavalryBlue > 0 && numberOfRegWantCavalryRed > 0) {
                giveCavalry();
            }
            totalCavalry = __INT32_MAX__;
            continue;
        }
    }
}

void Game::giveArtillery()
{
    for (auto &regiment : _regimentsBlue) {
        if (regiment == blueSpe[0] || regiment == blueSpe[1] || regiment == blueSpe[2])
            continue;
        if (this->blueSpe[0] == nullptr && regiment->wantedSpeciality->arty == 1) {
            this->blueSpe[0] = regiment;
            break;
        }
    }
    for (auto &regiment : _regimentsRed) {
        if (regiment == redSpe[0] || regiment == redSpe[1] || regiment == redSpe[2])
            continue;
        if (this->redSpe[0] == nullptr && regiment->wantedSpeciality->arty == 1) {
            this->redSpe[0] = regiment;
            break;
        }
    }
}

void Game::giveSkirm()
{
    for (auto &regiment : _regimentsBlue) {
        if (regiment == blueSpe[0] || regiment == blueSpe[1] || regiment == blueSpe[2])
            continue;
        if (this->blueSpe[1] == nullptr && regiment->wantedSpeciality->skirm == 1) {
            this->blueSpe[1] = regiment;
            break;
        }
    }
    for (auto &regiment : _regimentsRed) {
        if (regiment == redSpe[0] || regiment == redSpe[1] || regiment == redSpe[2])
            continue;
        if (this->redSpe[1] == nullptr && regiment->wantedSpeciality->skirm == 1) {
            this->redSpe[1] = regiment;
            break;
        }
    }
}

void Game::giveCavalry()
{
    for (auto &regiment : _regimentsBlue) {
        if (regiment == blueSpe[0] || regiment == blueSpe[1] || regiment == blueSpe[2])
            continue;
        if (this->blueSpe[2] == nullptr && regiment->wantedSpeciality->cav == 1) {
            this->blueSpe[2] = regiment;
            break;
        }
    }
    for (auto &regiment : _regimentsRed) {
        if (regiment == redSpe[0] || regiment == redSpe[1] || regiment == redSpe[2])
            continue;
        if (this->redSpe[2] == nullptr && regiment->wantedSpeciality->cav == 1) {
            this->redSpe[2] = regiment;
            break;
        }
    }
}

uint Game::numberOfSpeciality()
{
    uint nb = 0;

    for (int i = 0; i < 3; i++) {
        if (this->blueSpe[i] != nullptr)
            nb++;
        if (this->redSpe[i] != nullptr)
            nb++;
    }
    return nb;
}

bool Game::invalidGame()
{
    if (_nbPlayerBlue == 0 || _nbPlayerRed == 0)
        return true;
    if (this->blueSpe[0] != nullptr && this->redSpe[0] == nullptr 
    || this->blueSpe[0] == nullptr && this->redSpe[0] != nullptr)
        return true;
    if (this->blueSpe[1] != nullptr && this->redSpe[1] == nullptr
    || this->blueSpe[1] == nullptr && this->redSpe[1] != nullptr)
        return true;
    if (this->blueSpe[2] != nullptr && this->redSpe[2] == nullptr
    || this->blueSpe[2] == nullptr && this->redSpe[2] != nullptr)
        return true;
    return false;
}

void Game::display()
{
    Printer::file << "Game " << _id << std::endl;
    Printer::file << "Blue team:" << std::endl;
    for (auto& regiment : _regimentsBlue) {
        Printer::file << "Regiment " << regiment->_name << " : " << regiment->_nbPlayer << " players";
        if (regiment == this->blueSpe[0])
            Printer::file << " (Artillery)";
        if (regiment == this->blueSpe[1])
            Printer::file << " (Skirmisher)";
        if (regiment == this->blueSpe[2])
            Printer::file << " (Cavalry)";
        Printer::file << std::endl;
    }
    Printer::file << "Red team:" << std::endl;
    for (auto& regiment : _regimentsRed) {
        Printer::file << "Regiment " << regiment->_name << " : " << regiment->_nbPlayer << " players";
        if (regiment == this->redSpe[0])
            Printer::file << " (Artillery)";
        if (regiment == this->redSpe[1])
            Printer::file << " (Skirmisher)";
        if (regiment == this->redSpe[2])
            Printer::file << " (Cavalry)";
        Printer::file << std::endl;
    }
    Printer::file << "---------------------" << std::endl;
    Printer::file << "number of speciality : " << this->numberOfSpeciality() << std::endl;
    Printer::file << "total player blue : " << this->_nbPlayerBlue << std::endl;
    Printer::file << "total player red : " << this->_nbPlayerRed << std::endl;
    Printer::file << "total player : " << this->_nbPlayerBlue + this->_nbPlayerRed << std::endl;
    Printer::file << "diff speciality old : " << _diffSpecialityOld << std::endl;
    Printer::file << "ratio : " << this->_ratio << std::endl;
    Printer::file << "---------------------" << std::endl;
}
