/*
** Arcade | Graph
** Sarah-Keppler
*/

#ifndef ARCADE_GRAPH_COMPONENT
#define ARCADE_GRAPH_COMPONENT

#include <string>
#include "IComponent.hpp"

namespace Arcade
{
    enum class FormIdx : uint8_t
    {
	RECT = 0,
	OTHER
    };
}

namespace Graph
{
    struct Position : public IComponent
    {
	Position(int x = 0, int y = 0) : _x{x}, _y{y} {};

	int _x, _y;
    };

    struct Size : public IComponent
    {
	Size(std::size_t x = 0, std::size_t y = 0) : _width{x}, _height{y} {};

	std::size_t _width, _height;
    };

    struct Color : public IComponent
    {
	Color(std::size_t r = 0, std::size_t g = 0, std::size_t b = 0, std::size_t a = 0) noexcept
	    : _r{r}, _g{g}, _b{b}, _a{a}{};

	std::size_t _r, _g, _b, _a;
    };

    struct Form : public IComponent
    {
	Form(Arcade::FormIdx idx = Arcade::FormIdx::OTHER, std::string path = "") : _idx{idx}, _path{path} {};

	Arcade::FormIdx _idx;
	std::string _path;
    };

    struct Text : public IComponent
    {
	Text(std::string text) : _text{text}{};

	std::string _text;
    };
}

#endif /* ARCADE_GRAPH_COMPONENT */
