/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IGraph.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Graph
{
    class SFML : public AGraph
    {
    public:
	SFML();
	virtual ~SFML() = default;

        const std::unordered_map<int, Arcade::Events> Events {
                {sf::Keyboard::Z, Arcade::Events::MV_Z},
                {sf::Keyboard::Q, Arcade::Events::MV_Q},
                {sf::Keyboard::S, Arcade::Events::MV_S},
                {sf::Keyboard::D, Arcade::Events::MV_D},
                {sf::Keyboard::L, Arcade::Events::NEXT_LIB},
                {sf::Keyboard::K, Arcade::Events::PREV_LIB},
                {sf::Keyboard::G, Arcade::Events::NEXT_GAME},
                {sf::Keyboard::F, Arcade::Events::PREV_GAME},
                {sf::Keyboard::T, Arcade::Events::RESTART},
                {sf::Keyboard::M, Arcade::Events::MENU},
                {sf::Keyboard::O, Arcade::Events::NONE},
        };
        // const sf::Keyboard
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
	virtual void close(void);

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
	virtual void displayImage(Graph::Position &pos, Graph::Form &form, Arcade::ColorIdx color, Graph::Size &size);

	/**
	 * @brief Display a text.
	 *
	 * @param text.
	 * @param text position.
	 * @param size position.
	 */
	virtual void displayText(Graph::Text &text, Graph::Position &pos, Arcade::ColorIdx colorIdx, Graph::Size &size);
    private:
        sf::RenderWindow _window;
        sf::Image _icon;
        sf::Font _font;
	virtual void drawRect(Graph::Position &pos, Arcade::ColorIdx color, Graph::Size &size) noexcept;


	sf::Color getColor(Arcade::ColorIdx color) noexcept;
    };
}

/**
 * @brief end point of the library.
 *
 * @return Must return an unique_ptr of the graphic library class
 */
extern "C" Graph::AGraph *endPoint(void);

#endif /* !SFML_HPP_ */
