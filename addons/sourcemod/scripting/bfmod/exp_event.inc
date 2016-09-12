char weaponAlias[][] =
{
  "sawedoff",
  "mag7",
  "nova",
  "xm1014",
  "mp7",
  "mp9",
  "ssg08",
  "awp",
  "famas",
  "ump45",
  "bizon",
  "mac10",
  "galilar",
  "p90",
  "ak47",
  "m4a1_silencer",
  "m4a1_silencer_off",
  "m4a1",
  "sg556",
  "aug",
  "m249",
  "negev",
  "scar20",
  "g3sg1",
  "cz75a",
  "usp_silencer",
  "usp_silencer_off",
  "deagle",
  "revolver",
  "glock",
  "p250",
  "hkp2000",
  "tec9",
  "fiveseven",
  "elite"
};
char weaponFullName[][] =
{
  "Obrzyn",
  "MAG-7",
  "Nova",
  "XM1014",
  "MP7",
  "MP9",
  "SSG 08",
  "AWP",
  "FAMAS",
  "UMP-45",
  "PP-Bizon",
  "Mac-10",
  "Galil AR",
  "P90",
  "AK-47",
  "M4A1-S",
  "M4A1-S",
  "M4A4",
  "SG 553",
  "AUG",
  "M249",
  "Negev",
  "Scar-20",
  "G3SG1",
  "CZ-75",
  "USP-S",
  "USP-S",
  "DEAGLE",
  "Revolver",
  "Glock",
  "P250",
  "P2000",
  "TEC-9",
  "FiveSeven",
  "Dwie Berrety"
};
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

  fullWeaponName = new StringMap();

  for(int i = 0;i < sizeof(weaponAlias); i++)
  {
    fullWeaponName.SetString(weaponAlias[i], weaponFullName[i]);
  }
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
