/*
** Arcade
** Sarah-Keppler
*/

#ifndef ARCADE_LOADER_HPP
#define ARCADE_LOADER_HPP

#include <string>
#include <vector>
#include <memory>
#include <fcntl.h>
#include <dlfcn.h>
#include <dirent.h>
#include "../../Common/Error.hpp"
#include "../../Games/include/IGame.hpp"
#include "../../Graphs/include/IGraph.hpp"

namespace Arcade
{
    /**
     * @brief Instance of IGame ir IGraph
     */
    class Loader {
    public:
	Loader() = default;

	/**
	 * @brief Close all the librairies.
	 */
	~Loader();

	/**
	 * @brief Load the library given in the path.
	 *
	 * @param library path.
	 * @param end point name.
	 *
	 * @return a pointer of the library class.
	 */
	Arcade::ILib *getInstance(std::string const &path, std::string const &name);

	/**
	 * @brief open a directory and re vector of path files
	 *
	 * @return vector of path files
	 */
	std::vector<std::string> getLibrariesPath(void);

    private:
	std::vector<void *> _handle;
    };
}

#endif /* ARCADE_LOADER_HPP */
