#include <iostream>

#include "main.hpp"
#include "default.hpp"

const int winningInv = 7;
const char* separator = "-------------------------------";

int main() {
	// Instantiate default world, program is running, default CommandBuf
	ProgState ps = { // Since all command functions receive same arguments, this is the single common arg.
		true, CommandBuf(), makeDefaultWorld()
	};
	// printf("%s %s %s %s\n%s %s %s %s\n",
	// 	NORTH.data,EAST.data,SOUTH.data,WEST.data,
	// 	NORTHEAST.data,SOUTHEAST.data,SOUTHWEST.data,NORTHWEST.data);
	// w.printAll();

	Command::Help(ps);
	printf("Welcome to %s!\n", ps.world.name_cstr());

	while (ps.running) { // Keep prompting for commands as long as user hasn't ended program
		printf("%s\n",separator);
		ps.world.printLocation();
		ps.cb("> "); // Prompt user for input
		if (ps.cb.Tokens() < 1) continue; // If no tokens are passed, skip loop.
		const char* cmd = ps.cb.GetToken(0); // Commands are case-INSENSITIVE.
		try { // Try to find the user's command!
			CommandDefinition::Function func = Command::cmd_map.at({cmd}).func; // Find command function from key.
			func(ps); // Call found function using the current ProgState 
		} catch (...) { printf("\"%s\" is not a known command!\n", ps.cb.GetToken(0)); } // When key is not found in map.
		
		checkWin(ps);
	}	
}

// The the program state for a win, if won, stop the game and congradulate!
void checkWin(ProgState& ps) {

}

namespace Command {
	// Quits program as long as additional arguments aren't accidentally passed.
	void Quit(ProgState& ps) {
		if (ps.cb.Tokens() > 1) {
			printf("Didn't expect additional arguments!\n");
			return;
		}
		printf("Quit!\n");
		ps.running = false;
	}
	// Prints all commands, their arguments and descriptions as well.
	void Help(ProgState& ps) {
		const char* const prefix = "	";
		printf("Help:\n");
		size_t maxlen = 0; // strlen(cmd) + 1 + strlen(args)
		for (auto it = cmd_map.cbegin();it!=cmd_map.cend();++it) {
			size_t len = strlen(it->first.data) + 1 + strlen(it->second.args);
			if (len > maxlen) maxlen = len;
		}

		const size_t CMAXLEN = maxlen;
		char cmddef[CMAXLEN+1]; // allow for null terminating char
		for (auto it = cmd_map.cbegin();it!=cmd_map.cend();++it) {	
			snprintf(cmddef, CMAXLEN+1, strlen(it->second.args)<1 ? "%s":"%s %s", it->first.data, it->second.args);
			printf("%*s - %s\n", CMAXLEN, cmddef, it->second.help);
		}
	}

	// Go a specfied heading from this room, moving the playerLoc there.
	void Go(ProgState& ps) {
		
	}

	// List items in players inventory
	void Inv(ProgState& ps) {
		printf("Player inventory (%u,%d): \n", ps.world.itemCount(),winningInv);
		ps.world.printInv("    ");
		printf("\n");
	}

	// Pickup specified item from current room, put in player inventory.
	void Pickup(ProgState& ps) {

	}
}