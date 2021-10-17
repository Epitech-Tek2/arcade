/*
** Arcade tests | Game
** Sarah-Keppler
*/

#include "Menu.hpp"
#include "../../Graphs/include/SDL2.hpp"
#include "../../Common/Error.hpp"

int main()
{
    std::vector<std::string> graphs{std::string{"ncurses"}, std::string{"SDL2"}, std::string{"SFML"}};
    std::vector<std::string> games{std::string{"Nibbler"}, std::string{"Pacman"}};
    std::unordered_map<std::string, std::array<std::pair<std::string, std::size_t>, 3>> scores;
    std::pair<std::string, std::size_t> g1j1{"Sosoh", 18000};
    std::pair<std::string, std::size_t> g1j2{"Clement", 19000};
    std::pair<std::string, std::size_t> g1j3{"Jojo", 17000};
    std::pair<std::string, std::size_t> g2j1{"Sosoh", 18000};
    std::pair<std::string, std::size_t> g2j2{"Clement", 17000};
    std::pair<std::string, std::size_t> g2j3{"Jojo", 19000};
    std::string g1{"Nibbler"}, g2{"Pacman"};
    scores[g1] = std::array<std::pair<std::string, std::size_t>, 3>{g1j1, g1j2, g1j3};
    scores[g2] = std::array<std::pair<std::string, std::size_t>, 3>{g2j1, g2j2, g2j3};
    Game::Menu menu{graphs, games, scores};
    Graph::SDL2 *SDL2 = new Graph::SDL2();
    SDL2->open("Title", "wallpaper.png");
    try {
        menu.load((Graph::AGraph *)SDL2);
	Arcade::Events evt = menu.handleEvents();
	while (Arcade::Events::QUIT != evt) {
	    menu.handleUpdate(0.5f);
	    menu.display();
	    evt = menu.handleEvents();
	}
    } catch (Arcade::Error const &error) {
	std::cerr << error.what() << std::endl;
    }
    /*
      Arcade::Events evt = Arcade::Events::NONE;
      while (Arcade::Events::QUIT != evt) {
      std::cout << "her" << std::endl;
      evt = menu.handleEvents();
      }*/
    return 0;
}
