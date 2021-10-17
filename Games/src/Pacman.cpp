/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** Pacman
*/

#include "Pacman.hpp"

Game::Pacman *pacman;

Game::Pacman::Pacman() : AGame(Arcade::Type::GAME, "Pacman")
{
    _map = {0, 0};
    _offset = {20, 5};
    _period = 0.3;
    _ghostPeriod = 0.3;
    _score = 0;
    _life = 3;
    _len = 0;
    _last = std::chrono::steady_clock::now();
    _game = std::chrono::steady_clock::now();
    _pacgums = false;
    _nbpacgums = 0;
    _nbGhostEat = 0;
    _level = 1;
    _nbimage = 0;
    _icscore = 0;
    _tmp = Arcade::Events::NONE;
    _ghost.fill({NONE, false});
    _evtType = Arcade::Events::NONE;
    std::srand(std::time(nullptr));
}

Game::Pacman::~Pacman()
{
}

void Game::Pacman::load(Graph::AGraph *lib)
{
    _lib = lib;
    //_lib->open("Titre", "Ressources/Games/Pacman/ghost.png");
    _lib->setTitle("Pacman");
    _lib->setIcon("Ressources/Games/Pacman/ghost.png");
    initGame();
    display();
}

void Game::Pacman::initGame(void)
{
    _pos.clear();
    _size.clear();
    _form.clear();
    _color.clear();
    _text.clear();
    _nbpacgums = 0;
    openMap();

    _pos.push_back({12, 14});
    _color.push_back(Arcade::ColorIdx::RED);
    _size.push_back({16, 16});
    _form.push_back(ghost.at(BLINKY));

    _pos.push_back({13, 14});
    _color.push_back(Arcade::ColorIdx::BLUE_GREEN);
    _size.push_back({16, 16});
    _form.push_back(ghost.at(INKY));

    _pos.push_back({14, 14});
    _color.push_back(Arcade::ColorIdx::RED_VIOLET);
    _size.push_back({16, 16});
    _form.push_back(ghost.at(PINKY));

    _pos.push_back({15, 14});
    _color.push_back(Arcade::ColorIdx::ORANGE);
    _size.push_back({16, 16});
    _form.push_back(ghost.at(CLYDE));

    _pos.push_back({14, 23});
    _color.push_back(Arcade::ColorIdx::YELLOW);
    _size.push_back({16, 16});
    _form.push_back({Arcade::FormIdx::OTHER, "Ressources/Games/Pacman/forms/rightPacman.txt"});

    _nbimage = _pos.size();

    _pos.push_back({(int)_map._width + 2, 0});
    _size.push_back({6, 1});
    _text.push_back({"SCORE: "});

    _icscore = _text.size() - 1;
}

Arcade::Events Game::Pacman::handleEvents() noexcept
{
    Arcade::Events evt = _lib->getEvent();
    _lib->displayWindow();
    //if (evt != Arcade::Events::NONE)
    _evtType = evt;
    if (!_life)
        return (Arcade::Events::MENU);
    return (_evtType);
}

void Game::Pacman::handleUpdate(double elapsedTime) noexcept
{
    std::chrono::duration<double> diff = std::chrono::steady_clock::now() - _last;
    std::chrono::duration<double> difGhost = std::chrono::steady_clock::now() - _lastGhost;

    (void)elapsedTime;
    if (difGhost.count() > _ghostPeriod) {
        handleGhost();
        _lastGhost = std::chrono::steady_clock::now();
    }
    if (diff.count() > _period) {
        if (handleMove(_evtType)) {
            _tmp = _evtType;
        } else {
            handleMove(_tmp);
        }
        _last = std::chrono::steady_clock::now();
    }
    handleCollision();
    if (_pacgums)
        endChase();
    //std::cerr << _score << " " << (_nbGhostEat * 200) << " " << (_nbpacgums - 1) << " " << _level << std::endl;
    if (_score - (_nbGhostEat * 200) == (_nbpacgums - 1) * _level)
        restart(true);
    display();
}

void Game::Pacman::restart() noexcept
{
    _pos.clear();
    _size.clear();
    _form.clear();
    _color.clear();
    _text.clear();
    _nbpacgums = 0;
    _score = 0;
    initGame();
    _pos[_len + BLINKY] = {12, 14};
    _pos[_len + INKY] = {13, 14};
    _pos[_len + PINKY] = {14, 14};
    _pos[_len + CLYDE] = {15, 14};
    _pos[_len + PACMAN] = {14, 23};
    _ghost.fill({NONE, false});
    _tmp = Arcade::Events::NONE;
    _evtType = Arcade::Events::NONE;
    _game = std::chrono::steady_clock::now();
}

void Game::Pacman::setLib(Graph::AGraph *lib) noexcept
{
    _lib = lib;
    _lib->setTitle("Pacman");
    _lib->setIcon("Ressources/Games/Pacman/ghost.png");
}

void Game::Pacman::display(void)
{
    Graph::Position cpos = {0, 0};
    Graph::Text ctext = {""};

    for (std::size_t e = 0; e < _nbimage; ++e) {
        cpos._x = _pos[e]._x + _offset._width;
        cpos._y = _pos[e]._y + _offset._height;
        _lib->displayImage(cpos, _form[e], _color[e], _size[e]);
    }
    cpos._x = _offset._width;
    cpos._y = _offset._height + _map._height + 1;
    for (std::size_t i = 0; i < _life; ++i, cpos._x += 2)
        _lib->displayImage(cpos, _form[_len + PACMAN], _color[_len + PACMAN], _size[_len + PACMAN]);
    for (std::size_t e = 0; e < _text.size(); ++e) {
        //std::cerr << _pos[e + _nbimage]._x + _offset._width << " " << _pos[e + _nbimage]._y + _offset._height << std::endl;
        cpos._x = _pos[e + _nbimage]._x + _offset._width;
        cpos._y = _pos[e + _nbimage]._y + _offset._height;
        if (e == _icscore)
            ctext = _text[e]._text + std::to_string(_score);
        else
            ctext = _text[e]._text;
        _lib->displayText(ctext, cpos, Arcade::ColorIdx::WHITE, _size[_nbimage + e]);
    }
}

void Game::Pacman::endChase(void)
{
    std::chrono::duration<double> chase = std::chrono::steady_clock::now() - _chase;

    if (chase.count() > 10) {
        _pacgums = false;
        _form[_len + BLINKY] = ghost.at(BLINKY);
        _form[_len + INKY] = ghost.at(INKY);
        _form[_len + PINKY] = ghost.at(PINKY);
        _form[_len + CLYDE] = ghost.at(CLYDE);
        _ghostPeriod -= 0.2;
    }
}

bool Game::Pacman::handleMove(Arcade::Events evt)
{
    bool pass = false;

    if (evt == Arcade::Events::MV_Z)
        pass = movePacman(_len + PACMAN, -1, 0, evt);
    else if (evt == Arcade::Events::MV_S)
        pass = movePacman(_len + PACMAN, 1, 0, evt);
    else if (evt == Arcade::Events::MV_Q)
        pass = movePacman(_len + PACMAN, 0, -1, evt);
    else if (evt == Arcade::Events::MV_D)
        pass = movePacman(_len + PACMAN, 0, 1, evt);
    return (pass);
}

bool Game::Pacman::movePacman(std::size_t p, int y, int x, Arcade::Events evt)
{
    std::size_t base = _pos[p]._y * _map._width + _pos[p]._x;
    std::size_t emp = calcEmplacement(base, p, y, x);

    _form[_len + PACMAN]._path = pacman.at(evt);
    if (_color[emp] != Arcade::ColorIdx::BLUE && _color[emp] != Arcade::ColorIdx::VIOLET) {
        _color[base] = Arcade::ColorIdx::BLACK;
        _form[base] = {Arcade::FormIdx::RECT, ""};
        if (_color[emp] == Arcade::ColorIdx::WHITE)
            ++_score;
        if (_color[emp] == Arcade::ColorIdx::YELLOW_ORANGE)
            inverseChase();
        moveEntity(p, y, x);
        return (true);
    }
    return (false);
}

void Game::Pacman::handleGhost(void)
{
    std::chrono::duration<double> dif = std::chrono::steady_clock::now() - _game;
    if (dif.count() > 10)
        moveGhost(BLINKY, _len + BLINKY);
    if (dif.count() > 12)
        moveGhost(INKY, _len + INKY);
    if (dif.count() > 15)
        moveGhost(PINKY, _len + PINKY);
    if (dif.count() > 17)
        moveGhost(CLYDE, _len + CLYDE);
}

void Game::Pacman::moveGhost(AIname ref, std::size_t p)
{
    std::vector<std::pair<AImove, Graph::Position>> pos = getGhostPossibility(ref, p);
    if (!pos.size()) return;
    std::size_t move = std::rand() % pos.size();

    moveEntity(p, pos[move].second._y, pos[move].second._x);
    _ghost[ref].first = pos[move].first;
}

std::vector<std::pair<Game::Pacman::AImove, Graph::Position>> Game::Pacman::getGhostPossibility(AIname ref, std::size_t p)
{
    std::vector<std::pair<AImove, Graph::Position>> pos;
    std::size_t base = _pos[p]._y * _map._width + _pos[p]._x;

    if (_ghost[ref].first == Game::Pacman::NONE || !_ghost[ref].second) {
        if (_color[base] == Arcade::ColorIdx::VIOLET) {
            _ghost[ref].second = true;
        }
        pos.push_back({UP, {0, -1}});
        return (pos);
    }
    if (checkGhost(ref, DOWN, {0, -1}, base, p))
        pos.push_back({UP, {0, -1}});
    if (checkGhost(ref, UP, {0, 1}, base, p))
        pos.push_back({DOWN, {0, 1}});
    if (checkGhost(ref, RIGTH, {-1, 0}, base, p))
        pos.push_back({LEFT, {-1, 0}});
    if (checkGhost(ref, LEFT, {1, 0}, base, p))
        pos.push_back({RIGTH, {1, 0}});
    return (pos);
}

bool Game::Pacman::checkGhost(AIname ref, AImove move, Graph::Position dif, std::size_t base, std::size_t p)
{
    std::size_t emp = calcEmplacement(base, p, dif._y, dif._x);

    if (_ghost[ref].first != move && _color[emp] != Arcade::ColorIdx::BLUE && _color[emp] != Arcade::ColorIdx::VIOLET)
        return (true);
    return (false);
}

void Game::Pacman::moveEntity(std::size_t p, int y, int x)
{
    // faire une teleportation de l'autre coté de la map si besoin
    if ((int)_pos[p]._x + x >= (int)_map._width)
        _pos[p]._x = 0;
    else if ((int)_pos[p]._x + x < 0)
        _pos[p]._x = _map._width - 1;
    else
        _pos[p]._x += x;
    if ((int)_pos[p]._y + y >= (int)_map._height)
        _pos[p]._y = 0;
    else if ((int)_pos[p]._y + y < 0)
        _pos[p]._y = _map._height - 1;
    else
        _pos[p]._y += y;
}

void Game::Pacman::handleCollision(void)
{
    for (std::size_t e = 0; e < 4; ++e) {
        if (_lib->checkCollision(_pos[_len + e], _size[_len + e], _pos[_len + PACMAN], _size[_len + PACMAN])) {
            pacmanCollision(e);
        }
    }
}

void Game::Pacman::pacmanCollision(std::size_t ic)
{
    if (_pacgums) {
        ++_nbGhostEat;
        _score += 200;
        _pos[_len + ic] = {12 + (int)ic, 14};
        _ghost[ic] = {NONE, false};
        _form[_len + ic] = ghost.at((AIname)ic);
        return;
    }
    restart(false);
}

void Game::Pacman::restart(bool win)
{
    if (win) {
        _pos.clear();
        _size.clear();
        _form.clear();
        _color.clear();
        _text.clear();
        _nbpacgums = 0;
        initGame();
        _period /= 1.2;
        ++_level;
    } else {
        --_life;
    }
    _pos[_len + BLINKY] = {12, 14};
    _pos[_len + INKY] = {13, 14};
    _pos[_len + PINKY] = {14, 14};
    _pos[_len + CLYDE] = {15, 14};
    _pos[_len + PACMAN] = {14, 23};
    _ghost.fill({NONE, false});
    _tmp = Arcade::Events::NONE;
    _evtType = Arcade::Events::NONE;
    _game = std::chrono::steady_clock::now();
}

void Game::Pacman::inverseChase(void)
{
    Graph::Form form = {Arcade::FormIdx::OTHER, "Ressources/Games/Pacman/forms/chasedGhost.txt"};

    ++_score;
    _pacgums = true;
    _form[_len + BLINKY] = form;
    _form[_len + INKY] = form;
    _form[_len + PINKY] = form;
    _form[_len + CLYDE] = form;
    _ghostPeriod += 0.2;
    _chase = std::chrono::steady_clock::now();
}

std::size_t Game::Pacman::calcEmplacement(std::size_t base, std::size_t p, int y, int x)
{
    // 4 condition de verification si sur une tranche de la map
    if ((int)_pos[p]._x + x >= (int)_map._width)
        return (base - _pos[p]._x);
    if ((int)_pos[p]._x + x < 0)
        return (base - _pos[p]._x + _map._width - 1);
    if ((int)_pos[p]._y + y >= (int)_map._height)
        return (_pos[x]._x);
    if ((int)_pos[p]._y + y < 0)
        return (_map._width * (_map._height - 1) + _pos[x]._y);
    return (base + y * _map._width + x);
}

void Game::Pacman::openMap(void)
{
    std::ifstream file;
    std::stringstream strStream;
    Graph::Position pos = {0, 0};
    std::string scontent;
    const char *content;

    file.open("Ressources/Games/Pacman/forms/IPacman.txt");
    if (!file)
        throw Arcade::GameError("Impossible to open the file");
    strStream << file.rdbuf();
    scontent = strStream.str();
    if (scontent.find_first_not_of("WAYyGgBbVvRrOo \n") != std::string::npos)
        throw Arcade::GameError("Pacman: Invalid character inside");
    content = scontent.c_str();
    for (std::size_t e = 0; content[e]; ++e, ++pos._x) {
        if (content[e] == '\n') {
            if (pos._y && (int)_map._width != pos._x)
                throw Arcade::GameError("Pacman: map not in rectangle");
            _map._width = pos._x;
            ++pos._y;
            pos._x = -1;
            continue;
        }
        _pos.push_back(pos);
        _color.push_back((Arcade::ColorIdx)content[e]);
        _size.push_back({16, 16});
        if (content[e] == 'W') {
            _form.push_back({Arcade::FormIdx::OTHER, "Ressources/Games/Pacman/forms/pacgum.txt"});
            ++_nbpacgums;
        } else if (content[e] == 'o') {
            _form.push_back({Arcade::FormIdx::OTHER, "Ressources/Games/Pacman/forms/megaPacgum.txt"});
            ++_nbpacgums;
        } else {
            _form.push_back({Arcade::FormIdx::RECT, ""});
        }
    }
    _map._height = pos._y;
    _len = _map._height * _map._width;
}

extern "C" Game::AGame *endPoint(void)
{
    return (pacman);
}

__attribute__((constructor))
void start(void)
{
    pacman = new Game::Pacman();
}

__attribute__((destructor))
void end(void)
{
    delete pacman;
}
