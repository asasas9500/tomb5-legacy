#pragma once
#include "../global/types.h"

long ControlPhase(long nframes, long demo_mode);
long GetChange(ITEM_INFO* item, ANIM_STRUCT* anim);
long CheckGuardOnTrigger();
void InterpolateAngle(short dest, short* src, short* diff, short speed);
void TranslateItem(ITEM_INFO* item, short x, short y, short z);
void InitCutPlayed();
void SetCutPlayed(long num);
void SetCutNotPlayed(long num);
long CheckCutPlayed(long num);
void NeatAndTidyTriggerCutscene(long value, long timer);
long is_object_in_room(long roomnumber, long objnumber);
long check_xray_machine_trigger();
long GetHeight(FLOOR_INFO* floor, long x, long y, long z);
long GetCeiling(FLOOR_INFO* floor, long x, long y, long z);
FLOOR_INFO* GetFloor(long x, long y, long z, short* room_number);
long ExplodeItemNode(ITEM_INFO* item, long Node, long NoXZVel, long bits);
short GetDoor(FLOOR_INFO* floor);
long LOS(GAME_VECTOR* start, GAME_VECTOR* target);
long xLOS(GAME_VECTOR* start, GAME_VECTOR* target);
long zLOS(GAME_VECTOR* start, GAME_VECTOR* target);
long ClipTarget(GAME_VECTOR* start, GAME_VECTOR* target);
long GetTargetOnLOS(GAME_VECTOR* src, GAME_VECTOR* dest, long DrawTarget, long firing);
long ObjectOnLOS2(GAME_VECTOR* start, GAME_VECTOR* target, PHD_VECTOR* Coord, MESH_INFO** StaticMesh);
void TestTriggers(short* data, long heavy, long HeavyFlags);
void _TestTriggers(short* data, long heavy, long HeavyFlags);
void FlipMap(long FlipNumber);
void RemoveRoomFlipItems(ROOM_INFO* r);
void AddRoomFlipItems(ROOM_INFO* r);
void RefreshCamera(short type, short* data);
void KillMoveItems();
void KillMoveEffects();
void UpdateSky();
void AlterFloorHeight(ITEM_INFO* item, long height);
long GetWaterHeight(long x, long y, long z, short room_number);
long TriggerActive(ITEM_INFO* item);
long CheckNoColFloorTriangle(FLOOR_INFO* floor, long x, long z);
long CheckNoColCeilingTriangle(FLOOR_INFO* floor, long x, long z);
void FireCrossBowFromLaserSight(GAME_VECTOR* start, GAME_VECTOR* target);
void TriggerCDTrack(short value, short flags, short type);
void TriggerNormalCDTrack(short value, short flags, short type);
long IsRoomOutside(long x, long y, long z);
void AnimateItem(ITEM_INFO* item);
long RayBoxIntersect(PHD_VECTOR* min, PHD_VECTOR* max, PHD_VECTOR* origin, PHD_VECTOR* dir, PHD_VECTOR* Coord);
long DoRayBox(GAME_VECTOR* start, GAME_VECTOR* target, short* bounds, PHD_3DPOS* ItemPos, PHD_VECTOR* Coord, short item_number);
void ResetGuards();

extern uchar ShatterSounds[18][10];

extern ITEM_INFO* items;
extern ANIM_STRUCT* anims;
extern ROOM_INFO* room;
extern short** meshes;
extern long* bones;
extern long level_items;
extern short number_rooms;

extern short* OutsideRoomOffsets;
extern char* OutsideRoomTable;
extern short IsRoomOutsideNo;

extern MESH_INFO* SmashedMesh[16];
extern short SmashedMeshRoom[16];
extern short SmashedMeshCount;

extern long flipmap[255];
extern long flip_stats[255];
extern long flip_status;
extern long flipeffect;
extern long fliptimer;

extern short* trigger_index;
extern long tiltxoff;
extern long tiltyoff;
extern long OnObject;
extern long height_type;

extern uchar InItemControlLoop;
extern short ItemNewRooms[256][2];
extern short ItemNewRoomNo;

extern ulong FmvSceneTriggered;
extern ulong _CutSceneTriggered1;
extern ulong _CutSceneTriggered2;
extern long SetDebounce;
extern long framecount;
extern long reset_flag;
extern long LaserSightX;
extern long LaserSightY;
extern long LaserSightZ;
extern ushort GlobalCounter;
extern short XSoff1;
extern short XSoff2;
extern short YSoff1;
extern short YSoff2;
extern short ZSoff1;
extern short ZSoff2;
extern short FXType;
extern char PoisonFlag;
extern char LaserSightActive;
extern char LaserSightCol;
extern char TriggerTimer;
extern char GetLaraOnLOS;

extern uchar CurrentAtmosphere;
extern uchar IsAtmospherePlaying;
extern char cd_flags[136];
