/*
** Arcade
** Sarah-Keppler
*/

#ifndef ARCADE_HH_
#define ARCADE_HH_

#include <unordered_map>
#include "../Graphs/include/Component.hpp"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

namespace Arcade
{
    enum class Type : uint8_t
    {
	GAME = 0,
	GRAPH,
	MENU
    };

    enum class ColorIdx : char
    {
	WHITE = 'W',
	BLACK = 'A',
	YELLOW = 'Y',
	YELLOW_GREEN = 'y',
	GREEN = 'G',
	BLUE_GREEN = 'g',
	BLUE = 'B',
	BLUE_VIOLET = 'b',
	VIOLET = 'V',
	RED_VIOLET = 'v',
	RED = 'R',
	RED_ORANGE = 'r',
	ORANGE = 'O',
	YELLOW_ORANGE = 'o'
    };

    const std::unordered_map<Arcade::ColorIdx, Graph::Color> Colors {
	{Arcade::ColorIdx::WHITE, Graph::Color{255, 255, 255, 255}},
	{Arcade::ColorIdx::BLACK, Graph::Color{0, 0, 0, 255}},
	{Arcade::ColorIdx::YELLOW, Graph::Color{255, 255, 0, 255}},
	{Arcade::ColorIdx::YELLOW_GREEN, Graph::Color{0, 155, 0, 255}},
	{Arcade::ColorIdx::GREEN, Graph::Color{0, 121, 0, 255}},
	{Arcade::ColorIdx::BLUE_GREEN, Graph::Color{0, 174, 174, 255}},
	{Arcade::ColorIdx::BLUE, Graph::Color{0, 0, 255, 255}},
	{Arcade::ColorIdx::BLUE_VIOLET, Graph::Color{115, 8, 165, 255}},
	{Arcade::ColorIdx::VIOLET, Graph::Color{186, 0, 255, 255}},
	{Arcade::ColorIdx::RED_VIOLET, Graph::Color{204, 0, 175, 255}},
	{Arcade::ColorIdx::RED, Graph::Color{255, 0, 0, 255}},
	{Arcade::ColorIdx::RED_ORANGE, Graph::Color{255, 70, 0, 255}},
	{Arcade::ColorIdx::ORANGE, Graph::Color{255, 127, 0, 255}},
	{Arcade::ColorIdx::YELLOW_ORANGE, Graph::Color{254, 179, 0, 255}},
    };

    //ekys ZSQDLKGFTM
    enum class Events : uint8_t
    {
	MV_Z = 0,
	MV_S,
	MV_Q,
	MV_D,
	NEXT_LIB,
	PREV_LIB,
	NEXT_GAME,
	PREV_GAME,
	RESTART,
	MENU,
	QUIT,
	NONE
    };
}

#endif /* !ARCADE_HH_ */
