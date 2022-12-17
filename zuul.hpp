#pragma once


#include "jstring.hpp"

struct Item {
	jstring name;
	Item(jstring&& name) : name(name) {}

	const char* name_cstr() const {
		return name.data;
	}

};

class Room {
	jstring name;
    Item* item; // Rooms can only store single items for now, can only be picked up as well!
	std::unordered_map<jstring, Room*> portals;
public:
    void add_portal(const jstring& heading, Room* dest) {
        portals.insert({heading, dest});
    };
	Room(const char* name) : name(jstring(name)) {}
	const char* name_cstr() const { return name.data; }

	void set_item(Item* ptr) { item = ptr; }
    bool hasItem() const { return item != nullptr; }
    const char* itemCstr() const { return item->name_cstr(); }
    Item* pickupItem() { // Transfer ownership of item to player
        Item* tmp = item;
        item = nullptr;
        return tmp;
    }

    Room* portal_dest(const char* att) {
		try { // Try to find the user's direction!
			Room* r = portals.at({att}); // Find room from given heading.
			return r; // Return found destination 
		} catch (...) { return nullptr; } // When key is not found in map.
		
    }

    void print_items() {
        if (!hasItem()) { // If item is nullptr
            printf("%s has no items.\n", name_cstr());
            return;
        }
        printf("Items: %s\n", item->name_cstr());
    }
    void print_portals() {
        static const char* prefix = "    ";
        printf("Exits:\n");
        if (portals.size() == 0) {
            printf("%sNone.\n", prefix);
            return;
        }
		for (auto it = portals.cbegin();it!=portals.cend();++it) {	
			printf("%s%*s: %s\n", prefix, 9, it->first, it->second->name_cstr());
		}
    }

};

class World {
	jstring name;
	std::vector<Room*> rooms;
	Room* playerLoc;
	std::vector<Item*> playerInv;
public:
    World(jstring name, std::initializer_list<Room*> init_list) : name(name) {
        rooms = init_list;
        playerLoc = rooms[0];
    }
	const char* name_cstr() const { return name.data; }

	const char* room_name_cstr() const { return playerLoc->name_cstr(); }
	bool roomHasItem() const { return playerLoc->hasItem(); }
    void pickupItem() { 
        Item* i = playerLoc->pickupItem();
        if (i) {
            printf("Picked up \"%s\"\n",i->name_cstr());
            playerInv.push_back(i);
        } else {
            printf("No item in this room!\n");
        }
    }

    size_t itemCount() const { return playerInv.size(); }
    void printInv(const char* prefix) {
        for (auto it = playerInv.cbegin();it!=playerInv.cend();++it) {
            printf("%s%s\n", prefix, (*it)->name_cstr());
        }
    }

    void moveTo(const char* headingAtt) {
        Room* r = playerLoc->portal_dest(headingAtt);
        if (r) {
            playerLoc = r;
        } else {
            printf("Couldn't find \"%s\"!\n", headingAtt);
        }
    }
	void printLocation() {
        playerLoc->print_items();
        playerLoc->print_portals();
    }
	void printAll() {
		printf("World \"%s\":\n", name.data);
		for (auto it = rooms.cbegin(); it != rooms.cend(); ++it) {
			const Room& r = *(*it);
			printf("  %s\n", r.name_cstr());
            if (r.hasItem()) printf("    %s\n", r.itemCstr());
		}
	}
};