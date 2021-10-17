/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** Nibbler
*/

#include "../include/Nibbler.hpp"

Game::Nibbler *nibbler;

Game::Nibbler::Nibbler() : AGame(Arcade::Type::GAME, "Nibbler")
{
    _period = 0.3;
    _map = {0, 0};
    _len = 0;
    _head = 0;
    _score = 0;
    _tmp = Arcade::Events::NONE;
    _start = {0, 0};
    _last = std::chrono::steady_clock::now();
    _evtType = Arcade::Events::NONE;
    std::srand(std::time(nullptr));
}

Game::Nibbler::~Nibbler()
{
}

void Game::Nibbler::load(Graph::AGraph *lib)
{
    _lib = lib;
//    _lib->open("Nibbler", "Ressources/Games/Nibbler/snake.png");
    _lib->setTitle("Nibbler");
    _lib->setIcon("Ressources/Games/Nibbler/snake.png");
    initGame();
    for (std::size_t e = 0; e < _pos.size(); ++e)
        _lib->displayImage(_pos[e], _form[e], _color[e], _size[e]);
}

void Game::Nibbler::initGame(void)
{
    openMap();
    _food = _pos.size();
    _pos.push_back({0, 0});
    _color.push_back(Arcade::ColorIdx::GREEN);
    _size.push_back({16, 16});
    _form.push_back({Arcade::FormIdx::OTHER, "Ressources/Games/Nibbler/food.txt"});
    _start = {((int)_map._width / 2) - 2, (int)_map._height / 2};
    _head = _pos.size();
    _pos.push_back(_start);
    _color.push_back(Arcade::ColorIdx::GREEN);
    _size.push_back({16, 16});
    _form.push_back({Arcade::FormIdx::OTHER, "Ressources/Games/Nibbler/leftHead.txt"});
    for (int e = 0; e < 3; ++e) {
        _pos.push_back({_start._x + e + 1, _start._y});
        _color.push_back(Arcade::ColorIdx::GREEN);
        _size.push_back({16, 16});
        _form.push_back({Arcade::FormIdx::RECT, ""});
    }
    generateFood();
}

Arcade::Events Game::Nibbler::handleEvents() noexcept
{
    Arcade::Events evt = _lib->getEvent();
    _lib->displayWindow();
    //if (evt != Arcade::Events::NONE)
        _evtType = evt;
    return (_evtType);
}

void Game::Nibbler::handleUpdate(double elapsedTime) noexcept
{
    std::chrono::duration<double> diff = std::chrono::steady_clock::now() - _last;
    (void)elapsedTime;

    if (diff.count() > _period) {
        moveTail();
         if (handleMove(_evtType)) {
            _tmp = _evtType;
        } else {
            handleMove(_tmp);
        }
        _last = std::chrono::steady_clock::now();
    }
    for (std::size_t e = 0; e < _pos.size(); ++e) 
        _lib->displayImage(_pos[e], _form[e], _color[e], _size[e]);
}

void Game::Nibbler::setLib(Graph::AGraph *lib) noexcept
{
    _lib = lib;
    _lib->setTitle("Nibbler");
    _lib->setIcon("Ressources/Games/Nibbler/snake.png");
}

bool Game::Nibbler::handleMove(Arcade::Events evt)
{
    bool pass = false;

    if (evt == Arcade::Events::MV_Z && _tmp != Arcade::Events::MV_S)
        pass = moveNibbler(-1, 0, evt);
    else if (evt == Arcade::Events::MV_S && _tmp != Arcade::Events::MV_Z)
        pass = moveNibbler(1, 0, evt);
    else if (evt == Arcade::Events::MV_Q && _tmp != Arcade::Events::MV_D)
        pass = moveNibbler(0, -1, evt);
    else if (evt == Arcade::Events::MV_D && _tmp != Arcade::Events::MV_Q && _tmp != Arcade::Events::NONE)
        pass = moveNibbler(0, 1, evt);
    return (pass);
}

bool Game::Nibbler::moveNibbler(int y, int x, Arcade::Events evt)
{
    std::size_t base = _pos[_head]._y * _map._width + _pos[_head]._x;
    std::size_t emp = base + y * _map._width + x;

    _form[_head]._path = nibbler.at(evt);
    if (lose(emp)) {
        restart();
        return (true);
    }
    _pos[_head]._y += y;
    _pos[_head]._x += x;
    _color[base] = Arcade::ColorIdx::BLACK;
    if (_pos[emp]._x == _pos[_food]._x && _pos[emp]._y == _pos[_food]._y) {
        ++_score;
        addElement();
        generateFood();
    }
    return (true);
}

void Game::Nibbler::addElement(void)
{
    std::size_t last = _pos.size() - 1;

    _pos.push_back({_pos[last]._x, _pos[last]._y});
    _color.push_back(Arcade::ColorIdx::GREEN);
    _size.push_back({16, 16});
    _form.push_back({Arcade::FormIdx::RECT, ""});
}

void Game::Nibbler::moveTail(void)
{
    if (_evtType == Arcade::Events::NONE || (_evtType == Arcade::Events::MV_D && _tmp == Arcade::Events::NONE))
        return;
    for (std::size_t e = _pos.size() - 1; e > _head; --e) {
        _pos[e]._x = _pos[e - 1]._x;
        _pos[e]._y = _pos[e - 1]._y;
    }
}

bool Game::Nibbler::lose(std::size_t emp)
{
    if (_color[emp] == Arcade::ColorIdx::BLUE)
        return (true);
    for (std::size_t i = _head; i < _pos.size(); ++i) {
        if (_pos[emp]._x == _pos[i]._x && _pos[emp]._y == _pos[i]._y) {
            return (true);
        }
    }
    return (false);
}

void Game::Nibbler::restart() noexcept
{
    _tmp = Arcade::Events::NONE;
    _evtType = Arcade::Events::NONE;
    _score = 0;
    initGame();
}

void Game::Nibbler::generateFood(void)
{
    std::size_t place = std::rand() % _len;
    bool next = false;

    for (std::size_t e = place; e != place - 1; ++e) {
        for (std::size_t i = _head; i < _pos.size(); ++i) {
            if (_pos[e]._x == _pos[i]._x && _pos[e]._y == _pos[i]._y) {
                next = true;
                break;
            }
        }
        if (!next && _color[e] == Arcade::ColorIdx::BLACK) {
            _pos[_food] = _pos[e];
            return;
        }
        next = false;
        if (e == _len)
            e = -1;
    }
}

void Game::Nibbler::openMap(void)
{
    std::ifstream file;
    std::stringstream strStream;
    Graph::Position pos = {0, 0};
    std::string scontent;
    const char *content;

    file.open("Ressources/Games/Nibbler/map.txt");
    if (!file)
        throw Arcade::GameError("Impossible to open the file");
    strStream << file.rdbuf();
    scontent = strStream.str();
    if (scontent.find_first_not_of("WAYyGgBbVvRrOo\n") != std::string::npos)
        throw Arcade::GameError("Nibbler: Invalid character inside");
    content = scontent.c_str();
    for (std::size_t e = 0; content[e]; ++e, ++pos._x) {
        if (content[e] == '\n') {
            if (pos._y && (int)_map._width != pos._x)
                throw Arcade::GameError("Nibbler: map not in rectangle shape");
            _map._width = pos._x;
            ++pos._y;
            pos._x = -1;
            continue;
        }
        _pos.push_back(pos);
        _color.push_back((Arcade::ColorIdx)content[e]);
        _size.push_back({16, 16});
        _form.push_back({Arcade::FormIdx::RECT, ""});
    }
    _map._height = pos._y;
    _len = _map._height * _map._width;
}

extern "C" Game::AGame *endPoint(void)
{
    return (nibbler);
}

__attribute__((constructor))
void start(void)
{
    nibbler = new Game::Nibbler();
}

__attribute__((destructor))
void end(void)
{
    delete nibbler;
}

