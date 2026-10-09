#include "gta2_shim.h"

// Module: other, Class: CameraManager
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x004c4b80: CameraManager::Push
// IDA: CameraManager::Push
// Ghidra: ---
CameraManager * gta2::CameraManager_Push(struct CameraManager *self, int a2)
{
  CameraManager *result; // eax

  *(_DWORD *)self->CameraManager_ = a2;
  result = (CameraManager *)&self->CameraManager_->gap1[3];
  self->CameraManager_ = result;
  return result;
}


// 0x004c4ba0: CameraManager::Pop
// IDA: CameraManager::Pop
// Ghidra: ---
int gta2::CameraManager_Pop(struct CameraManager *self)
{
  CameraManager *v1; // eax

  v1 = (CameraManager *)((char *)self->CameraManager_ - 4);
  self->CameraManager_ = v1;
  return *(_DWORD *)&v1->field;
}


// 0x004c4bc0: CameraManager::IsEmpty
// IDA: CameraManager::IsEmpty
// Ghidra: ---
bool gta2::CameraManager_IsEmpty(struct CameraManager *self)
{
  return self->CameraManager_ == self;
}


// 0x004c4bd0: CameraManager::CameraManager
// IDA: CameraManager::CameraManager
// Ghidra: ---
CameraManager * gta2::CameraManager_CameraManager(struct CameraManager *self)
{
  CameraManager *result; // eax

  result = self;
  self->CameraManager_ = self;
  return result;
}


// 0x004c4da0: CameraManager::CameraManager_desc
// IDA: CameraManager::CameraManager_desc
// Ghidra: ---
CameraManager * gta2::CameraManager_CameraManager_desc(struct CameraManager *self, char a2)
{
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}



