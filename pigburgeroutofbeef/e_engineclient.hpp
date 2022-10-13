#pragma once

#ifndef engineclient
#define engineclient

#include "pch.h"
typedef uint32_t CRC32_t;
typedef uint64_t uint64;
typedef uint32_t uint32;

#define DECLARE_BYTESWAP_DATADESC() DECLARE_SIMPLE_DATADESC()
#define BEGIN_BYTESWAP_DATADESC(name) BEGIN_SIMPLE_DATADESC(name) 
#define BEGIN_BYTESWAP_DATADESC_(name,base) BEGIN_SIMPLE_DATADESC_(name,base) 
#define END_BYTESWAP_DATADESC() END_DATADESC()

typedef struct player_info_s
{
	//DECLARE_BYTESWAP_DATADESC();
	// version for future compatibility
	uint64			version;
	// network xuid
	uint64			xuid;
	// scoreboard information
	char			name[128];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[32 + 1];
	// friends identification number
	uint32			friendsID;
	// friends name
	char			friendsName[128];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
#if defined( REPLAY_ENABLED )
	// true if player is the Replay proxy
	bool			isreplay;
#endif
	// custom files CRC for this player
	CRC32_t			customFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
} player_info_t;


class IVEngineClient
{
public:

	// Find the model's surfaces that intersect the given sphere.
// Returns the number of surfaces filled in.
	virtual int					GetIntersectingSurfaces(
		const model_t* model,
		const vec3_t vCenter,
		const float radius,
		const bool bOnlyVisibleSurfaces,	// Only return surfaces visible to vCenter.
		void* pInfos,
		const int nMaxInfos) = 0;

	// Get the lighting intensivty for a specified point
	// If bClamp is specified, the resulting Vector is restricted to the 0.0 to 1.0 for each element
	virtual vec_t*				GetLightForPoint(const vec3_t pos, bool bClamp) = 0;

	virtual void* TraceLineMaterialAndLighting(const vec3_t start, const vec3_t end,
		vec3_t diffuseLightColor, vec3_t baseColor) = 0;

	// Given an input text buffer data pointer, parses a single token into the variable token and returns the new
	//  reading position
	virtual const char* ParseFile(const char* data, char* token, int maxlen) = 0;
	virtual bool				CopyLocalFile(const char* source, const char* destination) = 0;

	// Gets the dimensions of the game window
	virtual void				GetScreenSize(int& width, int& height) = 0;

	// Forwards szCmdString to the server, sent reliably if bReliable is set
	virtual void				ServerCmd(const char* szCmdString, bool bReliable = true) = 0;
	// Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
	// Note: Calls to this are checked against FCVAR_CLIENTCMD_CAN_EXECUTE (if that bit is not set, then this function can't change it).
	//       Call ClientCmd_Unrestricted to have access to FCVAR_CLIENTCMD_CAN_EXECUTE vars.
	virtual void				ClientCmd(const char* szCmdString) = 0;

	// Fill in the player info structure for the specified player index (name, model, etc.)
	virtual bool				GetPlayerInfo(int ent_num, player_info_t* pinfo) = 0;

	// Retrieve the player entity number for a specified userID
	virtual int					GetPlayerForUserID(int userID) = 0;

	// Retrieves text message system information for the specified message by name
	virtual void* TextMessageGet(const char* pName) = 0;

	// Returns true if the console is visible
	virtual bool				Con_IsVisible(void) = 0;

	// Get the entity index of the local player
	virtual int					GetLocalPlayer(void) = 0;

	// Client DLL is hooking a model, loads the model into memory and returns  pointer to the model_t
	virtual const model_t* LoadModel(const char* pName, bool bProp = false) = 0;

	// Get the exact server timesstamp ( server time ) from the last message received from the server
	virtual float				GetLastTimeStamp(void) = 0;

	// Given a CAudioSource (opaque pointer), retrieve the underlying CSentence object ( stores the words, phonemes, and close
	//  captioning data )
	virtual void* GetSentence(void* pAudioSource) = 0;
	// Given a CAudioSource, determines the length of the underlying audio file (.wav, .mp3, etc.)
	virtual float				GetSentenceLength(void* pAudioSource) = 0;
	// Returns true if the sound is streaming off of the hard disk (instead of being memory resident)
	virtual bool				IsStreaming(void* pAudioSource) const = 0;

	// Copy current view orientation into va
	virtual void				GetViewAngles(vec3_t va) = 0;
	// Set current view orientation from va
	virtual void				SetViewAngles(vec3_t va) = 0;

	// Retrieve the current game's maxclients setting
	virtual int					GetMaxClients(void) = 0;

	// Given the string pBinding which may be bound to a key, 
	//  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
	virtual	const char* Key_LookupBinding(const char* pBinding) = 0;

	// Given the name of the key "mouse1", "e", "tab", etc., return the string it is bound to "+jump", "impulse 50", etc.
	virtual const char* Key_BindingForKey(int code) = 0;

	// Bind a key
	virtual	void				Key_SetBinding(int code, const char* pBinding) = 0;

	// key trapping (for binding keys)
	virtual void				StartKeyTrapMode(void) = 0;
	virtual bool				CheckDoneKeyTrapping(int& code) = 0;

	// Returns true if the player is fully connected and active in game (i.e, not still loading)
	virtual bool				IsInGame(void) = 0;
	// Returns true if the player is connected, but not necessarily active in game (could still be loading)
	virtual bool				IsConnected(void) = 0;
	// Returns true if the loading plaque should be drawn
	virtual bool				IsDrawingLoadingImage(void) = 0;
	virtual void				HideLoadingPlaque(void) = 0;

	// Prints the formatted string to the notification area of the screen ( down the right hand edge
//  numbered lines starting at position 0
	virtual void				Con_NPrintf(int pos, const char* fmt, ...) = 0;

	// Similar to Con_NPrintf, but allows specifying custom text color and duration information
	virtual void				Con_NXPrintf(const void* info, const char* fmt, ...) = 0;

	// Is the specified world-space bounding box inside the view frustum?
	virtual int					IsBoxVisible(const vec3_t mins, const vec3_t maxs) = 0;

	// Is the specified world-space boudning box in the same PVS cluster as the view origin?
	virtual int					IsBoxInViewCluster(const vec3_t mins, const vec3_t maxs) = 0;

	// Returns true if the specified box is outside of the view frustum and should be culled
	virtual bool				CullBox(const vec3_t mins, const vec3_t maxs) = 0;

	// Allow the sound system to paint additional data (during lengthy rendering operations) to prevent stuttering sound.
	virtual void				Sound_ExtraUpdate(void) = 0;

	// Get the current game directory ( e.g., hl2, tf2, cstrike, hl1 )
	virtual const char* GetGameDirectory(void) = 0;

	// Get access to the world to screen transformation matrix
	virtual const vec_t* WorldToScreenMatrix() = 0;

	// Get the matrix to move a point from world space into view space
	// (translate and rotate so the camera is at the origin looking down X).
	virtual const vec_t* WorldToViewMatrix() = 0;


	// The .bsp file can have mod-specified data lumps. These APIs are for working with such game lumps.

	// Get mod-specified lump version id for the specified game data lump
	virtual int					GameLumpVersion(int lumpId) const = 0;
	// Get the raw size of the specified game data lump.
	virtual int					GameLumpSize(int lumpId) const = 0;
	// Loads a game lump off disk, writing the data into the buffer pointed to bye pBuffer
	// Returns false if the data can't be read or the destination buffer is too small
	virtual bool				LoadGameLump(int lumpId, void* pBuffer, int size) = 0;

	// Returns the number of leaves in the level
	virtual int					LevelLeafCount() const = 0;

	// Gets a way to perform spatial queries on the BSP tree
	virtual void* GetBSPTreeQuery() = 0;

	// Convert texlight to gamma...
	virtual void		LinearToGamma(float* linear, float* gamma) = 0;

	// Get the lightstyle value
	virtual float		LightStyleValue(int style) = 0;

	// Computes light due to dynamic lighting at a point
	// If the normal isn't specified, then it'll return the maximum lighting
	virtual void		ComputeDynamicLighting(const vec3_t pt, const vec3_t pNormal, vec3_t color) = 0;

	// Returns the color of the ambient light
	virtual void		GetAmbientLightColor(vec3_t color) = 0;

	// Returns the dx support level
	virtual int			GetDXSupportLevel() = 0;

	// GR - returns the HDR support status
	virtual bool        SupportsHDR() = 0;

	// Replace the engine's material system pointer.
	virtual void		Mat_Stub(void* pMatSys) = 0;

	// Get the name of the current map
	virtual void GetChapterName(char* pchBuff, int iMaxLength) = 0;
	virtual char const* GetLevelName(void) = 0;
	virtual char const* GetLevelNameShort(void) = 0;
	virtual char const* GetMapGroupName(void) = 0;

#if !defined( NO_VOICE )
	// Obtain access to the voice tweaking API
	virtual void* GetVoiceTweakAPI(void) = 0;
	virtual void SetVoiceCasterID(uint32 casterID) = 0;
#endif

	// Tell engine stats gathering system that the rendering frame is beginning/ending
	virtual void		EngineStats_BeginFrame(void) = 0;
	virtual void		EngineStats_EndFrame(void) = 0;

	// This tells the engine to fire any events (temp entity messages) that it has queued up this frame. 
	// It should only be called once per frame.
	virtual void		FireEvents() = 0;

	// Returns an area index if all the leaves are in the same area. If they span multple areas, then it returns -1.
	virtual int			GetLeavesArea(unsigned short* pLeaves, int nLeaves) = 0;

	// Returns true if the box touches the specified area's frustum.
	virtual bool		DoesBoxTouchAreaFrustum(const vec3_t mins, const vec3_t maxs, int iArea) = 0;
	virtual int			GetFrustumList(void** pList, int listMax) = 0;
	virtual bool		ShouldUseAreaFrustum(int area) = 0;

	// Sets the hearing origin (i.e., the origin and orientation of the listener so that the sound system can spatialize 
	//  sound appropriately ).
	virtual void		SetAudioState(const void* state) = 0;

	// Sentences / sentence groups
	virtual int			SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
	virtual int			SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int			SentenceIndexFromName(const char* pSentenceName) = 0;
	virtual const char* SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int			SentenceGroupIndexFromName(const char* pGroupName) = 0;
	virtual const char* SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float		SentenceLength(int sentenceIndex) = 0;



};
#endif