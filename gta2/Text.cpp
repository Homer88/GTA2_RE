#include "Text.h"
#include "Global.h"

Text gText;

int compare_strings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void* Text::Bsearch(const void* pKey) {
    char ** resultat=(char**)bsearch(pKey, (const char*)this->Base, this->NumberOfElements, 12, compare_strings);
    if (resultat) {
        return resultat;
    }
    else { return " "; }
}