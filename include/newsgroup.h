

#ifndef newsgroup_H
#define newsgroup_H

#include <string.h>
#include <iostream>

class Newsgroup
{
private:
    std::string name;
    std::string id;

public:
    Newsgroup(const std::string &name, const std::string &id) : name{name}, id{id} {}

    const std::string& getName() const { return name; }
    const std::string& getId() const { return id; }
};

#endif