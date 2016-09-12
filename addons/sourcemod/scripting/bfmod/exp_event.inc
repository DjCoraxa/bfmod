ConVar cvarKillExp;
ConVar cvarAssistExp;
ConVar cvarHsBonusExp;
ConVar cvarBombPlantExp;
ConVar cvarBombDefuseExp;
ConVar cvarBombExpMinPlayer;
ConVar cvarRoundWinExp;

void ExpEvent_init() {
  cvarKillExp = CreateConVar("bfmod_kill_exp", "100", "Exp amount from kill");
  cvarAssistExp = CreateConVar("bfmod_assist_exp", "25", "Exp amount from assist");
  cvarHsBonusExp = CreateConVar("bfmod_hs_exp", "30", "Exp amount from hs");
  cvarBombPlantExp = CreateConVar("bfmod_bomb_plant_exp", "300", "Exp amount from bomb plant");
  cvarBombDefuseExp = CreateConVar("bfmod_bomb_defuse_exp", "300", "Exp amount from bomb defuse");
  cvarRoundWinExp = CreateConVar("bfmod_round_win_exp", "100", "Exp amount from win round");
  cvarBombExpMinPlayer = CreateConVar("bfmod_bomb_exp_min_players", "4", "Min players for exp from bomb");
}

void ExpEvent_eventOnPlayerDeath(int victim, int attacker, int assister, char[] weapon, bool hs) {
  if (IsValidClient(assister)) {
    ExpEvent_giveExpForAssist(assister);
  }

  if (IsValidClient(attacker) && attacker != victim) {
    ExpEvent_giveExpForKill(attacker, victim, weapon);

    if (hs) {
      ExpEvent_giveBonusExpForHS(attacker);
    }
  }
}

void ExpEvent_eventOnBombPlant(int client) {
  if (IsValidClient(client)) {
    ExpEvent_giveExpForBombPlant(client);
  }
}

void ExpEvent_eventOnBombDefuse(int client) {
  if (IsValidClient(client)) {
    ExpEvent_giveExpForBombDefuse(client);
  }
}

void ExpEvent_eventOnRoundEnd(int winnerTeam) {
  for (int client = 1; client <= MaxClients; client++) {
    if(IsValidClient(client) && GetClientTeam(client) == winnerTeam) {
      giveExpForWinRound(client);
    }
  }
}

void ExpEvent_giveExpForKill(int attacker, int victim, char[] weapon) {
  int exp = ClientRank_giveExp(attacker, cvarKillExp.IntValue);
  char weaponAlias[64];

  WeaponName_get(weapon, weaponAlias, sizeof(weaponAlias));
  CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_kill", exp);
  Hud_print(attacker, "[%s] <font color='#DB9773'>%N</font> +%d", weaponAlias, victim, exp);
  ClientRank_checkLvl(attacker);
}

void ExpEvent_giveBonusExpForHS(int attacker) {
  int exp = ClientRank_giveExp(attacker, cvarHsBonusExp.IntValue);
  CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_bonus_hs", exp);
  Hud_print(attacker, "HS bonus +%d", exp);
  ClientRank_checkLvl(attacker);
}

void ExpEvent_giveExpForAssist(int assister) {
  int exp = ClientRank_giveExp(assister, cvarAssistExp.IntValue);
  CPrintToChat(assister, "%s %t", MOD_NAME, "bfmod_exp_assist", exp);
  Hud_print(assister, "Assist +%d", exp)
  ClientRank_checkLvl(assister);
}

void ExpEvent_giveExpForBombPlant(int client) {
  if (GetClientCount(true) < cvarBombExpMinPlayer.IntValue) {
    return;
  }

  int exp = ClientRank_giveExp(client, cvarBombPlantExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_bomb_plant", exp);
  Hud_print(client, "Plant bomb +%d", exp);
  ClientRank_checkLvl(client);
}

void ExpEvent_giveExpForBombDefuse(int client) {
  if (GetClientCount(true) < cvarBombExpMinPlayer.IntValue) {
    return;
  }

  int exp = ClientRank_giveExp(client, cvarBombDefuseExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_bomb_defuse", exp);
  Hud_print(client, "Defuse bomb +%d", exp);
  ClientRank_checkLvl(client);
}

void giveExpForWinRound(int client) {
  int exp = ClientRank_giveExp(client, cvarRoundWinExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_round_win", exp);
  Hud_print(client, "Won round +%d", exp);
  ClientRank_checkLvl(client);
}
