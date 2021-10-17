/*
** Arcade
** Sarah-Keppler
*/

#ifndef ARCADE_ILIB_HPP_
#define ARCADE_ILIB_HPP_

#include <iostream>
#include "Arcade.hh"

namespace Arcade {
    class ILib
    {
    public:
        /**
	 * @brief Set the type and the name of the library.
	 *
	 * @param type of the library.
	 * @param name of the library.
	 */
	ILib() = default;
	~ILib() = default;

	/**
	 * @brief Get the library type.
	 *
	 * @param type of the library.
	 */
	virtual Arcade::Type getType() const noexcept = 0;

	/**
	 * @brief Get the library name.
	 *
	 * @param name of the library.
	 */
	virtual std::string getName() const noexcept = 0;
    };
}

#endif /* ARCADE_ILIB_HPP_ */
