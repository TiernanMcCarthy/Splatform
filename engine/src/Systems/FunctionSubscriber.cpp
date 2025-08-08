//
// Created by tiernan on 7/3/25.
//
#include "../../include/Systems/FunctionSubscriber.h"

FunctionSubscriber::FunctionSubscriber()
{


}


FunctionSubscriber::~FunctionSubscriber()
{

}

void FunctionSubscriber::Subscribe(const std::function<void()>& func)
{
    functionList.push_back(func);
}


void FunctionSubscriber::Activate()
{
    for (int i = 0; i < functionList.size(); i++)
    {
        functionList[i]();
    }
}







