/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include "IGame.hpp"
#include "../../Graphs/include/IGraph.hpp"
#include "../../Common/Error.hpp"

namespace Game
{
    class Pacman : public AGame
    {
    public:
	Pacman();
	virtual ~Pacman();

	enum AImove {
	    UP,
	    DOWN,
	    LEFT,
	    RIGTH,
	    NONE,
	};

	enum AIname {
	    BLINKY,
	    INKY,
	    PINKY,
	    CLYDE,
	    PACMAN,
	};

	const std::unordered_map<AIname, Graph::Form> ghost {
	    {BLINKY, {Arcade::FormIdx::OTHER, "Ressources/Games/Pacman/forms/redGhost.txt"}},
	    {INKY, {Arcade::FormIdx::OTHER, "Ressources/Games/Pacman/forms/blueGhost.txt"}},
	    {PINKY, {Arcade::FormIdx::OTHER, "Ressources/Games/Pacman/forms/pinkGhost.txt"}},
	    {CLYDE, {Arcade::FormIdx::OTHER, "Ressources/Games/Pacman/forms/orangeGhost.txt"}},
	};

	const std::unordered_map<Arcade::Events, std::string> pacman {
	    {Arcade::Events::MV_Z, "Ressources/Games/Pacman/forms/upPacman.txt"},
	    {Arcade::Events::MV_S, "Ressources/Games/Pacman/forms/downPacman.txt"},
	    {Arcade::Events::MV_D, "Ressources/Games/Pacman/forms/rightPacman.txt"},
	    {Arcade::Events::MV_Q, "Ressources/Games/Pacman/forms/leftPacman.txt"},
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

	virtual void restart() noexcept;

	void setLib(Graph::AGraph *lib) noexcept;

    protected:

	/**
	 * @brief intiate the game
	 */
	virtual void initGame(void);

	/**
	 * @brief open map for the game
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
	 * @brief display all component
	 */
	virtual void display(void);

	/**
	 * @brief move Nibbler position
	 * 
	 * @param p place
	 * @param y that must be add
	 * @param x that must be has
	 * @param evt that have been made
	 * 
	 * @return if the move is valid
	 */
	virtual bool movePacman(std::size_t p, int y, int x, Arcade::Events evt);

	/**
	 * @brief handle ghost movement
	 */
	virtual void handleGhost(void);

	/**
	 * @brief move ghost
	 * 
	 * @param ref entity reference
	 * @param place place
	 * 
	 */
	virtual void moveGhost(AIname ref, std::size_t place);

	/**
	 * @brief get all the movement possibility
	 * 
	 * @param ref entity reference
	 * @param place place
	 * 
	 * @return vectore off all movement possible
	 * 
	 */
	virtual std::vector<std::pair<AImove, Graph::Position>> getGhostPossibility(Game::Pacman::AIname name, std::size_t place);

	/**
	 * @brief check ghost
	 * 
	 * @param ref entity reference
	 * @param move to make
	 * @param dif difference to check
	 * @param base emplacement
	 * @param p place
	 * 
	 * @return if collision
	 */
	virtual bool checkGhost(Game::Pacman::AIname ref, Game::Pacman::AImove move, Graph::Position dif, std::size_t base, std::size_t p);

	/**
	 * @brief move entity
	 * 
	 * @param p place
	 * @param y that must be add
	 * @param x that must be add
	 * 
	 */
	virtual void moveEntity(std::size_t p, int y, int x);

	/**
	 * @brief handle collision between
	 */
	virtual void handleCollision(void);

	/**
	 * @brief do if pacman is collide
	 * 
	 * @param ic emplacement
	 */
	virtual void pacmanCollision(std::size_t ic);

	/**
	 * @brief restart the game if win or lose
	 * 
	 * @param win define win
	 */
	virtual void restart(bool win);

	/**
	 * @brief inverse chase
	 */
	virtual void inverseChase(void);

	/**
	 * @brief end chase
	 */
	virtual void endChase(void);

	/**
	 * @brief move entity and verified is collision
	 * 
	 * @param base base emplacement
	 * @param p place
	 * @param y that has to be add
	 * @param x that has to be add
	 * 
	 * @return emplacement to check
	 */
	virtual std::size_t calcEmplacement(std::size_t base, std::size_t p, int y, int x);

    private:
        Arcade::Events _tmp;
	std::array<std::pair<AImove, bool>, 4> _ghost;
        double _period;
        double _ghostPeriod;
	bool _pacgums;
	Graph::Size _offset;
        Graph::Size _map;
	std::size_t _len;
	std::size_t _life;
	std::size_t _score;
	std::size_t _nbGhostEat;
	std::size_t _nbpacgums;
	std::size_t _level;
	std::size_t _nbimage;
	std::size_t _icscore;
        std::chrono::_V2::steady_clock::time_point _last;
	std::chrono::_V2::steady_clock::time_point _lastGhost;
	std::chrono::_V2::steady_clock::time_point _game;
	std::chrono::_V2::steady_clock::time_point _chase;
    };
}

/**
 * @brief end point of the library.
 *
 * @return Must return an unique_ptr of the graphic library class
 */
extern "C" Game::AGame *endPoint(void);

#endif /* !NIBBLER_HPP_ */
