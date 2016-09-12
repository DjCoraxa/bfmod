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

void ExpEvent_giveExpForKill(int attacker, int victim, char[] weapon) {
  int exp = giveExp(attacker, cvarKillExp.IntValue);
  CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_kill", exp);
  Hud_print(attacker, "[%s] <font color='#DB9773'>%N</font> +%d", weapon, victim, exp);
  checkLvl(attacker);
}

void ExpEvent_giveBonusExpForHS(int attacker) {
  int exp = giveExp(attacker, cvarHsBonusExp.IntValue);
  CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_bonus_hs", exp);
  Hud_print(attacker, "HS bonus +%d", exp);
  checkLvl(attacker);
}

void ExpEvent_giveExpForAssist(int assister) {
  int exp = giveExp(assister, cvarAssistExp.IntValue);
  CPrintToChat(assister, "%s %t", MOD_NAME, "bfmod_exp_assist", giveExp(assister, exp));
  Hud_print(assister, "Assist +%d", exp)
  checkLvl(assister);
}

void ExpEvent_giveExpForBombPlant(int client) {
  if (GetClientCount(true) < cvarBombExpMinPlayer.IntValue) {
    return;
  }

  int exp = giveExp(client, cvarBombPlantExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_bomb_plant", exp);
  Hud_print(client, "Plant bomb +%d", exp);
  checkLvl(client);
}

void ExpEvent_giveExpForBombDefuse(int client) {
  if (GetClientCount(true) < cvarBombExpMinPlayer.IntValue) {
    return;
  }

  int exp = giveExp(client, cvarBombDefuseExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_bomb_defuse", exp);
  Hud_print(client, "Defuse bomb +%d", exp);
  checkLvl(client);
}

void giveExpForWinRound(int client) {
  int exp = giveExp(client, cvarRoundWinExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_round_win", exp);
  Hud_print(client, "Won round +%d", exp);
  checkLvl(client);
}
