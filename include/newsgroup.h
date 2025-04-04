

#ifndef newsgroup_H
#define newsgroup_H

#include <string.h>
#include <iostream>

class Newsgroup
{
private:
    std::string name;
    std::time_t creationDate;
    std::string id;

public:
    Newsgroup(const std::string &name, const std::time_t creationDate, const std::string &id) : name{name}, creationDate{creationDate}, id{id} {}

    const std::string& getName() const { return name; }
    const std::time_t& getCreationDate() const { return creationDate; }
    const std::string& getId() const { return id; }
};

#endif