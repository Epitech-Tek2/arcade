/*
** EPITECH PROJECT, 2021
** Arcade_2020
** File description:
** Core
*/

#include "Core.hpp"
#include <iostream>

Arcade::Core::Core(int const ac, char ** const av) : _run{true}, _menu{true}, _cgraph{0}, _cgame{0}
{
    if (ac != 2)
        throw FatalError("Core: Invalid number of arguments");

    Arcade::ILib *lib{_loader.getInstance(av[1], "endPoint")};
    std::string name{lib->getName()};
    std::vector<std::string> libs = _loader.getLibrariesPath();

    if (lib->getType() != Arcade::Type::GRAPH)
        throw FatalError("Core: The argument must be a graphical library.");
    _graphs.push_back(static_cast<Graph::AGraph *>(lib));
    for (std::vector<std::string>::const_iterator i = libs.cbegin(), et = libs.cend(); et != i; ++i) {
        lib = _loader.getInstance(*i, "endPoint");
        if (lib->getType() == Arcade::Type::GRAPH && name.compare(lib->getName()))
            _graphs.push_back(static_cast<Graph::AGraph *>(lib));
        else if (lib->getType() == Arcade::Type::GAME) {
            _games.push_back(static_cast<Game::AGame *>(lib));
            _scores.init(_games.back()->getName());
        }
    }
    _scoreboard = _scores.getScores();
    if (_games.empty())
        throw FatalError("Core: Must have one game library at least.");
    initNames();
}

void Arcade::Core::initNames() noexcept
{
    for (std::vector<Graph::AGraph *>::const_iterator i = _graphs.cbegin(), et = _graphs.cend(); et != i; ++i)
        _Ngraphs.push_back((*i)->getName());
    for (std::vector<Game::AGame *>::const_iterator i = _games.cbegin(), et = _games.cend(); et != i; ++i)
        _Ngames.push_back((*i)->getName());
}

Arcade::Core::~Core()
{
}

void Arcade::Core::changeGraph(std::string const &graph)
{
std::vector<Graph::AGraph *>::const_iterator i = _graphs.begin();

    for (; i != _graphs.end(); ++i) {
        if (!graph.compare((*i)->getName())) {
            _cgraph = i - _graphs.begin();
            return;
    }
}
throw MinorError("Core: \"" + graph + "\": unknown game");
}

void Arcade::Core::changeGame(std::string const &game)
{
    std::vector<Game::AGame *>::const_iterator i = _games.begin();

    for (; i != _games.end(); ++i) {
        if (!game.compare((*i)->getName())) {
            _cgame = i - _games.begin();
            return;
	}
    }
    throw MinorError("Core: \"" + game + "\": unknown game");
}

void Arcade::Core::handleLibEvents(Arcade::Events const evt)
{
    if (evt == Arcade::Events::NEXT_GAME) {
        _cgame = (_cgame >= _games.size()) ? 0 : _cgame + 1;
    } else if (evt == Arcade::Events::PREV_GAME) {
        _cgame = (!_cgame) ? _games.size() - 1 : _cgame - 1;
    } else if (evt == Arcade::Events::NEXT_LIB) {
        _cgraph = (_cgraph >= _graphs.size()) ? 0 : _cgraph + 1;
    } else if (evt == Arcade::Events::PREV_LIB) {
        _cgraph = (!_cgraph) ? _graphs.size() - 1 : _cgraph - 1;
    }
}

void Arcade::Core::handleCoreEvents(Arcade::Events &evt, Game::Menu &menu)
{
    if (Arcade::Events::QUIT == evt) {
	_graphs[_cgraph]->close();
	_games[_cgame]->restart();
	_run = false;
    }
    if (_menu) {
	if (Arcade::Events::MENU == evt) {
	    _graphs[_cgraph]->close();
	    changeGame(menu.getGame());
	    changeGraph(menu.getGraph());
	    _graphs[_cgraph]->open("Arcade", "Ressources/wallpaper.png");
	    _games[_cgame]->load(_graphs[_cgraph]);
	    _menu = false;
	    evt = menu.handleEvents();
	    handleCoreEvents(evt, menu);
	}
    } else {
	if (Arcade::Events::MENU == evt) {
	    _menu = true;
 	    _games[_cgame]->restart();
	    menu.setLib(_graphs[_cgraph]);
	    _graphs[_cgraph]->setTitle("Arcade");
	    _graphs[_cgraph]->setIcon("Ressources/wallpaper.png");
	}
	if (evt == Arcade::Events::NEXT_LIB) {
	    _graphs[_cgraph]->close();
	    ++_cgraph;
	    if (_graphs.size() == _cgraph)
		_cgraph = 0;
	    _graphs[_cgraph]->open("Arcade", "Ressources/wallpaper.png");
	    _games[_cgame]->setLib(_graphs[_cgraph]);
	} else if (evt == Arcade::Events::PREV_LIB) {
	    _graphs[_cgraph]->close();
	    if (0 == _cgraph)
		_cgraph = _graphs.size() - 1;
	    else
		--_cgraph;
	    _graphs[_cgraph]->open("Arcade", "Ressources/wallpaper.png");
	    _games[_cgame]->setLib(_graphs[_cgraph]);
	}
	return;
	handleLibEvents(evt);
    }
}

void Arcade::Core::run(void)
{
    std::chrono::_V2::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapse = std::chrono::steady_clock::now() - begin;
    Game::Menu _Menu(_Ngraphs, _Ngames, _scoreboard);

    try {
	_graphs[_cgraph]->open("Arcade", "Ressources/wallpaper.png");
	_Menu.load(_graphs[_cgraph]);
	Arcade::Events evt = _Menu.handleEvents();
	handleCoreEvents(evt, _Menu);
	while (_run) {
	    if (_menu) {
		elapse = std::chrono::steady_clock::now() - begin;
		_Menu.handleUpdate(elapse.count());
		_Menu.display();
		evt = _Menu.handleEvents();
		handleCoreEvents(evt, _Menu);
	    } else {
		elapse = std::chrono::steady_clock::now() - begin;
		_games[_cgame]->handleUpdate(elapse.count());
		evt = _games[_cgame]->handleEvents();
		handleCoreEvents(evt, _Menu);
	    }
	}
    } catch (Arcade::Error const &err)
    {
	std::cerr << err.what() << std::endl;
    }
}
