#ifndef ___GLOBAL__H_
#define ___GLOBAL__H_
//  файлы подключаемые  (порядок: фундамент -> спрайты/Map -> Game-сущности -> остальное)

#include "../Engine/bink/bink.h"
#include "../Engine/Font/Font.h"
#include "../Engine/FileMgr/FileMgr.h"
#include "../Engine/Input/Keybrd.h"
#include "../Engine/System/System.h"
#include "../Engine/Text/Text.h"
#include "../Engine/TextureManager/TextureManager.h"
#include "../Engine/Registry/Registry.h"
#include "../Engine/ultil/WinApi.h"
#include "../Engine/AudioManager/AudioManager.h"
#include "../Engine/DMAudio/DMAudio.h"
#include "../Engine/AudioSourceParams/AudioSourceParams.h"
#include "../Engine/Sprite/Sprite.h"
#include "../Engine/SpriteInfo/SpriteInfo.h"
#include "../Engine/SpriteS1/SpriteS1.h"
#include "../Engine/SpriteS2/SpriteS2.h"
#include "../Engine/SpriteS3/SpriteS3.h"
#include "../Engine/SpriteS4/SpriteS4.h"
#include "../Engine/SpriteSx/SpriteSx.h"
#include "../Engine/Object/Object.h"
#include "../Engine/GameObject/GameObject.h"
#include "../Engine/EventHandler/EventHandler.h"
#include "../Engine/General/General.h"
#include "../Engine/Math/Math.h"
#include "../Engine/Matrix3D/Matrix3D.h"
#include "../Engine/Rect2D/Rect2D.h"
#include "../Engine/Map/Map.h"
#include "../Engine/MapGm/MapGm.h"
#include "../Engine/MapRelatedStruct/MapRelatedStruct.h"
#include "../Engine/TileNode/TileNode.h"
#include "../Engine/Random/Random.h"
#include "../Engine/Timing/Timing.h"
#include "../Engine/ColorRGBA/ColorRGBA.h"
#include "../Engine/Renderer/Renderer.h"
#include "../Engine/Display/Display.h"
#include "../Engine/Animation/Animation.h"
#include "../Engine/App/App.h"
#include "../Engine/LoadScreen/LoadScreen.h"
#include "../Engine/Network/Network.h"
#include "../Engine/Replay/Replay.h"
#include "../Engine/SoundCard/SoundCard.h"
#include "../Engine/SoundInfo/SoundInfo.h"
#include "../Engine/ScriptCommand/ScriptCommand.h"
#include "../Engine/ScriptThread/ScriptThread.h"
#include "../Engine/ScriptVar/ScriptVar.h"
#include "../Engine/Controller/Controller.h"
#include "../Engine/IController/IController.h"
#include "../Engine/Input2/Input2.h"
#include "../Engine/KeyBinding/KeyBinding.h"
#include "../Engine/Crt/Crt.h"
#include "../Engine/Debug/DebugLogFile.h"
#include "../Engine/Keybord/Keybord.h"
#include "../Engine/Movie/Movie.h"
#include "../Engine/Res/TGA.h"
#include "../Engine/Sound/Sound.h"
#include "../Engine/match/match.h"

#include "EngineStruct/EngineStruct.h"
#include "AIController/AIController.h"
#include "Ambulance/Ambulance.h"
#include "AmbulanceInfo/AmbulanceInfo.h"
#include "ArrowTrace/ArrowTrace.h"
#include "BrakeInfo/BrakeInfo.h"
#include "Camera/Camera.h"
#include "CameraOrPhysics/CameraOrPhysics.h"
#include "Car/Car.h"
#include "CarDoor/CarDoor.h"
#include "CarEngines/CarEngines.h"
#include "CarGenerator/CarGenerator.h"
#include "CarPair/CarPair.h"
#include "CarSystemManager/CarSystemManager.h"
#include "CarsPrefabs/CarsPrefabs.h"
#include "Character/Character.h"
#include "Checkpoint/Checkpoint.h"
#include "Collide/Collide.h"
#include "CollisionBox/CollisionBox.h"
#include "CollisionResult/CollisionResult.h"
#include "CrashData/CrashData.h"
#include "DamageInfo/DamageInfo.h"
#include "DebrisInfo/DebrisInfo.h"
#include "DecalInfo/DecalInfo.h"
#include "Door/Door.h"
#include "FireInfo/FireInfo.h"
#include "GUI/GUI.h"
#include "Game/Game.h"
#include "Gang/Gang.h"
#include "Gangs/Gangs.h"
#include "GangInfo/GangInfo.h"
#include "GarageInfo/GarageInfo.h"
#include "GlassInfo/GlassInfo.h"
#include "Hud/Hud.h"
#include "HudArrow/HudArrow.h"
#include "HudBrief/HudBrief.h"
#include "HudElement/HudElement.h"
#include "HudMessage/HudMessage.h"
#include "ImpactInfo/ImpactInfo.h"
#include "LinkedList/LinkedList.h"
#include "MAudio/MAudio.h"
#include "Medical/Medical.h"
#include "Menu/Menu.h"
#include "MenuEntry/MenuEntry.h"
#include "MenuItemConfig/MenuItemConfig.h"
#include "Mike/Mike.h"
#include "MissionData/MissionData.h"
#include "MissionManager/MissionManager.h"
#include "ModelIndex/ModelIndex.h"
#include "PacketInfo/PacketInfo.h"
#include "Particle/Particle.h"
#include "Particle1/Particle1.h"
#include "Particle2/Particle2.h"
#include "Particles/Particles.h"
#include "Passenger/Passenger.h"
#include "PathNode/PathNode.h"
#include "PickupInfo/PickupInfo.h"
#include "Police/Police.h"
#include "PoliceRoadblock/PoliceRoadblock.h"
#include "PublicTransport/PublicTransport.h"
#include "RouteInfo/RouteInfo.h"
#include "SaveSlotAnimatedValue/SaveSlotAnimatedValue.h"
#include "SkidmarkInfo/SkidmarkInfo.h"
#include "SpawnPoint/SpawnPoint.h"
#include "StreamWriter/StreamWriter.h"
#include "Tango/Tango.h"
#include "TangoMain/TangoMain.h"
#include "Taxi/Taxi.h"
#include "Teleporter/Teleporter.h"
#include "TextLabel/TextLabel.h"
#include "TextLabelPool/TextLabelPool.h"
#include "TimeCycle/TimeCycle.h"
#include "TrafficCar/TrafficCar.h"
#include "TrafficLigthStruct/TrafficLigthStruct.h"
#include "TransmissionInfo/TransmissionInfo.h"
#include "Turrel/Turrel.h"
#include "VehiclePool/VehiclePool.h"
#include "VertexBuffer/VertexBuffer.h"
#include "Viewport/Viewport.h"
#include "Weapon/Weapon.h"
#include "WeaponInfo/WeaponInfo.h"
#include "Weapons/Weapons.h"
#include "PlayerData/PlayerData.h"
#include "PlayerSlotSlave/PlayerSlotSlave.h"
#include "PowerUp/PowerUp.h"
#include "Ped/Ped.h"
#include "PedManager/PedManager.h"
#include "PedModel/PedModel.h"
#include "PedStats/PedStats.h"
#include "Point2D/Point2D.h"
#include "Sphere3D/Sphere3D.h"

extern Menu           *gMenu;
extern Registry       *gRegistry;
extern TextureManager *gTextureManager;
extern Text           *gText;
extern WinApi         *gWinApi;
extern PlayerData     *gPlayerData;
extern MapGm          *gMapGm;
extern Bink           *gBink;
extern Font           *gFont;
extern FileMgr        *gFileMgr;
extern Keyboard		  *gKeyboard;
extern MissionManager *gMissionManager;
extern MapRelatedStruct* gMapRelatedStruct;
extern EngineStruct      *gEngineStruct;
extern Gangs  *gGangs;
extern PowerUp  *gPowerUp;
extern Character *gCharacter;
extern int gCheatIs;
extern bool gSkipAudio;
extern unsigned char gGamma;
extern char TextArrayChar;
extern int gBinkBufferOffset;
extern BINKSUMMARY* gBinkSummary;
extern char* gKeyBuffer;

// переменнные 
extern bool gDoInfiteLives;
extern bool gGiveMoney20k ;
extern bool gGiveMoney99K ;
extern bool gFireGun ;
extern bool gPointMultiPlayerX10 ;
extern bool gJailFreeCard ;
extern bool gInvisibilit ;
extern bool gDoubleDamag ;
extern bool gDo_Blood ;
extern bool gBunt ;
extern bool gVoltfest ;
extern bool gMademan ;
extern bool gLasvegas ;
extern bool gNEKKID ;
extern bool gDoFreeShopping ;
extern bool gHeats99 ;
extern bool gKeepWeaponsAfterDeath ;
extern bool gGetAllWeapons ;
extern bool gDoInvulnerable ;
extern bool gDANISGOD ;
extern bool gFYOHZZ0 ;
extern bool gElectroGun ;
extern bool gSEGARULZ ;
extern bool gDAVEMOON ;
extern bool gExplodingOn ;
extern bool gFLAMEON ;
extern bool gUKGAMER ;
extern bool gSUPZZZ0 ;
extern bool gTUMYFROG ;
extern bool gSCHURULZ ;
extern bool gHUNSRUS ;
extern bool gFISHFLAP ;
extern bool gJailKey ;



//список 
extern enum WeaponType;
extern enum WantedLevelStat;
extern enum  PedState;
extern enum  GANG;
#endif //___GLOBAL__H_
