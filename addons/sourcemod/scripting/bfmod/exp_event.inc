int KILL_EXP = 100;
int ASSIST_EXP = 25;
int HS_BONUS = 30;
int COMBO_BONUS = 5;

int combo[MAXPLAYERS + 1];

void expEventInit() {
  HookEvent("player_spawn", expEventSpawn);
  HookEvent("player_death", expEventDeath);
}

void removeCombo(int client) {
  if (combo[client] > 1) {
    CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_combo_zero");
  }

  combo[client] = 0;
}

public Action expEventSpawn(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  removeCombo(client);
}

public Action expEventDeath(Event event, const char[] name, bool dontBroadcast) {
  int victim = GetClientOfUserId(event.GetInt("userid"));
  int attacker = GetClientOfUserId(event.GetInt("attacker"));
  int assister = GetClientOfUserId(event.GetInt("assister"));
  char weaponBuffer[64];
  event.GetString("weapon", weaponBuffer, sizeof(weaponBuffer));

  removeCombo(victim);

  if (IsValidClient(assister)) {
    int exp = giveExp(assister, ASSIST_EXP);
    CPrintToChat(assister, "%s %t", MOD_NAME, "bfmod_exp_assist", giveExp(assister, exp));
    printHudMSG(assister, "Assist +%d", exp)
    checkLvl(assister);
  }

  if (victim == attacker)
    return

  if (IsValidClient(attacker)) {
    int killExp = giveExp(attacker, KILL_EXP);
    CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_kill", killExp);
    printHudMSG(attacker, "[%s] <font color='#DB9773'>%N</font> +%d", weaponBuffer, victim, killExp);
    checkLvl(attacker);

    if (event.GetInt("headshot")) {
      int hsExp = giveExp(attacker, HS_BONUS);
      CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_bonus_hs", hsExp);
      printHudMSG(attacker, "Headshot bonus +%d", hsExp);
      checkLvl(attacker);
    }

    ++combo[attacker];

    if (combo[attacker] > 1) {
      int comboExp = giveExp(attacker, COMBO_BONUS * combo[attacker]);
      CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_combo_bonus", comboExp, combo[attacker]);
      printHudMSG(attacker, "Combo x%d bonus +%d", combo[attacker], comboExp);
      checkLvl(attacker);
    }
  }
}
