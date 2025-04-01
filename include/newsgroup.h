

#ifndef newsgroup_H
#define newsgroup_H

#include <string.h>
#include <iostream>

class Newsgroup
{
private:
    std::string& name;
    std::string& id;

public:
    Newsgroup(std::string &name, std::string &id) : name{name}, id{id} {}

    std::string& getName() const { return name; }
    std::string& getId() const { return id; }
};

#endif