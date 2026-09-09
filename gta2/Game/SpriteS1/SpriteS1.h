#ifndef __SPRITES1_H_
#define __SPRITES1_H_

class SpriteS1{

    public:

    // 0x00401AD0
    int SetToNewVal(void);
    // 0x0040F7B0
    int SetSpriteType(void);
    // 0x0040FE80
    int is_object(void);
    // 0x0040FEA0
    int Sub_UpdateCars(void);
    // 0x0040FEB0
    int GetObject(void);
    // 0x0040FEC0
    int GetEventHandler(void);
    // 0x0040FEE0 void __thiscall
    void SetTypeAndSprite(int arg0);
    // 0x00416B40
    int getSpriteType(void);
    // 0x0041C1F0
    int GetColorCar(void);
    // 0x0041CFF0
    int FindFirstElement(void);
    // 0x00420700
    int SetTo2(void);
    // 0x004207B0
    int SetPositionFromString(void);
    // 0x00421000
    int RemoveFirstElement(void);
    // 0x00421030
    int SpriteS1_Des(void);
    // 0x00447E20
    int SetPositionXY(void);
    // 0x00482A30
    int SetS63(void);
    // 0x00482A40
    int SpriteS1SetCollision(void);
    // 0x0048A8D0
    int IsNotEmpty(void);
    // 0x0048E060
    int SpriteS1EmitParticles(void);
    // 0x0048E480
    int SpawnParticleA(void);
    // 0x0048E5F0
    int SpawnParticleB(void);
    // 0x0048E750
    int SpawnParticleC(void);
    // 0x004B9AA0
    int SpriteS1SetDrawStyle(void);
    // 0x004B9CD0
    int SpriteS1Init(void);
    // 0x004B9F30
    int SpriteS1SetGlobalValue(void);
    // 0x004B9F40
    int GetTileIdFromPos(void);
    // 0x004BA230
    int get_global_sprite_id(void);
    // 0x004BAA90
    int IsOnSpecialTile(void);
    // 0x004BABB0
    int SpriteS1IsObjectType(void);
    // 0x004BABE0
    int SpriteS1SetPaletteRemap(void);
    // 0x004BAC10
    int SpriteS1GetVehicleFlag(void);
    // 0x004BC970
    int SpriteS1Dtor(void);
    // 0x004BCAC0
    int CheckCollision(void);
    // 0x004BCB90
    int AttachS3(void);
    // 0x004BCBD0
    int AllocateChildSprite(void);
    // 0x004BDFE0
    int UpdateSpawn(void);
};

#endif // !__SPRITES1_H_
