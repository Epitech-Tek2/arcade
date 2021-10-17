/*
** Arcade | Games
** Sarah-Keppler
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "../../Common/Error.hpp"
#include "../include/Menu.hpp"

Game::Menu::Menu(std::vector<std::string> const &graphLibs, std::vector<std::string> const &gameLibs, std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>> scores) noexcept : Game::AGame{Arcade::Type::MENU, "Main Menu"}, _graphLibs{graphLibs}, _gameLibs{gameLibs}, _scores{scores}, _idxGame{0}, _idxGraph{0}, _idxScore{0}, _editing{0}, _playerName{""}
{
    _map._width = 0;
    _map._height = 0;
}

void Game::Menu::load(Graph::AGraph *lib)
{
    _lib = lib;
    addComponent(Graph::Position{17, 43}, Graph::Size{0, 50}, Graph::Form{Arcade::FormIdx::RECT}, Arcade::ColorIdx::WHITE, Graph::Text{_playerName});
    addComponent(Graph::Position{53, 43}, Graph::Size{240, 50}, Graph::Form{Arcade::FormIdx::RECT}, Arcade::ColorIdx::WHITE, Graph::Text{"PRESS M TO PLAY"});
    addComponent(Graph::Position{3, 20}, Graph::Size{16, 16}, Graph::Form{Arcade::FormIdx::OTHER, "Ressources/arrow.txt"}, Arcade::ColorIdx::WHITE, Graph::Text{""});
    addComponent(Graph::Position{23, 20}, Graph::Size{16, 16}, Graph::Form{Arcade::FormIdx::OTHER, "Ressources/arrow.txt"}, Arcade::ColorIdx::WHITE, Graph::Text{""});
    
    int posY = 15;
    for (std::vector<std::string>::const_iterator it = _graphLibs.cbegin(), et = _graphLibs.cend(); et != it; ++it) {
	addComponent(Graph::Position{5, posY}, Graph::Size{100, 50}, Graph::Form{Arcade::FormIdx::RECT}, Arcade::ColorIdx::WHITE, Graph::Text{*it});
	posY += 5;
    }
    
    posY = 15;
    for (std::vector<std::string>::const_iterator it = _gameLibs.cbegin(), et = _gameLibs.cend(); et != it; ++it) {
	addComponent(Graph::Position{25, posY}, Graph::Size{100, 50}, Graph::Form{Arcade::FormIdx::RECT}, Arcade::ColorIdx::WHITE, Graph::Text{*it});
	posY += 5;
    }
    for (std::vector<std::string>::const_iterator it = _gameLibs.cbegin(), et = _gameLibs.cend(); et != it; ++it) {
	posY = 15;
	for (int i = 0; 3 > i; ++i) {
	    addComponent(Graph::Position{45, posY}, Graph::Size{16 * _scores.at(*it)[i].first.size(), 50}, Graph::Form{Arcade::FormIdx::RECT}, Arcade::ColorIdx::WHITE, Graph::Text{_scores.at(*it)[i].first});
	    addComponent(Graph::Position{65, posY}, Graph::Size{16 * std::to_string(_scores.at(*it)[i].second).size(), 50}, Graph::Form{Arcade::FormIdx::RECT}, Arcade::ColorIdx::WHITE, Graph::Text{std::to_string(_scores.at(*it)[i].second)});
	    posY += 5;
	}
    }
    openMap();
}

void Game::Menu::addComponent(Graph::Position const &pos, Graph::Size const &size, Graph::Form const &form, Arcade::ColorIdx const colorIdx, Graph::Text const &text) noexcept
{
    _pos.emplace_back(pos);
    _size.emplace_back(size);
    _form.emplace_back(form);
    _color.emplace_back(colorIdx);
    _text.emplace_back(text);
}

void Game::Menu::openMap(void)
{
    std::ifstream file;
    std::stringstream strStream;
    Graph::Position pos = {0, 0};
    std::string scontent;
    const char *content;

    file.open("Ressources/Menu/IMenu.txt");
    if (!file)
        throw Arcade::GameError("Impossible to open the file");
    strStream << file.rdbuf();
    scontent = strStream.str();
    if (scontent.find_first_not_of("WAYyGgBbVvRrOo\n") != std::string::npos)
        throw Arcade::GameError("Menu: Invalid character inside");
    content = scontent.c_str();
    //std::cout << "Content {" << std::endl << content << std::endl << "}" << std::endl;
    for (std::size_t e = 0; content[e]; ++e, ++pos._x) {
        if (content[e] == '\n') {
            if (pos._y && (int)_map._width != pos._x)
                throw Arcade::GameError("Menu: map not in rectangle shape");
            _map._width = pos._x;
            ++pos._y;
            pos._x = -1;
            continue;
        }
	//std::cout << "Pos: " << pos._x << "," << pos._y << std::endl;
	addComponent(pos, {16, 16}, {Arcade::FormIdx::RECT}, (Arcade::ColorIdx)content[e], Graph::Text{""});
    }
    _map._height = pos._y;
}

Arcade::Events Game::Menu::handleEvents() noexcept
{
    //std::cout << "Retrieve events . . ." << std::endl;
    Arcade::Events evt = _lib->getEvent();
    //std::cout << "Get events!" << std::endl;
    if (Arcade::Events::QUIT == evt) {
	std::cout << "Quit . . . {";
	std::cout << "OK}" << std::endl;
	return evt;
    }
    if (Arcade::Events::MENU == evt)
	return evt;
    if (Arcade::Events::RESTART == evt) {
	if (_editing)
	    _editing = 0;
	else {
	    _editing = 1;
	    _playerName = "";
	    _size[0]._width = 0;
	}
	return evt;
    }
    if (_editing) {
	char c = _lib->getEventChar();
	if ((c >= 65 && c <= 90) || (97 <= c && 122 >= c)) {
	    if (10 != _playerName.size()) {
		_playerName += c;
		_text[0]._text = _playerName;
		_size[0]._width += 16;
	    }
	}
	return evt;
    }
    if (Arcade::Events::PREV_LIB == evt) {
	if (0 == _idxGraph)
	    _idxGraph = _graphLibs.size() - 1;
	else
	    --_idxGraph;
    }
    if (Arcade::Events::NEXT_LIB == evt) {
	if (_idxGraph == _graphLibs.size() - 1)
	    _idxGraph = 0;
	else
	    ++_idxGraph;
    }
    if (Arcade::Events::PREV_GAME == evt) {
	if (0 == _idxGame)
	    _idxGame = _gameLibs.size() - 1;
	else
	    --_idxGame;
    }
    if (Arcade::Events::NEXT_GAME == evt) {
	if (_idxGame == _gameLibs.size() - 1)
	    _idxGame = 0;
	else
	    ++_idxGame;
    }
    if (Arcade::Events::MV_D == evt) {
	if (_idxScore == _gameLibs.size() - 1)
	    _idxScore = 0;
	else
	    ++_idxScore;
    }
    if (Arcade::Events::MV_Q == evt) {
	if (_idxScore == 0)
	    _idxScore = _gameLibs.size() - 1;
	else
	    --_idxScore;
    }
    return Arcade::Events::NONE;
}

void Game::Menu::handleUpdate(double elapsedTime) noexcept
{
    _pos[2]._y = 16 + _idxGraph * 5;
    _pos[3]._y = 16 + _idxGame * 5;
    return;
    std::cout << elapsedTime << std::endl;
}

void Game::Menu::display() noexcept
{
    _lib->displayWindow(); // a voir avec Jonathan
    std::size_t idx = 4 + _gameLibs.size() + _graphLibs.size();
    std::size_t mapIdx = idx + (3 * 6);
    for (std::size_t i = mapIdx; _pos.size() > i; ++i)
	_lib->displayImage(_pos[i], _form[i], _color[i], _size[i]);
    if (0 != _playerName.size())
	_lib->displayText(_text[0], _pos[0], _color[0], _size[0]);
    _lib->displayText(_text[1], _pos[1], _color[1], _size[1]);
    for (std::size_t i = 2; 4 > i; ++i) {
	_lib->displayImage(_pos[i], _form[i], _color[i], _size[i]);
    }

    for (std::size_t i = 4; idx > i; ++i)
	_lib->displayText(_text[i], _pos[i], _color[i], _size[i]);
    idx += (_idxGame * 6);
    for (std::size_t i = idx; (6 + idx) > i; ++i) {
	if (0 != _text[i]._text.size())
	    _lib->displayText(_text[i], _pos[i], _color[i], _size[i]);
    }
    //std::cout << "Display window . . ." << std::endl;
    //std::cout << "Displayed" << std::endl;
    return;
}

void Game::Menu::restart() noexcept
{
    _idxGame = _idxGraph = _idxScore = 0;
}

void Game::Menu::setLib(Graph::AGraph *lib) noexcept
{
    _lib = lib;
    _lib->setTitle("Arcade");
    _lib->setIcon("Ressources/wallpaper.png");
}

std::string Game::Menu::getGame() const noexcept
{
    return _gameLibs[_idxGame];
}

std::string Game::Menu::getGraph() const noexcept
{
    return _graphLibs[_idxGraph];
}
