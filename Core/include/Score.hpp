/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** Score
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <sys/stat.h>
#include <algorithm>
#include "../../Common/Error.hpp"
#include <map>

namespace Arcade
{
    /**
     * @brief Load and update score file
     */
    class Score
    {
    public:
	Score() = default;
	~Score() = default;

	/**
	 * @brief Load the save file of highScore
	 *
	 * @return map of game, link to map of player with is scores
	 */
	std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>> getScores(void);

	/**
	 * @brief update the score variable and file configuration if neccessary
	 *
	 * @param game on witch the score was made
	 * @param name of the player
	 * @param score that the player make
	 *
	 * @return map of game, link to map of player with is scores
	 */
	std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>>
	newScore(std::string const &game, std::string const &name, std::size_t score);

	/**
	 * @brief init game score
	 *
	 * @param name of a game
	 */
	void init(std::string const &name);
    protected:

	/**
	 * @brief parse line of scores
	 *
	 * @param line is the line to be parse
	 * @param cGame name of the current game
	 * @param i incremeter
	 *
	 */
	void parseLine(std::string const &line, std::string const &cGame, std::size_t i);

	/**
	 * @brief parse line of scores
	 */
	void parseFile(std::fstream &file);

	/**
	 * @brief parse line of scores
	 *
	 * @param game game to update
	 * @param player name of the player
	 * @param score of the player
	 * @param position of the player
	 */
	void writeFile(std::string const &game, std::string const &name, std::size_t score, std::size_t position);

	/**
	 * @brief dump scores
	 */
	void dump(void);
    private:
	std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>> _scores;
	std::string _path;
    };
}

#endif /* !SCORE_HPP_ */
