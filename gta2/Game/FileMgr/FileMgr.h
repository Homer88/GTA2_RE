#ifndef __FILEMGR_H_
#define __FILEMGR_H_

class FileMgr{

    public:

    // 0x00402B20
    int ReadFileContent(void);
    // 0x00402CF0
    int StyleLoader(void);
    // 0x00402DA0
    int FileMgrAppend(void);
    // 0x00402EB0
    int CloseFile(void);
    // 0x00402F60
    int Seek(void);
    // 0x00402FB0
    int Read(void);
    // 0x00403000
    int ReadLine(void);
    // 0x00403160
    int FileOpen(void);
    // 0x0044DBB0
    int SetFilePath(void);
    // 0x0044DC50
    int _______FUN_0044dc50(void);
    // 0x00460CC0
    int DrawKanjiSmall(void);
    // 0x00460D30
    int DrawKanjiBig(void);
    // 0x00460DA0
    int SetKanjiColor(void);
    // 0x00460DE0
    int LoadFontSprites(void);
    // 0x00460E90
    int FreeBuffers(void);
    // 0x00460F10
    int getKanji(void);
    // 0x004CBA00
    int Get_field_10(void);
    // 0x004CBA10
    int GetFiled_14(void);
    // 0x004CBA20
    int Get_field_1C(void);
    // 0x004CBA30
    int Get_field_20(void);
    // 0x004CBA40
    int SetKanjiColorDefault(void);
};

#endif // !__FILEMGR_H_
