#pragma once

// Defines all methods and jstring struct useful for case-insensitive behaviour.

// Code borrowed in part from https://stackoverflow.com/questions/5820810/case-insensitive-string-comparison-in-c
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
	const char* data; 
	jstring(const char* data) : data(data) {} 
	
	bool operator==(const jstring& o) const { 
		return strcmp(data, o.data) == 0;
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
