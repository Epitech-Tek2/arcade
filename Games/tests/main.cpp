/*
** Arcade tests | Game
** Sarah-Keppler
*/

#include "IGame.hpp"
#include "Pacman.hpp"
#include "Nibbler.hpp"
#include "../../Graphs/include/NCurses.hpp"
#include "../../Graphs/include/SDL2.hpp"
#include "../../Graphs/include/SFML.hpp"
#include <chrono>

int main(void)
{
    try {
        Game::Pacman game;
        // Game::Nibbler game;
        // Graph::SDL2 *graph = new Graph::SDL2();
        // Graph::NCurses *graph = new Graph::NCurses();
        Graph::SFML *graph = new Graph::SFML();
        Arcade::Events evt = Arcade::Events::NONE;
        std::chrono::_V2::steady_clock::time_point begin =std::chrono::steady_clock::now();
        std::chrono::duration<double> elapse = std::chrono::steady_clock::now() - begin;

        game.load((Graph::AGraph *)(graph));
        while (Arcade::Events::QUIT != evt) {
            evt = game.handleEvents();
            elapse = std::chrono::steady_clock::now() - begin;
            game.handleUpdate(elapse.count());
        }
    } catch (Arcade::Error const &error) {
        std::cerr << error.what() << std::endl;
        return (84);
    }
    return (0);
}


// int main(void)
// {
//     try {
//         Game::Pacman game;
//         // Game::Nibbler game;
//         // Graph::SDL2 *graph = new Graph::SDL2();
//         // Graph::NCurses *graph = new Graph::NCurses();

//         Graph::Position pos = {5, 5};
//         Arcade::ColorIdx color = {Arcade::ColorIdx::GREEN};
//         Graph::Size size = {16, 16};
//         Graph::Form form = {Arcade::FormIdx::RECT, ""};

//         // Graph::Position pos = {13, 5};
//         // Graph::Size size = {16, 16};
//         // Graph::Text text = {"text"};

//         Arcade::Events evt = Arcade::Events::NONE;
//         Graph::SFML *graph = new Graph::SFML();
//         graph->open("ici", "Ressources/Games/Pacman/ghost.png");
//         while (Arcade::Events::QUIT != evt) {
//             evt = graph->getEvent();
//             graph->displayWindow();
//             graph->displayImage(pos, form, color, size);
//             // graph->displayText(text, pos, size);
//         }
//         // std::chrono::_V2::steady_clock::time_point begin =std::chrono::steady_clock::now();
//         // std::chrono::duration<double> elapse = std::chrono::steady_clock::now() - begin;

//         // game.load((Graph::AGraph *)(graph));
//         //     elapse = std::chrono::steady_clock::now() - begin;
//         //     game.handleUpdate(elapse.count());
//         // }
//     } catch (Arcade::Error const &error) {
//         std::cerr << error.what() << std::endl;
//         return (84);
//     }
//     return (0);
// }

// int main(void)
// {
//     try {
//         Game::Pacman game;
//         Graph::SDL2 *SDL2 = new Graph::SDL2();
//         Arcade::Events evt = Arcade::Events::NONE;
//         std::chrono::_V2::steady_clock::time_point begin = std::chrono::steady_clock::now();
//         std::chrono::duration<double> elapse = std::chrono::steady_clock::now() - begin;

//         game.load((Graph::AGraph *)(SDL2));
//         while (Arcade::Events::QUIT != evt) {
//             evt = game.handleEvents();
//             elapse = std::chrono::steady_clock::now() - begin;
//             game.handleUpdate(elapse.count());
//         }
//     } catch (Arcade::GameError const &error) {
//         std::cerr << error.what() << std::endl;
//         return (84);
//     } catch (Arcade::Error const &error) {
//         std::cerr << error.what() << std::endl;
//         return (84);
//     }
//     return (0);
// }