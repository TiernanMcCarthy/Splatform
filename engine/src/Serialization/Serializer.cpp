//
// Created by tiernux on 09/01/2026.
//
#include "Serialization/Serializer.h"

#include "Objects/Object.h"


// load or save template classes from stream
template<typename T>
void Serializer::Property(const char* name, T& value) {
    std::string key = currentContext + "." + name;
    if (mode == Mode::Saving) {
        std::stringstream ss;
        ss << value;
        database[key] = ss.str();
    } else if (database.count(key)) {
        std::stringstream ss(database[key]);
        ss >> value;
    }
}

// Version B: Object Pointers (Overload)
// This resolves the Clangd "invalid operands" error by bypassing the template
void Serializer::Property(const char* name, Object*& ptr) {
    std::string key = currentContext + "." + name;
    if (mode == Mode::Saving) {
        database[key] = std::to_string(ptr ? ptr->m_uid : 0);
    } else if (database.count(key)) {
        if (database.count(key) && database[key] != "0") {
            ptr = Object::Find(std::stoull(database[key]));
        } else {
            ptr = nullptr;
        }
    }
}

void Object::Serialize(Serializer& s) {
    s.Property("m_uid", m_uid);
}