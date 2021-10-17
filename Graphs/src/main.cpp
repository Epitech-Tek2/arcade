/*
** Arcade tests | Graphs
** Sarah-Keppler
*/

#include "SDL2.hpp"
#include "../../Common/Error.hpp"
/*
** EVENTS **
int main()
{
    try {
	Graph::SDL2 sdl2;
	sdl2.open("Titre", "wallpaper.png");
	Arcade::Events evt = Arcade::Events::NONE;
	while (Arcade::Events::QUIT != evt) {
	    evt = sdl2.getEvent();
	    if (Arcade::Events::NONE != evt && Arcade::Events::QUIT != evt)
		std::cout << sdl2.getEventChar() << std::endl;
	}
	sdl2.close();
    } catch (Arcade::SDL2Error const &err) {
	std::cerr << err.what() << std::endl;
	return 84;
    }
    return 0;
}
*/

/*
** DISPLAY **
int main()
{
    try {
	Graph::SDL2 sdl2;
	sdl2.open("Titre", "wallpaper.png");
	Arcade::Events evt = Arcade::Events::NONE;
	while (Arcade::Events::QUIT != evt) {
	    evt = sdl2.getEvent();
	    Graph::Position pos{0, 0};
	    Graph::Color color{255, 0, 0, 255};
	    Graph::Size size{16, 16};
	    Graph::Form form{Arcade::FormIdx::OTHER, "leftGhost.txt"};
	    sdl2.displayImage(pos, form, color, size);
	    Graph::Position pos2{50, 50};
	    Graph::Color color2{255, 255, 0, 255};
	    Graph::Size size2{16, 16};
	    Graph::Form form2{Arcade::FormIdx::OTHER, "pacman.txt"};
	    sdl2.displayImage(pos2, form2, color2, size2);
	    sdl2.displayWindow();
	}
	sdl2.close();
    } catch (Arcade::SDL2Error const &err) {
	std::cerr << err.what() << std::endl;
	return 84;
    }
    return 0;
}
 */

int main()
{
    try {
	Graph::SDL2 sdl2;
	sdl2.open("Titre", "wallpaper.png");
	sdl2.setTitle("Titre 2");
	sdl2.setIcon("01.jpg");
	Arcade::Events evt = Arcade::Events::NONE;
	Graph::Position LGhostp{0, 0};
	Graph::Color LGhostc{255, 0, 0, 255};
	Graph::Size LGhosts{16, 16};
	Graph::Form LGhostf{Arcade::FormIdx::OTHER, "leftGhost.txt"};
	Graph::Position Pacmanp{3, 3};
	Graph::Color Pacmanc{255, 255, 0, 255};
	Graph::Size Pacmans{16, 16};
	Graph::Form Pacmanf{Arcade::FormIdx::OTHER, "pacman.txt"};
	Graph::Position LGhostp2{7, 7};
	Graph::Color LGhostc2{255, 0, 0, 255};
	Graph::Size LGhosts2{16, 16};
	Graph::Form LGhostf2{Arcade::FormIdx::OTHER, "leftGhost.txt"};
	Graph::Position Pacmanp2{8, 7};
	Graph::Color Pacmanc2{255, 255, 0, 255};
	Graph::Size Pacmans2{16, 16};
	Graph::Form Pacmanf2{Arcade::FormIdx::OTHER, "pacman.txt"};
	Graph::Position squarep{10, 10};
	Graph::Size squares{16, 16};
	Graph::Form squaref{Arcade::FormIdx::RECT};
	while (Arcade::Events::QUIT != evt) {
	    evt = sdl2.getEvent();
	    sdl2.displayImage(LGhostp, LGhostf, Arcade::ColorIdx::RED, LGhosts);
	    sdl2.displayImage(Pacmanp, Pacmanf, Arcade::ColorIdx::RED, Pacmans);
	    sdl2.displayImage(LGhostp2, LGhostf2, Arcade::ColorIdx::RED, LGhosts2);
	    sdl2.displayImage(Pacmanp2, Pacmanf2, Arcade::ColorIdx::RED, Pacmans2);
	    sdl2.displayImage(squarep, squaref, Arcade::ColorIdx::RED_VIOLET, squares);
	    if (sdl2.checkCollision(LGhostp, LGhosts, Pacmanp, Pacmans))
		std::cout << "Pacman is not safe" << std::endl;
	    else
		std::cout << "Pacman is safe" << std::endl;
	    if (sdl2.checkCollision(LGhostp2, LGhosts2, Pacmanp2, Pacmans2))
		std::cout << "Pacman is not safe" << std::endl;
	    else
		std::cout << "Pacman is safe" << std::endl;
	    std::cout << "---------------" << std::endl;
	    sdl2.displayWindow();
	}
	sdl2.close();
    } catch (Arcade::SDL2Error const &err) {
	std::cerr << err.what() << std::endl;
	return 84;
    }
    return 0;
}
