#include <iostream>

#include "main.hpp"
#include "default.hpp"

int main() {
	const jstring str_north = "North", str_east = "East",
		str_south = "South", str_west = "West";
	World w = makeDefaultWorld();
	printf("Hello World!\n");
	printf("%s %s %s %s\n",str_north.data,str_east.data,str_south.data,str_west.data);

	w.print();
	std::hash<jstring> jstrhash;
	jstring a = "JefF", b = "jEffrey";
	printf("a: %zu\n", jstrhash(a));
	printf("b: %zu\n", jstrhash(b));	
	jstring jstr;
	while (true) {
		jstr = jstring::getline();
		printf("string: \"%s\"\n", jstr.data);
		printf("hash: %zu\n", jstrhash(jstr));
		if (jstr.length() == 0) break;
	}
}