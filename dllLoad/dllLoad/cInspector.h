#ifndef __CINSPECTOR_H__
#define __CINSPECTOR_H__

void StartInspector(void);
void StopInspector(void);
void InspectorRequestRefresh(void);

const char* GetGlobalStructName(unsigned long addr);

#endif // !__CINSPECTOR_H__