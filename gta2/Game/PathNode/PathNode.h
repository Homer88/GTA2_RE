
#ifndef __PATHNODE_H_
#define __PATHNODE_H_


class PathNode{
    public:

    // 0x00488170
    int GetNode(void);
    // 0x00488420
    int AddNode(void);
    // 0x00488450
    int LoadFurnitureNodes(void);
    // 0x004884B0
    int LoadNodeData(void);
    // 0x00488570
    int CreateDefaultConnections(void);
    // 0x00488D10
    int LoadPlayerNodeData(void);
    // 0x00488E50
    int UpdateGlobalNodeIndex(void);
    // 0x00488F70
    int CreatePhoneNodes(void);
    // 0x00489530
    int LoadNetwork(void);
    // 0x004C6E30
    int GetValue(void);


// ==== импорт имён из gm ====
    // 4 функций
    // 0x00488200: PathNode::SetNodeFlag
    void SetNodeFlag();
    // 0x004883A0: PathNode::ApplyToSprite
    void ApplyToSprite();
    // 0x00488E70: PathNode::UpdateNodeSprite
    void UpdateNodeSprite();
    // 0x00488EF0: PathNode::CreateSprite
    void CreateSprite();
};
#endif // !__PATHNODE_H_