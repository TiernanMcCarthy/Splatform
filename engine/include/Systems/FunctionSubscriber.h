//
// Created by tiernan on 7/3/25.
//
#pragma once

#include "../Objects/Object.h"
#include <functional>
#include <iostream>
#include <vector>
//Argument Template, generic that can hold function arguments

template <typename... Args>
class ArgumentHolder
{

};


/// Designed to subscribe to another object's function, generic and should work will all data types
/// Expansion would be to use an Unordered Map that hashes the object this is attached to with the Function
/// This way we could add and remove functions, but this isn't needed yet.
/// Also, can add arguments later, but really not needed for behaviour right now
class FunctionSubscriber
{
public:

    FunctionSubscriber();

    ~FunctionSubscriber();

    ///If executing a member function, use std::bind(&ObjectType::ExampleFunction, &Object)
    ///If Just a generic or static function, no need to bind, just call Subscribe(Function);
    void Subscribe(const std::function<void()>& func);


    void Activate();



private:



    std::vector<std::function<void()>> functionList;



};