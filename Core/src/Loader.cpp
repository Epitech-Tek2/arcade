/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Loader
*/

#include "Loader.hpp"

Arcade::Loader::~Loader()
{
    // std::vector<void *>::iterator i = _handle.begin();

    // for (; i != _handle.end(); ++i)
    //     dlclose(*i);
}

Arcade::ILib *Arcade::Loader::getInstance(std::string const &path, std::string const &name)
{
    void *handle;
    Arcade::ILib *(*endPoint)();
    Arcade::ILib *lib;

    handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle)
        throw FatalError(dlerror());
    endPoint = (Arcade::ILib *(*)())dlsym(handle, name.c_str());
    if (!endPoint)
        throw FatalError("Invalid library endPoint:\"" + name + "\"");
    lib = endPoint();
    if (!lib)
        throw FatalError("Invalid instance of endPoint");
    _handle.push_back(handle);
    return (lib);
}

std::vector<std::string> Arcade::Loader::getLibrariesPath(void)
{
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> paths;
    std::string path = "./lib/";

    dir = opendir(path.c_str());
    if (!dir) {
        path = "./../lib/";
        dir = opendir(path.c_str());
        if (!dir)
            throw FatalError("Loader: folder \"lib\" not found");
    }
    while ((ent = readdir(dir))) {
        if (ent->d_type & DT_DIR || ent->d_name[0] == '.')
            continue;
        paths.push_back(path + ent->d_name);
    }
    closedir(dir);
    return (paths);
}
