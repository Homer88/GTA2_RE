
#ifndef __PATHNODE_H_
#define __PATHNODE_H_


#include <cstdint>

// IDA: PathNode ctor 0x488EB0 (S57::PathNode), size 0x8CA8.
// Layout: +0 Index, +4 S58[300] (116 bytes each = 0x87F0), +0x87F4 buffer_0x4B0/nodePtrs[300] (1200 bytes), +0x8CA4 field_8CA4.
class PathNode {
public:
    uint16_t Index;           // +0x0000
    char field_2;
    char field_3;
    char S58_blob[300 * 116]; // +0x0004, opaque S58[300]
    void* nodePtrs[300];      // +0x87F4, IDA: buffer_0x4B0[4*index]
    int16_t field_8CA4;       // +0x8CA4
    char field_8CA6;
    char field_8CA7;

    PathNode();
    void* GetNode(int index);
    int GetNode(void);
    void* AddRouteInfo(int idx);
    void* AddNode(int a2, int a3, short a4, unsigned char a5);
    int AddNode(void);
    int LoadFurnitureNodes(void);
    int LoadNodeData(void);
    int CreateDefaultConnections(void);
    int LoadPlayerNodeData(void);
    int UpdateGlobalNodeIndex(void);
    int CreatePhoneNodes(void);
    int LoadNetwork(void);
    int GetValue(void);
    void SetNodeFlag();
    void ApplyToSprite();
    void UpdateNodeSprite();
    void CreateSprite();
};


extern PathNode* gPathNode;
#endif // !__PATHNODE_H_