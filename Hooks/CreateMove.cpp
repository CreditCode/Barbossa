#include "../main.h"
#include "../Hacks/aimbot.h"
#include "../Hacks/antiaim.h"
#include "../Hacks/autoshoot.h"
#include "../Hacks/bhop.h"
#include "../Hacks/clantag.h"
#include "../Hacks/spammer.h"
#include "../Hacks/triggerbot.h"

Vector tpangles;
bool* bSendPacket = nullptr;

void RecoilControl(C_BaseEntity* local, CUserCmd* cmd) {
    if(!vars.misc.norecoil && !vars.aimbot.rcs)
        return;
    
    Vector punch = local->GetPunchAngles() * 2.f;
    
    if(vars.misc.norecoil) {
        if(cmd->buttons & IN_ATTACK) {
            
            cmd->viewangles.x -= punch.x;
            cmd->viewangles.y -= punch.y;
        }
        return;
    }
    if(vars.aimbot.rcs) {
        if(cmd->buttons & IN_ATTACK) {
            cmd->viewangles.x -= punch.x * (2.f / 100.f * (vars.aimbot.rcsf / 2));
            cmd->viewangles.y -= punch.y * (2.f / 100.f * (vars.aimbot.rcsf / 2));
        }
        return;
    }
}

string GetLocalName() {
    player_info_t localInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &localInfo);
    return localInfo.name;
}

void ChangeName(const char* szName) {
    ConVar* cvar_name = pCvar->FindVar("name");
    *(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
    cvar_name->SetValue(szName);
}

void showranks(CUserCmd* cmd) {
    if(!vars.misc.showrank)
        return;
    if(!(cmd->buttons & IN_SCORE))
        return;
    
    float input[3] = { 0.f };
    MsgFunc_ServerRankRevealAll(input);
}

void hacks(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, Vector& vOldAngles, bool& sendpacket) {
    DoAutoStrafe(cmd, local);
    DoBhop(cmd, local);
    DoAim(cmd, local, weapon, sendpacket);
    DoAntiaim(cmd, local, weapon, sendpacket);
    ContinuousPistols(cmd, weapon); // will continously fire pistol when trigger is  held
    showranks(cmd);                 // Show all ranks
    DoTrigger(cmd);                 // Add triggerbot
    clantag();                      // Clantag
    DoSpammer();                    // Spammer
    RecoilControl(local, cmd);
    if(draw->m_szChangedValue[2].length() > 0)                      // Name Changer
        ChangeName(draw->m_szChangedValue[2].c_str());    
    if(draw->m_szChangedValue[3].length() > 0 && vars.misc.clantag) // Clantag Changer
        SetClanTag(draw->m_szChangedValue[3].c_str(), "Barbossa");
    
}

bool bOnce = false;
bool SendPacket = true;
bool hkCreateMove(void* thisptr, float flSampleInput, CUserCmd* cmd) {
    createmoveVMT->GetOriginalMethod<tCreateMove>(25)(thisptr, flSampleInput, cmd);
    if(!cmd->command_number)
        return true;
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!local)
        return false;
    if(local->GetLifeState() != 0)
        return false;
    if(local->GetHealth() < 1)
        return false;
    if(local->GetDormant())
        return false;
    if(bSendPacket == nullptr)
        return false;
    
    if(!bOnce) {
        if(draw->m_szCurrentString[2].empty()) {
            draw->m_szCurrentString[2] = GetLocalName();
        }
        bOnce = true;
    }
    
    C_BaseCombatWeapon* weapon = GetActiveWeapon(local);
    
    if(!weapon)
        return false;
    
    SendPacket = true;
    *bSendPacket = SendPacket;
    
    Vector vOldAngles = cmd->viewangles;
    Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
    Vector qAimAngles;
    float forward = cmd->forwardmove;
    float sidemove = cmd->sidemove;
    float upmove = cmd->upmove;
    
    if(pEngine->IsInGame() && pEngine->IsConnected()) {
        hacks(cmd, local, weapon, vOldAngles, *bSendPacket); 
        if(pInputSystem->IsButtonDown(KEY_N))
            *bSendPacket = false;
        else
            *bSendPacket = true;
        
        FixMovement(vOldAngles, cmd);
        ClampMoves(forward, sidemove, upmove);
        
        if(vars.misc.antiuntrust) {
            cmd->viewangles.ClampAngles();
        }
        if(*bSendPacket)
            tpangles = cmd->viewangles;
    }
    return false;
}