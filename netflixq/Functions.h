#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <Windows.h>
#include <string>
bool IsOwnWindow();
BOOL WINAPI SignalControlCHandler(DWORD ctrlEvent);
std::string GetLastErrorAsString();
#endif // !FUNCTIONS_H