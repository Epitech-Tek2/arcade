/*
** Arcade | Graph
** Sarah-Keppler
*/

#ifndef ARCADE_GRAPH_SDL2_HPP
#define ARCADE_GRAPH_SDL2_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "IGraph.hpp"

namespace Graph
{
    class SDL2 : public AGraph
    {
    public:
	SDL2();
	virtual ~SDL2() = default;

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
	virtual void displayImage(Graph::Position &pos, Graph::Form &form, Arcade::ColorIdx colorIdx, Graph::Size &size);

	/**
	 * @brief Display a text.
	 *
	 * @param text.
	 * @param text position.
	 * @param size position.
	 */
	virtual void displayText(Graph::Text &text, Graph::Position &pos, Arcade::ColorIdx colorIdx, Graph::Size &size);
    private:
	SDL_Window *_window;
	SDL_Surface *_icon;
	SDL_Renderer *_renderer;
	TTF_Font *_font;

	virtual void drawRect(Graph::Position const &pos, Arcade::ColorIdx const color, Graph::Size const &size) noexcept;
    };
}

/**
 * @brief end point of the library.
 *
 * @return Must return an unique_ptr of the graphic library class
 */
extern "C" Graph::AGraph *endPoint(void);

#endif /* ARCADE_GRAPH_SDL2_HPP */
