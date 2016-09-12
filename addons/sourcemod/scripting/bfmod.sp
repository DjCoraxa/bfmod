#include <sourcemod>
#include <sdktools>
#include <cstrike>
#include <multicolors>
#include <sdkhooks>

char MOD_NAME[] = "{darkred}[BFMod]";

#include "bfmod/rank"
#include "bfmod/shop"
#include "bfmod/sql"
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

public void OnPluginStart() {
  LoadTranslations("bfmod.phrases.txt");
  sqlInit();
  BonusMenu_init();
  PerkMenu_init();
  PerkDescMenu_init();
  BFMenu_init();
  BFTop_init();
  initShop();
  initEvent();
  HudSprite_init();
  ExpEvent_init();
  HeadSprite_init();
  Hud_init();
  initTag();
  AutoExecConfig(true, "bfmod");
}

public void OnMapStart() {
  precacheRankHudSprite();
  BFTop_onMapStart();
}

public void OnClientPutInServer(int client) {
  loadClientData(client);
  Hud_create(client);
  setRankTag(client);
  Perk_hook(client);
}

public void OnClientDisconnect(int client) {
  PrintToServer("client disc %d", client);
  //saveClientData(client);
  Hud_remove(client);
  Perk_unhook(client);
}

void onLvlUp(int client, int lvl) {
  HudSprite_show(client, rankSprite[lvl]);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_promote_rank", rankName[lvl]);
}

bool IsValidClient(int client) {
    if (!(1 <= client <= MaxClients) || !IsClientInGame(client))
        return false;
    return true;
}
