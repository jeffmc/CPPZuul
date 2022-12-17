#pragma once

#include "main.hpp"

// Directions defined as global constants!
const jstring NORTH = { "north" },
	EAST = { "east" },
	SOUTH = { "south" },
	WEST = { "west" },
	NORTHEAST = { "northeast" },
	SOUTHEAST = { "southeast" },
	SOUTHWEST = { "southwest" },
	NORTHWEST = { "northwest" };

// returns a default world (map of oregon)
World makeDefaultWorld() {
	using rptr = Room*;
	rptr eug = new Room("Eugene"),
		port = new Room("Portland"),
		beav = new Room("Beaverton"),
		bend = new Room("Bend"),
		hboro = new Room("Hillsboro"),
		cannon = new Room("Cannon Beach"),
		salem = new Room("Salem"),
		tmook = new Room("Tillamook"),
		hriver = new Room("Hood River"),
		dalles = new Room("The Dalles"),
		pendleton = new Room("Pendleton"),
		enterprise = new Room("Enterprise"),
		newport = new Room("Newport"),
		burns = new Room("Burns"),
		vale = new Room("Vale"),
		coquille = new Room("Coquille"),
		medford = new Room("Medford");

#define ZUULLINK(ROOM_A,ROOM_B,HEADING_A,HEADING_B) \
	ROOM_A->add_portal(HEADING_A,ROOM_B); \
	ROOM_B->add_portal(HEADING_B,ROOM_A);

	// 26 links total
	// Green links on map (6)
	ZUULLINK(cannon,hboro,EAST,WEST);
	ZUULLINK(hboro,port,EAST,WEST);
	ZUULLINK(port,hriver,EAST,WEST);
	ZUULLINK(hriver,dalles,SOUTH,NORTH);
	ZUULLINK(dalles,pendleton,EAST,WEST);
	ZUULLINK(pendleton,enterprise,SOUTHEAST,NORTHWEST);
	// Cyan links on map: (9)
	ZUULLINK(cannon,tmook,SOUTH,NORTH);
	ZUULLINK(tmook,newport,SOUTH,NORTH);
	ZUULLINK(tmook,hboro,NORTHEAST,SOUTHWEST);
	ZUULLINK(hboro,beav,SOUTHEAST,NORTHWEST);
	ZUULLINK(beav,salem,SOUTH,NORTH);
	ZUULLINK(beav,port,NORTHEAST,SOUTHWEST);
	ZUULLINK(dalles,bend,SOUTH,NORTH);
	ZUULLINK(pendleton,burns,SOUTH,NORTH);
	ZUULLINK(enterprise,vale,SOUTH,NORTH);
	// Yellow links on map: (7)
	ZUULLINK(newport,salem,NORTHEAST,SOUTHWEST);
	ZUULLINK(newport,eug,SOUTHEAST,NORTHWEST);
	ZUULLINK(salem,eug,SOUTH,NORTH);
	ZUULLINK(salem,bend,SOUTHEAST,NORTHWEST);
	ZUULLINK(eug,bend,EAST,WEST);
	ZUULLINK(bend,burns,EAST,WEST);
	ZUULLINK(burns,vale,NORTHEAST,SOUTHWEST);
	// Red links on map: (4)
	ZUULLINK(newport,coquille,SOUTH,NORTH);
	ZUULLINK(coquille,medford,SOUTHEAST,NORTHWEST);
	ZUULLINK(eug,medford,SOUTH,NORTH);
	ZUULLINK(medford,bend,NORTHEAST,SOUTHWEST);

	using iptr = Item*;
	iptr ducks = new Item("ducks"),
		skys = new Item("skyscraper"),
		nike = new Item("nike"),
		skiing = new Item("skiing"),
		hops = new Item("hops"),
		water = new Item("water"),
		capital = new Item("capital");
	
	World w("The State of Oregon", {
		eug, port, beav, bend, hboro, cannon, salem,
		tmook,hriver,dalles,pendleton,enterprise,newport,burns,vale,coquille,medford
	});
	eug->set_item(ducks);
	port->set_item(skys);
	beav->set_item(nike);
	bend->set_item(skiing);
	hboro->set_item(hops);
	cannon->set_item(water);
	salem->set_item(capital);

	return w;
}
