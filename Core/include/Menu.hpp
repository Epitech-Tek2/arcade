/*
** Arcade | Games
** Sarah-Keppler
*/

#ifndef ARCADE_GAME_MENU_HPP
#define ARCADE_GAME_MENU_HPP

#include "../../Games/include/IGame.hpp"

namespace Game
{
    class Menu : protected Game::AGame
    {
    public:
	Menu(std::vector<std::string> const &graphLibs, std::vector<std::string> const &gameLibs, std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>> scores) noexcept;
	~Menu() = default;

	/**
	 * @brief Load a scene and create all the components
	 */
	void load(Graph::AGraph *lib);

	// /**
	//  * @brief Get the type of the library.
	//  *
	//  * @return type of the library.
	//  */
        // Arcade::Type getType() const noexcept;
	
        // /**
	//  * @brief Get the type of the name.
	//  *
	//  * @return name of the library.
	//  */
	
        // std::string getName() const noexcept;
	/**
	 * @brief Retrieve the events and react if possitble immediately.
	 *
	 * @return event type.
	 */
	Arcade::Events handleEvents() noexcept;

	/**
	 * @brief React to the events related on the elapsed time and simulate the game.
	 *
	 * @param elapsed time.
	*/
	void handleUpdate(double elapsedTime) noexcept;

	/**
	 * @brief Display all the components.
	 */
	void display() noexcept;

	void restart() noexcept;

	void setLib(Graph::AGraph *lib) noexcept;

	std::string getGame() const noexcept;
	std::string getGraph() const noexcept;
    private:
	std::vector<std::string> const _graphLibs;
	std::vector<std::string> const _gameLibs;
	std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>> _scores;
	std::size_t _idxGame, _idxGraph, _idxScore;
	int _editing;
	std::string _playerName;
	Graph::Size _map;

	/**
	 * @brief Create an entity with its position, size, color and form.
	 *
	 * @param map buffer.
	 * @param x position.
	 * @param y position.
	 */
	void addComponent(Graph::Position const &pos, Graph::Size const &size, Graph::Form const &form, Arcade::ColorIdx const colorIdx, Graph::Text const &text) noexcept;

	void openMap();
	/*
	  std::unique_ptr<Graph::IGraph> _lib;
	  Arcade::Events _evtType;
	  char _evt;
	  std::vector<Graph::Life> _life;
	  std::vector<Graph::Position> _pos;
	  std::vector<Graph::Size> _size;
	  std::vector<Graph::Color> _color;
	  std::vector<Graph::Form> _form;
	  std::vector<Graph::Text> _text;
	*/
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
