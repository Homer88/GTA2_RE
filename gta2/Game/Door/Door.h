
#ifndef ___DOOR_H_
#define ___DOOR_H_

class Door {
public:
	bool Status;
	Door();
	~Door();
    void Update(void);
};

extern Door* gDoor;

#endif