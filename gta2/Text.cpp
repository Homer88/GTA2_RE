#include "Text.h"
#include "Global.h"

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

Text::Text() {
    gRegistry.GetLanguage("language", gLanguage, 256);
    if (gLanguage[0] == 'e' ||
        gLanguage[0] == 'f' ||
        gLanguage[0] == 'g' ||
        gLanguage[0] == 'i' ||
        gLanguage[0] == 's' ||
        gLanguage[0] == 'j' ||
        gLanguage[0] == 'r')
        this->Language = gLanguage[0];
    else
        this->Language = 'e';
}

Text::~Text() {

}