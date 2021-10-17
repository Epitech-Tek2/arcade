/*
** Arcade tests
** Sarah-Keppler
*/

#include <iostream>
#include "Error.hpp"
#include "Arcade.hh"
#include "ILib.hpp"

int main(int const ac, char ** const av)
{
    try {
	if (2 != ac)
	    throw Arcade::Error{std::string{av[0]} + " need one argument."};
    } catch (Arcade::Error const &err) {
	std::cerr << err.what() << std::endl;
	return 84;
    }
    return 0;
}
