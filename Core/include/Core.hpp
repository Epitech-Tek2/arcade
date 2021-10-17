/*
** Arcade
** Sarah-Keppler
*/

#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include "Loader.hpp"
#include "Score.hpp"
#include "Menu.hpp"
#include "../../Graphs/include/IGraph.hpp"
#include "../../Games/include/IGame.hpp"
#include "../../Common/ILib.hpp"
#include "../../Common/Error.hpp"

namespace Arcade
{
    class Core
    {
    public:
	/**
	 * @brief Verify arguments, load all the libraries and verify them.
	 *
	 * @param number of arguments.
	 * @param arguments list.
	 */
	Core(int const ac, char ** const av);

	/**
	 * @brief Close all the libraries and destroy all the graphical elements.
	 */
	~Core();

	/**
	 * @brief Load, run and display scenes.
	 */
	void run();
    protected:

	/**
	 * @brief change actual game
	 */
	void initNames(void) noexcept;

	/**
	 * @brief change the actual Graph
	 */
	void changeGraph(std::string const &Graph);

	/**
	 * @brief change actual game
	 */
	void changeGame(std::string const &game);

	/**
	 * @brief change actual game
	 *
	 * @param key event made in game
	 */
	void handleCoreEvents(Arcade::Events &key, Game::Menu &menu);

	/**
	 * @brief change actual game
	 *
	 * @param key event made in game
	 */
	void handleLibEvents(Arcade::Events const key);
    private:
	bool _run;
	bool _menu;
	std::size_t _cgraph;
	std::size_t _cgame;
	std::vector<Graph::AGraph *> _graphs;
	std::vector<Game::AGame *> _games;
	std::vector<std::string> _Ngraphs;
	std::vector<std::string> _Ngames;
	Arcade::Loader _loader;
	Arcade::Score _scores;
	Arcade::Events _evtType;
	char _evt;
	std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>> _scoreboard;
	std::string _playerName;
	int _score;
    };
}

#endif /* ARCADE_CORE_HPP */
