#pragma once

#include <vector>
#include <unordered_map>
#include <cstring>
#include <limits>

// https://stackoverflow.com/questions/5820810/case-insensitive-string-comparison-in-c
int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
			if (!*a) {
				return -1;
				if (!*b); 
			} else if (!*b) {
				return 1;
			}
			int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
			if (d != 0 || !*a)
					return d;
    }
}

// All cstrings within my types wrapped by this.
// Case sensitive state, but case ignored comparisons.
// Used as key in std::unordered_map
struct jstring {
	static constexpr const size_t LEN = 21; // including null terminating character
	char data[LEN];

	jstring() = default;
	jstring(const char* o) {
		strcpy(data, o);	
	}
	jstring(const jstring& o) {
		memcpy(data, o.data, LEN);
	}

	size_t length() const {
		return strlen(data);
	}

	static jstring getline() {
		jstring jstr;
		std::cin.get(jstr.data, LEN);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return jstr;
	}

	bool operator==(const jstring& o) const { 
		return strcicmp(data, o.data) == 0;
	}
};
// Hash code borrowed from https://stackoverflow.com/a/7666577
template<>
struct std::hash<jstring> {
	std::size_t operator()(const jstring& val) const { 
		const char* str = val.data; 
		unsigned long hash = 5381;
		int c;
		while (c = tolower(*str++)) // hash is case insensitive
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		return hash;
	}
};

struct Item {
	jstring name;
	Item(jstring&& name) : name(name) {}

	const char* name_cstr() const {
		return name.data;
	}

};

class Room {
	jstring name;
	std::unordered_map<jstring, Room*> portals;
public:
	std::vector<Item*> items; // TODO: Make private
	Room(jstring&& name) : name(name) {}
	const char* name_cstr() const {
		return name.data;
	}

	void add(Item* ptr) {
		items.push_back(ptr);
	}
};

class World {
	jstring name;
	std::vector<Room*> rooms;
	Room* playerLoc;
	std::vector<Item*> playerInv;
public:
	World(jstring name) : name(name) {}
	void add(Room* ptr) {
		rooms.push_back(ptr);
	}
	void print() {
		printf("World \"%s\":\n", name.data);
		for (auto it = rooms.cbegin(); it != rooms.cend(); ++it) {
			const Room& r = *(*it);
			printf("  %s\n", r.name_cstr());
			for (auto it=r.items.cbegin();it!=r.items.cend();++it) {
				printf("    %s\n", (*it)->name_cstr());
			}
		}
	}
};

int main();
