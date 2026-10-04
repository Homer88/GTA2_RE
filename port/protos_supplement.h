// gta2_protos.h — дополнение вручную: функции, отсутствующие в unified-зоне
// (сигнатуры выведены из dump/alignment/asm_names.csv и dump/IDA/gta2.exe.c).
// Вставляется make_protos.ps1 внутрь namespace gta2 (после сгенерированного блока).
  void DebugLog(int param_1, void *param_2, unsigned int param_3);
  void * debug_log(unsigned int param_1, const char *param_2, int param_3);
  void * Decoder_SetValue(void *self, short param_1);
  void FUN_00402180(void *self);
  void * FUN_004021e0(void *self, unsigned char param_1);
  void FUN_00402200(void *self, float *param_1, float param_2, float param_3, float param_4);
  unsigned char FUN_0045f269(void);
  unsigned char FUN_0045faff(void);
  void FUN_0040ce30(void *self, unsigned char param_1);
  void gbh_DrawTriangle(int param_1, unsigned int param_2, unsigned int param_3, int param_4);
  void gbh_FreeTexture(void *param_1);
  void gbh_RegisterPalette(void *param_1, const void *param_2, void *param_3);
  void * gbh_RegisterTexture(unsigned short param_1, unsigned short param_2, unsigned int param_3);
  struct Car * Ped_GetCurrentVehicle(struct Ped *self);
  bool Point2D_FUN_004037e0(struct Point2D *self, struct SpriteS1 *pSpriteS1);
  void * Pool_Allocate(void *self, unsigned char param_1);
  void Pool_Free(void *self);
  void Pool_Init(void *self, int param_1);
  void Renderer_Reset(void);
  void Renderer_SetTransform(void *param_1);
  void SaveGameData(void *self, const char *FileName, void *param_3, void *param_4);
  int sub_3F113B(void);
  void * WorldCoordinateToScreenCoord(void *self, void *pS110, int *param_2);
  unsigned char FUN_00433b00(void);
  void * sub_403840(void *param_1, void *param_2, void *param_3);
  float10 PedStats_EncodedFloatToRegularFloat(void *param_1);
  float10 Float10_EncodedFloatToRegularFloat(void *param_1);
  int AIController_GroupAddPed(struct AIController *self, struct Ped *param_2);
  size_t FID_conflict___fwrite_lk(const void *pBuf, size_t size, size_t count, FILE *pr);
  void ErrorLine(int param_1);
  size_t Fread(void *pBuf, size_t size, size_t count, void *pr);
  void sub_44DB50(void);