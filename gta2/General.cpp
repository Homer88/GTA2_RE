#include "General.h"

General gGeneral;

General::General(){
	this->Cycle = 0;
	this->b = 0;

}

General::~General(){

}


int General::GetCycle(){
   return this->Cycle;
}