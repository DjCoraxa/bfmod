static ConVar cvarKillExp;
static ConVar cvarAssistExp;
static ConVar cvarHsBonusExp;
static ConVar cvarBombPlantExp;
static ConVar cvarBombDefuseExp;
static ConVar cvarBombExpMinPlayer;
static ConVar cvarRoundWinExp;

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
  int exp = ClientRank_giveExpWithMSG(attacker, cvarKillExp.IntValue, "enemy kill");

  char weaponAlias[64];
  WeaponName_get(weapon, weaponAlias, sizeof(weaponAlias));
  Hud_print(attacker, "[%s] <font color='#DB9773'>%N</font> +%d", weaponAlias, victim, exp);

  ClientRank_checkLvl(attacker);
}

void ExpEvent_giveBonusExpForHS(int attacker) {
  int exp = ClientRank_giveExpWithMSG(attacker, cvarHsBonusExp.IntValue, "headshot");
  Hud_print(attacker, "Headshot +%d", exp);
  ClientRank_checkLvl(attacker);
}

void ExpEvent_giveExpForAssist(int assister) {
  int exp = ClientRank_giveExpWithMSG(assister, cvarAssistExp.IntValue, "assist");
  Hud_print(assister, "Assist +%d", exp)
  ClientRank_checkLvl(assister);
}

void ExpEvent_giveExpForBombPlant(int client) {
  if (GetClientCount(true) < cvarBombExpMinPlayer.IntValue) {
    return;
  }

  int exp = ClientRank_giveExpWithMSG(client, cvarBombPlantExp.IntValue, "plant bomb");
  Hud_print(client, "Plant bomb +%d", exp);
  ClientRank_checkLvl(client);
}

void ExpEvent_giveExpForBombDefuse(int client) {
  if (GetClientCount(true) < cvarBombExpMinPlayer.IntValue) {
    return;
  }

  int exp = ClientRank_giveExpWithMSG(client, cvarBombDefuseExp.IntValue, "defuse bomb");
  Hud_print(client, "Defuse bomb +%d", exp);
  ClientRank_checkLvl(client);
}

void giveExpForWinRound(int client) {
  int exp = ClientRank_giveExpWithMSG(client, cvarRoundWinExp.IntValue, "won round");
  Hud_print(client, "Won round +%d", exp);
  ClientRank_checkLvl(client);
}
