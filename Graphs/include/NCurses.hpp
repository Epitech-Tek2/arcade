/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IGraph.hpp"
#include <curses.h>
#include <fstream>
#include "../../Common/Error.hpp"
#include "../../Common/ILib.hpp"

namespace Graph
{
    class NCurses : public AGraph
    {
    public:
	NCurses();
	virtual ~NCurses() = default;

	const std::unordered_map<Arcade::ColorIdx, int> Ncolors {
		{Arcade::ColorIdx::WHITE, 15},
		{Arcade::ColorIdx::BLACK, 16},
		{Arcade::ColorIdx::YELLOW, 220},
		{Arcade::ColorIdx::YELLOW_GREEN, 112},
		{Arcade::ColorIdx::GREEN, 10},
		{Arcade::ColorIdx::BLUE_GREEN, 43},
		{Arcade::ColorIdx::BLUE, 21},
		{Arcade::ColorIdx::BLUE_VIOLET, 57},
		{Arcade::ColorIdx::VIOLET, 129},
		{Arcade::ColorIdx::RED_VIOLET, 163},
		{Arcade::ColorIdx::RED, 196},
		{Arcade::ColorIdx::RED_ORANGE, 166},
		{Arcade::ColorIdx::ORANGE, 208},
		{Arcade::ColorIdx::YELLOW_ORANGE, 214},
	};
	/**
	 * @brief Play the role of the constructor. Create the window.
	 * 
	 * @param window title.
	 * @param window icon.
	 */
	virtual void open(std::string const &title = "", std::string const &icon = "");

	/**
	 * @brief Play the role of the deconstructor. Destroy all the components.
	 */
	virtual void close();

	/**
	 * @brief Change the title of the window.
	 * 
	 * @param new window title.
	 */
	virtual void setTitle(std::string const &title) noexcept;

	/**
	 * @brief Change the icon of the window.
	 * 
	 * @param new window icon.
	 */
	virtual void setIcon(std::string const &icon);

	/**
	 * @brief Retrieve the current event.
	 *
	 * @return current event type.
	 */
	virtual Arcade::Events getEvent() noexcept;

	/**
	 * @brief Retrive the letter key of the last event.
	 *
	 * @return char of the letter key.
	 */
	virtual char getEventChar() const noexcept;

	/**
	 * @brief Check if there is a collision between two entities.
	 *
	 * @param position of the first entity.
	 * @param size of the first entity.
	 * @param position of the second entity.
	 * @param size of the second entity.
	 *
	 * @return 1 if there is a collision, 0 otherwise.
	 */
	virtual int checkCollision(Position const &pos1, Size const &size1, Position const &pos2, Size const &size2) const noexcept;

	/**
	 * @brief Display the window after clearing it.
	 */
	virtual void displayWindow() noexcept;

	/**
	 * @brief Display an image (= pixel array) according to its components.
	 * 
	 * @param position.
	 * @param form.
	 * @param color.
	 * @param size.
	 */
	virtual void displayImage(Graph::Position &pos, Graph::Form &form, Arcade::ColorIdx idx, Graph::Size &size);

	/**
	 * @brief Display a text
	 *
	 * @param text.
	 * @param text position.
	 * @param text size.
	 */
	virtual void displayText(Text &text, Position &position, Arcade::ColorIdx colorIdx, Size &size);

	/**
	 * @brief dump value
	 */
	virtual void dump(void) const;
        protected:
	/**
	 * @brief draw rectangle
	 * 
	 * @param position.
	 * @param color.
	 * @param size.
	 */
	virtual void drawRect(Graph::Position &pos, Arcade::ColorIdx &idx, Graph::Size &size) noexcept;

	/**
	 * @brief draw rectangle
	 * 
	 * @param form
	 * @param size
	 * 
	 * @return pair of size and color determine thanks to the file
	 */
	virtual std::pair<Graph::Size, Arcade::ColorIdx> getEntityFromFile(Graph::Form &form, Graph::Size &size);

    private:
        std::unordered_map<std::string, std::pair<Graph::Size, Arcade::ColorIdx>> _entity;
    };
}

/**
 * @brief end point of the library.
 *
 * @return Must return an unique_ptr of the graphic library class
 */
extern "C" Graph::AGraph *endPoint(void);

#endif /* !NCURSES_HPP_ */
