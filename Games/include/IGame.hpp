/*
** Arcade | Games
** Sarah-Keppler
*/

#ifndef ARCADE_GAME_HPP
#define ARCADE_GAME_HPP

#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include "../../Common/ILib.hpp"
#include "../../Graphs/include/IGraph.hpp"
// #include "../../Common/Arcade.hh"

namespace Game
{
    class IGame : public Arcade::ILib
    {
    public:
	IGame() = default;
	virtual ~IGame() = default;

	/**
	 * @brief Load a scene and create all the components
	 */
	virtual void load(Graph::AGraph *lib) = 0;
	
	/**
	 * @brief Retrieve the events and react if possitble immediately.
	 *
	 * @return event type.
	 */
	virtual Arcade::Events handleEvents() noexcept = 0;

	/**
	 * @brief React to the events related on the elapsed time and simulate the game.
	 *
	 * @param elapsed time.
	 */
	virtual void handleUpdate(double elapsedTime) noexcept = 0;

	virtual void restart() noexcept = 0;

	virtual void setLib(Graph::AGraph *lib) noexcept = 0;
    protected:
	Graph::IGraph *_lib;
	Arcade::Events _evtType;
	char _evt;
	std::vector<Graph::Position> _pos;
	std::vector<Graph::Size> _size;
	std::vector<Arcade::ColorIdx> _color;
	std::vector<Graph::Form> _form;
	std::vector<Graph::Text> _text;
    };

    class AGame : public IGame
    {
    public:
	/**
	 * @brief Set the type and the name of the library.
	 *
	 * @param type of the library.
	 * @param name of the library.
	 */
	AGame(Arcade::Type const type, std::string const &name) noexcept;

	/**
	 * @brief Get the type of the library.
	 *
	 * @return type of the library.
	 */
	Arcade::Type getType() const noexcept;

	/**
	 * @brief Get the type of the name.
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

#endif /* ARCADE_GAME_HPP */
