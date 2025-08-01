#include "../tomb5/pch.h"
#include "control.h"
#include "pickup.h"
#include "../specific/input.h"
#include "newinv2.h"
#include "lara_states.h"
#include "camera.h"
#include "gameflow.h"
#include "items.h"
#include "effect2.h"
#include "box.h"
#include "laramisc.h"
#include "spotcam.h"
#include "tomb4fx.h"
#include "../specific/3dmath.h"
#include "sound.h"
#include "hair.h"
#include "bat.h"
#include "spider.h"
#include "rat.h"
#include "objects.h"
#include "../specific/function_stubs.h"
#include "sphere.h"
#include "debris.h"
#include "larafire.h"
#include "switch.h"
#include "draw.h"
#include "joby.h"
#include "../specific/LoadSave.h"
#include "subsuit.h"
#include "traps.h"
#include "lot.h"
#include "effects.h"
#include "twogun.h"
#include "text.h"
#include "../specific/dxsound.h"
#include "lara1gun.h"
#include "../specific/audio.h"
#include "rope.h"
#include "../specific/file.h"
#include "../specific/dxshell.h"
#include "health.h"
#include "lara.h"
#include "savegame.h"
#include "deltapak.h"
#include "../specific/gamemain.h"

uchar ShatterSounds[18][10] =
{
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_WOOD, SFX_SMASH_WOOD, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_METAL, SFX_SMASH_METAL, SFX_SMASH_METAL, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_METAL, SFX_SMASH_METAL, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_METAL, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_METAL, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS},
{SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS}
};

ITEM_INFO* items;
ANIM_STRUCT* anims;
ROOM_INFO* room;
short** meshes;
long* bones;
long level_items;
short number_rooms;

short* OutsideRoomOffsets;
char* OutsideRoomTable;
short IsRoomOutsideNo;

MESH_INFO* SmashedMesh[16];
short SmashedMeshRoom[16];
short SmashedMeshCount = 0;

long flipmap[255];
long flip_stats[255];
long flip_status;
long flipeffect = -1;
long fliptimer = 0;

short* trigger_index;
long tiltxoff;
long tiltyoff;
long OnObject;
long height_type;

uchar InItemControlLoop = 0;
short ItemNewRooms[256][2];
short ItemNewRoomNo = 0;

ulong FmvSceneTriggered;
ulong _CutSceneTriggered1;
ulong _CutSceneTriggered2;
long SetDebounce;
long framecount = 0;
long reset_flag = 0;
long LaserSightX;
long LaserSightY;
long LaserSightZ;
ushort GlobalCounter = 0;
short XSoff1;
short XSoff2;
short YSoff1;
short YSoff2;
short ZSoff1;
short ZSoff2;
short FXType;
char PoisonFlag;
char LaserSightActive;
char LaserSightCol;
char TriggerTimer = 0;
char GetLaraOnLOS = 0;

uchar CurrentAtmosphere;
uchar IsAtmospherePlaying;
char cd_flags[136];

static PHD_VECTOR ClosestCoord;
static long ClosestItem;
static long ClosestDist;

static long number_los_rooms = 0;
static short los_rooms[20];

static short cdtrack = -1;
static char richcutfrigflag = 0;
static char globoncuttrig;

long ControlPhase(long nframes, long demo_mode)
{
	ITEM_INFO* item;
	FX_INFO* fx;
	MESH_INFO* mesh;
	FLOOR_INFO* floor;
	short item_num, nex, fx_num;

	RegeneratePickups();

	if (nframes > 10)
		nframes = 10;

	if (bTrackCamInit)
		bUseSpotCam = 0;

	SetDebounce = 1;

	for (framecount += nframes; framecount > 0; framecount -= 2)
	{
		GlobalCounter++;
		UpdateSky();

		if (cdtrack > 0)
			S_CDLoop();

		if (S_UpdateInput() == IN_ALL)
			return 0;

		if (bDisableLaraControl)
		{
			if (gfCurrentLevel != LVL5_TITLE)
				dbinput = 0;

			input &= IN_LOOK;
		}

		if (cutseq_trig)
			input = 0;

		SetDebounce = 0;

		if (gfCurrentLevel != LVL5_TITLE)
		{
			if ((dbinput & IN_OPTION || GLOBAL_enterinventory != NO_ITEM) && !cutseq_trig && lara_item->hit_points > 0)
			{
				S_SoundStopAllSamples();

				if (S_CallInventory2())
					return 2;
			}
		}

		if (keymap[DIK_I])
			dels_give_lara_items_cheat();

		if (gfLevelComplete)
			return 3;

		if (reset_flag || lara.death_count > 300 || (lara.death_count > 60 && input))
		{
			if (Gameflow->DemoDisc && reset_flag)
			{
				reset_flag = 0;
				return 4;
			}
			else
			{
				reset_flag = 0;
				return 1;
			}
		}

		if (demo_mode && input == IN_ALL)
			input = IN_NONE;

		if (!lara.death_count && !FadeScreenHeight)
		{
			if (input & IN_SAVE)
				S_LoadSave(IN_SAVE, 0);
			else if (input & IN_LOAD)
			{
				if (S_LoadSave(IN_LOAD, 0) >= 0)
					return 2;
			}

			if (input & IN_PAUSE && gfGameMode == 0)
			{
				if (S_PauseMenu() == 8)
					return 1;
			}
		}

		if (MainThread.ended)
			return 4;

		if (input & IN_LOOK && !SniperCamActive && !bUseSpotCam && !bTrackCamInit &&
			((lara_item->current_anim_state == AS_STOP && lara_item->anim_number == ANIM_BREATH) ||
			 (lara.IsDucked && !(input & IN_DUCK) && lara_item->anim_number == ANIM_DUCKBREATHE && lara_item->goal_anim_state == AS_DUCK)))
		{
			if (!BinocularRange)
			{
				switch (lara.gun_type)
				{
				case WEAPON_REVOLVER:

					if (lara.sixshooter_type_carried & W_LASERSIGHT && lara.gun_status == LG_READY)
					{
						BinocularRange = 128;
						BinocularOldCamera = camera.old_type;
						LaserSight = 1;
						lara.Busy = 1;
					}

					break;

				case WEAPON_CROSSBOW:

					if (lara.crossbow_type_carried & W_LASERSIGHT && lara.gun_status == LG_READY)
					{
						BinocularRange = 128;
						BinocularOldCamera = camera.old_type;
						LaserSight = 1;
						lara.Busy = 1;
					}

					break;

				case WEAPON_HK:

					if (lara.gun_status == LG_READY)
					{
						BinocularRange = 128;
						BinocularOldCamera = camera.old_type;
						LaserSight = 1;
						lara.Busy = 1;
					}

					break;
				}
			}
		}
		else if (BinocularRange)
		{
			if (LaserSight)
			{
				BinocularRange = 0;
				LaserSight = 0;
				AlterFOV(14560);
				lara_item->mesh_bits = -1;
				lara.Busy = 0;
				camera.type = BinocularOldCamera;
				lara.torso_x_rot = 0;
				lara.torso_y_rot = 0;
				lara.head_x_rot = 0;
				lara.head_y_rot = 0;
				camera.bounce = 0;
				BinocularOn = -8;
				input &= ~IN_LOOK;
			}
			else
				input |= IN_LOOK;
		}
		else if (SniperCamActive || bUseSpotCam || bTrackCamInit)
			input &= ~IN_LOOK;

		if (BinocularRange && (!LaserSight && gfLevelFlags & GF_OFFICE && inputBusy & IN_ACTION))//VCI levels, headset + action
			InfraRed = 1;
		else if (BinocularRange && (LaserSight && !(gfLevelFlags & GF_OFFICE)))//none vci levels, lasersight
			InfraRed = 1;
		else
			InfraRed = 0;

		ClearDynamics();
		ClearFires();
		GotLaraSpheres = 0;
		InItemControlLoop = 1;
		item_num = next_item_active;

		while (item_num != NO_ITEM)
		{
			item = &items[item_num];
			nex = item->next_active;

			if (item->after_death < 128)
			{
				if (objects[item->object_number].control)
					objects[item->object_number].control(item_num);
			}
			else
				KillItem(item_num);

			item_num = nex;
		}

		InItemControlLoop = 0;
		KillMoveItems();
		InItemControlLoop = 1;
		fx_num = next_fx_active;

		while (fx_num != NO_ITEM)
		{
			fx = &effects[fx_num];
			nex = fx->next_active;

			if (objects[fx->object_number].control)
				objects[fx->object_number].control(fx_num);

			fx_num = nex;
		}

		InItemControlLoop = 0;
		KillMoveEffects();

		if (KillEverythingFlag)
			KillEverything();

		if (SmokeCountL)
			SmokeCountL--;

		if (SmokeCountR)
			SmokeCountR--;

		if (SplashCount)
			SplashCount--;

		if (WeaponDelay)
			WeaponDelay--;

		if (lara.has_fired && !(wibble & 0x7F))
		{
			AlertNearbyGuards(lara_item);
			lara.has_fired = 0;
		}

		XSoff1 += 150;
		YSoff1 += 230;
		ZSoff1 += 660;
		XSoff2 += 270;
		YSoff2 += 440;
		ZSoff2 += 160;

		if (lara.poisoned && !GLOBAL_playing_cutseq)
		{
			if (lara.poisoned > 4096)
				lara.poisoned = 4096;
			else if (lara.dpoisoned)
				lara.dpoisoned++;

			if (gfLevelFlags & GF_OFFICE && !lara.Gassed)
			{
				if (lara.dpoisoned)
				{
					lara.dpoisoned -= 8;

					if (lara.dpoisoned < 0)
						lara.dpoisoned = 0;
				}
			}

			if (lara.poisoned >= 256 && !(wibble & 0xFF))
			{
				lara_item->hit_points -= lara.poisoned >> (8 - lara.Gassed);
				PoisonFlag = 16;
			}
		}

		lara.skelebob = 0;
		InItemControlLoop = 1;

		if (!GLOBAL_playing_cutseq && !gfGameMode)
		{
			lara.Fired = 0;
			LaraControl(0);

			if (LaraDrawType == LARA_DIVESUIT)
				DoSubsuitStuff();
		}

		InItemControlLoop = 0;
		KillMoveItems();

		if (gfLevelFlags & GF_OFFICE && !bUseSpotCam)
		{
			if (room[lara_item->room_number].FlipNumber > 10)
			{
				InitialiseSpotCam(room[lara_item->room_number].FlipNumber);
				bUseSpotCam = 1;
			}
		}

		if (GLOBAL_inventoryitemchosen != NO_ITEM)
		{
			SayNo();
			GLOBAL_inventoryitemchosen = NO_ITEM;
		}

		if (GLOBAL_playing_cutseq)
		{
			camera.type = CINEMATIC_CAMERA;
			CalculateCamera();
		}
		else
		{
			if (LaraDrawType != LARA_DIVESUIT)
			{
				HairControl(0, 0, 0);

				if (gfLevelFlags & GF_YOUNGLARA)
					HairControl(0, 1, 0);
			}

			if (!bUseSpotCam)
			{
				bTrackCamInit = 0;
				CalculateCamera();
			}
			else
				CalculateSpotCams();
		}

		CamRot.y = (mGetAngle(camera.pos.z, camera.pos.x, camera.target.z, camera.target.x) >> 4) & 0xFFF;
		wibble = (wibble + 4) & 0xFC;
		TriggerLaraDrips();	

		while (SmashedMeshCount)
		{
			SmashedMeshCount--;
			mesh = SmashedMesh[SmashedMeshCount];
			floor = GetFloor(mesh->x, mesh->y, mesh->z, &SmashedMeshRoom[SmashedMeshCount]);
			GetHeight(floor, mesh->x, mesh->y, mesh->z);
			TestTriggers(trigger_index, 1, 0);
			floor->stopper = 0;
			SmashedMesh[SmashedMeshCount] = 0;
		}

		UpdateSparks();
		UpdateFireSparks();
		UpdateSmokeSparks();
		UpdateBubbles();
		UpdateSplashes();
		UpdateDebris();
		UpdateBlood();
		UpdateDrips();
		UpdateGunShells();
		UpdateRats();
		UpdateBats();
		UpdateSpiders();
		UpdateShockwaves();
		UpdateLightning();
		UpdateTwogunLasers();
		AnimateWaterfalls();
		UpdatePulseColour();

		if (gfCurrentLevel == LVL5_SINKING_SUBMARINE)
			KlaxonTremor();

		SoundEffects();
		health_bar_timer--;

		if (gfGameMode == 0)
		{
			GameTimer++;

			if (savegame.Level.Timer)
			{
				if (!GLOBAL_playing_cutseq)
					savegame.Level.Timer++;
			}
		}

		UpdateFadeClip();
	}

	return 0;
}

long GetChange(ITEM_INFO* item, ANIM_STRUCT* anim)
{
	CHANGE_STRUCT* change;
	RANGE_STRUCT* range;

	if (item->current_anim_state == item->goal_anim_state || anim->number_changes <= 0)
		return 0;

	change = &changes[anim->change_index];

	for (int i = 0; i < anim->number_changes; i++, change++)
	{
		if (change->goal_anim_state == item->goal_anim_state && change->number_ranges > 0)
		{
			range = &ranges[change->range_index];

			for (int j = 0; j < change->number_ranges; j++, range++)
			{
				if (item->frame_number >= range->start_frame && item->frame_number <= range->end_frame)
				{
					item->anim_number = range->link_anim_num;
					item->frame_number = range->link_frame_num;
					return 1;
				}
			}
		}
	}

	return 0;
}

long CheckGuardOnTrigger()
{
	ITEM_INFO* item;
	CREATURE_INFO* cinfo;
	short room_number;
	
	room_number = lara_item->room_number;
	GetFloor(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos, &room_number);

	for (int i = 0; i < 5; i++)
	{
		cinfo = &baddie_slots[i];

		if (cinfo->item_num != -1 && !cinfo->alerted)
		{
			item = &items[cinfo->item_num];

			if (room_number == item->room_number && item->current_anim_state == 1)
			{
				if (abs(item->pos.x_pos - lara_item->pos.x_pos) < 1024 &&
					abs(item->pos.z_pos - lara_item->pos.z_pos) < 1024 &&
					abs(item->pos.y_pos - lara_item->pos.y_pos) < 256)
					return 1;
			}
		}
	}

	return 0;
}

void InterpolateAngle(short dest, short* src, short* diff, short speed)
{
	long adiff;

	adiff = (ushort)dest - (ushort)*src;

	if (adiff > 0x8000)
		adiff -= 0x10000;
	else if (adiff < -0x8000)
		adiff += 0x10000;

	if (diff)
		diff[0] = (short)adiff;

	*src += short(adiff >> speed);
}

void TranslateItem(ITEM_INFO* item, short x, short y, short z)
{
	long s, c;

	s = phd_sin(item->pos.y_rot);
	c = phd_cos(item->pos.y_rot);
	item->pos.x_pos += (z * s + x * c) >> 14;
	item->pos.y_pos += y;
	item->pos.z_pos += (z * c - x * s) >> 14;
}

void InitCutPlayed()
{
	_CutSceneTriggered1 = 0;
	_CutSceneTriggered2 = 0;
}

void SetCutPlayed(long num)
{
	if (num < 1 || num > 4)
	{
		if (num < 32)
			_CutSceneTriggered1 |= 1 << num;
		else
			_CutSceneTriggered2 |= 1 << (num - 32);
	}
}

void SetCutNotPlayed(long num)
{
	if (num < 32)
		_CutSceneTriggered1 &= ~(1 << num);
	else
		_CutSceneTriggered2 &= ~(1 << (num - 32));
}

long CheckCutPlayed(long num)
{
	if (num < 32)
		return _CutSceneTriggered1 & (1 << num);
	else
		return _CutSceneTriggered2 & (1 << (num - 32));
}

void NeatAndTidyTriggerCutscene(long value, long timer)
{
	ITEM_INFO* item;
	long inv_item_stealth_frigggggs;
	short item_num;

	if (value == 65)
	{
		if (lara_item->pos.y_pos <= 13824 && have_i_got_object(PICKUP_ITEM1))
			gfLevelComplete = gfCurrentLevel + 1;

		return;
	}

	if ((value == 28 || value == 29 || value == 30 || value == 31) && !cutseq_trig)
	{
		cutseq_num = value;
		cutrot = timer & 3;
		return;
	}

	if (lara.burn)
		return;
	
	if (value == 23)
	{
		if (!cutseq_trig && CheckCutPlayed(23))
			richcutfrigflag = 1;
	}

	if (cutseq_trig || CheckCutPlayed(value))
		return;

	cutrot = timer & 3;

	if (value <= 4 || value > 63)	//stealth "frigggggs"
	{
		if (value == 2)
			inv_item_stealth_frigggggs = CROWBAR_ITEM;
		else
			inv_item_stealth_frigggggs = WET_CLOTH;

		if (input & IN_ACTION && !BinocularRange && lara.gun_status == LG_NO_ARMS &&
			lara_item->current_anim_state == AS_STOP && lara_item->anim_number == ANIM_BREATH &&
			GLOBAL_inventoryitemchosen == NO_ITEM && have_i_got_object((short)inv_item_stealth_frigggggs))
		{
			if (CheckGuardOnTrigger())
				GLOBAL_enterinventory = inv_item_stealth_frigggggs;

			return;
		}

		if (GLOBAL_inventoryitemchosen == inv_item_stealth_frigggggs && CheckGuardOnTrigger())
		{
			if (inv_item_stealth_frigggggs == WET_CLOTH)
				lara.wetcloth = 1;

			GLOBAL_inventoryitemchosen = NO_ITEM;
			cutseq_num = value;
		}

		return;
	}

	switch (value)
	{
	case 43:

		if (cutrot != 1 || is_object_in_room(lara_item->room_number, GREEN_TEETH) && !have_i_got_object(PUZZLE_ITEM2))
			cutseq_num = 43;

		return;

	case 39:

		if (input & IN_ACTION && !BinocularRange && lara.gun_status == LG_NO_ARMS &&
			lara_item->current_anim_state == AS_TREAD && lara_item->anim_number == ANIM_TREAD &&
			GLOBAL_inventoryitemchosen == NO_ITEM && have_i_got_object(PUZZLE_ITEM2))
			GLOBAL_enterinventory = PUZZLE_ITEM2;
		else if (GLOBAL_inventoryitemchosen == PUZZLE_ITEM2)
		{
			GLOBAL_inventoryitemchosen = NO_ITEM;
			cutseq_num = 39;
		}

		return;

	case 38:

		if (input & IN_ACTION && !BinocularRange && lara.gun_status == LG_NO_ARMS &&
			lara_item->current_anim_state == AS_STOP && lara_item->anim_number == ANIM_BREATH &&
			GLOBAL_inventoryitemchosen == NO_ITEM && have_i_got_object(PUZZLE_ITEM1))
			GLOBAL_enterinventory = PUZZLE_ITEM1;
		else if (GLOBAL_inventoryitemchosen == PUZZLE_ITEM1)
		{
			GLOBAL_inventoryitemchosen = NO_ITEM;
			cutseq_num = 38;
		}

		return;

	case 10:

		if (have_i_got_object(PUZZLE_ITEM3))
		{
			SetCutPlayed(10);
			cutseq_num = 9;
			return;
		}

		break;

	case 24:

		for (item_num = room[lara_item->room_number].item_number; item_num != NO_ITEM; item_num = item->next_item)
		{
			item = &items[item_num];

			if (item->object_number == SCIENTIST && item->hit_points > 0 && item->anim_number == objects[BLUE_GUARD].anim_index + 62 &&
				item->frame_number == anims[item->anim_number].frame_end)
			{
				cutseq_num = 24;
				break;
			}
		}

		return;

	case 20:

		if (input & IN_ACTION && !BinocularRange && lara.gun_status == LG_NO_ARMS &&
			lara_item->current_anim_state == AS_STOP && lara_item->anim_number == ANIM_BREATH &&
			GLOBAL_inventoryitemchosen == NO_ITEM && have_i_got_object(KEY_ITEM7))
			GLOBAL_enterinventory = KEY_ITEM7;
		else if (GLOBAL_inventoryitemchosen == KEY_ITEM7)
		{
			GLOBAL_inventoryitemchosen = NO_ITEM;
			cutseq_num = 20;
		}

		return;

	case 14:

		if (input & IN_ACTION && !BinocularRange && lara.gun_status == LG_NO_ARMS &&
			lara_item->current_anim_state == AS_STOP && lara_item->anim_number == ANIM_BREATH &&
			GLOBAL_inventoryitemchosen == NO_ITEM && have_i_got_object(PUZZLE_ITEM2))
			GLOBAL_enterinventory = PUZZLE_ITEM2;
		else if (GLOBAL_inventoryitemchosen == PUZZLE_ITEM2)
		{
			GLOBAL_inventoryitemchosen = NO_ITEM;
			cutseq_num = 14;
			remove_inventory_item(PUZZLE_ITEM2);
		}

		return;

	case 23:

		if (lara.hk_type_carried && !check_xray_machine_trigger() && !richcutfrigflag)
			cutseq_num = 23;

		return;
	}

	cutseq_num = value;
}

long is_object_in_room(long roomnumber, long objnumber)
{
	ITEM_INFO* item;

	for (int i = room[roomnumber].item_number; i != NO_ITEM; i = item->next_item)
	{
		item = &items[i];

		if (item->object_number == objnumber)
			return 1;
	}

	return 0;
}

long check_xray_machine_trigger()
{
	for (int i = 0; i < level_items; i++)
	{
		if (items[i].object_number == XRAY_CONTROLLER && !items[i].trigger_flags && items[i].item_flags[0] == 666)
			return 1;
	}

	return 0;
}

long GetHeight(FLOOR_INFO* floor, long x, long y, long z)
{
	ITEM_INFO* item;
	ROOM_INFO* r;
	short* data;
	long height;
	ushort trigger;
	short type, dx, dz, xoff, yoff, tilt, hadj, tilt0, tilt1, tilt2, tilt3;

	tiltxoff = 0;
	tiltyoff = 0;
	OnObject = 0;
	height_type = WALL;

	while (floor->pit_room != NO_ROOM)
	{
		if (CheckNoColFloorTriangle(floor, x, z) == 1)
			break;

		r = &room[floor->pit_room];
		floor = &r->floor[((z - r->z) >> 10) + ((x - r->x) >> 10) * r->x_size];
	}

	height = floor->floor << 8;

	if (height == NO_HEIGHT)
		return height;

	trigger_index = 0;

	if (!floor->index)
		return height;

	data = &floor_data[floor->index];

	do
	{
		type = *data++;

		switch (type & 0x1F)
		{
		case DOOR_TYPE:
		case ROOF_TYPE:
		case SPLIT3:
		case SPLIT4:
		case NOCOLC1T:
		case NOCOLC1B:
		case NOCOLC2T:
		case NOCOLC2B:
			data++;
			break;

		case TILT_TYPE:
			xoff = *data >> 8;
			yoff = *(char*)data;
			tiltxoff = xoff;
			tiltyoff = yoff;

			if (abs(xoff) > 2 || abs(yoff) > 2)
				height_type = BIG_SLOPE;
			else
				height_type = SMALL_SLOPE;

			if (xoff < 0)
				height -= xoff * (z & 1023) >> 2;
			else
				height += xoff * ((-1 - z) & 1023) >> 2;

			if (yoff < 0)
				height -= yoff * (x & 1023) >> 2;
			else
				height += yoff * ((-1 - x) & 1023) >> 2;

			data++;
			break;

		case TRIGGER_TYPE:

			if (!trigger_index)
				trigger_index = data - 1;

			data++;
			
			do
			{

				trigger = *data++;

				if ((trigger & 0x3C00) != (TO_OBJECT << 10))
				{
					if ((trigger & 0x3C00) == (TO_CAMERA << 10) || (trigger & 0x3C00) == (TO_FLYBY << 10))
						trigger = *data++;

					continue;
				}

				item = &items[trigger & 0x3FF];

				if (objects[item->object_number].floor && !(item->flags & 0x8000))
					(*objects[item->object_number].floor)(item, x, y, z, &height);

			} while (!(trigger & 0x8000));

			break;

		case LAVA_TYPE:
			trigger_index = data - 1;
			break;

		case CLIMB_TYPE:
		case MONKEY_TYPE:
		case TRIGTRIGGER_TYPE:

			if (!trigger_index)
				trigger_index = data - 1;

			break;

		case SPLIT1:
		case SPLIT2:
		case NOCOLF1T:
		case NOCOLF1B:
		case NOCOLF2T:
		case NOCOLF2B:
			tilt = *data;
			tilt0 = tilt & 0xF;
			tilt1 = (tilt >> 4) & 0xF;
			tilt2 = (tilt >> 8) & 0xF;
			tilt3 = (tilt >> 12) & 0xF;
			dx = x & 1023;
			dz = z & 1023;
			height_type = SPLIT_TRI;

			if ((type & 0x1F) == SPLIT1 || (type & 0x1F) == NOCOLF1T || (type & 0x1F) == NOCOLF1B)
			{
				if (dx > (1024 - dz))
				{
					hadj = (type >> 5) & 0x1F;

					if ((type >> 5) & 0x10)
						hadj |= 0xFFF0;

					height += hadj << 8;
					xoff = tilt3 - tilt0;
					yoff = tilt3 - tilt2;
				}
				else
				{
					hadj = (type >> 10) & 0x1F;

					if ((type >> 10) & 0x10)
						hadj |= 0xFFF0;

					height += hadj << 8;
					xoff = tilt2 - tilt1;
					yoff = tilt0 - tilt1;
				}
			}
			else
			{
				if (dx > dz)
				{
					hadj = (type >> 5) & 0x1F;

					if ((type >> 5) & 0x10)
						hadj |= 0xFFF0;

					height += hadj << 8;
					xoff = tilt3 - tilt0;
					yoff = tilt0 - tilt1;
				}
				else
				{
					
					hadj = (type >> 10) & 0x1F;

					if ((type >> 10) & 0x10)
						hadj |= 0xFFF0;

					height += hadj << 8;
					xoff = tilt2 - tilt1;
					yoff = tilt3 - tilt2;
				}
			}

			tiltxoff = xoff;
			tiltyoff = yoff;

			if (abs(xoff) > 2 || abs(yoff) > 2)
				height_type = DIAGONAL;

			if (xoff >= 0)
				height += xoff * ((-1 - z) & 1023) >> 2;
			else
				height -= xoff * (z & 1023) >> 2;

			if (yoff >= 0)
				height += yoff * ((-1 - x) & 1023) >> 2;
			else
				height -= yoff * (x & 1023) >> 2;

			data++;
			break;

		default:
			S_ExitSystem("GetHeight(): Unknown type");
			break;
		}

	} while (!(type & 0x8000));

	return height;
}

FLOOR_INFO* GetFloor(long x, long y, long z, short* room_number)
{
	ROOM_INFO* r;
	FLOOR_INFO* floor;
	long x_floor, y_floor;
	short door;

	r = &room[*room_number];

	do
	{
		x_floor = (z - r->z) >> 10;
		y_floor = (x - r->x) >> 10;

		if (x_floor <= 0)
		{
			x_floor = 0;

			if (y_floor < 1)
				y_floor = 1;
			else if (y_floor > r->y_size - 2)
				y_floor = r->y_size - 2;
		}
		else if (x_floor >= r->x_size - 1)
		{
			x_floor = r->x_size - 1;

			if (y_floor < 1)
				y_floor = 1;
			else if (y_floor > r->y_size - 2)
				y_floor = r->y_size - 2;
		}
		else if (y_floor < 0)
			y_floor = 0;
		else if (y_floor >= r->y_size)
			y_floor = r->y_size - 1;

		floor = &r->floor[x_floor + y_floor * r->x_size];
		door = GetDoor(floor);

		if (door == NO_ROOM)
			break;

		*room_number = door;
		r = &room[door];

	} while (door != NO_ROOM);

	if (y < floor->floor << 8)
	{
		if (y < floor->ceiling << 8 && floor->sky_room != NO_ROOM)
		{
			do
			{
				if (CheckNoColCeilingTriangle(floor, x, z) == 1 || CheckNoColCeilingTriangle(floor, x, z) == -1 && y >= r->maxceiling)
					break;

				*room_number = floor->sky_room;
				r = &room[floor->sky_room];
				floor = &r->floor[((z - r->z) >> 10) + r->x_size * ((x - r->x) >> 10)];

				if (y >= floor->ceiling << 8)
					break;

			} while (floor->sky_room != NO_ROOM);
		}
	}
	else if (floor->pit_room != NO_ROOM)
	{
		while (1)
		{
			if (CheckNoColFloorTriangle(floor, x, z) == 1 || CheckNoColFloorTriangle(floor, x, z) == -1 && y < r->minfloor)
				break;

			*room_number = floor->pit_room;
			r = &room[floor->pit_room];

			floor = &r->floor[((z - r->z) >> 10) + r->x_size * ((x - r->x) >> 10)];

			if (y < floor->floor << 8)
				break;

			if (floor->pit_room == NO_ROOM)
				return floor;
		}
	}

	return floor;
}

long ExplodeItemNode(ITEM_INFO* item, long Node, long NoXZVel, long bits)
{
	OBJECT_INFO* object;
	short** meshpp;

	if (!(item->mesh_bits & (1 << Node)))
		return 0;

	if (item->object_number == SWITCH_TYPE7 && (gfCurrentLevel == LVL5_SINKING_SUBMARINE || gfCurrentLevel == LVL5_BASE))
		SoundEffect(SFX_SMASH_METAL, &item->pos, SFX_DEFAULT);
	else if (bits == 256)
		bits = -64;

	object = &objects[item->object_number];
	meshpp = &meshes[object->mesh_index + 2 * Node];
	GetSpheres(item, Slist, 3);
	ShatterItem.YRot = item->pos.y_rot;
	ShatterItem.Bit = 1 << Node;
	ShatterItem.meshp = *meshpp;
	ShatterItem.Sphere.x = Slist[Node].x;
	ShatterItem.Sphere.y = Slist[Node].y;
	ShatterItem.Sphere.z = Slist[Node].z;
	ShatterItem.il = &item->il;
	ShatterItem.Flags = item->object_number != CROSSBOW_BOLT ? 0 : 1024;
	ShatterObject(&ShatterItem, 0, (short)bits, item->room_number, NoXZVel);
	item->mesh_bits &= ~ShatterItem.Bit;
	return 1;
}

short GetDoor(FLOOR_INFO* floor)
{
	short* data;
	short type;

	if (!floor->index)
		return NO_ROOM;

	data = &floor_data[floor->index];
	type = *data++;

	if ((type & 0x1F) == TILT_TYPE || (type & 0x1F) == SPLIT1 || (type & 0x1F) == SPLIT2 || (type & 0x1F) == NOCOLF1B ||
		(type & 0x1F) == NOCOLF1T || (type & 0x1F) == NOCOLF2B || (type & 0x1F) == NOCOLF2T)
	{
		if (type & 0x8000)
			return NO_ROOM;

		data++;
		type = *data++;
	}

	if ((type & 0x1F) == ROOF_TYPE || (type & 0x1F) == SPLIT3 || (type & 0x1F) == SPLIT4 || (type & 0x1F) == NOCOLC1B ||
		(type & 0x1F) == NOCOLC1T || (type & 0x1F) == NOCOLC2B || (type & 0x1F) == NOCOLC2T)
	{
		if (type & 0x8000)
			return NO_ROOM;

		data++;
		type = *data++;
	}

	if ((type & 0x1F) == DOOR_TYPE)
		return *data;

	return NO_ROOM;
}

long GetCeiling(FLOOR_INFO* floor, long x, long y, long z)
{
	ITEM_INFO* item;
	ROOM_INFO* r;
	FLOOR_INFO* f;
	long xoff, yoff, height, h1, h2;
	short* data, type, trigger, dx, dz, t0, t1, t2, t3, hadj, ended;

	f = floor;

	while (f->sky_room != NO_ROOM)
	{
		if (CheckNoColCeilingTriangle(floor, x, z) == 1)
			break;

		r = &room[f->sky_room];
		xoff = (z - r->z) >> 10;
		yoff = (x - r->x) >> 10;
		f = &r->floor[xoff + r->x_size * yoff];
	}

	height = f->ceiling << 8;

	if (height == NO_HEIGHT)
		return NO_HEIGHT;

	if (f->index)
	{
		data = &floor_data[f->index];
		type = *data++;
		ended = 0;

		if ((type & 0x1F) == TILT_TYPE || (type & 0x1F) == SPLIT1 || (type & 0x1F) == SPLIT2 || (type & 0x1F) == NOCOLF1T ||
			(type & 0x1F) == NOCOLF1B || (type & 0x1F) == NOCOLF2T || (type & 0x1F) == NOCOLF2B)
		{
			data++;

			if (type & 0x8000)
				ended = 1;

			type = *data++;
		}

		if (!ended)
		{
			h1 = 0;
			h2 = 0;

			if ((type & 0x1F) != ROOF_TYPE)
			{
				if ((type & 0x1F) == SPLIT3 || (type & 0x1F) == SPLIT4 || (type & 0x1F) == NOCOLC1T ||
					(type & 0x1F) == NOCOLC1B || (type & 0x1F) == NOCOLC2T || (type & 0x1F) == NOCOLC2B)
				{
					dx = x & 0x3FF;
					dz = z & 0x3FF;
					t0 = -(*data & 0xF);
					t1 = -(*data >> 4 & 0xF);
					t2 = -(*data >> 8 & 0xF);
					t3 = -(*data >> 12 & 0xF);

					if ((type & 0x1F) == SPLIT3 || (type & 0x1F) == NOCOLC1T || (type & 0x1F) == NOCOLC1B)
					{
						if (dx <= 1024 - dz)
						{
							hadj = type >> 10 & 0x1F;

							if (hadj & 0x10)
								hadj |= 0xFFF0;

							height += 256 * hadj;
							h1 = t2 - t1;
							h2 = t3 - t2;
						}
						else
						{
							hadj = type >> 5 & 0x1F;

							if (hadj & 0x10)
								hadj |= 0xFFF0;

							height += 256 * hadj;
							h1 = t3 - t0;
							h2 = t0 - t1;
						}
					}
					else
					{
						if (dx <= dz)
						{
							hadj = type >> 10 & 0x1F;

							if (hadj & 0x10)
								hadj |= 0xFFF0;

							height += 256 * hadj;
							h1 = t2 - t1;
							h2 = t0 - t1;
						}
						else
						{
							hadj = type >> 5 & 0x1F;

							if (hadj & 0x10)
								hadj |= 0xFFF0;

							height += 256 * hadj;
							h1 = t3 - t0;
							h2 = t3 - t2;
						}
					}
				}
			}
			else
			{
				h1 = *data >> 8;
				h2 = *(char*)data;
			}

			if (h1 < 0)
				height += (z & 0x3FF) * h1 >> 2;
			else
				height -= (-1 - z & 0x3FF) * h1 >> 2;

			if (h2 < 0)
				height += (-1 - x & 0x3FF) * h2 >> 2;
			else
				height -= (x & 0x3FF) * h2 >> 2;
		}
	}

	while (floor->pit_room != NO_ROOM)
	{
		if (CheckNoColFloorTriangle(floor, x, z) == 1)
			break;

		r = &room[floor->pit_room];
		xoff = (z - r->z) >> 10;
		yoff = (x - r->x) >> 10;
		floor = &r->floor[xoff + r->x_size * yoff];
	}

	if (floor->index)
	{
		data = &floor_data[floor->index];

		do
		{
			type = *data++;

			switch (type & 0x1F)
			{
			case DOOR_TYPE:
			case TILT_TYPE:
			case ROOF_TYPE:
			case SPLIT1:
			case SPLIT2:
			case SPLIT3:
			case SPLIT4:
			case NOCOLF1T:
			case NOCOLF1B:
			case NOCOLF2T:
			case NOCOLF2B:
			case NOCOLC1T:
			case NOCOLC1B:
			case NOCOLC2T:
			case NOCOLC2B:
				data++;
				break;

			case TRIGGER_TYPE:
				data++;

				do
				{
					trigger = *data;
					data++;

					if ((trigger & 0x3C00) != (TO_OBJECT << 10))
					{
						if ((trigger & 0x3C00) == (TO_CAMERA << 10) || (trigger & 0x3C00) == (TO_FLYBY << 10))
							trigger = *data++;
					}
					else
					{
						item = &items[trigger & 0x3FF];

						if (objects[item->object_number].ceiling && !(item->flags & 0x8000))
							objects[item->object_number].ceiling(item, x, y, z, &height);
					}

				} while (!(trigger & 0x8000));

				break;

			case LAVA_TYPE:
			case CLIMB_TYPE:
			case MONKEY_TYPE:
			case TRIGTRIGGER_TYPE:
				break;

			default:
				S_ExitSystem("GetCeiling(): Unknown type");
				break;
			}

		} while (!(type & 0x8000));
	}

	return height;
}

long LOS(GAME_VECTOR* start, GAME_VECTOR* target)
{
	long los1, los2;

	target->room_number = start->room_number;

	if (abs(target->z - start->z) > abs(target->x - start->x))
	{
		los1 = xLOS(start, target);
		los2 = zLOS(start, target);
	}
	else
	{
		los1 = zLOS(start, target);
		los2 = xLOS(start, target);
	}

	if (los2)
	{
		GetFloor(target->x, target->y, target->z, &target->room_number);

		if (ClipTarget(start, target) && los1 == 1 && los2 == 1)
			return 1;
	}

	return 0;
}

long xLOS(GAME_VECTOR* start, GAME_VECTOR* target)
{
	FLOOR_INFO* floor;
	long dx, dy, dz, x, y, z;
	short room_number, last_room;

	dx = target->x - start->x;

	if (!dx)
		return 1;

	dy = 1024 * (target->y - start->y) / dx;
	dz = 1024 * (target->z - start->z) / dx;
	number_los_rooms = 1;
	los_rooms[0] = start->room_number;
	room_number = start->room_number;
	last_room = start->room_number;

	if (dx < 0)
	{
		x = start->x & 0xFFFFFC00;
		y = ((x - start->x) * dy >> 10) + start->y;
		z = ((x - start->x) * dz >> 10) + start->z;

		while (x > target->x)
		{
			floor = GetFloor(x, y, z, &room_number);

			if (room_number != last_room)
			{
				last_room = room_number;
				los_rooms[number_los_rooms] = room_number;
				number_los_rooms++;
			}

			if (y > GetHeight(floor, x, y, z) || y < GetCeiling(floor, x, y, z))
			{
				target->x = x;
				target->y = y;
				target->z = z;
				target->room_number = room_number;
				return -1;
			}

			floor = GetFloor(x - 1, y, z, &room_number);

			if (room_number != last_room)
			{
				last_room = room_number;
				los_rooms[number_los_rooms] = room_number;
				number_los_rooms++;
			}

			if (y > GetHeight(floor, x - 1, y, z) || y < GetCeiling(floor, x - 1, y, z))
			{
				target->x = x;
				target->y = y;
				target->z = z;
				target->room_number = last_room;
				return 0;
			}

			x -= 1024;
			y -= dy;
			z -= dz;
		}
	}
	else
	{
		x = start->x | 0x3FF;
		y = ((x - start->x) * dy >> 10) + start->y;
		z = ((x - start->x) * dz >> 10) + start->z;

		while (x < target->x)
		{
			floor = GetFloor(x, y, z, &room_number);

			if (room_number != last_room)
			{
				last_room = room_number;
				los_rooms[number_los_rooms] = room_number;
				number_los_rooms++;
			}

			if (y > GetHeight(floor, x, y, z) || y < GetCeiling(floor, x, y, z))
			{
				target->x = x;
				target->y = y;
				target->z = z;
				target->room_number = room_number;
				return -1;
			}

			floor = GetFloor(x + 1, y, z, &room_number);

			if (room_number != last_room)
			{
				last_room = room_number;
				los_rooms[number_los_rooms] = room_number;
				number_los_rooms++;
			}

			if (y > GetHeight(floor, x + 1, y, z) || y < GetCeiling(floor, x + 1, y, z))
			{
				target->x = x;
				target->y = y;
				target->z = z;
				target->room_number = last_room;
				return 0;
			}

			x += 1024;
			y += dy;
			z += dz;
		}
	}

	target->room_number = room_number;
	return 1;
}

long zLOS(GAME_VECTOR* start, GAME_VECTOR* target)
{
	FLOOR_INFO* floor;
	long dx, dy, dz, x, y, z;
	short room_number, last_room;

	dz = target->z - start->z;

	if (!dz)
		return 1;

	dx = 1024 * (target->x - start->x) / dz;
	dy = 1024 * (target->y - start->y) / dz;
	number_los_rooms = 1;
	los_rooms[0] = start->room_number;
	room_number = start->room_number;
	last_room = start->room_number;

	if (dz < 0)
	{
		z = start->z & 0xFFFFFC00;
		x = ((z - start->z) * dx >> 10) + start->x;
		y = ((z - start->z) * dy >> 10) + start->y;

		while (z > target->z)
		{
			floor = GetFloor(x, y, z, &room_number);

			if (room_number != last_room)
			{
				last_room = room_number;
				los_rooms[number_los_rooms] = room_number;
				number_los_rooms++;
			}

			if (y > GetHeight(floor, x, y, z) || y < GetCeiling(floor, x, y, z))
			{
				target->x = x;
				target->y = y;
				target->z = z;
				target->room_number = room_number;
				return -1;
			}

			floor = GetFloor(x, y, z - 1, &room_number);

			if (room_number != last_room)
			{
				last_room = room_number;
				los_rooms[number_los_rooms] = room_number;
				number_los_rooms++;
			}

			if (y > GetHeight(floor, x, y, z - 1) || y < GetCeiling(floor, x, y, z - 1))
			{
				target->x = x;
				target->y = y;
				target->z = z;
				target->room_number = last_room;
				return 0;
			}

			z -= 1024;
			x -= dx;
			y -= dy;
		}
	}
	else
	{
		z = start->z | 0x3FF;
		x = ((z - start->z) * dx >> 10) + start->x;
		y = ((z - start->z) * dy >> 10) + start->y;

		while (z < target->z)
		{
			floor = GetFloor(x, y, z, &room_number);

			if (room_number != last_room)
			{
				last_room = room_number;
				los_rooms[number_los_rooms] = room_number;
				number_los_rooms++;
			}

			if (y > GetHeight(floor, x, y, z) || y < GetCeiling(floor, x, y, z))
			{
				target->x = x;
				target->y = y;
				target->z = z;
				target->room_number = room_number;
				return -1;
			}

			floor = GetFloor(x, y, z + 1, &room_number);

			if (room_number != last_room)
			{
				last_room = room_number;
				los_rooms[number_los_rooms] = room_number;
				number_los_rooms++;
			}

			if (y > GetHeight(floor, x, y, z + 1) || y < GetCeiling(floor, x, y, z + 1))
			{
				target->x = x;
				target->y = y;
				target->z = z;
				target->room_number = last_room;
				return 0;
			}

			z += 1024;
			x += dx;
			y += dy;
		}
	}

	target->room_number = room_number;
	return 1;
}

long ClipTarget(GAME_VECTOR* start, GAME_VECTOR* target)
{
	GAME_VECTOR src;
	long dx, dy, dz;
	short room_no;

	room_no = target->room_number;

	if (target->y > GetHeight(GetFloor(target->x, target->y, target->z, &room_no), target->x, target->y, target->z))
	{
		src.x = (7 * (target->x - start->x) >> 3) + start->x;
		src.y = (7 * (target->y - start->y) >> 3) + start->y;
		src.z = (7 * (target->z - start->z) >> 3) + start->z;

		for (int i = 3; i > 0; i--)
		{
			dx = ((target->x - src.x) * i >> 2) + src.x;
			dy = ((target->y - src.y) * i >> 2) + src.y;
			dz = ((target->z - src.z) * i >> 2) + src.z;

			if (dy < GetHeight(GetFloor(dx, dy, dz, &room_no), dx, dy, dz))
				break;
		}

		target->x = dx;
		target->y = dy;
		target->z = dz;
		target->room_number = room_no;
		return 0;
	}

	room_no = target->room_number;

	if (target->y < GetCeiling(GetFloor(target->x, target->y, target->z, &room_no), target->x, target->y, target->z))
	{
		src.x = (7 * (target->x - start->x) >> 3) + start->x;
		src.y = (7 * (target->y - start->y) >> 3) + start->y;
		src.z = (7 * (target->z - start->z) >> 3) + start->z;

		for (int i = 3; i > 0; i--)
		{
			dx = ((target->x - src.x) * i >> 2) + src.x;
			dy = ((target->y - src.y) * i >> 2) + src.y;
			dz = ((target->z - src.z) * i >> 2) + src.z;

			if (dy > GetCeiling(GetFloor(dx, dy, dz, &room_no), dx, dy, dz))
				break;
		}

		target->x = dx;
		target->y = dy;
		target->z = dz;
		target->room_number = room_no;
		return 0;
	}

	return 1;
}

long GetTargetOnLOS(GAME_VECTOR* src, GAME_VECTOR* dest, long DrawTarget, long firing)
{
	ITEM_INFO* shotitem;
	MESH_INFO* Mesh;
	GAME_VECTOR target;
	PHD_VECTOR v;
	short item_no, hit, ricochet, room_number, TriggerItems[8], NumTrigs;

	target.x = dest->x;
	target.y = dest->y;
	target.z = dest->z;
	ricochet = (short)LOS(src, &target);
	GetFloor(target.x, target.y, target.z, &target.room_number);

	if (firing && LaserSight)
	{
		lara.has_fired = 1;
		lara.Fired = 1;

		if (lara.gun_type == WEAPON_REVOLVER)
			SoundEffect(SFX_REVOLVER, 0, SFX_DEFAULT);
	}

	hit = 0;
	item_no = (short)ObjectOnLOS2(src, dest, &v, &Mesh);

	if (item_no != 999)
	{
		target.x = v.x - ((v.x - src->x) >> 5);
		target.y = v.y - ((v.y - src->y) >> 5);
		target.z = v.z - ((v.z - src->z) >> 5);
		GetFloor(target.x, target.y, target.z, &target.room_number);

		if (item_no >= 0)
			lara.target = &items[item_no];

		if (firing)
		{
			if (lara.gun_type != WEAPON_CROSSBOW)
			{
				if (item_no < 0)
				{
					if (Mesh->static_number >= 50 && Mesh->static_number < 58)
					{
						ShatterObject(0, Mesh, 128, target.room_number, 0);
						SmashedMeshRoom[SmashedMeshCount] = target.room_number;
						SmashedMesh[SmashedMeshCount] = Mesh;
						SmashedMeshCount++;
						Mesh->Flags &= ~0x1;
						SoundEffect(ShatterSounds[gfCurrentLevel][Mesh->static_number - 50], (PHD_3DPOS*)Mesh, 0);
					}

					TriggerRicochetSpark(&target, lara_item->pos.y_rot, 3, 0);
					TriggerRicochetSpark(&target, lara_item->pos.y_rot, 3, 0);
				}
				else
				{
					shotitem = &items[item_no];

					if (shotitem->object_number != SWITCH_TYPE7 && shotitem->object_number != SWITCH_TYPE8)
					{
						if (objects[shotitem->object_number].explodable_meshbits & ShatterItem.Bit && LaserSight)
						{
							if (!objects[shotitem->object_number].intelligent)
							{
								ShatterObject(&ShatterItem, 0, 128, target.room_number, 0);
								shotitem->mesh_bits &= ~ShatterItem.Bit;
								TriggerRicochetSpark(&target, lara_item->pos.y_rot, 3, 0);
							}
							else if (shotitem->object_number != TWOGUN)
							{
								shotitem->hit_points -= 30;

								if (shotitem->hit_points < 0)
									shotitem->hit_points = 0;

								HitTarget(shotitem, &target, weapons[lara.gun_type].damage, 0);
							}
							else if (abs(phd_atan(lara_item->pos.z_pos - shotitem->pos.z_pos, lara_item->pos.x_pos - shotitem->pos.x_pos) - shotitem->pos.y_rot) < 16384)
							{
								shotitem->hit_points = 0;
								HitTarget(shotitem, &target, weapons[lara.gun_type].damage, 0);
							}
						}
						else if (DrawTarget && (lara.gun_type == WEAPON_REVOLVER || lara.gun_type == WEAPON_HK))
						{
							if (objects[shotitem->object_number].intelligent)
								HitTarget(shotitem, &target, weapons[lara.gun_type].damage, 0);
							else if (objects[shotitem->object_number].HitEffect == 3)
								TriggerRicochetSpark(&target, lara_item->pos.y_rot, 3, 0);
						}
						else if (shotitem->object_number >= SMASH_OBJECT1 && shotitem->object_number <= SMASH_OBJECT8)
							SmashObject(item_no);
						else
						{
							if (objects[shotitem->object_number].HitEffect == 1)
								DoBloodSplat(target.x, target.y, target.z, (GetRandomControl() & 3) + 3, shotitem->pos.y_rot, shotitem->room_number);
							else if (objects[shotitem->object_number].HitEffect == 2)
								TriggerRicochetSpark(&target, lara_item->pos.y_rot, 3, -5);
							else if (objects[shotitem->object_number].HitEffect == 3)
								TriggerRicochetSpark(&target, lara_item->pos.y_rot, 3, 0);

							shotitem->hit_status = 1;

							if (!objects[shotitem->object_number].undead)
								shotitem->hit_points -= weapons[lara.gun_type].damage;
						}
					}
					else
					{
						if (ShatterItem.Bit == 1 << (objects[shotitem->object_number].nmeshes - 1))
						{
							if (!(shotitem->flags & IFL_SWITCH_ONESHOT))
							{
								if (shotitem->object_number == SWITCH_TYPE7)
									ExplodeItemNode(shotitem, objects[shotitem->object_number].nmeshes - 1, 0, 64);

								if (shotitem->trigger_flags == 444 && shotitem->object_number == SWITCH_TYPE8)
									ProcessExplodingSwitchType8(shotitem);
								else if (shotitem->flags & IFL_CODEBITS && (shotitem->flags & IFL_CODEBITS) != IFL_CODEBITS)
								{
									room_number = shotitem->room_number;
									GetHeight(GetFloor(shotitem->pos.x_pos, shotitem->pos.y_pos - 256, shotitem->pos.z_pos, &room_number), shotitem->pos.x_pos, shotitem->pos.y_pos - 256, shotitem->pos.z_pos);
									TestTriggers(trigger_index, 1, shotitem->flags & IFL_CODEBITS);
								}
								else
								{
									NumTrigs = (short)GetSwitchTrigger(shotitem, TriggerItems, 1);

									for (int i = NumTrigs - 1; i >= 0; i--)
									{
										AddActiveItem(TriggerItems[i]);
										items[TriggerItems[i]].status = ITEM_ACTIVE;
										items[TriggerItems[i]].flags |= IFL_CODEBITS;
									}
								}
							}

							if (shotitem->status != ITEM_DEACTIVATED)
							{
								AddActiveItem(item_no);
								shotitem->status = ITEM_ACTIVE;
								shotitem->flags |= IFL_SWITCH_ONESHOT | IFL_CODEBITS;
							}
						}

						TriggerRicochetSpark(&target, lara_item->pos.y_rot, 3, 0);
					}
				}
			}
			else if (LaserSight && item_no >= 0)
			{
				shotitem = &items[item_no];

				if (shotitem->object_number == GRAPPLING_TARGET && shotitem->mesh_bits & 1)
				{
					LaserSightCol = gfLevelFlags & GF_OFFICE;

					if (gfLevelFlags & GF_OFFICE)
					{
						target.x = shotitem->pos.x_pos;
						target.y = shotitem->pos.y_pos;
						target.z = shotitem->pos.z_pos;
					}

					FireCrossBowFromLaserSight(src, &target);
				}
			}
		}
		else if (item_no >= 0)
		{
			shotitem = &items[item_no];

			if (shotitem->object_number == GRAPPLING_TARGET && lara.gun_type == WEAPON_CROSSBOW && shotitem->mesh_bits & 1)
				LaserSightCol = gfLevelFlags & GF_OFFICE;
		}

		hit = 1;
	}
	else if (lara.gun_type != WEAPON_CROSSBOW)
	{
		target.x -= (target.x - src->x) >> 5;
		target.y -= (target.y - src->y) >> 5;
		target.z -= (target.z - src->z) >> 5;

		if (firing && !ricochet)
			TriggerRicochetSpark(&target, lara_item->pos.y_rot, 8, 0);
	}
	else if (firing && LaserSight && LaserSightCol == (gfLevelFlags & GF_OFFICE))
		FireCrossBowFromLaserSight(src, &target);

	if (DrawTarget && (hit || !ricochet))
	{
		TriggerDynamic(target.x, target.y, target.z, 64, 255, 0, 0);
		LaserSightActive = 1;
		LaserSightX = target.x;
		LaserSightY = target.y;
		LaserSightZ = target.z;
	}

	return hit;
}

long ObjectOnLOS2(GAME_VECTOR* start, GAME_VECTOR* target, PHD_VECTOR* Coord, MESH_INFO** StaticMesh)
{
	ITEM_INFO* item;
	MESH_INFO* mesh;
	ROOM_INFO* r;
	PHD_3DPOS ItemPos;
	short* bounds;
	long dx, dy, dz;
	short item_number;

	ClosestItem = 999;
	dx = target->x - start->x;
	dy = target->y - start->y;
	dz = target->z - start->z;
	ClosestDist = SQUARE(dx) + SQUARE(dy) + SQUARE(dz);

	for (int i = 0; i < number_los_rooms; i++)
	{
		r = &room[los_rooms[i]];

		for (item_number = r->item_number; item_number != NO_ITEM; item_number = item->next_item)
		{
			item = &items[item_number];

			if (item->status != ITEM_DEACTIVATED && item->status != ITEM_INVISIBLE && (item->object_number != LARA && objects[item->object_number].collision || item->object_number == LARA && GetLaraOnLOS))
			{
				bounds = GetBoundsAccurate(item);
				ItemPos.x_pos = item->pos.x_pos;
				ItemPos.y_pos = item->pos.y_pos;
				ItemPos.z_pos = item->pos.z_pos;
				ItemPos.y_rot = item->pos.y_rot;

				if (DoRayBox(start, target, bounds, &ItemPos, Coord, item_number))
					target->room_number = los_rooms[i];
			}
		}

		for (int j = 0; j < r->num_meshes; j++)
		{
			mesh = &r->mesh[j];

			if (mesh->Flags & 1)
			{
				ItemPos.x_pos = mesh->x;
				ItemPos.y_pos = mesh->y;
				ItemPos.z_pos = mesh->z;
				ItemPos.y_rot = mesh->y_rot;

				if (DoRayBox(start, target, &static_objects[mesh->static_number].x_minc, &ItemPos, Coord, -1 - mesh->static_number))
				{
					*StaticMesh = mesh;
					target->room_number = los_rooms[i];
				}
			}
		}
	}

	Coord->x = ClosestCoord.x;
	Coord->y = ClosestCoord.y;
	Coord->z = ClosestCoord.z;
	return ClosestItem;
}

void TestTriggers(short* data, long heavy, long HeavyFlags)
{
	globoncuttrig = 0;
	_TestTriggers(data, heavy, HeavyFlags);

	if (!globoncuttrig && richcutfrigflag)
			richcutfrigflag = 0;
}

void _TestTriggers(short* data, long heavy, long HeavyFlags)
{
	ITEM_INFO* item;
	ITEM_INFO* camera_item;
	long switch_off, flip, flip_available, neweffect, key, quad;
	short camera_flags, camera_timer, type, trigger, value, flags, state, CamSeq;
	static uchar HeavyTriggered;
	char timer, SwitchOnOnly;
	
	switch_off = 0;
	flip = -1;
	flip_available = 0;
	neweffect = -1;
	key = 0;
	HeavyTriggered = 0;

	if (!heavy)
	{
		lara.CanMonkeySwing = 0;
		lara.climb_status = 0;
	}

	if (!data)
		return;

	if ((*data & 0x1F) == LAVA_TYPE)
	{
		if (!heavy && (lara_item->pos.y_pos == lara_item->floor || lara.water_status != LW_ABOVE_WATER))
			LavaBurn(lara_item);

		if (*data & 0x8000)
			return;

		data++;
	}

	if ((*data & 0x1F) == CLIMB_TYPE)
	{
		if (!heavy)
		{
			quad = ushort(lara_item->pos.y_rot + 8192) >> 14;

			if ((1 << (quad + 8)) & *data)
				lara.climb_status = 1;
		}

		if (*data & 0x8000)
			return;

		data++;
	}

	if ((*data & 0x1F) == MONKEY_TYPE)
	{
		if (!heavy)
			lara.CanMonkeySwing = 1;

		if (*data & 0x8000)
			return;

		data++;
	}

	if ((*data & 0x1F) == TRIGTRIGGER_TYPE)
	{
		if (!(*data & 0x20) || *data & 0x8000)
			return;

		data++;
	}

	type = (*data++ >> 8) & 0x3F;
	flags = *data++;
	timer = flags & 0xff;

	if (camera.type != HEAVY_CAMERA)
		RefreshCamera(type, data);

	SwitchOnOnly = 0;

	if (heavy)
	{
		switch (type)
		{
		case HEAVY:
		case HEAVYANTITRIGGER:
			break;

		case HEAVYSWITCH:

			if (!HeavyFlags)
				return;

			if (HeavyFlags >= 0)
			{
				flags &= IFL_CODEBITS;

				if (flags != HeavyFlags)
					return;
			}
			else
			{
				flags |= IFL_CODEBITS;
				flags += (short)HeavyFlags;
			}

			break;

		default:
			return;
		}
	}
	else
	{
		switch (type)
		{
		case PAD:
		case ANTIPAD:

			if (lara_item->pos.y_pos != lara_item->floor)
				return;

			break;

		case SWITCH:
			value = *data++ & 0x3FF;

			if (flags & IFL_INVISIBLE)
				items[value].item_flags[0] = 1;

			if (!SwitchTrigger(value, timer))
				return;

			if (items[value].object_number >= SWITCH_TYPE1 && items[value].object_number <= SWITCH_TYPE6 && items[value].trigger_flags == 5)
				SwitchOnOnly = 1;

			switch_off = items[value].current_anim_state == 1;
			break;

		case KEY:
			value = *(data++) & 0x3FF;
			key = KeyTrigger(value);

			if (key != -1)
				break;

			return;

		case PICKUP:
			value = *(data++) & 0x3FF;

			if (PickupTrigger(value))
				break;

			return;

		case HEAVY:
		case DUMMY:
		case HEAVYSWITCH:
		case HEAVYANTITRIGGER:
				return;

		case COMBAT:

			if (lara.gun_status == LG_READY)
				break;

			return;

		case MONKEY:
			state = lara_item->current_anim_state;

			if (state >= AS_HANG2 && (state <= AS_MONKEY180 || state == AS_HANGTURNL || state == AS_HANGTURNR))
				break;

			return;

		case SKELETON_T:
			lara.skelebob = 2;
			break;

		case TIGHTROPE_T:
			state = lara_item->current_anim_state;

			if (state >= AS_TROPEPOSE && state <= AS_TROPEUNDOFALL && state != AS_CROWDOVE)
				break;

			return;

		case CRAWLDUCK_T:
			state = lara_item->current_anim_state;

			if (state == AS_ALL4S || state == AS_CRAWL || state == AS_ALL4TURNL || state == AS_ALL4TURNR ||
				state == AS_CRAWLBACK || state == AS_DUCK || state == AS_DUCKROLL || state == AS_DUCKROTL || state == AS_DUCKROTR)
				break;

			return;

		case CLIMB_T:
			state = lara_item->current_anim_state;

			if (state == AS_HANG || state == AS_CLIMBSTNC || state == AS_CLIMBING || state == AS_CLIMBLEFT ||
				state == AS_CLIMBEND || state == AS_CLIMBRIGHT || state == AS_CLIMBDOWN || state == AS_HANG2)
				break;

			return;
		}
	}

	camera_item = 0;

	do
	{
		trigger = *data++;
		value = trigger & 0x3FF;

		switch ((trigger & 0x3FFF) >> 10)
		{
		case TO_OBJECT:
			item = &items[value];

			if (key >= 2 || ((type == ANTIPAD || type == ANTITRIGGER || type == HEAVYANTITRIGGER) && item->flags & IFL_ANTITRIGGER_ONESHOT) ||
				(type == SWITCH && item->flags & IFL_SWITCH_ONESHOT) ||
				(type != SWITCH && type != ANTIPAD && type != ANTITRIGGER && type != HEAVYANTITRIGGER && item->flags & IFL_INVISIBLE) ||
				((type != ANTIPAD && type != ANTITRIGGER && type != HEAVYANTITRIGGER) && (item->object_number == DART_EMITTER && item->active)))
				break;

			item->timer = timer;

			if (timer != 1)
				item->timer *= 30;

			if (type == SWITCH || type == HEAVYSWITCH)
			{
				if (HeavyFlags >= 0)
				{
					if (SwitchOnOnly)
						item->flags |= flags & IFL_CODEBITS;
					else
						item->flags ^= flags & IFL_CODEBITS;

					if (flags & IFL_INVISIBLE)
						item->flags |= IFL_SWITCH_ONESHOT;
				}
				else if (((item->flags ^ (flags & IFL_CODEBITS)) & IFL_CODEBITS) == IFL_CODEBITS)
				{
					item->flags ^= (flags & IFL_CODEBITS);

					if (flags & IFL_INVISIBLE)
						item->flags |= IFL_SWITCH_ONESHOT;
				}
			}
			else if (type == ANTIPAD || type == ANTITRIGGER || type == HEAVYANTITRIGGER)
			{
				if (item->object_number == EARTHQUAKE)
				{
					item->item_flags[0] = 0;
					item->item_flags[1] = 100;
				}

				item->flags &= ~(IFL_CODEBITS | IFL_REVERSE);

				if (flags & IFL_INVISIBLE)
					item->flags |= IFL_ANTITRIGGER_ONESHOT;

				if (item->active && objects[item->object_number].intelligent)
				{
					item->hit_points = -16384;
					DisableBaddieAI(value);
					KillItem(value);
				}

			}
			else if (flags & IFL_CODEBITS)
				item->flags |= flags & IFL_CODEBITS;

			if ((item->flags & IFL_CODEBITS) != IFL_CODEBITS)
				break;

			item->flags |= IFL_TRIGGERED;

			if (flags & IFL_INVISIBLE)
				item->flags |= IFL_INVISIBLE;

			if (!item->active)
			{
				if (objects[item->object_number].intelligent)
				{
					if (item->status == ITEM_INACTIVE)
					{
						item->touch_bits = 0;
						item->status = ITEM_ACTIVE;
						AddActiveItem(value);
						EnableBaddieAI(value, 1);
					}
					else if (item->status == ITEM_INVISIBLE)
					{
						item->touch_bits = 0;

						if (EnableBaddieAI(value, 0))
							item->status = ITEM_ACTIVE;
						else
							item->status = ITEM_INVISIBLE;

						AddActiveItem(value);

					}
				}
				else
				{
					item->touch_bits = 0;
					AddActiveItem(value);
					item->status = ITEM_ACTIVE;
					HeavyTriggered = (uchar)heavy;
				}
			}

			break;

		case TO_CAMERA:
			trigger = *data++;
			camera_flags = trigger;
			camera_timer = trigger & 0xFF;

			if (key == 1 || camera.fixed[value].flags & IFL_INVISIBLE)
				break;

			camera.number = value;

			if (type == COMBAT || ((camera.type == LOOK_CAMERA || camera.type == COMBAT_CAMERA) && !(camera.fixed[camera.number].flags & 3)) ||
				(type == SWITCH && timer && switch_off))
				break;

			if (camera.number != camera.last || type == SWITCH)
			{
				camera.timer = camera_timer * 30;

				if (camera_flags & IFL_INVISIBLE)
					camera.fixed[camera.number].flags |= IFL_INVISIBLE;

				camera.speed = ((camera_flags & IFL_CODEBITS) >> 6) + 1;

				if (heavy)
					camera.type = HEAVY_CAMERA;
				else
					camera.type = FIXED_CAMERA;
			}

			break;

		case TO_SINK:
			lara.current_active = value + 1;
			break;

		case TO_FLIPMAP:
			flip_available = 1;

			if (flipmap[value] & IFL_INVISIBLE)
				break;

			if (type == SWITCH)
				flipmap[value] ^= flags & IFL_CODEBITS;
			else if (flags & IFL_CODEBITS)
				flipmap[value] |= flags & IFL_CODEBITS;

			if ((flipmap[value] & IFL_CODEBITS) == IFL_CODEBITS)
			{
				if (flags & IFL_INVISIBLE)
					flipmap[value] |= IFL_INVISIBLE;

				if (!flip_stats[value])
					flip = value;
			}
			else if (flip_stats[value])
				flip = value;

			break;

		case TO_FLIPON:
			flip_available = 1;

			flipmap[value] |= 0x3E00;

			if (!flip_stats[value])
				flip = value;

			break;

		case TO_FLIPOFF:
			flip_available = 1;

			flipmap[value] &= 0xC1FF;

			if (flip_stats[value])
				flip = value;

			break;

		case TO_TARGET:
			camera_item = &items[value];
			break;

		case TO_FINISH:
			gfLevelComplete = gfCurrentLevel + 1;
			gfRequiredStartPos = 0;
			break;

		case TO_CD:
			TriggerCDTrack(value, flags, type);
			break;

		case TO_FLIPEFFECT:
			TriggerTimer = timer;
			neweffect = value;
			break;

		case TO_BODYBAG:
			ResetGuards();
			break;

		case TO_FLYBY:
			trigger = *data++;
			camera_flags = trigger;
			camera_timer = trigger & 0xFF;

			if (key == 1)
				break;

			if (type == ANTIPAD || type == ANTITRIGGER || type == HEAVYANTITRIGGER)
			{
				bUseSpotCam = 0;
				break;
			}

			CamSeq = 0;

			for (int i = 0; i < SpotRemap[value]; i++)
				CamSeq += CameraCnt[i];

			if (SpotCam[CamSeq].flags & SP_FLYBYONESHOT)
				break;

			if (camera_flags & IFL_INVISIBLE)
				SpotCam[CamSeq].flags |= SP_FLYBYONESHOT;

			if (bUseSpotCam)
				break;

			bUseSpotCam = 1;

			if (LastSequence != value)
				bTrackCamInit = 0;

			InitialiseSpotCam(value);
			break;

		case TO_CUTSCENE:
			globoncuttrig = 1;
			NeatAndTidyTriggerCutscene(value, timer);
			break;
		}
	}
	while (!(trigger & 0x8000));

	if (camera_item && (camera.type == FIXED_CAMERA || camera.type == HEAVY_CAMERA))
		camera.item = camera_item;

	if (flip != -1)
		FlipMap(flip);

	if (neweffect != -1 && (flip || !flip_available))
	{
		flipeffect = neweffect;
		fliptimer = 0;
	}
}

void FlipMap(long FlipNumber)
{
	ROOM_INFO* r;
	ROOM_INFO* flipped;
	CREATURE_INFO* cinfo;
	ROOM_INFO temp;

	for (int i = 0; i < number_rooms; i++)
	{
		r = &room[i];

		if (r->flipped_room >= 0 && r->FlipNumber == FlipNumber)
		{
			RemoveRoomFlipItems(r);
			flipped = &room[r->flipped_room];
			memcpy(&temp, r, sizeof(temp));
			memcpy(r, flipped, sizeof(ROOM_INFO));
			memcpy(flipped, &temp, sizeof(ROOM_INFO));
			r->flipped_room = flipped->flipped_room;
			flipped->flipped_room = -1;
			r->item_number = flipped->item_number;
			r->fx_number = flipped->fx_number;
			AddRoomFlipItems(r);
		}
	}

	flip_stats[FlipNumber] = !flip_stats[FlipNumber];
	flip_status = flip_stats[FlipNumber];

	for (short slot = 0; slot < 5; slot++)
	{
		cinfo = &baddie_slots[slot];
		cinfo->LOT.target_box = 0x7FF;
	}
}

void RemoveRoomFlipItems(ROOM_INFO* r)
{
	ITEM_INFO* item;

	for (short item_num = 0; item_num != NO_ITEM; item_num = items[item_num].next_item)
	{
		item = &items[item_num];

		if (item->flags & IFL_INVISIBLE && objects[item->object_number].intelligent)
		{
			if (item->hit_points <= 0 && item->hit_points != -16384)
				KillItem(item_num);
		}
	}
}

void AddRoomFlipItems(ROOM_INFO* r)
{
	ITEM_INFO* item;

	for (short item_num = r->item_number; item_num != -1; item_num = items[item_num].next_item)
	{
		item = &items[item_num];

		if (items[item_num].object_number == 134 && item->item_flags[1])
			AlterFloorHeight(item, -1024);

		if (item->object_number == 135 && item->item_flags[1])
			AlterFloorHeight(item, -2048);
	}
}

void RefreshCamera(short type, short* data)
{
	short trigger, value, target_ok;

	target_ok = 2;

	do
	{
		trigger = *data++;
		value = trigger & 0x3FF;

		if (((trigger >> 10) & 0xF) == TO_CAMERA)
		{
			data++;

			if (value == camera.last)
			{
				camera.number = trigger & 0x3FF;

				if (camera.timer >= 0 && (camera.type != LOOK_CAMERA && camera.type != COMBAT_CAMERA || camera.fixed[camera.number].flags & 3))
				{
					camera.type = FIXED_CAMERA;
					target_ok = 1;
					continue;
				}

				camera.timer = -1;
			}

			target_ok = 0;
		}
		else if (((trigger >> 10) & 0xF) == TO_TARGET)
		{
			if (camera.type != LOOK_CAMERA && camera.type != COMBAT_CAMERA || camera.number == NO_ITEM || camera.fixed[camera.number].flags & 3)
				camera.item = &items[value];
		}

	} while (!(trigger & 0x8000));

	if (camera.item)
	{
		if (!target_ok || target_ok == 2 && camera.item->looked_at && camera.item != camera.last_item)
			camera.item = 0;
	}

	if (camera.number == -1 && camera.timer > 0)
		camera.timer = -1;
}

void KillMoveItems()
{
	for (int i = 0; i < ItemNewRoomNo; i++)
	{
		if (ItemNewRooms[i][0] & 0x8000)
			KillItem(ItemNewRooms[i][0] & 0x7FFF);
		else
			ItemNewRoom(ItemNewRooms[i][0], ItemNewRooms[i][1]);
	}

	ItemNewRoomNo = 0;
}

void KillMoveEffects()
{
	for (int i = 0; i < ItemNewRoomNo; i++)
	{
		if (ItemNewRooms[i][0] & 0x8000)
			KillEffect(ItemNewRooms[i][0] & 0x7FFF);
		else
			EffectNewRoom(ItemNewRooms[i][0], ItemNewRooms[i][1]);
	}

	ItemNewRoomNo = 0;
}

void UpdateSky()
{
	if (gfLevelFlags & GF_LAYER1)
	{
		SkyPos += gfLayer1Vel;

		if (SkyPos > 0x2600)
			SkyPos -= 0x2600;
		else if (SkyPos < 0)
			SkyPos += 0x2600;
	}

	if (gfLevelFlags & GF_LAYER2)
	{
		SkyPos2 += gfLayer2Vel;

		if (SkyPos2 > 0x2600)
			SkyPos2 -= 0x2600;
		else if (SkyPos2 < 0)
			SkyPos2 += 0x2600;
	}
}

void AlterFloorHeight(ITEM_INFO* item, long height)
{
	FLOOR_INFO* floor;
	FLOOR_INFO* ceiling;
	short room_num, joby;

	joby = 0;

	if (abs(height) & 0xFF)
	{
		joby = 1;

		if (height < 0)
			height--;
		else
			height++;
	}

	room_num = item->room_number;
	floor = GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_num);
	ceiling = GetFloor(item->pos.x_pos, item->pos.y_pos + height - 1024, item->pos.z_pos, &room_num);

	if (floor->floor == -127)
		floor->floor = ceiling->ceiling + char(height >> 8);
	else
	{
		floor->floor += char(height >> 8);

		if (floor->floor == ceiling->ceiling && !joby)
			floor->floor = -127;
	}

	if (boxes[floor->box].overlap_index & 0x8000)
	{
		if (height >= 0)
			boxes[floor->box].overlap_index &= ~0x4000;
		else
			boxes[floor->box].overlap_index |= 0x4000;
	}
}

long GetWaterHeight(long x, long y, long z, short room_number)
{
	ROOM_INFO* r;
	FLOOR_INFO* floor;
	long x_floor, y_floor;
	short data;

	r = &room[room_number];

	do
	{
		x_floor = (z - r->z) >> 10;
		y_floor = (x - r->x) >> 10;

		if (x_floor <= 0)
		{
			x_floor = 0;

			if (y_floor < 1)
				y_floor = 1;
			else if (y_floor > r->y_size - 2)
				y_floor = r->y_size - 2;
		}
		else if (x_floor >= r->x_size - 1)
		{
			x_floor = r->x_size - 1;

			if (y_floor < 1)
				y_floor = 1;
			else if (y_floor > r->y_size - 2)
				y_floor = r->y_size - 2;
		}
		else if (y_floor < 0)
			y_floor = 0;
		else if (y_floor >= r->y_size)
			y_floor = r->y_size - 1;

		floor = &r->floor[x_floor + y_floor * r->x_size];
		data = GetDoor(floor);

		if (data != NO_ROOM)
		{
			room_number = data;
			r = &room[data];
		}

	} while (data != NO_ROOM);

	if (r->flags & ROOM_UNDERWATER)
	{
		while (floor->sky_room != NO_ROOM)
		{
			if (CheckNoColCeilingTriangle(floor, x, z) == 1)
				break;

			r = &room[floor->sky_room];

			if (!(r->flags & ROOM_UNDERWATER))
				return r->minfloor;

			floor = &r->floor[((z - r->z) >> 10) + r->x_size * ((x - r->x) >> 10)];
		}

		return r->maxceiling;
	}
	else
	{
		while (floor->pit_room != NO_ROOM)
		{
			if (CheckNoColFloorTriangle(floor, x, z) == 1)
				break;

			r = &room[floor->pit_room];

			if (r->flags & ROOM_UNDERWATER)
				return r->maxceiling;

			floor = &r->floor[((z - r->z) >> 10) + r->x_size * ((x - r->x) >> 10)];
		}
	}

	return NO_HEIGHT;
}

long TriggerActive(ITEM_INFO* item)
{
	long reverse;

	reverse = (item->flags & IFL_REVERSE) ? 1 : 0;

	if ((item->flags & IFL_CODEBITS) != IFL_CODEBITS)
		return reverse;

	if (!item->timer)
		return !reverse;

	if (item->timer > 0)
	{
		item->timer--;

		if (!item->timer)
			item->timer = -1;
	}
	else if (item->timer < -1)
	{
		item->timer++;

		if (item->timer == -1)
			item->timer = 0;
	}

	if (item->timer <= -1)
		return reverse;

	return !reverse;
}

long CheckNoColFloorTriangle(FLOOR_INFO* floor, long x, long z)
{
	short type;

	if (!floor->index)
		return 0;

	type = floor_data[floor->index] & 0x1F;

	if (type == NOCOLF1T || type == NOCOLF1B || type == NOCOLF2T || type == NOCOLF2B)
	{
		x &= 0x3FF;
		z &= 0x3FF;

		switch (type)
		{
		case NOCOLF1T:

			if (x <= 1024 - z)
				return -1;

			break;

		case NOCOLF1B:

			if (x > 1024 - z)
				return -1;

			break;

		case NOCOLF2T:

			if (x <= z)
				return -1;

			break;

		case NOCOLF2B:

			if (x > z)
				return -1;

			break;
		}

		return 1;
	}

	return 0;
}

long CheckNoColCeilingTriangle(FLOOR_INFO* floor, long x, long z)
{
	short* data;
	short type;

	if (!floor->index)
		return 0;

	data = &floor_data[floor->index];
	type = *data & 0x1F;

	if (type == TILT_TYPE || type == SPLIT1 || type == SPLIT2 || type == NOCOLF1T || type == NOCOLF1B || type == NOCOLF2T || type == NOCOLF2B)
	{
		if (*data & 0x8000)
			return 0;

		type = data[2] & 0x1F;
	}

	if (type == NOCOLC1T || type == NOCOLC1B || type == NOCOLC2T || type == NOCOLC2B)
	{
		x &= 0x3FF;
		z &= 0x3FF;

		switch (type)
		{
		case NOCOLC1T:

			if (x <= 1024 - z)
				return -1;

			break;

		case NOCOLC1B:

			if (x > 1024 - z)
				return -1;

			break;

		case NOCOLC2T:

			if (x <= z)
				return -1;

			break;

		case NOCOLC2B:

			if (x > z)
				return -1;

			break;
		}

		return 1;
	}

	return 0;
}

void FireCrossBowFromLaserSight(GAME_VECTOR* start, GAME_VECTOR* target)
{
	PHD_3DPOS pos;
	short angles[2];

	target->x = target->x & ~0x3FF | 512;
	target->z = target->z & ~0x3FF | 512;
	phd_GetVectorAngles(target->x - start->x, target->y - start->y, target->z - start->z, angles);
	pos.x_pos = start->x;
	pos.y_pos = start->y;
	pos.z_pos = start->z;
	pos.x_rot = angles[1];
	pos.y_rot = angles[0];
	pos.z_rot = 0;
	FireCrossbow(&pos);
}

void TriggerCDTrack(short value, short flags, short type)
{
	if (value < 136)
		TriggerNormalCDTrack(value, flags, type);
}

void TriggerNormalCDTrack(short value, short flags, short type)
{
	long code;

	if (value == 117 || value == 118 || value == 121 || value >= 123 && value <= 130)
	{
		if (CurrentAtmosphere != value)
		{
			CurrentAtmosphere = (uchar)value;

			if (IsAtmospherePlaying)
				S_CDPlay(value, 1);
		}
	}
	else
	{
		code = (flags >> 8) & 0x3F;	//(IFL_CODEBITS | IFL_INVISIBLE)= 0x3F00, then >> 8, 3F

		if ((cd_flags[value] & code) != code)
		{
			cd_flags[value] |= code;
			S_CDPlay(value, 0);
			IsAtmospherePlaying = 0;
		}
	}
}

long IsRoomOutside(long x, long y, long z)
{
	ROOM_INFO* r;
	FLOOR_INFO* floor;
	uchar* pTable;
	long h, c;
	short offset, room_no;

	if (x < 0 || z < 0)
		return -2;

	offset = OutsideRoomOffsets[27 * (x >> 12) + (z >> 12)];

	if (offset == -1)
		return -2;

	if (offset < 0)
	{
		r = &room[offset & 0x7FFF];

		if (y >= r->maxceiling && y <= r->minfloor &&
			z >= r->z + 1024 && z <= (r->x_size << 10) + r->z - 1024 &&
			x >= r->x + 1024 && x <= (r->y_size << 10) + r->x - 1024)
		{
			IsRoomOutsideNo = offset & 0x7FFF;
			room_no = IsRoomOutsideNo;
			floor = GetFloor(x, y, z, &room_no);
			h = GetHeight(floor, x, y, z);
			c = GetCeiling(floor, x, y, z);

			if (h == NO_HEIGHT || y > h || y < c)
				return -2;

			if (r->flags & (ROOM_UNDERWATER | ROOM_NOT_INSIDE))
				return 1;
			else
				return -3;
		}
	}
	else
	{
		pTable = (uchar*)&OutsideRoomTable[offset];

		while (*pTable != 255)
		{
			r = &room[*pTable];

			if (y >= r->maxceiling && y <= r->minfloor &&
				z >= r->z + 1024 && z <= (r->x_size << 10) + r->z - 1024 &&
				x >= r->x + 1024 && x <= (r->y_size << 10) + r->x - 1024)
			{
				IsRoomOutsideNo = *pTable;
				room_no = IsRoomOutsideNo;
				floor = GetFloor(x, y, z, &room_no);
				h = GetHeight(floor, x, y, z);
				c = GetCeiling(floor, x, y, z);

				if (h == NO_HEIGHT || y > h || y < c)
					return -2;

				if (r->flags & (ROOM_UNDERWATER | ROOM_NOT_INSIDE))
					return 1;
				else
					return -3;
			}

			pTable++;
		}
	}

	return -2;
}

void AnimateItem(ITEM_INFO* item)
{
	ANIM_STRUCT* anim;
	short* cmd;
	long speed, speed2;
	ushort type, num;

	anim = &anims[item->anim_number];
	item->touch_bits = 0;
	item->hit_status = 0;
	item->frame_number++;

	if (anim->number_changes > 0)
	{
		if (GetChange(item, anim))
		{
			anim = &anims[item->anim_number];
			item->current_anim_state = anim->current_anim_state;

			if (item->required_anim_state == item->current_anim_state)
				item->required_anim_state = 0;
		}
	}

	if (item->frame_number > anim->frame_end)
	{
		if (anim->number_commands > 0)
		{
			cmd = &commands[anim->command_index];

			for (int i = anim->number_commands; i > 0; i--)
			{
				switch (*cmd++)
				{
				case 1:
					TranslateItem(item, cmd[0], cmd[1], cmd[2]);
					cmd += 3;
					break;

				case 2:
					item->fallspeed = cmd[0];
					item->speed = cmd[1];
					item->gravity_status = 1;
					cmd += 2;
					break;

				case 4:

					if (objects[item->object_number].intelligent && !item->after_death)
						item->after_death = 1;

					item->status = ITEM_DEACTIVATED;
					break;

				case 5:
				case 6:
					cmd += 2;
					break;
				}
			}
		}

		item->anim_number = anim->jump_anim_num;
		item->frame_number = anim->jump_frame_num;
		anim = &anims[item->anim_number];

		if (item->current_anim_state != anim->current_anim_state)
		{
			item->current_anim_state = anim->current_anim_state;
			item->goal_anim_state = anim->current_anim_state;
		}

		if (item->required_anim_state == item->current_anim_state)
			item->required_anim_state = 0;
	}

	if (anim->number_commands > 0)
	{
		cmd = &commands[anim->command_index];

		for (int i = anim->number_commands; i > 0; i--)
		{
			switch (*cmd++)
			{
			case 1:
				cmd += 3;
				break;

			case 2:
				cmd += 2;
				break;

			case 5:

				if (item->frame_number == *cmd)
				{
					num = cmd[1] & 0x3FFF;
					type = cmd[1] & 0xC000;

					if (objects[item->object_number].water_creature)
					{
						if (room[item->room_number].flags & ROOM_UNDERWATER)
							SoundEffect(num, &item->pos, SFX_WATER);
						else
							SoundEffect(num, &item->pos, SFX_DEFAULT);
					}
					else if (item->room_number == NO_ROOM)
					{
						item->pos.x_pos = lara_item->pos.x_pos;
						item->pos.y_pos = lara_item->pos.y_pos - 762;
						item->pos.z_pos = lara_item->pos.z_pos;
						SoundEffect(num, &item->pos, SFX_ALWAYS);
					}
					else if (room[item->room_number].flags & ROOM_UNDERWATER)
					{
						if (type == SFX_LANDANDWATER || type == SFX_WATERONLY &&
							(room[camera.pos.room_number].flags & ROOM_UNDERWATER || objects[item->object_number].intelligent))
							SoundEffect(num, &item->pos, SFX_DEFAULT);
					}
					else if (type == SFX_LANDANDWATER || type == SFX_LANDONLY && !(room[camera.pos.room_number].flags & ROOM_UNDERWATER))
						SoundEffect(num, &item->pos, SFX_DEFAULT);
				}

				cmd += 2;
				break;

			case 6:

				if (item->frame_number == *cmd)
				{
					FXType = cmd[1] & 0xC000;
					effect_routines[cmd[1] & 0x3FFF](item);
				}

				cmd += 2;
				break;
			}
		}
	}

	speed2 = 0;

	if (item->gravity_status)
	{
		if (item->fallspeed < 128)
			item->fallspeed += 6;
		else
			item->fallspeed++;

		item->pos.y_pos += item->fallspeed;
	}
	else
	{
		speed = anim->velocity;

		if (anim->acceleration)
			speed += anim->acceleration * (item->frame_number - anim->frame_base);

		item->speed = speed >> 16;

		speed2 = anim->Xvelocity;

		if (anim->Xacceleration)
			speed2 += anim->Xacceleration * (item->frame_number - anim->frame_base);

		speed2 >>= 16;
	}

	item->pos.x_pos += (item->speed * phd_sin(item->pos.y_rot)) >> 14;
	item->pos.z_pos += (item->speed * phd_cos(item->pos.y_rot)) >> 14;
	item->pos.x_pos += (speed2 * phd_sin(item->pos.y_rot + 0x4000)) >> 14;
	item->pos.z_pos += (speed2 * phd_cos(item->pos.y_rot + 0x4000)) >> 14;
}

long RayBoxIntersect(PHD_VECTOR* min, PHD_VECTOR* max, PHD_VECTOR* origin, PHD_VECTOR* dir, PHD_VECTOR* Coord)
{
	long planes[3];
	long dists[3];
	long plane;
	char quad[3];
	char inside;

	inside = 1;

	if (origin->x < min->x)
	{
		quad[0] = 1;
		planes[0] = min->x;
		inside = 0;
	}
	else if (origin->x > max->x)
	{
		quad[0] = 0;
		planes[0] = max->x;
		inside = 0;
	}
	else
		quad[0] = 2;

	if (origin->y < min->y)
	{
		quad[1] = 1;
		planes[1] = min->y;
		inside = 0;
	}
	else if (origin->y > max->y)
	{
		quad[1] = 0;
		planes[1] = max->y;
		inside = 0;
	}
	else
		quad[1] = 2;

	if (origin->z < min->z)
	{
		quad[2] = 1;
		planes[2] = min->z;
		inside = 0;
	}
	else if (origin->z > max->z)
	{
		quad[2] = 0;
		planes[2] = max->z;
		inside = 0;
	}
	else
		quad[2] = 2;

	if (inside)
	{
		Coord->x = origin->x >> 16;
		Coord->y = origin->y >> 16;
		Coord->z = origin->z >> 16;
		return 1;
	}

	if (quad[0] == 2 || !dir->x)
		dists[0] = -65536;
	else
		dists[0] = ((planes[0] - origin->x) / (dir->x >> 8)) << 8;

	if (quad[1] == 2 || !dir->y)
		dists[1] = -65536;
	else
		dists[1] = ((planes[1] - origin->y) / (dir->y >> 8)) << 8;

	if (quad[2] == 2 || !dir->z)
		dists[2] = -65536;
	else
		dists[2] = ((planes[2] - origin->z) / (dir->z >> 8)) << 8;

	plane = 0;

	for (int i = 1; i < 3; i++)
	{
		if (dists[plane] < dists[i])
			plane = i;
	}

	if (dists[plane] < 0)
		return 0;

	if (!plane)
		Coord->x = planes[0];
	else
	{
		Coord->x = origin->x + (((__int64)dir->x * (__int64)dists[plane]) >> 16);

		if ((!quad[0] && Coord->x < min->x) || (quad[0] == 1 && Coord->x > max->x))
			return 0;
	}

	if (plane == 1)
		Coord->y = planes[1];
	else
	{
		Coord->y = origin->y + (((__int64)dir->y * (__int64)dists[plane]) >> 16);

		if ((!quad[1] && Coord->y < min->y) || (quad[1] == 1 && Coord->y > max->y))
			return 0;
	}

	if (plane == 2)
		Coord->z = planes[2];
	else
	{
		Coord->z = origin->z + (((__int64)dir->z * (__int64)dists[plane]) >> 16);

		if ((!quad[2] && Coord->z < min->z) || (quad[2] == 1 && Coord->z > max->z))
			return 0;
	}

	Coord->x >>= 16;
	Coord->y >>= 16;
	Coord->z >>= 16;
	return 1;
}

long DoRayBox(GAME_VECTOR* start, GAME_VECTOR* target, short* bounds, PHD_3DPOS* ItemPos, PHD_VECTOR* Coord, short item_number)
{
	ITEM_INFO* item;
	OBJECT_INFO* obj;
	SPHERE* sphere;
	PHD_VECTOR min, max, origin, dir;
	PHD_VECTOR spos, tpos, s, t, sp, pos;
	short** meshpp;
	short* ClosestMesh;
	long x, y, z, ClosestNode, ClosestBit, bit, r, r0, r1, dist, max_dist;

	min.x = bounds[0] << 16;
	min.y = bounds[2] << 16;
	min.z = bounds[4] << 16;

	max.x = bounds[1] << 16;
	max.y = bounds[3] << 16;
	max.z = bounds[5] << 16;

	phd_PushUnitMatrix();
	phd_RotY(-ItemPos->y_rot);

	x = target->x - ItemPos->x_pos;
	y = target->y - ItemPos->y_pos;
	z = target->z - ItemPos->z_pos;
	tpos.x = (phd_mxptr[M00] * x + phd_mxptr[M01] * y + phd_mxptr[M02] * z) >> 14;
	tpos.y = (phd_mxptr[M10] * x + phd_mxptr[M11] * y + phd_mxptr[M12] * z) >> 14;
	tpos.z = (phd_mxptr[M20] * x + phd_mxptr[M21] * y + phd_mxptr[M22] * z) >> 14;

	x = start->x - ItemPos->x_pos;
	y = start->y - ItemPos->y_pos;
	z = start->z - ItemPos->z_pos;
	spos.x = (phd_mxptr[M00] * x + phd_mxptr[M01] * y + phd_mxptr[M02] * z) >> 14;
	spos.y = (phd_mxptr[M10] * x + phd_mxptr[M11] * y + phd_mxptr[M12] * z) >> 14;
	spos.z = (phd_mxptr[M20] * x + phd_mxptr[M21] * y + phd_mxptr[M22] * z) >> 14;

	phd_PopMatrix();

	dir.x = (tpos.x - spos.x) << 16;
	dir.y = (tpos.y - spos.y) << 16;
	dir.z = (tpos.z - spos.z) << 16;
	origin.x = spos.x << 16;
	origin.y = spos.y << 16;
	origin.z = spos.z << 16;
	Normalise(&dir);
	dir.x <<= 8;
	dir.y <<= 8;
	dir.z <<= 8;

	if (!RayBoxIntersect(&min, &max, &origin, &dir, Coord))
		return 0;

	if (Coord->x < bounds[0] || Coord->x > bounds[1] ||
		Coord->y < bounds[2] || Coord->y > bounds[3] ||
		Coord->z < bounds[4] || Coord->z > bounds[5])
		return 0;

	phd_PushUnitMatrix();
	phd_RotY(ItemPos->y_rot);

	x = (phd_mxptr[M00] * Coord->x + phd_mxptr[M01] * Coord->y + phd_mxptr[M02] * Coord->z) >> 14;
	y = (phd_mxptr[M10] * Coord->x + phd_mxptr[M11] * Coord->y + phd_mxptr[M12] * Coord->z) >> 14;
	z = (phd_mxptr[M20] * Coord->x + phd_mxptr[M21] * Coord->y + phd_mxptr[M22] * Coord->z) >> 14;
	Coord->x = x;
	Coord->y = y;
	Coord->z = z;

	phd_PopMatrix();
	max_dist = 0x7FFFFFFF;
	ClosestMesh = 0;
	ClosestBit = 0;
	item = 0;

	if (item_number < 0)
		ClosestNode = -1;
	else
	{
		item = &items[item_number];
		obj = &objects[item->object_number];
		meshpp = &meshes[obj->mesh_index];

		GetSpheres(item, Slist, 1);
		bit = 1;
		ClosestNode = -2;

		for (int i = 0; i < obj->nmeshes; i++, meshpp += 2, bit <<= 1)
		{
			if (!(item->mesh_bits & bit))
				continue;

			sphere = &Slist[i];
			s.x = start->x;
			s.y = start->y;
			s.z = start->z;

			t.x = target->x;
			t.y = target->y;
			t.z = target->z;

			sp.x = sphere->x;
			sp.y = sphere->y;
			sp.z = sphere->z;

			r0 = ((sp.x - s.x) * (t.x - s.x)) + ((sp.y - s.y) * (t.y - s.y)) + ((sp.z - s.z) * (t.z - s.z));
			r1 = SQUARE(t.x - s.x) + SQUARE(t.y - s.y) + SQUARE(t.z - s.z);

			if ((r0 >= 0 || r1 >= 0) && (r1 <= 0 || r0 <= 0) || (abs(r0) > abs(r1)))
				continue;

			r1 >>= 16;

			if (r1)
				r = r0 / r1;
			else
				r = 0;

			pos.x = s.x + ((r * (t.x - s.x)) >> 16);
			pos.y = s.y + ((r * (t.y - s.y)) >> 16);
			pos.z = s.z + ((r * (t.z - s.z)) >> 16);

			if (SQUARE(pos.x - sp.x) + SQUARE(pos.y - sp.y) + SQUARE(pos.z - sp.z) < SQUARE(sphere->r))
			{
				dist = SQUARE(sphere->x - start->x) + SQUARE(sphere->y - start->y) + SQUARE(sphere->z - start->z);

				if (dist < max_dist)
				{
					max_dist = dist;
					ClosestMesh = *meshpp;
					ClosestBit = bit;
					ClosestNode = i;
				}
			}
		}
	}

	if (ClosestNode >= -1)
	{
		dist = SQUARE(Coord->x + ItemPos->x_pos - start->x) + SQUARE(Coord->y + ItemPos->y_pos - start->y) + SQUARE(Coord->z + ItemPos->z_pos - start->z);

		if (dist < ClosestDist)
		{
			ClosestCoord.x = Coord->x + ItemPos->x_pos;
			ClosestCoord.y = Coord->y + ItemPos->y_pos;
			ClosestCoord.z = Coord->z + ItemPos->z_pos;
			ClosestItem = item_number;
			ClosestDist = dist;

			if (ClosestNode >= 0)
			{
				GetSpheres(item, Slist, 3);
				ShatterItem.YRot = item->pos.y_rot;
				ShatterItem.meshp = ClosestMesh;
				ShatterItem.Sphere.x = Slist[ClosestNode].x;
				ShatterItem.Sphere.y = Slist[ClosestNode].y;
				ShatterItem.Sphere.z = Slist[ClosestNode].z;
				ShatterItem.Bit = ClosestBit;
				ShatterItem.il = &item->il;
				ShatterItem.Flags = 0;
			}

			return 1;
		}
	}

	return 0;
}

void ResetGuards()
{
	ITEM_INFO* item;
	ROOM_INFO* r;
	short item_number, room_number, object_number;

	for (item_number = next_item_active; item_number != NO_ITEM; item_number = item->next_active)
	{
		item = &items[item_number];

		if (!objects[item->object_number].intelligent)
			continue;

		item->status = ITEM_INVISIBLE;
		RemoveActiveItem(item_number);
		DisableBaddieAI(item_number);

		room_number = item->item_flags[2] & 0xFF;
		r = &room[room_number];
		item->pos.x_pos = r->x + ((item->draw_room & 0xFFFFFF00) << 2) + 512;
		item->pos.y_pos = r->minfloor + (item->item_flags[2] & 0xFFFFFF00);
		item->pos.z_pos = ((item->draw_room & 0xFF) << 10) + r->z + 512;
		item->pos.y_rot = item->TOSSPAD & 0xE000;
		item->ai_bits = item->TOSSPAD >> 8;
		item->item_flags[3] = item->TOSSPAD & 0xFF;

		object_number = item->object_number;

		if (object_number == CHEF || object_number == MAZE_MONSTER || object_number == WILLOWISP)
			item->anim_number = objects[object_number].anim_index;
		else if (object_number == TWOGUN)
			item->anim_number = objects[object_number].anim_index + 6;
		else if (objects[SWAT].loaded)
			item->anim_number = objects[SWAT].anim_index;
		else if (objects[ATTACK_SUB].loaded)
			item->anim_number = objects[ATTACK_SUB].anim_index;
		else
			item->anim_number = objects[BLUE_GUARD].anim_index;

		if (object_number == MAZE_MONSTER)
		{
			item->current_anim_state = 0;
			item->goal_anim_state = 0;
		}
		else
		{
			item->current_anim_state = 1;
			item->goal_anim_state = 1;
		}

		item->frame_number = anims[item->anim_number].frame_base;

		if (item->room_number != room_number)
			ItemNewRoom(item_number, room_number);
	}
}
