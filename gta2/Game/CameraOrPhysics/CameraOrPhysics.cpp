#include "CameraOrPhysics.h"
#include <cstdio>
#include <cstdlib>
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

CameraOrPhysics* gCameraOrPhysics;
CameraOrPhysics* gCameraOrPhysics_5E3CC4 = nullptr;

CameraOrPhysics::CameraOrPhysics() {
    // Minimal IDA-compatible zeroing for cameraPosTarget layout. Full IDA ctor
    // (0x4104B0: Constructor(cameraPosTarget,40,80,S132), audio, SetPararm) is
    // still not fully ported; this is a debug/compat safety init.
    for (int i = 0; i < 80; ++i) {
        cameraPosTarget[i].fild = 0;
        cameraPosTarget[i].field_4 = 0;
        cameraPosTarget[i].CameraOrPhysics = 0;
        cameraPosTarget[i].Car = 0;
        cameraPosTarget[i].field_10 = 0;
        cameraPosTarget[i].field_14 = 0;
        cameraPosTarget[i].S32 = 0;
        cameraPosTarget[i].Player = 0;
        cameraPosTarget[i].field_20 = 0;
        cameraPosTarget[i].field_24 = 0;
    }
    Index = 0;
    cameraPosTarget2 = 0;
}

// 0x0041F580 - minimal IDA-faithful subset.
// IDA sets many cameraPosTarget fields, then calls SetWindowDimensions(640,480),
// clears cameraPosTarget[1].S32 low byte, and calls ResetPositions.
// We only port fields required by BA2C0/debug probe path and keep behavior safe.
void CameraOrPhysics::Init() {
    cameraPosTarget[2].field_14 = 0;
    cameraPosTarget[2].S32 = 0;
    // IDA computes scaled fild/target intermediates via bitShiftLeft1(-1) and
    // SetTargetPosition/UpdateCurrentState/ResetPositions; not fully ported.
    cameraPosTarget[2].Car = 0;
    cameraPosTarget[2].field_10 = 0;
    cameraPosTarget[1].field_10 = 0;
    cameraPosTarget[1].field_4 = 0;
    cameraPosTarget[1].CameraOrPhysics = 0;
    cameraPosTarget[1].S32 = 0;
    SetWindowDimensions(640u, 480);
}

int CameraOrPhysics::GetBA2C0A5Value(bool& ok) const {
    ok = false;
    // IDA BA2C0: v3=&gCameraOrPhysics_5E3CC4->cameraPosTarget[4].field_4 (+0xA4)
    // a5=v3->BaseCar[0].field; BaseCar[0].field is first int of that struct/value.
    // RE does not have verified BaseCar object layout at this pointer in normal flow;
    // use read-only SEH-guarded read of the value at +0xA4.
    int v = 0;
    __try {
        v = *(const int*)((const char*)this + 0xA4);
        ok = true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        ok = false;
        v = 0;
    }
    return v;
}

    // 0x0040FE50


int CameraOrPhysics::SetPararm(void){
        // IDA 0x40FE50: this->Index = 0
        Index = 0;
        // Debug-only: report RE layout vs expected IDA layout.
        const char* dbg = std::getenv("GTA2_TEXT_GBH");
        if (dbg && dbg[0] == '1') {
            static bool once = false;
            if (!once) {
                once = true;
                std::FILE* f = std::fopen("gta2_text_gbh_reason.log", "a");
                if (f) {
                    std::fprintf(f,
                        "cam-layout-re this=%p sizeof(CameraOrPhysics)=%u expected_size=0xC88 expected_index=0xC80 expected_cam2=0xC84 expected_a8=0xA8\n",
                        (void*)this, (unsigned)sizeof(CameraOrPhysics));
                    std::fclose(f);
                }
            }
        }
        return 0;
    }

// Debug/compat subset of IDA SetWindowDimensions @ 0x41EB70.
// Computes cameraPosTarget[4].field_4 (+0xA8) as in IDA:
//   decoderfloat_0040CE00(&v9, windowWidth); // v9 = windowWidth<<14
//   CarModel::ApplyMatrix(v7,&WindowHeight,&WindowWidthTmp=640); // v7 = v9/640
//   cameraPosTarget[4].field_4 = *v8 (=v7)
void CameraOrPhysics::SetWindowDimensions(unsigned int windowWidth, int /*windowHeight*/) {
    // Preserve minimal fields IDA writes; many are still stubbed/untyped in RE.
    cameraPosTarget[2].field_14 = windowWidth;
    std::uint32_t v9 = windowWidth << 14;
    std::uint32_t v7 = (640u == 0u) ? 0u : (v9 / 640u);
    cameraPosTarget[4].field_4 = v7;
    const char* dbg = std::getenv("GTA2_TEXT_GBH");
    if (dbg && dbg[0] == '1') {
        static bool once = false;
        if (!once) {
            once = true;
            std::FILE* f = std::fopen("gta2_text_gbh_reason.log", "a");
            if (f) {
                std::fprintf(f, "cam-setwnd this=%p winW=%u cam4f4=%08X\n", (void*)this, windowWidth, (unsigned)cameraPosTarget[4].field_4);
                std::fclose(f);
            }
        }
    }
}


    // 0x0040FE60


int CameraOrPhysics::DMAudio(void){
        return 0;
    }


    // 0x0041E010


int CameraOrPhysics::SetFollowTarget(void){
        return 0;
    }


    // 0x0041E410


int CameraOrPhysics::UpdateCurrentState(void){
        return 0;
    }


    // 0x0041EA10


int CameraOrPhysics::ProcessActions(void){
        return 0;
    }


    // 0x0041EAC0


int CameraOrPhysics::thunk_FUN_0041e7a0(void){
        return 0;
    }


    // 0x0041F410


int CameraOrPhysics::FocusOnObject(void){
        return 0;
    }


    // 0x00433E90


int CameraOrPhysics::IsActive(void){
        return 0;
    }


    // 0x00475B60


int CameraOrPhysics::ResetAccuracy(void){
        return 0;
    }
