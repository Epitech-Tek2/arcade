/*
** Arcade
** Sarah-Keppler
*/

#include "../include/IGraph.hpp"

Graph::AGraph::AGraph(Arcade::Type const type, std::string const &name) noexcept : _type{type}, _name{name}
{
}

Arcade::Type Graph::AGraph::getType() const noexcept
{
    return _type;
}

std::string Graph::AGraph::getName() const noexcept
{
    return _name;
}
