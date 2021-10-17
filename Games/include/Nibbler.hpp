/*
** EPITECH PROJECT, 2021
** saveNOFloat
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include "IGame.hpp"
// #include "../../Graphs/include/IGraph.hpp"
#include "../../Common/Error.hpp"

namespace Game
{
    class Nibbler : public AGame
    {
    public:
	Nibbler();
	virtual ~Nibbler();

	const std::unordered_map<Arcade::Events, std::string> nibbler {
	    {Arcade::Events::MV_Z, "Ressources/Games/Nibbler/upHead.txt"},
	    {Arcade::Events::MV_S, "Ressources/Games/Nibbler/downHead.txt"},
	    {Arcade::Events::MV_D, "Ressources/Games/Nibbler/rightHead.txt"},
	    {Arcade::Events::MV_Q, "Ressources/Games/Nibbler/leftHead.txt"},
	};

	/**
	 * @brief Load a scene and create all the components
	 */
	virtual void load(Graph::AGraph *lib);

	/**
	 * @brief Retrieve the events and react if possitble immediately.
	 *
	 * @return event type.
	 */
	virtual Arcade::Events handleEvents() noexcept;

	/**
	 * @brief React to the events related on the elapsed time and simulate the game.
	 *
	 * @param elapsed time.
	 */
	virtual void handleUpdate(double elapsedTime) noexcept; //perhaps an int

	/**
	 * @brief restart game
	 */
	virtual void restart() noexcept;

	void setLib(Graph::AGraph *lib) noexcept;

    protected:

	/**
	 * @brief initiate the game component
	 */
	virtual void initGame(void);

	/**
	 * @brief open map and parse map
	 */
	virtual void openMap(void);

	/**
	 * @brief handle move from event
	 * 
	 * @param evt that have been made
	 * 
	 * @return if the move is valid
	 */
	virtual bool handleMove(Arcade::Events evt);

	/**
	 * @brief move Nibbler position
	 * 
	 * @param y that must be add
	 * @param x that must be has
	 * @param evt that have been made
	 * 
	 * @return if the move is valid
	 */
	virtual bool moveNibbler(int y, int x, Arcade::Events evt);

	/**
	 * @brief move tail
	 */
	virtual void moveTail(void);

	/**
	 * @brief generate food
	 */
	virtual void generateFood(void);

	/**
	 * @brief add element
	 */
	virtual void addElement(void);

	/**
	 * @brief check lose
	 * 
	 * @param emp that must be check
	 * 
	 * @return if he lose
	 */
	virtual bool lose(std::size_t emp);
    private:
        double _period;
        Graph::Size _map;
        std::size_t _len;
        std::size_t _head;
        std::size_t _food;
        std::size_t _score;
        Arcade::Events _tmp;
        Graph::Position _start;
        std::chrono::_V2::steady_clock::time_point _last;
    };
}

/**
 * @brief end point of the library.
 *
 * @return Must return an unique_ptr of the graphic library class
 */
extern "C" Game::AGame *endPoint(void);

#endif /* !NIBBLER_HPP_ */
