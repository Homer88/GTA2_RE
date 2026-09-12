
#ifndef __TILENODE_H_
#define __TILENODE_H_


class TileNode{
    public:

    // 0x0040CE90 ushort __fastcall
    // (new_class) старый: Player::GetJunctionId -> GetTileIndex
    unsigned short GetTileIndex(void *arg0);

};
#endif // !__TILENODE_H_
