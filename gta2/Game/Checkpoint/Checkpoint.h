#ifndef __CHECKPOINT_H_
#define __CHECKPOINT_H_

class Checkpoint{

    public:

    // 0x00446740
    int FindFirstObject(void);
    // 0x00446860
    int Initialise(void);
    // 0x00446CB0
    int ProcessCellRange(void);
    // 0x00446D00
    int ProcessRange(void);
    // 0x00446D60
    int CheckpointProcessObjectsInCells(void);
    // 0x00446DE0
    int CheckpointCheckPlayerCollision(void);
    // 0x00446F30
    int CheckSpriteCollision(void);
    // 0x00447390
    int ProcessScreenRange(void);
    // 0x00447850
    int CheckpointRemoveObjectFromCell(void);
    // 0x004479D0
    int CheckpointAddObjectToCell(void);
    // 0x00447A60
    int CheckpointAddObjectToCellRange(void);
    // 0x00447BA0
    int AddObject(void);
    // 0x00447BD0
    int RemoveObject(void);
    // 0x00485290
    int ObjectSpawnObjectWithData(void);
};

#endif // !__CHECKPOINT_H_
