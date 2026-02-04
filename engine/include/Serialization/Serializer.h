//
// Created by tiernux on 09/01/2026.
//
#pragma once
#include "Objects/EntityID.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include <sstream>
#include <string>
#include <unordered_map>

class Object;

enum class Mode { Saving, Loading };




class Serializer {
public:
    Mode mode;
    std::unordered_map<std::string, std::string> database;
    std::string currentContext;

    Serializer(Mode m);

    template<typename T> //Generic predefined types
    void Property(const std::string& name, T& value) {
        std::string key = currentContext.empty() ? name : currentContext + "." + name;

        if (mode == Mode::Saving) {
            std::stringstream ss;
            ss << value;
            database[key] = ss.str();
        }
        else if (database.count(key)) {
            std::stringstream ss(database[key]);
            ss >> value;
        }
    }


    //Overides for specific objects

    //SF::Color
    void Property(const std::string& name, sf::Color& value) {
        std::string key = currentContext.empty() ? name : currentContext + "." + name;
        if (mode == Mode::Saving) {
            std::stringstream ss;
            ss << (int)value.r << " " << (int)value.g << " " << (int)value.b << " " << (int)value.a;
            database[key] = ss.str();
        } else if (database.count(key)) {
            std::stringstream ss(database[key]);
            int r, g, b, a;
            ss >> r >> g >> b >> a;
            value = sf::Color(r, g, b, a);
        }
    }


    // Handle sf::Vector2f
    void Property(const std::string& name, sf::Vector2f& value) {
        std::string key = currentContext.empty() ? name : currentContext + "." + name;
        if (mode == Mode::Saving) {
            database[key] = std::to_string(value.x) + " " + std::to_string(value.y);
        } else if (database.count(key)) {
            std::stringstream ss(database[key]);
            ss >> value.x >> value.y;
        }
    }

    void SaveString(const std::string& name, const std::string& value);

    // Specific overload for Object pointers
    void Property(const std::string& name, Object*& ptr);
};

// --- MACROS for Reflection on classes
#define REFLECT_BEGIN(ClassName, ParentClass) \
std::string GetTypeName() const override { return #ClassName; } \
void Serialize(Serializer& s) override { \
std::string oldCtx = s.currentContext; \
s.currentContext = #ClassName + std::to_string(ObjectID); \
s.Property("ObjectID", ObjectID);

#define REFLECT_VAR(VarName) s.Property(#VarName, VarName);

#define REFLECT_LINK(VarName) \
{ Object* temp = static_cast<Object*>(VarName); \
s.Property(#VarName, temp); \
if (s.mode == Mode::Loading) VarName = (decltype(VarName))temp; }

#define REFLECT_END() s.currentContext = oldCtx; }