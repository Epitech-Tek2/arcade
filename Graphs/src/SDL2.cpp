/*
** Arcade | Graphs
** Sarah-Keppler
*/

#include <iostream>
#include <SDL2/SDL_image.h>
#include <fstream>
#include "../include/SDL2.hpp"
#include "../../Common/Error.hpp"

Graph::SDL2 *SDL2;

Graph::SDL2::SDL2() : AGraph{Arcade::Type::GRAPH, "SDL2"}
{
}

void Graph::SDL2::open(std::string const &title, std::string const &icon)
{
    if (0 != SDL_Init(SDL_INIT_EVERYTHING))
	throw Arcade::SDL2Error{std::string{"Unable to initialize SDL2"}, SDL_GetError()};
    TTF_Init();
    
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 800, 0);
    if (nullptr == _window) {
	close();
	throw Arcade::SDL2Error{std::string{"Could not create the window"}, SDL_GetError()};
    }
    
    _icon = IMG_Load(icon.c_str());
    if (nullptr == _icon) {
	close();
	throw Arcade::SDL2Error{std::string{"Impossible to load the image at " + icon}, IMG_GetError()};
    }
    SDL_SetWindowIcon(_window, _icon);

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == _renderer) {
	close();
	throw Arcade::SDL2Error{std::string{"Renderer could not me created"}, SDL_GetError()};
    }

    if (0 != SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND)) {
	close();
	throw Arcade::SDL2Error{std::string{"Failed to apply the Blend Mode"}, SDL_GetError()};
    }

    _font = TTF_OpenFont("Ressources/Ravenna.ttf", 16);
    if (!_font)
	throw Arcade::SDL2Error{std::string{"Failed to load font"}, TTF_GetError()};
}

void Graph::SDL2::close()
{
    SDL_DestroyWindow(_window);
    SDL_FreeSurface(_icon);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}

void Graph::SDL2::setTitle(std::string const &title) noexcept
{
    SDL_SetWindowTitle(_window, title.c_str());
}

void Graph::SDL2::setIcon(std::string const &icon)
{
    SDL_Surface *surface = IMG_Load(icon.c_str());
    if (nullptr == surface) {
	close();
	throw Arcade::SDL2Error{std::string{"Impossible to load the image at " + icon}, IMG_GetError()};
    }
    SDL_FreeSurface(_icon);
    _icon = surface;
    SDL_SetWindowIcon(_window, _icon);
}

Arcade::Events Graph::SDL2::getEvent() noexcept
{
    SDL_Event event;
    std::string keys{"ZSQDLKGFTM"};
    _evtType = Arcade::Events::NONE;
    _evt = '\0';
    while (SDL_PollEvent(&event)) {
	if (SDL_WINDOWEVENT == event.type && event.window.event == SDL_WINDOWEVENT_CLOSE)
	    _evtType = Arcade::Events::QUIT;
        if (SDL_KEYDOWN == event.type) {
	    _evt = SDL_GetKeyName(event.key.keysym.sym)[0];
	    std::size_t found = keys.find(_evt);
	    if (std::string::npos != found)
		_evtType = (Arcade::Events)found;
	}
    }
    return _evtType;
}

char Graph::SDL2::getEventChar() const noexcept
{
    return _evt;
}

int Graph::SDL2::checkCollision(Position const &pos1, Size const &size1, Position const &pos2, Size const &size2) const noexcept
{
    Graph::Position sdlPos1{pos1._x * 16, pos1._y * 16}, sdlPos2{pos2._x * 16, pos2._y * 16};
    Graph::Position posEnt1[3] = {sdlPos1, Graph::Position{sdlPos1._x + (int)size1._width, sdlPos1._y}, Graph::Position{sdlPos1._x, sdlPos1._y + (int)size1._height}};
    Graph::Position posEnt2[4] = {sdlPos2, Graph::Position{sdlPos2._x + (int)size2._width, sdlPos2._y}, Graph::Position{sdlPos2._x, sdlPos2._y + (int)size2._height}, Graph::Position{sdlPos2._x + (int)size2._width, sdlPos2._y + (int)size2._height}};
    for (int i = 0; 4 > i; ++i)
	if ((posEnt1[0]._x < posEnt2[i]._x && posEnt1[1]._x > posEnt2[i]._x) &&
	    (posEnt1[1]._y < posEnt2[i]._y && posEnt1[3]._y > posEnt2[i]._y))
	    return 1;
    return 0;
}

void Graph::SDL2::displayWindow() noexcept
{
    SDL_RenderPresent(_renderer);

    Color black = Arcade::Colors.at(Arcade::ColorIdx::BLACK);
    SDL_SetRenderDrawColor(_renderer, black._r, black._g, black._b, black._a);
    SDL_RenderClear(_renderer);
}

void Graph::SDL2::displayImage(Graph::Position &pos, Graph::Form &form, Arcade::ColorIdx colorIdx, Graph::Size &size)
{
    Graph::Position sdlPos{pos._x * 16, pos._y * 16};
    if (Arcade::FormIdx::RECT == form._idx) {
	drawRect(sdlPos, colorIdx, size);
	return;
    }
    std::ifstream file{form._path};
    if (!file.is_open())
	throw Arcade::Error{std::string{"File failed to load and does not exist: " + form._path}};
    std::string line;
    std::vector<std::string> buf;
    while (std::getline(file, line)) {
	if (line.size() != size._width) {
	    file.close();
	    close();
	    throw Arcade::SDL2Error{std::string{"One line has not the same size as the size given in parameter"}, SDL_GetError()};
	} else if (std::string::npos != line.find_first_not_of("AWBYyGgBbVvRrOo ")) {
	    std::cout << "|" <<line << "|" << std::endl;
	    file.close();
	    close();
	    throw Arcade::SDL2Error{std::string{"One line has an incorrect character"}, SDL_GetError()};
	}
	buf.emplace_back(line);
    }
    if (size._height != buf.size())
        throw Arcade::Error{std::string{"The column size of the image is incorrect"}};
    file.close();
    Color blackAlpha = Arcade::Colors.at(Arcade::ColorIdx::BLACK);
    blackAlpha._a = 0;
    for (std::size_t y = 0; size._height > y; ++y)
	for (std::size_t x = 0; size._width > x; ++x) {
	    Color c = (' ' == buf[y][x] || 'A' == buf[y][x]) ? blackAlpha : Arcade::Colors.at((Arcade::ColorIdx)buf[y][x]);
	    SDL_SetRenderDrawColor(_renderer, c._r, c._g, c._b, c._a);
	    SDL_RenderDrawPoint(_renderer, x + sdlPos._x, y + sdlPos._y);
	}
}

void Graph::SDL2::displayText(Graph::Text &text, Graph::Position &pos, Arcade::ColorIdx colorIdx, Graph::Size &size)
{
    Graph::Position posSdl{pos._x * 16, pos._y * 16};
    Graph::Color color = Arcade::Colors.at(colorIdx);
    SDL_Color colorSdl = {(unsigned char)color._r, (unsigned char)color._g, (unsigned char)color._b, (unsigned char)color._a};
    SDL_Surface *surface = TTF_RenderText_Solid(_font, text._text.c_str(), colorSdl);
    if (!surface)
	throw Arcade::SDL2Error{std::string{"Failed to create surface"}, SDL_GetError()};
    SDL_Texture *message = SDL_CreateTextureFromSurface(_renderer, surface);
    if (!message)
	throw Arcade::SDL2Error{std::string{"Failed to create texture"}, SDL_GetError()};
    SDL_Rect rect;
    rect.x = posSdl._x;
    rect.y = posSdl._y;
    rect.w = size._width;
    rect.h = size._height;
    SDL_RenderCopy(_renderer, message, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}

void Graph::SDL2::drawRect(Graph::Position const &pos, Arcade::ColorIdx const colorIdx, Graph::Size const &size) noexcept
{
    Graph::Color color = Arcade::Colors.at(colorIdx);
    SDL_SetRenderDrawColor(_renderer, color._r, color._g, color._b, 255);
    for (std::size_t y = 0; size._height > y; ++y)
	for (std::size_t x = 0; size._width > x; ++x)
	    SDL_RenderDrawPoint(_renderer, x + pos._x, y + pos._y);
}


extern "C" Graph::AGraph *endPoint(void)
{
    return (SDL2);
}

__attribute__((constructor))
void start(void)
{
    SDL2 = new Graph::SDL2();
}

__attribute__((destructor))
void end(void)
{
    delete SDL2;
}
