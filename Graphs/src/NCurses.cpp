/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** NCurses
*/

#include "../include/NCurses.hpp"

Graph::NCurses *ncurses;

Graph::NCurses::NCurses() : AGraph{Arcade::Type::GRAPH, "NCurses"}
{
}

void Graph::NCurses::open(std::string const &title, std::string const &icon)
{
    (void)title;
    (void)icon;
    initscr();
    cbreak();
    keypad(nullptr, TRUE);
    timeout(100);
    start_color();
    for (int e = 1; e < 255; e++)
        init_pair(e, e, 0);
    clear();
    curs_set(0);
    refresh();
}

void Graph::NCurses::close()
{
    endwin();
}

void Graph::NCurses::setTitle(std::string const &title) noexcept
{
    (void)title;
}

void Graph::NCurses::setIcon(std::string const &icon)
{
    (void)icon;
}

Arcade::Events Graph::NCurses::getEvent() noexcept
{
    std::string keys("zsqdlkgftmo");
    std::size_t found = 0;

    _evtType = Arcade::Events::NONE;
    _evt = '\0';
    _evt = getch();
    found = keys.find(_evt);
    if (std::string::npos != found)
        _evtType = (Arcade::Events)found;
    return (_evtType);
}

char Graph::NCurses::getEventChar() const noexcept
{
    return _evt;
}

int Graph::NCurses::checkCollision(Position const &pos1, Size const &size1, Position const &pos2, Size const &size2) const noexcept
{
    std::pair<int, int> s1 = {size1._height / 16, size1._width / 16};
    std::pair<int, int> s2 = {size2._height / 16, size2._width / 16};

    if (pos1._x < pos2._x + s2.second && pos1._x + s1.second > pos2._x &&
        pos1._y < pos2._y + s2.first && pos1._y +s1.first > pos2._y)
        return (1);
    return (0);
}

void Graph::NCurses::displayWindow() noexcept
{
    noecho();
    clear();
    curs_set(0);
    refresh();
}

std::pair<Graph::Size, Arcade::ColorIdx>
Graph::NCurses::getEntityFromFile(Graph::Form &form, Graph::Size &size)
{
    std::ifstream file(form._path);
    std::string line;
    std::array<std::size_t, 15> characters;
    std::string ref = "WAYyGgBbVvRrOo ";
    std::size_t position = 0;
    std::pair<Graph::Size, Arcade::ColorIdx> entity;
    std::size_t tmp = 0;

    entity.first._width = size._width;// / 16;
    entity.first._height = size._height;// / 16;
    characters.fill(0);
    while (std::getline(file, line)) {
        if (line.size() != size._width) {
            file.close();
            close();
            throw Arcade::GraphicError("NCurses: with line do not have expected value");
        } else if (std::string::npos != line.find_first_not_of(ref)) {
            file.close();
            close();
            throw Arcade::GraphicError("NCurses: Unknow character");
        }
        for (char const c: line) {
            position = ref.find(c);
            ++characters[position];
        }
    }
    file.close();
    for (std::size_t e = 0; e < characters.size() - 1; ++e)
        if (characters[tmp] < characters[e])
            tmp = e;
    entity.second = (Arcade::ColorIdx)ref[tmp];
    _entity[form._path] = entity;
    return (entity);
}

void Graph::NCurses::displayImage(Graph::Position &pos, Graph::Form &form, Arcade::ColorIdx idx, Graph::Size &size)
{
    std::pair<Graph::Size, Arcade::ColorIdx> feature;

    try {
        if (form._idx == Arcade::FormIdx::OTHER) {
            if (!_entity.count(form._path))
                feature = getEntityFromFile(form, size);
            else
                feature = _entity.at(form._path);
            drawRect(pos, feature.second, feature.first);
        } else if (Arcade::FormIdx::RECT == form._idx) {
            drawRect(pos, idx, size);
        }
    } catch (std::exception const &err) {
        std::cerr << "displayImage: " << err.what() << std::endl;
    }
}

void Graph::NCurses::displayText(Graph::Text &text, Graph::Position &pos, Arcade::ColorIdx colorIdx, Graph::Size &size)
{
    (void)size;
    (void)colorIdx;
    try {
        attron(COLOR_PAIR(Ncolors.at(Arcade::ColorIdx::WHITE)));
        mvprintw(pos._y, pos._x * 2, text._text.c_str());
        attroff(COLOR_PAIR(Ncolors.at(Arcade::ColorIdx::WHITE)));
    } catch (std::exception const &err) {
        std::cerr << "displayText: " << err.what() << std::endl;
    }
}

void Graph::NCurses::drawRect(Graph::Position &pos, Arcade::ColorIdx &idx, Graph::Size &size) noexcept
{
    try {
        attron(COLOR_PAIR(Ncolors.at(idx)));
        attron(A_REVERSE);

        for (std::size_t i = 0; i < size._height / 16; ++i) {
            for (std::size_t e = 0; e < size._width / 16; ++e) {
                mvprintw(pos._y + i, (pos._x + e) * 2, "  ");
            }
        }
        attroff(A_REVERSE);
        attroff(COLOR_PAIR(Ncolors.at(idx)));
    } catch (std::exception const &err) {
        std::cerr << "drawRect: " << err.what() << std::endl;
    }
}

void Graph::NCurses::dump(void) const
{
    std::unordered_map<std::string, std::pair<Graph::Size, Arcade::ColorIdx>>::const_iterator it = _entity.begin();

    std::cerr << "Dump:" << std::endl;
    try {
        for (; it != _entity.end(); ++it) {
            std::cerr << "Name:" << it->first;
            std::cerr << "(x:" << it->second.first._width << ",y:" << it->second.first._height << ",c:" << Ncolors.at(it->second.second) << ")" << std::endl;
        }
    } catch (std::exception const &err) {
        std::cerr << "dump: " << err.what() << std::endl;
    }
}

extern "C" Graph::AGraph *endPoint(void)
{
    return (ncurses);
}

__attribute__((constructor))
void start(void)
{
    ncurses = new Graph::NCurses();
}

__attribute__((destructor))
void end(void)
{
    delete ncurses;
}
