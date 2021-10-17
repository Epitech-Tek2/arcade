/*
** EPITECH PROJECT, 2021
** B-OOP-400-STG-4-1-arcade-sarah.keppler
** File description:
** Score
*/

#include "Score.hpp"

void Arcade::Score::init(std::string const &name)
{
    _scores[name].fill({"", 0});
}

void Arcade::Score::parseLine(std::string const &line, std::string const &cGame, std::size_t i)
{
    if (i >= 3) return;
    if (std::count(line.begin(), line.end(), ':') != 1)
        throw MinorError("Score: \"" + line + "\": invalid line");
    std::size_t pos = line.find_first_of(":");
    std::string name = line.substr(0, pos);
    std::size_t score = std::stoi(line.substr(pos + 1));

    _scores[cGame][i].first = name;
    _scores[cGame][i].second = score;
}

void Arcade::Score::parseFile(std::fstream &file)
{
    std::string line;
    std::string cGame = "";

    for (std::size_t nb = 0; getline(file, line); ++nb) {
        try {
            std::cout << line << std::endl;
            if (line.size() && line[0] == '#') {
                cGame = line.substr(1);
                _scores[cGame].fill({"", 0});
                nb = -1;
            }
            else if (!cGame.empty())
                parseLine(line, cGame, nb);
        } catch (MinorError const &error) {
            std::cerr << error.what() << std::endl;
        }
    }
}

void Arcade::Score::dump(void)
{
    std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>>::iterator i= _scores.begin();

    std::cout << std::endl << "dump:" << std::endl;
    for (; i != _scores.end(); ++i) {
        std::cout << i->first << std::endl;
        for (std::size_t e = 0; e < 3; ++e) {
            std::cout << i->second[e].first << " " << i->second[e].second << std::endl;
        }
    }
}

std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>>
Arcade::Score::getScores(void)
{
    struct stat buffer;
    std::fstream file;

    _path = "./Ressources/Score";
    if (stat(_path.c_str(), &buffer))
        _path = "./../Ressources/Score";
    if (stat(_path.c_str(), &buffer))
        throw FatalError("Impossible update or create file, folder Score has been removed");
    file.open(_path + "/Score.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    if (file) {
        parseFile(file);
    } else {
        throw FatalError("Score: " + _path + ": No such file or directory");
    }
    // dump();
    file.close();
    return (_scores);
}

void Arcade::Score::writeFile(std::string const &game, std::string const &name, std::size_t score, std::size_t position)
{
    std::ofstream content(_path + "/temp.txt");
    std::fstream file(_path + "/Score.txt");
    std::string sentence = name + ":" + std::to_string(score);
    std::string line;
    int rank = 0;
    bool insert = false;
    bool isInsert = false;

    if (!file || !content)
        throw MinorError("Score: cannot be update");
    for (; getline(file, line); ++rank) {
        if (!line.compare("#" + game)) {
            insert = true;
        } else if (insert && rank == (int)position && !isInsert) {
            content << sentence << std::endl;
            ++rank;
            isInsert = true;
        }
        if (line.size() && line[0] == '#')
            rank = -1;
        if (rank <= 2)
            content << line << std::endl;
    }
    if (!insert)
        content << "#" << game << std::endl;
    if (!isInsert)
        content << sentence << std::endl;
    file.close();
    content.close();
    if(remove((_path + "/Score.txt").c_str()))
        throw MinorError("Score: impossible to remove file");
    if(rename((_path + "/temp.txt").c_str(), (_path + "/Score.txt").c_str()))
        throw MinorError("Score: impossibe to rename temp.txt file");
}

std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>>
Arcade::Score::newScore(std::string const &game, std::string const &name, std::size_t score)
{
    std::pair<std::string, std::size_t> pair;
    bool insert = false;
    std::size_t e = 0;

    for (; e < 3; ++e) {
        if (score > _scores[game][e].second) {
            pair = _scores[game][e];
            insert = true;
            break;
        }
    }
    if (insert) {
        std::cout << "e:" << e << std::endl;
        for (std::size_t i = 2; i > e; --i)
            _scores[game][i] = _scores[game][i - 1];
        _scores[game][e] = {name, score};
        try {
            writeFile(game, name, score, e);
        } catch (MinorError const &error) {
            std::cerr << error.what() << std::endl;
        }
    }
    // dump();
    return (_scores);
}
