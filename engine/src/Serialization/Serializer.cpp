//
// Created by tiernux on 09/01/2026.
//
#include "Serialization/Serializer.h"

#include "Objects/Object.h"


Serializer::Serializer(Mode m) : mode(m) {}

void Serializer::SaveString(const std::string& name, const std::string& value) {
    if (mode != Mode::Saving) return;
    std::string key = currentContext.empty() ? name : currentContext + "." + name;
    database[key] = value;
}

void Serializer::Property(const std::string& name, Object*& ptr) {
    std::string key = currentContext.empty() ? name : currentContext + "." + name;

    if (mode == Mode::Saving) {
        database[key] = std::to_string(ptr ? ptr->ObjectID : 0);
    }
    else if (database.count(key)) {
        std::string val = database[key];
        if (val == "0" || val.empty()) {
            ptr = nullptr;
            return;
        }
        // This is safe because we included Object.h
        ptr = Object::Find(std::stoull(val));
    }
}