/*
** Arcade
** Sarah-Keppler
*/

#include "Error.hpp"

Arcade::Error::Error(std::string const &message) noexcept : _message{message}
{
}

char const *Arcade::Error::what() const noexcept
{
    return _message.c_str();
}
