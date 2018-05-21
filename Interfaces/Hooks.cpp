#include "../main.h"

void InitializeInterfaces() {
    pSurface        = GetInterface<ISurface>("./bin/osx64/vguimatsurface.dylib", "VGUI_Surface");
    pPanel          = GetInterface<IPanel>("./bin/osx64/vgui2.dylib", "VGUI_Panel");
    pEffects        = GetInterface<CEffects>("./bin/osx64/engine.dylib", "VEngineEffects"); 
    pCvar           = GetInterface<ICvar>("./bin/osx64/materialsystem.dylib", "VEngineCvar");
    pClient         = GetInterface<IBaseClientDLL>("./csgo/bin/osx64/client.dylib", "VClient");
    pEngine         = GetInterface<IEngineClient>("./bin/osx64/engine.dylib", "VEngineClient");
    pEntList        = GetInterface<IClientEntityList>("./csgo/bin/osx64/client.dylib", "VClientEntityList");
    pOverlay        = GetInterface<IVDebugOverlay>("./bin/osx64/engine.dylib", "VDebugOverlay");
    pEngineTrace    = GetInterface<IEngineTrace>("./bin/osx64/engine.dylib", "EngineTraceClient");
    pModelInfo      = GetInterface<IVModelInfo>("./bin/osx64/engine.dylib", "VModelInfoClient");
    pInputSystem    = GetInterface<IInputSystem>("./bin/osx64/inputsystem.dylib", "InputSystemVersion");
    pModelRender    = GetInterface<IVModelRender>("./bin/osx64/engine.dylib", "VEngineModel");
    pMatSystem      = GetInterface<IMaterialSystem>("./bin/osx64/materialsystem.dylib", "VMaterialSystem");
    pPrediction     = GetInterface<IPrediction>("./csgo/bin/osx64/client.dylib", "VClientPrediction");
    pGameMovement   = GetInterface<IGameMovement>("./csgo/bin/osx64/client.dylib", "GameMovement");
    pPhysics        = GetInterface<IPhysicsSurfaceProps>("./bin/osx64/vphysics.dylib", "VPhysicsSurfaceProps");
}

void ProtectAddr(void* addr, int prot) {
    long pagesize = sysconf(_SC_PAGESIZE);
    void* address = (void *)((long)(uintptr_t)addr & ~(pagesize - 1));
    mprotect(address, sizeof(address), prot);
}

void InitializeVMTs() {
    uintptr_t findClientMode = CPatternScanner::Instance()->GetPointer("client.dylib",(unsigned char*)CLIENTMODE_SIG, CLIENTMODE_MASK, 0xF) + 0x4;
    uintptr_t findGlobalVars = CPatternScanner::Instance()->GetPointer("client.dylib", (unsigned char*)GLOBALS_SIG, GLOBALS_MASK, 0x3) + 0x4;
    uintptr_t findRankReveal = CPatternScanner::Instance()->GetPointer("client.dylib",(unsigned char*)RANKREVEAL_SIG, RANKREVEAL_MASK, 0x15) + 0x4;
    uintptr_t findClanTag    = CPatternScanner::Instance()->GetPointer("engine.dylib", (unsigned char*) CLANTAG_SIG, CLANTAG_MASK, 0xB) + 0x4;
    uintptr_t booladdr       = CPatternScanner::Instance()->GetProcedure("engine.dylib", (unsigned char*)SENDPACKET_SIG, SENDPACKET_MASK, 0x1) + 0x2;

    bSendPacket = reinterpret_cast<bool*>(booladdr);
    ProtectAddr(bSendPacket, PROT_READ | PROT_WRITE | PROT_EXEC);

    void* handle = dlopen("./csgo/bin/osx64/client.dylib", RTLD_NOLOAD | RTLD_NOW);
    RandomInt       = reinterpret_cast<RandomIntFn>(dlsym(handle, "RandomInt"));
    dlclose(handle);
    
    SetClanTag  = reinterpret_cast<SendClanTagFn>(findClanTag);
    pClientMode = reinterpret_cast<IClientMode*>(findClientMode);
    pGlobals    = *reinterpret_cast<CGlobalVarsBase**>(findGlobalVars);
    MsgFunc_ServerRankRevealAll = reinterpret_cast<MsgFunc_ServerRankRevealAllFn>(findRankReveal);

    paintVMT        = new VMT(pPanel);
    createmoveVMT   = new VMT(pClientMode);
    clientVMT       = new VMT(pClient);
    modelVMT        = new VMT(pModelRender);
    predVMT         = new VMT(pPrediction);
}

void InitializeHooks() {
    paintVMT->HookVM((void*)hkPaintTraverse, 42);
    paintVMT->ApplyVMT();
        
    createmoveVMT->HookVM((void*)hkCreateMove, 25);
    createmoveVMT->HookVM((void*)hkOverrideView, 19);
    createmoveVMT->ApplyVMT();
    
    clientVMT->HookVM((void*)hkKeyEvent, 20);
    clientVMT->HookVM((void*)hkFrameStage, 36);
    clientVMT->ApplyVMT();
    
    modelVMT->HookVM((void*)hkDrawModelExecute, 21);
    modelVMT->ApplyVMT();
    
    predVMT->HookVM((void*)hkRunCommand, 20);
    predVMT->ApplyVMT();
}

void Unhook() {
    pEngine->ExecuteClientCmd("cl_mouseenable 1");
    paintVMT        ->ReleaseVMT();
    createmoveVMT   ->ReleaseVMT();
    clientVMT       ->ReleaseVMT();
    modelVMT        ->ReleaseVMT();
    predVMT         ->ReleaseVMT();
    
    delete paintVMT;
    delete createmoveVMT;
    delete clientVMT;
    delete modelVMT;
    delete predVMT;
}

void UpdateResolver() {
    OldProxy_X = (RecvVarProxyFn)NetVarManager::HookProp("DT_CSPlayer", "m_angEyeAngles[0]", FixPitch);
    OldProxy_Y = (RecvVarProxyFn)NetVarManager::HookProp("DT_CSPlayer", "m_angEyeAngles[1]", FixYaw);
}

void PrintInfo() {
    pCvar->ConsoleColorPrintf(Color::Green(),           "Barbossa version 1.3\n");
    pCvar->ConsoleColorPrintf(Color::White(),           "Coded by : \n");
    pCvar->ConsoleColorPrintf(Color::White(),           "ViKiNG\n");
    pCvar->ConsoleColorPrintf(Color::White(),           "Improved by :\n");
    pCvar->ConsoleColorPrintf(Color::Pink(),            "- pwned\n"); 
    pCvar->ConsoleColorPrintf(Color::Red(),             "- Warlauke\n");
    pCvar->ConsoleColorPrintf(Color::Blue(),            "- Bypass\n");
    pCvar->ConsoleColorPrintf(Color::Yellow(),          "- Ziwiiz\n");
}

