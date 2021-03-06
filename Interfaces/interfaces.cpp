#include "../main.h"

// CLEAN CODE > ALL

ISurface*           pSurface        = nullptr;
CEffects*           pEffects        = nullptr;
IPanel*             pPanel          = nullptr;
ICvar*              pCvar           = nullptr;
IBaseClientDLL*     pClient         = nullptr;
IClientEntityList*  pEntList        = nullptr;
IVDebugOverlay*     pOverlay        = nullptr;
IEngineClient*      pEngine         = nullptr;
IVModelInfo*        pModelInfo      = nullptr;
IEngineTrace*       pEngineTrace    = nullptr;
IClientMode*        pClientMode     = nullptr;
CGlobalVarsBase*    pGlobals        = nullptr;
IInputSystem*       pInputSystem    = nullptr;
CInput*             pInput          = nullptr;
IMaterialSystem*    pMatSystem      = nullptr;
IVModelRender*      pModelRender    = nullptr;
IPrediction*        pPrediction     = nullptr;
IMoveHelper*        pMoveHelper     = nullptr;
IGameMovement*      pGameMovement   = nullptr;
IPhysicsSurfaceProps* pPhysics      = nullptr;

SendClanTagFn       SetClanTag;
RandomIntFn         RandomInt;
MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;


VMT* paintVMT;
VMT* createmoveVMT;
VMT* clientVMT;
VMT* modelVMT;
VMT* predVMT;
VMT* materialVMT;

