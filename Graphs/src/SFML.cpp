/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** SFML
*/

#include <iostream>
#include <fstream>
#include "../include/SFML.hpp"
#include "../../Common/Error.hpp"

Graph::SFML *SFML;

Graph::SFML::SFML() : AGraph{Arcade::Type::GRAPH, "SFML"} {}

void Graph::SFML::open(std::string const &title, std::string const &icon)
{
    sf::VideoMode a = {1240, 800, 32};
    _window.create(a, title.c_str(), sf::Style::Close | sf::Style::Titlebar);
    if (!_icon.loadFromFile(icon)) {
        close();
        throw Arcade::GraphicError{std::string{"Impossible to load the image at " + icon}};
    }
    _window.setIcon(256, 256, _icon.getPixelsPtr());
    if (!_font.loadFromFile("Ressources/Ravenna.ttf")) {
        close();
        throw Arcade::GraphicError{std::string{"SFML: error while loading font"}};
    }
}

void Graph::SFML::close()
{
    _window.close();
}

void Graph::SFML::setTitle(std::string const &title) noexcept
{
    _window.setTitle(title.c_str());
}

void Graph::SFML::setIcon(std::string const &icon)
{
    if (!_icon.loadFromFile(icon)) {
        close();
        throw Arcade::GraphicError{std::string{"Impossible to load the image at " + icon}};
    }
}

Arcade::Events Graph::SFML::getEvent() noexcept
{
    sf::Event event;

    _evtType = Arcade::Events::NONE;
    _evt = '\0';
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _evtType = Arcade::Events::QUIT;
        }
        if (event.type == sf::Event::Closed) {
            _evtType = Arcade::Events::QUIT;
            _window.close();
        }
	if (event.type == sf::Event::KeyPressed && Events.find(event.key.code) != Events.end()) {
            _evtType = Events.at((int)event.key.code);
        }
    }
    return _evtType;
}

char Graph::SFML::getEventChar() const noexcept
{
    return _evt;
}

int Graph::SFML::checkCollision(Position const &pos1, Size const &size1, Position const &pos2, Size const &size2) const noexcept
{
    Graph::Position p1 = {pos1._x * 16, pos1._y * 16};
    Graph::Position p2 = {pos2._x * 16, pos2._y * 16};

    if (p1._x < p2._x + (int)size2._width && p1._x + (int)size1._width > p2._x &&
        p1._y < p2._y + (int)size2._height && p1._y + (int)size2._height > p2._y)
        return (1);
    return (0);
}

void Graph::SFML::displayWindow() noexcept
{
    sf::Color black = getColor(Arcade::ColorIdx::BLACK);

    _window.display();
    _window.clear(black);
}

void Graph::SFML::displayImage(Graph::Position &pos, Graph::Form &form, Arcade::ColorIdx idx, Graph::Size &size)
{
    if (Arcade::FormIdx::RECT == form._idx) {
        drawRect(pos, idx, size);
        return;
    }

    std::ifstream file{form._path};
    std::string line;
    std::vector<std::string> buf;
    std::size_t a = 0;
    while (std::getline(file, line)) {
        a++;
        if (line.size() != size._width) {
            file.close();
            close();
            throw Arcade::GraphicError{std::string{"One line has not the same size as the size given in parameter"}};
        } else if (std::string::npos != line.find_first_not_of("WAYyGgBbVvRrOo ")) {
            file.close();
            close();
            throw Arcade::GraphicError{std::string{"One line has an incorrect character"}};
        }
        buf.emplace_back(line);
    }
    sf::Color blackAlpha = getColor(Arcade::ColorIdx::BLACK);
    for (std::size_t i = 0; size._height > i; ++i) {
        for (std::size_t y = 0; size._width > y; ++y) {
            sf::Color c = (' ' == buf[i][y]) ? blackAlpha : getColor((Arcade::ColorIdx)buf[i][y]);
            sf::Vertex point(sf::Vector2f(y + pos._x * 16, i + pos._y * 16), c);
            _window.draw(&point, 1, sf::Points);
        }
    }
    file.close();
}

void Graph::SFML::displayText(Graph::Text &text, Graph::Position &pos,  Arcade::ColorIdx colorIdx, Graph::Size &size)
{
        sf::Text sftext;
        sf::Vector2f sfpos = {(float)pos._x * 16, (float)pos._y * 16};

        (void)size;
        (void)colorIdx;
        sftext.setString(text._text);
        sftext.setFont(_font);
        sftext.setCharacterSize(24);
        sftext.setFillColor(sf::Color::White);
        sftext.setPosition(sfpos);
        _window.draw(sftext);
}

void Graph::SFML::drawRect(Graph::Position &pos, Arcade::ColorIdx idx, Graph::Size &size) noexcept
{
    sf::Color c = getColor(idx);

    for (std::size_t y = 0; size._height > y; ++y)
        for (std::size_t x = 0; size._width > x; ++x) {
            sf::Vertex point(sf::Vector2f(x + pos._x * 16, y + pos._y * 16), c);
            _window.draw(&point, 1, sf::Points);
    }
}

sf::Color Graph::SFML::getColor(Arcade::ColorIdx idx) noexcept
{
        Graph::Color c = Arcade::Colors.at(idx);

        return (sf::Color{(sf::Uint8)c._r, (sf::Uint8)c._g, (sf::Uint8)c._b, 255});
}


extern "C" Graph::AGraph *endPoint(void)
{
    return (SFML);
}

__attribute__((constructor))
void start(void)
{
    SFML = new Graph::SFML();
}

__attribute__((destructor))
void end(void)
{
    //delete SFML; SegV
}
