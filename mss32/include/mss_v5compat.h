/*
 * mss_v5compat.h - обёртка поверх mss.h (SDK MSS 6.5c) для API времен retail
 * mss32.dll v5.0r, которым пользуется GTA2.exe.
 *
 * В 6.x часть функций была переименована/изменена по агрументам;
 * эти объявления повторяют СТАРЫЕ v5-сигнатуры. Арность сверена с
 * именами импорта GTA2.exe (_AIL_*@N):
 *   @8  = 2 аргумента, @4 = 1 аргумент, @20 = 5 аргументов.
 *
 * ПРИМЕЧАНИЕ: единственный источник имени в линковке - импорт-либа из
 * retail-шной mss32.dll (mss32\mss32.lib), поэтому даже вызвав эти
 * обёртки, лinker свяжется с нужными экспортами v5.0r.
 */
#ifndef MSS_V5COMPAT_H
#define MSS_V5COMPAT_H

#include "mss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AIL_set_digital_master_volume)
#undef AIL_set_digital_master_volume
#endif
DXDEC void AILCALL AIL_set_digital_master_volume(HDIGDRIVER dig, S32 volume); /* @8 */

#if defined(AIL_set_stream_volume)
#undef AIL_set_stream_volume
#endif
DXDEC void AILCALL AIL_set_stream_volume(HSTREAM stream, S32 volume);          /* @8 */

#if defined(AIL_stream_volume)
#undef AIL_stream_volume
#endif
DXDEC S32  AILCALL AIL_stream_volume(HSTREAM stream);                          /* @4 */

#if defined(AIL_set_sample_volume)
#undef AIL_set_sample_volume
#endif
DXDEC void AILCALL AIL_set_sample_volume(HSAMPLE S, S32 volume);               /* @8 */

#if defined(AIL_set_sample_pan)
#undef AIL_set_sample_pan
#endif
DXDEC void AILCALL AIL_set_sample_pan(HSAMPLE S, S32 pan);                     /* @8 */

/* @20 = 5 аргументов × 4 байта; точный v5-прототип (front/back/... ) не
 * сверен с авторитетным v5-заголовком - пометить при первом вызове. */
#if defined(AIL_set_3D_sample_float_distances)
#undef AIL_set_3D_sample_float_distances
#endif
DXDEC void AILCALL AIL_set_3D_sample_float_distances(HSAMPLE S, F32 a, F32 b, F32 c, F32 d); /* @20 */

#ifdef __cplusplus
}
#endif

#endif /* MSS_V5COMPAT_H */