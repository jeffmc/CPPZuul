#pragma once
#include "main.hpp"

World makeDefaultWorld() {
	using rptr = Room*;
	rptr citySquare = new Room("City Square"),
		grandExchange = new Room("Grand Exchange"),
		groceryStore = new Room("Grocery Store");
	
	World w("Jeff's Map");
	w.add(citySquare);
	w.add(grandExchange);
	w.add(groceryStore);

	return w;
}