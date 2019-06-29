#include "utility.h"


/*
	*
	*  Compares Two C-Strings.
	*
*/
bool utility::isMatch(const char *s1, const char *s2) {
	
	if(s1 && s2) {

		size_t indx = 0;

		while(s1[indx] == s2[indx]) {

			if(s1[indx] == '\0' && s2[indx] == '\0') return true;

			indx++;
		}
	}		
	return false;
};