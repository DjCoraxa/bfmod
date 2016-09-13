#include <sourcemod>
#include <sdktools>
#include <cstrike>
#include <multicolors>
#include <sdkhooks>

char MOD_NAME[] = "{darkred}[BFMod]";

#define TEST_ENABLE

#include "bfmod/rank"
#include "bfmod/client_rank"
#include "bfmod/shop"
#include "bfmod/ribbon"
#include "bfmod/sql"
#include "bfmod/weapon_name"
#include "bfmod/exp_event"
#include "bfmod/hud_sprite"
#include "bfmod/tag"
#include "bfmod/spawn_bonus"
#include "bfmod/bonus_menu"
#include "bfmod/perk"
#include "bfmod/perk_menu"
#include "bfmod/perk_descmenu"
#include "bfmod/head_sprite"
#include "bfmod/bftop"

#include "bfmod/bfmenu"
#include "bfmod/hud"
#include "bfmod/event"

#if defined TEST_ENABLE
  #include "bfmodtest/hud_sprite_stack"
  #include "bfmodtest/ribbon"
#endif

public void OnPluginStart() {
  LoadTranslations("bfmod.phrases.txt");
  Rank_init();
  Sql_init();
  BonusMenu_init();
  PerkMenu_init();
  PerkDescMenu_init();
  BFMenu_init();
  BFTop_init();
  Shop_init();
  Event_init();
  HudSprite_init();
  ExpEvent_init();
  HeadSprite_init();
  Hud_init();
  Tag_init();
  WeaponName_init();
  Ribbon_init();
  AutoExecConfig(true, "bfmod");

  #if defined TEST_ENABLE
    TestHudSpriteStack_init();
    TestRibbon_init();
  #endif
}

public void OnMapStart() {
  Rank_onMapStart();
  BFTop_onMapStart();
}

public void OnClientPutInServer(int client) {
  Sql_onClientPutInServer(client);
  Hud_onClientPutInServer(client);
  Tag_onClientPutInServer(client);
  Perk_onClientPutInServer(client);
}

public void OnClientDisconnect(int client) {
  Hud_onClientDisconnect(client);
  Perk_onClientDisconnect(client);
}

void onLvlUp(int client, int lvl) {
  HudSprite_onLvlUp(client, lvl);
  ClientRank_onLvlUp(client, lvl);
}

bool IsValidClient(int client) {
    if (!(1 <= client <= MaxClients) || !IsClientInGame(client))
        return false;
    return true;
}
