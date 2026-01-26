//
// Created by tiernux on 09/01/2026.
//

#ifndef SPLATFORM_SERIALIZER_H
#define SPLATFORM_SERIALIZER_H
#include <iosfwd>
#include <unordered_map>

#include "SFML/Audio/Music.hpp"

#endif //SPLATFORM_SERIALIZER_H

class Object;

enum class Mode { Saving, Loading };

class Serializer {
public:
    Mode mode;
    std::unordered_map<std::string, std::string> database;
    std::string currentContext;

    Serializer(Mode m) : mode(m) {}


    template<typename T>
    void Property(const char* name, T& value);

    void Property(const char* name, Object*& ptr);



};

