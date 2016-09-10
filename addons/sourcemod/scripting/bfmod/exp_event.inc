int KILL_EXP = 100;
int ASSIST_EXP = 25;
int HS_BONUS = 30;
//int COMBO_BONUS = 5;
int BOMB_PLANT_EXP = 300;
int BOMB_DEFUSE_EXP = 300;
//int PLAYER_MIN_BOMB = 4;

int combo[MAXPLAYERS + 1];

void removeCombo(int client) {
  if (combo[client] > 1) {
    CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_combo_zero");
  }
  combo[client] = 0;
}

void giveExpForKill(int attacker, int victim, char[] weapon) {
  int exp = giveExp(attacker, KILL_EXP);
  CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_kill", exp);
  printHudMSG(attacker, "[%s] <font color='#DB9773'>%N</font> +%d", weapon, victim, exp);
  checkLvl(attacker);
}

void giveBonusExpForHS(int attacker) {
  int exp = giveExp(attacker, HS_BONUS);
  CPrintToChat(attacker, "%s %t", MOD_NAME, "bfmod_exp_bonus_hs", exp);
  printHudMSG(attacker, "HS bonus +%d", exp);
  checkLvl(attacker);
}

void giveExpForAssist(int assister) {
  int exp = giveExp(assister, ASSIST_EXP);
  CPrintToChat(assister, "%s %t", MOD_NAME, "bfmod_exp_assist", giveExp(assister, exp));
  printHudMSG(assister, "Assist +%d", exp)
  checkLvl(assister);
}

void giveExpForBombPlant(int client) {
  int exp = giveExp(client, BOMB_PLANT_EXP);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_bomb_plant", exp);
  printHudMSG(client, "Plant bomb +%d", exp);
  checkLvl(client);
}

void giveExpForBombDefuse(int client) {
  int exp = giveExp(client, BOMB_DEFUSE_EXP);
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_exp_bomb_defuse", exp);
  printHudMSG(client, "Defuse bomb +%d", exp);
  checkLvl(client);
}
