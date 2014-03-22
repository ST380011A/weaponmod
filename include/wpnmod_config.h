/*
 * Half-Life Weapon Mod
 * Copyright (c) 2012 - 2014 AGHL.RU Dev Team
 * 
 * http://aghl.ru/forum/ - Russian Half-Life and Adrenaline Gamer Community
 *
 *
 *    This program is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#include "amxxmodule.h"

#include "CString.h"
#include "CVector.h"
#include "cbase.h"

#include "wpnmod_vtable.h"
#include "wpnmod_pvdata.h"
#include "wpnmod_log.h"


typedef enum
{
	SUBMOD_UNKNOWN = 0,

	SUBMOD_AG,
	SUBMOD_VALVE,
	SUBMOD_GEARBOX,

	SUBMOD_AGHLRU,
	SUBMOD_MINIAG,
} SUBMOD;

class CConfig
{
private:
	bool	m_bInited;
	bool	m_bWorldSpawned;
	char	m_cfgpath[1024];

public:
	CConfig();

	int**	m_pCurrentSlots;
	int		m_iMaxWeaponSlots;
	int		m_iMaxWeaponPositions;

	bool	m_bWpnBoxModels;
	int		m_iWpnBoxLifeTime;
	int		m_iWpnBoxRenderColor;

	edict_t*	m_pEquipEnt;

	void	InitGameMod			(void);
	void	WorldPrecache		(void);
	void	SetConfigFile		(void);
	char*	GetConfigFile		(void)		{ return &m_cfgpath[0]; };

	//SUBMOD GetSubMod(void);
	SUBMOD	CheckSubMod			(const char* game);

	void	ServerActivate		(void);
	void	ServerShutDown		(void);
	void	ServerDeactivate	(void);
	void	ManageEquipment		(void);
	void	AutoSlotDetection	(int iWeaponID, int iSlot, int iPosition);
};

extern CConfig g_Config;










#define PS_STOPPED		4
#define UD_FINDPLUGIN	3

#ifdef __linux__
	#define stricmp	strcasecmp
#endif

#define WEAPON_RESPAWN_TIME					20

#define ITEM_FLAG_SELECTONEMPTY				1
#define ITEM_FLAG_NOAUTORELOAD				2
#define ITEM_FLAG_NOAUTOSWITCHEMPTY			4
#define ITEM_FLAG_LIMITINWORLD				8
#define ITEM_FLAG_EXHAUSTIBLE				16


enum e_AmmoFwds
{
	Fwd_Ammo_Spawn,
	Fwd_Ammo_AddAmmo,

	Fwd_Ammo_End
};

enum e_WpnFwds
{
	Fwd_Wpn_Spawn,
	Fwd_Wpn_CanDeploy,
	Fwd_Wpn_Deploy,
	Fwd_Wpn_Idle,
	Fwd_Wpn_PrimaryAttack,
	Fwd_Wpn_SecondaryAttack,
	Fwd_Wpn_Reload,
	Fwd_Wpn_CanHolster,
	Fwd_Wpn_Holster,
	Fwd_Wpn_IsUseable,
	Fwd_Wpn_AddToPlayer,
	Fwd_Wpn_AddToPlayer2,
	Fwd_Wpn_ItemPostFrame,

	Fwd_Wpn_End
};

enum e_WpnType
{
	Wpn_None,
	Wpn_Default,
	Wpn_Custom,

	Wpn_End
};

class CPlugin
{
public:
	AMX amx;
	void* code;

	String	name;
	String	version;
	String	title;
	String	author;
	String	errorMsg;

	int dummy_1;
	int dummy_2;
	int dummy_3;
	int dummy_4;
	int status;
};

typedef struct
{
	int		iSlot;
	int		iPosition;
	const char	*pszAmmo1;	// ammo 1 type
	int		iMaxAmmo1;		// max ammo 1
	const char	*pszAmmo2;	// ammo 2 type
	int		iMaxAmmo2;		// max ammo 2
	const char	*pszName;
	int		iMaxClip;
	int		iId;
	int		iFlags;
	int		iWeight;// this value used to determine this weapon's importance in autoselection.
} ItemInfo;

typedef struct
{
	String	classname;
	int		iForward[Fwd_Ammo_End];

} AmmoBoxData;

typedef struct
{
	String		title;
	String		author;
	String		version;
	String		worldModel;

	e_WpnType	iType;
	ItemInfo	ItemData;

	int			iForward[Fwd_Wpn_End];

} WeaponData;

typedef struct 
{
	const char*	name;
	int			index;

} DecalList;

typedef struct
{
	const char*	ammoname;
	int			count;

} StartAmmo;

extern AMX_NATIVE_INFO Natives[];


extern int g_iWeaponsCount;
extern int g_iWeaponInitID;
extern int g_iAmmoBoxIndex;

extern cvar_t *cvar_sv_cheats;
extern cvar_t *cvar_mp_weaponstay;

extern CVector <DecalList*>			g_Decals;
extern CVector <StartAmmo*>			g_StartAmmo;
extern CVector <VirtualHookData*>	g_BlockedItems;

extern bool g_bAmmoBoxHooked;
extern bool g_bCrowbarHooked;

extern SUBMOD g_GameMod;

extern WeaponData	WeaponInfoArray	[MAX_WEAPONS];
extern AmmoBoxData	AmmoBoxInfoArray[MAX_WEAPONS];

extern void		WpnModCommand	(void);

extern	edict_t*		Ammo_Spawn			(const char* szName, Vector vecOrigin, Vector vecAngles);
extern	edict_t*		Weapon_Spawn		(const char* szName, Vector vecOrigin, Vector vecAngles);

inline int			GetWeapon_Slot(const int iId)			{ return WeaponInfoArray[iId].ItemData.iSlot; }
inline int			GetWeapon_ItemPosition(const int iId)	{ return WeaponInfoArray[iId].ItemData.iPosition; }
inline const char*	GetWeapon_pszAmmo1(const int iId)		{ return WeaponInfoArray[iId].ItemData.pszAmmo1; }
inline int			GetWeapon_MaxAmmo1(const int iId)		{ return WeaponInfoArray[iId].ItemData.iMaxAmmo1; }
inline const char*	GetWeapon_pszAmmo2(const int iId)		{ return WeaponInfoArray[iId].ItemData.pszAmmo2; }
inline int			GetWeapon_MaxAmmo2(const int iId)		{ return WeaponInfoArray[iId].ItemData.iMaxAmmo2; }
inline const char*	GetWeapon_pszName(const int iId)		{ return WeaponInfoArray[iId].ItemData.pszName; }
inline int			GetWeapon_MaxClip(const int iId)		{ return WeaponInfoArray[iId].ItemData.iMaxClip; }
inline int			GetWeapon_Weight(const int iId)			{ return WeaponInfoArray[iId].ItemData.iWeight; }
inline int			GetWeapon_Flags(const int iId)			{ return WeaponInfoArray[iId].ItemData.iFlags; }

#endif // _CONFIG_H
