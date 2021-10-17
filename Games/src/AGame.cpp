
/*
** Arcade
** jonathan-Cohen && Sarah-Keppler
*/

#include "../include/IGame.hpp"

Game::AGame::AGame(Arcade::Type const type, std::string const &name) noexcept : _type{type}, _name{name}
{
}

Arcade::Type Game::AGame::getType() const noexcept
{
    return _type;
}

std::string Game::AGame::getName() const noexcept
{
    return _name;
}
