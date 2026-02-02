//
// Created by tiernux on 09/01/2026.
//
#pragma once
#include <string>
#include <unordered_map>
#include <sstream>
#include "Objects/EntityID.h"


class Object;

enum class Mode { Saving, Loading };




class Serializer {
public:
    Mode mode;
    std::unordered_map<std::string, std::string> database;
    std::string currentContext;

    Serializer(Mode m);

    // Template for prebuilt types
    template<typename T>
    void Property(const std::string& name, T& value) {
        std::string key = currentContext.empty() ? name : currentContext + "." + name;
        if (mode == Mode::Saving) {
            std::stringstream ss;
            ss << value;
            database[key] = ss.str();
        } else if (database.count(key)) {
            std::stringstream ss(database[key]);
            ss >> value;
        }
    }

    void SaveString(const std::string& name, const std::string& value);

    // Specific overload for Object pointers
    void Property(const std::string& name, Object*& ptr);
};

// --- MACROS --- Used to define objects
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