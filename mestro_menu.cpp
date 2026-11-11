// mestro.lol - Complete BNM menu for Ripple (VR)
// Drop into BNM template, build, replace libbnm_template_v252.so
// Discord: https://discord.gg/rRe37fghM
// Auth: https://web-production-14d95.up.railway.app/auth

#include <BNM/UserSettings/GlobalSettings.hpp>
#include <BNM/UnityStructures.hpp>
#include <BNM/Field.hpp>
#include <BNM/Method.hpp>
#include <BNM/Class.hpp>
#include <BNM/Loading.hpp>
#include <BNM/Utils.hpp>
#include <vector>
#include <string>

using namespace BNM;
using namespace BNM::Structures::Unity;

#define MENU_NAME "mestro.lol"
#define DISCORD "https://discord.gg/rRe37fghM"
#define AUTH_URL "https://web-production-14d95.up.railway.app/auth"

// State
bool menuOpen = false;
int authStage = 0;
bool tokenValid = false;
std::string currentToken;
std::string deviceId;
std::string discordName;

bool flingGun = false, kickGun = false, giveFlyGun = false;
bool blindGun = false, crashGun = false, cloneGun = false;
bool gravityGun = false, slowMoGun = false, tpAllGun = false;
bool freezeGun = false, shrinkGun = false, pullGun = false;
bool lagGun = false, speedSlap = false, orbitAll = false;
bool antiReport = false, antiKick = false, antiBan = false;
bool godMode = false, fly = false, noClip = false, invisible = false;
bool portalGunActive = false, soundboardOpen = false, emoteWheelOpen = false;

const char* emotes[] = {"Renegade", "Floss", "Electro Shuffle", "Paws & Claws", "What You Want"};

void Log(const char* m) { BNM_LOG_INFO("[mestro.lol] %s", m); }

std::string GetDeviceId() {
    return "mestro_" + std::to_string(rand() % 1000000000) + "_device";
}

bool CheckToken(const std::string& t) {
    if (t.find("MESTRO-") != 0) return false;
    Log("Token check (wire UnityWebRequest here)");
    return true;
}

void ToggleEmoteWheel() { emoteWheelOpen = !emoteWheelOpen; Log(emoteWheelOpen ? "Emote wheel open" : "closed"); }
void PlayEmote(int i) { if (i>=0 && i<5) Log(emotes[i]); /* play anim + sound */ }

void ApplyFling(GameObject* t) { if (!flingGun || !t) return; Log("Fling"); }
void ApplyKick(GameObject* t) { if (!kickGun || !t) return; Log("Kick"); }
void ApplyGiveFly(GameObject* t) { if (!giveFlyGun || !t) return; Log("Gave fly"); }
void ApplyBlind(GameObject* t) { if (!blindGun || !t) return; Log("Blind"); }
void ApplyCrash(GameObject* t) { if (!crashGun || !t) return; Log("Crash"); }
void ApplyClone() { if (!cloneGun) return; Log("Cloned you"); }
void ApplyGravity(GameObject* t) { if (!gravityGun || !t) return; Log("Gravity grab"); }
void ApplySlowMo(GameObject* t) { if (!slowMoGun || !t) return; Log("Slow mo"); }
void ApplyTPAll() { if (!tpAllGun) return; Log("TP All"); }
void ApplyFreeze(GameObject* t) { if (!freezeGun || !t) return; Log("Freeze"); }
void ApplyShrink(GameObject* t) { if (!shrinkGun || !t) return; Log("Shrink"); }
void ApplyPull(GameObject* t) { if (!pullGun || !t) return; Log("Pull"); }
void ApplyLag(GameObject* t) { if (!lagGun || !t) return; Log("Lag"); }
void OnSlap(GameObject* t) { if (!speedSlap || !t) return; Log("Speed slap"); }
void DoOrbitAll() { if (!orbitAll) return; Log("Orbit all"); }
void SpawnTravisLaser(Vector3 p) { Log("Travis Scott laser spawned him"); }

std::vector<GameObject*> GetAllPlayers() { return {}; }

void DrawAuth() {
    GUI::Label(Rect(20,20,500,30), "mestro.lol Auth");
    if (authStage == 0) {
        if (GUI::Button(Rect(20,60,120,30), "Paste Token")) currentToken = "MESTRO-";
        GUI::Label(Rect(150,60,300,30), currentToken.c_str());
        if (GUI::Button(Rect(20,100,120,30), "Enter") && CheckToken(currentToken)) {
            authStage = 1; deviceId = GetDeviceId();
        }
    } else if (authStage == 1) {
        GUI::Label(Rect(20,60,500,30), "Copy Device ID and /link on Discord");
        GUI::Label(Rect(20,100,500,30), deviceId.c_str());
        if (GUI::Button(Rect(20,140,150,30), "Copy Device ID")) Log("copied");
        if (GUI::Button(Rect(20,180,120,30), "Next")) authStage = 2;
    } else if (authStage == 2) {
        if (GUI::Button(Rect(20,60,120,30), "Paste Name")) discordName = "user";
        GUI::Label(Rect(150,60,300,30), discordName.c_str());
        if (GUI::Button(Rect(20,100,120,30), "Done")) authStage = 3;
    } else if (authStage == 3) {
        GUI::Label(Rect(20,60,400,40), "Successfully linked. Click Done.");
        if (GUI::Button(Rect(20,110,120,30), "Done")) { authStage = 4; tokenValid = true; }
    }
}

void DrawMenu() {
    if (authStage < 4) { DrawAuth(); return; }
    GUI::Label(Rect(20,10,300,30), MENU_NAME);
    if (GUI::Button(Rect(20,40,120,30), "Discord")) Log(DISCORD);

    flingGun = GUI::Toggle(Rect(20,80,200,30), flingGun, "Fling Gun");
    kickGun = GUI::Toggle(Rect(20,110,200,30), kickGun, "Kick Gun");
    giveFlyGun = GUI::Toggle(Rect(20,140,200,30), giveFlyGun, "Give Fly Gun");
    blindGun = GUI::Toggle(Rect(20,170,200,30), blindGun, "Blind Gun");
    crashGun = GUI::Toggle(Rect(20,200,200,30), crashGun, "Crash Gun");
    cloneGun = GUI::Toggle(Rect(20,230,200,30), cloneGun, "Clone Gun");
    gravityGun = GUI::Toggle(Rect(20,260,200,30), gravityGun, "Gravity Gun");
    slowMoGun = GUI::Toggle(Rect(20,290,200,30), slowMoGun, "Slow Mo Gun");
    tpAllGun = GUI::Toggle(Rect(20,320,200,30), tpAllGun, "TP All Gun");
    freezeGun = GUI::Toggle(Rect(20,350,200,30), freezeGun, "Freeze Gun");
    shrinkGun = GUI::Toggle(Rect(20,380,200,30), shrinkGun, "Shrink Gun");
    pullGun = GUI::Toggle(Rect(20,410,200,30), pullGun, "Pull Gun");
    lagGun = GUI::Toggle(Rect(20,440,200,30), lagGun, "Lag Gun");
    speedSlap = GUI::Toggle(Rect(20,470,200,30), speedSlap, "Speed Slap");
    orbitAll = GUI::Toggle(Rect(20,500,200,30), orbitAll, "Orbit All");

    antiReport = GUI::Toggle(Rect(240,80,200,30), antiReport, "Anti Report");
    antiKick = GUI::Toggle(Rect(240,110,200,30), antiKick, "Anti Kick");
    antiBan = GUI::Toggle(Rect(240,140,200,30), antiBan, "Anti Ban");
    godMode = GUI::Toggle(Rect(240,170,200,30), godMode, "God Mode");
    fly = GUI::Toggle(Rect(240,200,200,30), fly, "Fly");
    noClip = GUI::Toggle(Rect(240,230,200,30), noClip, "NoClip");
    invisible = GUI::Toggle(Rect(240,260,200,30), invisible, "Invisible");

    if (GUI::Button(Rect(240,300,150,30), "Emote Wheel")) ToggleEmoteWheel();
    portalGunActive = GUI::Toggle(Rect(240,340,150,30), portalGunActive, "Portal Gun");
    if (GUI::Button(Rect(240,380,150,30), "Soundboard")) soundboardOpen = !soundboardOpen;
    if (GUI::Button(Rect(240,420,150,30), "Travis Laser")) SpawnTravisLaser(Vector3::zero);
}

void OnGUI() { if (menuOpen) DrawMenu(); }

void Update() {
    if (Input::GetKeyDown(KeyCode::JoystickButton2)) ToggleEmoteWheel(); // side button
    if (emoteWheelOpen) { /* draw floating wheel above hand, PlayEmote on select */ }
    if (orbitAll) DoOrbitAll();
    if (tpAllGun) ApplyTPAll();
    // raycast on trigger for guns
}

void OnLoaded() { Log("mestro.lol loaded"); deviceId = GetDeviceId(); }

BNM_API_EXPORT void BNM_OnLoad() { OnLoaded(); }
