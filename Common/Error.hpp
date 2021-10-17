/*
** Arcade
** Sarah-Keppler
*/

#ifndef ARCADE_ERROR_HPP
#define ARCADE_ERROR_HPP

#include <string>
#include <exception>

namespace Arcade
{
    class Error : std::exception
    {
    public:
	Error(std::string const &message) noexcept;
	~Error() = default;

	char const *what() const noexcept;
    private:
	std::string const _message;
    };

    class FatalError : public Error
    {
    public:
	FatalError(std::string const &message) noexcept : Error(message) {}
    private:
	std::string const _message;
    };

    class SDL2Error : public Error
    {
    public:
	SDL2Error(std::string const &message, std::string const &sdlErr) noexcept : Error{message + ": " + sdlErr} {}
    private:
	std::string const message;
    };

    class GameError : public Error
    {
    public:
	GameError(std::string const &message) noexcept : Error(message) {}
    private:
	std::string const _message;
    };

    class GraphicError : public Error
    {
    public:
	GraphicError(std::string const &message) noexcept : Error(message) {}
    private:
	std::string const _message;
    };

    class MinorError : public Error
    {
    public:
	MinorError(std::string const &message) noexcept : Error(message) {}
    private:
	std::string const _message;
    };
}

#endif /* ARCADE_ERROR_HPP */
