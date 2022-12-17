#pragma once
// This file contains the declaration of the entry point

#include <vector>
#include <unordered_map>
#include <cstring>
#include <limits>

#include "jstring.hpp"
#include "command.hpp"
#include "zuul.hpp"

int main();

// This CommandDefinition/ProgState structure follows a similar pattern to my previous project
// I found it the easiest to develop command-line apps with.

// ProgState is passed to each of the command functions
struct ProgState {
	bool running; // If set to false within command, user will NOT be prompted for additional command and program will end.
	CommandBuf cb; // Contains user-input
	World world; // Could contain additional user-defined media, or none at all. 
};

// Store command keywords, arguments, and descriptions.
struct CommandDefinition {
	using Function = void(*)(ProgState&); // Called when key is found in 0th arg of CommandBuf
	const Function func;
	const char* const args;
	const char* const help;	
};

void checkWin(ProgState& ps);

namespace Command {
	void Quit(ProgState& ps);       // Quits program as long as additional arguments aren't accidentally passed.
	void Help(ProgState& ps);       // Prints command keywords, arguments, and descriptions
	void Inv(ProgState& ps);       
	void Pickup(ProgState& ps);   
	void Go(ProgState& ps);  

	const std::unordered_map<jstring, CommandDefinition> cmd_map = {
		{       {"quit"}, { Quit,       "", "Ends the program." }},
		{       {"help"}, { Help,       "", "this" }},
		{       {"inv"}, { Inv,       "", "List items in your inventory" }},
		{       {"go"}, { Go,       "[heading]", "Go to the room in this direction." }},
		{       {"pickup"}, { Pickup,       "[item]", "Pickup this item from current room." }},
	};
}