#pragma once

class ccombobox { // this class only handles all the open checks for the combo boxes, nothing more
public:
    // Anti aim
    bool aaY_opend;
    bool aaX_opend;
    bool FaaY_opend;
    // Chams
    bool hands_opend;
    bool weapons_opend;
    bool players_opend;
    // Menu
    bool colors_opend;
    // For aa corrections
    bool playerlist_opend_x[64];
    bool playerlist_opend_y[64];
    // For text input
    bool misc_clantag, misc_name, misc_changename;
};

class cVariables : public ccombobox {
public: 
    bool menu               = false; // Disables menu from displaying on injection, set to true if you want the menu to display on injection.
    int  buttonPadding      = 24;
    int  playerTab          = 0;
    int  inputIndex         = 0;
    class cAimbot {
    public:  
        bool enabled    = false;        // Enable
        bool silent     = false;        // Silent Aim ob
        int  fov         = 20;          // Aimbot Fov
        int  hitbox      = 0;           // Hitbox
        int  pointscale  = 0;           // Pointscale
        bool trigger    = false;         // Will shoot when an enemy is in your crosshair
        bool prediction = false;        // Player prediction
        bool autowall   = false;        // Shoots through walls if calulated damage is higher than set amount
        int  mindmg      = 20;          // Autowall min damage
        bool hitscan    = false;        // Hitscan
        bool autoshoot  = false;        // Shoots for you
        bool autoscope  = false;        // Autoscope
        bool autopistol = false;        // Pistol is like AK
        bool autocrouch = false;        // Crouch when something is in fov
        bool rcs        = false;        // Recoil control system
        int rcsf        = 0;            // Recoil control

    }aimbot;
    
    class cVisuals
    {
    public:
        
        bool enabled    = false;        // Enable
        bool enemyonly  = false;        // Enemy only
        bool visonly    = false;        // Visual only
        bool box        = false;        // Box ESP
        bool name       = false;        // Name ESP
        bool health     = false;        // Health Bar
        bool healthtext = false;        // Health Text
        bool armour     = false;        // Armour Bar
        bool skeleton   = false;        // Skeleton ESP
        bool snapline   = false;        // Snaplines obv
        bool rcrosshair = false;        // Recoil Crosshair (Shows but doesn't move)
        bool scrosshair = false;        // Sniper Crosshair

        // Chams
        bool chams      = false;        // Player Chams
        bool handchams  = false;         // Handchams obv
        bool weaponchams= false;         // Weapon chams obv
        int weaponType  = 1;            // Weapon Type 0 - Lit 1 - Texture 2 - Wireframe
        int handsType   = 1;            // Hand   Type 0 - Lit 1 - Texture 2 - Wireframe
        int playersType = 0;            // Player Type 0 - Lit 1 - Texture
    }visuals;
    
    class cMisc {
    public:
        bool antiuntrust    = true;     // Anti Untrust KEEP ON AT ALL TIMES UNLESS YOU KNOW WHAT YOURE DOING
        bool norecoil       = false;    // Basically RCS without slider
        bool novisual       = false;    // No visual recoil ofc
        bool bhop           = false;    // BunnyHop
        bool autostrafe     = false;    // Strafes for you ofc
        bool cstrafe        = false;    // Circle strafes
        bool airstuck       = false;    // Airstuck
        bool fovt           = false;    // Fov Changer Enabled
        int fov             = 10;       // FOV changer
        bool clantag        = false;    // Clantag changer
        bool showrank       = false;     // Show everyboys rank in MM
        bool spammer        = false;    // Chat spammer
        bool noflash        = false;     // Disabled flashbangs
        int flashalpha      = 0.f;      // How "flashed" you are
    
        bool worldpaint     = false;    // World Paint
        bool changesky      = false;    // Changes Sky
        bool antiscreenshot = false;    // Anti screenshot
        bool showspectators = false;    // Spectator List
        // AntiAim
        bool antiaim        = false;    // Anti aims / "spinbot"
        bool thirdpersonmode= false;    // Thirdperson
        bool attargets      = false;    // AtTargets ofc
        bool fakeaa         = false;    // Fake anti aim
        int aaY             = 0;        // Y AntiAim
        int aaX             = 0;        // X AntiAim
        int FaaY            = 0;        // Y Fake anti aim (Thnx Ziwiiz)
        int customaa        = 0;        // Custom Pitch
        int fakeyaw         = 180;      // Fake Y
        int realyaw         = 20;       // Real Y

    }misc;

    class cColors {
    public:
        int combo   = 0;
        // Player Chams
        Color ctchams;
        Color tchams;
        Color ctchams_ign;
        Color tchams_ign;
        // Box
        Color tbox;
        Color tbox_ign;
        Color ctbox;
        Color ctbox_ign;
        // Other
        Color hands;
        Color weapon;
    }colors;
};

struct Corrections {
    float x, y;
    bool whitelist;
    bool resolved;
    bool baim;
    int dropdown_x = 0;
    int dropdown_y = 0;
};

extern cVariables vars;
extern Corrections gCorrections[64];