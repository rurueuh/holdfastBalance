#include "Regiment.hpp"

Regiment::Regiment(const std::string &name, int nbSoldiers, Speciality *wantedSpeciality)
    : _name(name), _nbPlayer(nbSoldiers), wantedSpeciality(wantedSpeciality)
{
}

Regiment::~Regiment()
{
}
