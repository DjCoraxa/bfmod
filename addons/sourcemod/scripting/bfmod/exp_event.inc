ConVar cvarKillExp;
ConVar cvarAssistExp;
ConVar cvarHsBonusExp;
ConVar cvarBombPlantExp;
ConVar cvarBombDefuseExp;
ConVar cvarBombExpMinPlayer;
ConVar cvarRoundWinExp;

StringMap fullWeaponName;

void ExpEvent_init() {
  cvarKillExp = CreateConVar("bfmod_kill_exp", "100", "Exp amount from kill");
  cvarAssistExp = CreateConVar("bfmod_assist_exp", "25", "Exp amount from assist");
  cvarHsBonusExp = CreateConVar("bfmod_hs_exp", "30", "Exp amount from hs");
  cvarBombPlantExp = CreateConVar("bfmod_bomb_plant_exp", "300", "Exp amount from bomb plant");
  cvarBombDefuseExp = CreateConVar("bfmod_bomb_defuse_exp", "300", "Exp amount from bomb defuse");
  cvarRoundWinExp = CreateConVar("bfmod_round_win_exp", "100", "Exp amount from win round");
  cvarBombExpMinPlayer = CreateConVar("bfmod_bomb_exp_min_players", "4", "Min players for exp from bomb");

  fullWeaponName = CreateTrie();

  fullWeaponName.SetString("sawedoff", "Obrzyn (Sawed-Off)");
  fullWeaponName.SetString("mag7", "Mag-7");
  fullWeaponName.SetString("nova", "Nova");
  fullWeaponName.SetString("xm1014", "XM1014");
  fullWeaponName.SetString("mp7", "MP7");
  fullWeaponName.SetString("mp9", "MP9");
  fullWeaponName.SetString("ssg08", "SSG 08 (Scout)");
  fullWeaponName.SetString("awp", "AWP");
  fullWeaponName.SetString("famas", "FAMAS");
  fullWeaponName.SetString("ump45", "UMP-45");
  fullWeaponName.SetString("bizon", "PP-Bizon");
  fullWeaponName.SetString("mac10", "Mac-10");
  fullWeaponName.SetString("galilar", "Galil AR");
  fullWeaponName.SetString("p90", "P90");
  fullWeaponName.SetString("ak47", "AK-47");
  fullWeaponName.SetString("m4a1_silencer", "M4A1-S");
  fullWeaponName.SetString("m4a1_silencer_off", "M4A1-S");
  fullWeaponName.SetString("m4a1", "M4A4");
  fullWeaponName.SetString("sg556", "SG 553");
  fullWeaponName.SetString("aug", "AUG");
  fullWeaponName.SetString("m249", "M249");
  fullWeaponName.SetString("negev", "Negev");
  fullWeaponName.SetString("scar20", "Scar-20");
  fullWeaponName.SetString("g3sg1", "G3SG1");

  fullWeaponName.SetString("cz75a", "CZ-75");
  fullWeaponName.SetString("usp_silencer","USP-S");
  fullWeaponName.SetString("usp_silencer_off","USP-S");
  fullWeaponName.SetString("deagle", "Deagle");
  fullWeaponName.SetString("revolver", "Revolver");
  fullWeaponName.SetString("glock", "Glock");
  fullWeaponName.SetString("p250", "P250");
  fullWeaponName.SetString("hkp2000", "P2000");
  fullWeaponName.SetString("tec9", "TEC-9");
  fullWeaponName.SetString("fiveseven", "FiveSeven");
  fullWeaponName.SetString("elite", "Dwie Berrety");
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
  int exp = Rank_giveExp(attacker, cvarKillExp.IntValue);
  char fullName[16];

  if(!fullWeaponName.GetString(weapon, fullName, sizeof(fullName)))
  {
    Format(fullName, sizeof(fullName), weapon);
  }

  CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_kill", exp);
  Hud_print(attacker, "[%s] <font color='#DB9773'>%N</font> +%d", fullName, victim, exp);
  Rank_checkLvl(attacker);
}

void ExpEvent_giveBonusExpForHS(int attacker) {
  int exp = Rank_giveExp(attacker, cvarHsBonusExp.IntValue);
  CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_bonus_hs", exp);
  Hud_print(attacker, "HS bonus +%d", exp);
  Rank_checkLvl(attacker);
}

void ExpEvent_giveExpForAssist(int assister) {
  int exp = Rank_giveExp(assister, cvarAssistExp.IntValue);
  CPrintToChat(assister, "%s %t", MOD_NAME, "bfmod_exp_assist", exp);
  Hud_print(assister, "Assist +%d", exp)
  Rank_checkLvl(assister);
}

void ExpEvent_giveExpForBombPlant(int client) {
  if (GetClientCount(true) < cvarBombExpMinPlayer.IntValue) {
    return;
  }

  int exp = Rank_giveExp(client, cvarBombPlantExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_bomb_plant", exp);
  Hud_print(client, "Plant bomb +%d", exp);
  Rank_checkLvl(client);
}

void ExpEvent_giveExpForBombDefuse(int client) {
  if (GetClientCount(true) < cvarBombExpMinPlayer.IntValue) {
    return;
  }

  int exp = Rank_giveExp(client, cvarBombDefuseExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_bomb_defuse", exp);
  Hud_print(client, "Defuse bomb +%d", exp);
  Rank_checkLvl(client);
}

void giveExpForWinRound(int client) {
  int exp = Rank_giveExp(client, cvarRoundWinExp.IntValue);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_round_win", exp);
  Hud_print(client, "Won round +%d", exp);
  Rank_checkLvl(client);
}
