#include "Player.h"
#include "../Gangs/Gangs.h"
#include "../Weapon/Weapon.h"
#include "../PowerUp/PowerUp.h"
#include "../Ped/Ped.h"
#include "../PlayerData/PlayerData.h"
#include "../PlayerSlotSlave/PlayerSlotSlave.h"
#include "../Character/Character.h"

bool gDoInfiteLives = false;
bool gElectroGun = false;
bool gFireGun = false;
bool gPointMultiPlayerX10 = false;
bool gJailFreeCard = false;
bool gInvisibilit = false;
bool gDoubleDamag = false;
bool gJailKey = false;
extern bool gGiveMoney20k;
extern bool gGiveMoney99k;
extern bool gMademan;
extern Gangs* gGangs;
extern bool gBunt;
extern bool gHeats99;
extern Character* gCharacter;



Player::Player(){
    this->Damage = 900;
}


Player::~Player() {

}



byte Player::GivePowerUp(int PowerType) {

    switch (PowerType) {
    case POWERUP_TYPE_MULTIPLIER:
        if (this->MultiPlayer->GetValue() != 99) {
            this->SetMultiPlayer(1);
            return 1;
        }
        break;
    case POWERUP_TYPE_LIFE:
        if (this->Lives->GetValue() != 99) {
            this->AddLives(1);
            return 1;
        }
        break;
    case POWERUP_TYPE_HEALTH:
        if (this->MainPed->GetHealthPlayer() < 100) {
            this->MainPed->SetHealthFullPlayer();
            return 1;
        }
        break;
    case POWERUP_TYPE_ARMOR:
             if (this->Armo != 10) {
                this->Armo = 10;
        return 1;
        }
        break;

    case POWERUP_TYPE_COP_BRIBE:
        if (this->MainPed->GetPoliceStar() != LEVEL_WANTED_0)
            this->MainPed->SetPoliceNoStar();
    case POWERUP_TYPE_DOUBLE_DAMAGE:
            if (this->Damage != 1800) {
                this->Damage = 1800;
                return 1;
            }
            break;
    case POWERUP_TYPE_FAST_RELOAD:
        if (this->Reload != 1800) {
            this->Reload = 1800;
            return 1;
        }
        break;
    case POWERUP_TYPE_ELECTROFINGERS:
        if (this->Electrofinger != 2100) {
            this->Electrofinger = 2100;
            return 1;
        }
        break;
    case POWERUP_TYPE_RESPECT:
        if ((this->Respect != NULL) && (this->Respect->GetRespect(this->IDs) != 100)) {
            this->Respect->IncreaseRespect(this->IDs, 20);
            return 1;
        }
    case POWERUP_TYPE_INVISIBILITY:
        if (this->Invisibility != 1800) {
            this->Invisibility = 1800;
            this->MainPed->EnableInvisibility();
            return 1;
        }
    case POWERUP_TYPE_INSTANT_GANG:
        //if (this->MainPed->GetObject() != NULL) {
            //this->MainPed->CreateGroup(4, 0);
            return 1;
        //}
        break;
    default:
        break;
	}
    return 0;
}

void Player::SetMultiPlayer(byte Multi) {
    this->MultiPlayer->SetValue( Multi);
}

int  Player::AddLives(int Lives) {
    if ((gDoInfiteLives) && (Lives < 1)) {
        return Lives;
    }
    this->Lives->SetMultiPlayer(Lives);
    return Lives;
}
void Player::StartGame() {
        
    if (gGiveMoney20k != false) {
        this->Money->SetValue(200000);
    }
    if (gGiveMoney99k != false) {
        this->Money->SetValue(999999);
    }
    if (gElectroGun != false) {
        this->WeaponArray[ElectorGun].GiveWeaponInfiniti();

    }
    if (gFireGun != false) {
        this->WeaponArray[FireGun].GiveWeaponInfiniti();

    }
    if (gMademan != false) {
        Gang *pGang = gGangs->GetFirstUsedGang();
        while (pGang != NULL) {
            pGang->SetRespect(this->IDs, 100);
            pGang = gGangs->GetNextGang();

        }
    }
    if (gHeats99 != false) {
        this->Lives->SetValue(99);
    }
    if (gPointMultiPlayerX10 != false) {
        this->MultiPlayer->SetMultiPlayer(9);
    }
    if (gBunt) {
        gCharacter->Bunt = true;
    }
    if (gJailFreeCard != false) {
        this->GivePowerUp(POWERUP_TYPE_GET_OUTTA_JAIL_FREE_CARD);
    }
    if (gInvisibilit != false) {
        this->GivePowerUp(POWERUP_TYPE_INVISIBILITY);
    }
    if (gDoubleDamag != false) {
        this->GivePowerUp(POWERUP_TYPE_DOUBLE_DAMAGE);
    }
    if (gJailKey != false) {
        this->GivePowerUp(POWERUP_TYPE_GET_OUTTA_JAIL_FREE_CARD);
        this->SelectWeapon(PISTOL, 50);
        gGangs->GetFirstUsedGang();
    }
}
byte Player::SelectWeapon(int TypeWeapon, int Ammo) {

    return 0;
}