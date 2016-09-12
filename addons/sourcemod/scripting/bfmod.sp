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
  initPerkMenu();
  initPerkDescMenu();
  BFMenu_init();
  BFTop_init();
  initShop();
  initEvent();
  initHudSprite();
  ExpEvent_init();
  HeadSprite_init();
  initHud();
  initTag();
  AutoExecConfig(true, "bfmod");
}

public void OnMapStart() {
  precacheRankHudSprite();
  BFTop_onMapStart();
}

public void OnClientPutInServer(int client) {
  loadClientData(client);
  createHud(client);
  setRankTag(client);
  hookPerkClient(client);
}

public void OnClientDisconnect(int client) {
  PrintToServer("client disc %d", client);
  //saveClientData(client);
  removeHud(client);
  unhookPerkClient(client);
}

void onLvlUp(int client, int lvl) {
  showHudSprite(client, rankSprite[lvl]);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_promote_rank", rankName[lvl]);
}

bool IsValidClient(int client) {
    if (!(1 <= client <= MaxClients) || !IsClientInGame(client))
        return false;
    return true;
}
