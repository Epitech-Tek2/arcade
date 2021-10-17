/*
** Arcade | Graph
** Sarah-Keppler
*/

#ifndef ARCADE_GRAPH_HPP
#define ARCADE_GRAPH_HPP

#include <vector>
#include <string>
#include "Component.hpp"
// #include "../../Common/Arcade.hh"
#include "../../Common/ILib.hpp"

namespace Graph
{
    class IGraph : public Arcade::ILib
    {
    public:
	IGraph() = default;
	~IGraph() = default;

	/**
	 * @brief Play the role of the constructor. Create the window.
	 * 
	 * @param window title.
	 * @param window icon.
	 */
	virtual void open(std::string const &title = "", std::string const &icon = "") = 0;

	/**
	 * @brief Play the role of the deconstructor. Destroy all the components.
	 */
	virtual void close() = 0;

	/**
	 * @brief Change the title of the window.
	 * 
	 * @param new window title.
	 */
	virtual void setTitle(std::string const &title) noexcept = 0;

	/**
	 * @brief Change the icon of the window.
	 * 
	 * @param new window icon.
	 */
	virtual void setIcon(std::string const &icon) = 0;

	/**
	 * @brief Retrieve the current event.
	 *
	 * @return current event type.
	 */
	virtual Arcade::Events getEvent() noexcept = 0;

	/**
	 * @brief Retrieve the letter pressed of the last event.
	 *
	 * @return letter pressed.
	 */
	virtual char getEventChar() const noexcept = 0;

	/**
	 * @brief Check if there is a collision between two entities.
	 *
	 * @param position of the first entity.
	 * @param size of the first entity.
	 * @param position of second entity.
	 * @param size of the second entity.
	 *
	 * @return 1 if there is a collision, 0 otherwise.
	 */
	virtual int checkCollision(Position const &pos1, Size const &size1, Position const &pos2, Size const &size2) const noexcept = 0;

	/**
	 * @brief Display the window after clearing it.
	 */
	virtual void displayWindow() noexcept = 0;
	
	/**
	 * @brief Display an image (= pixel array) according to its components.
	 * 
	 * @param position.
	 * @param form.
	 * @param color.
	 * @param size.
	 */
	virtual void displayImage(Position &pos, Form &form, Arcade::ColorIdx colorIdx, Size &size) = 0;

	/**
	 * @brief Display a text.
	 *
	 * @param text.
	 * @param text position.
	 * @param text size.
	 */
	virtual void displayText(Text &text, Position &position, Arcade::ColorIdx colorIdx, Size &size) = 0;
    protected:
	Arcade::Events _evtType;
	char _evt;
    };

    class AGraph : public IGraph
    {
    public:
	/**
	 * @brief Set the type and the name of the library.
	 *
	 * @param type of the library.
	 * @param name of the library.
	 */
	AGraph(Arcade::Type const type, std::string const &name) noexcept;
	~AGraph() = default;

	/**
	 * @brief Get the type of the library.
	 *
	 * @return type of the library.
	 */
	Arcade::Type getType() const noexcept;

	/**
	 * @brief Get the name of the library.
	 *
	 * @return name of the library.
	 */
	std::string getName() const noexcept;
    protected:
	Arcade::Type const _type;
	std::string const _name;
    };
}

// Add in sub classes. Why not a unique_ptr instead of a pointer?
/*
SFMLController *sfml = nullptr;

__attribute__((constructor))
void start(void)
{
    smfl = new SFMLController();
}

__attribute__((destructor))
void end(void)
{
    delete smfl;
}

extern "C" SFMLController *endPoint(void)
{
    return (smfl);
}
*/

#endif /* ARCADE_GRAPH_HPP */
