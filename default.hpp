#pragma once
#include "main.hpp"

World makeDefaultWorld() {
	using rptr = Room*;
	rptr eug = new Room("Eugene"),
		port = new Room("Portland"),
		beav = new Room("Beaverton"),
		bend = new Room("Bend"),
		hboro = new Room("Hillsboro"),
		cannon = new Room("Cannon Beach"),
		salem = new Room("Salem");
	
	using iptr = Item*;
	iptr ducks = new Item("Ducks"),
		skys = new Item("Skyscrapers"),
		nike = new Item("Nike WHQ"),
		views = new Item("Good Views"),
		hops = new Item("Hops Baseball"),
		water = new Item("Water"),
		capital = new Item("State Capital");
	
	World w("State of Oregon");
	w.add(eug);
	w.add(port);
	w.add(beav);
	w.add(bend);
	w.add(hboro);
	w.add(cannon);
	w.add(salem);

	eug->add(ducks);
	port->add(skys);
	beav->add(nike);
	bend->add(views);
	hboro->add(hops);
	cannon->add(water);
	salem->add(capital);

	return w;
}
