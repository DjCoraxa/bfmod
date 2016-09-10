void initEvent() {
    HookEvent("player_spawn", eventPlayerSpawn);
    HookEvent("player_team", eventPlayerTeam);
    HookEvent("player_death", eventPlayerDeath);
    HookEvent("bomb_planted", eventBombPlanted);
    HookEvent("bomb_defused", eventBombDefused);
}

public Action eventPlayerSpawn(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (!IsValidClient(client) || !IsPlayerAlive(client)) {
    return;
  }

  CreateTimer(0.1, createModel, client);
  giveSpawnBonus(client);
  setRankTag(client);
}

public Action eventPlayerTeam(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (!IsValidClient(client)) {
    return;
  }

  setRankTag(client);
}

public Action eventPlayerDeath(Event event, const char[] name, bool dontBroadcast) {
  int victim = GetClientOfUserId(event.GetInt("userid"));
  int attacker = GetClientOfUserId(event.GetInt("attacker"));
  int assister = GetClientOfUserId(event.GetInt("assister"));
  char weaponBuffer[64];
  event.GetString("weapon", weaponBuffer, sizeof(weaponBuffer));
  int hs = event.GetInt("headshot");

  safeDelete(headSprite[victim]);

  if (!IsValidClient(attacker)) {
    return;
  }

  giveExpForKill(attacker, victim, weaponBuffer);

  if (hs) {
    giveBonusExpForHS(attacker);
  }

  if (!IsValidClient(assister)) {
    return;
  }

  giveExpForAssist(assister);
}

public Action eventBombPlanted(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (!IsValidClient(client)) {
    return;
  }

  giveExpForBombPlant(client);
}

public Action eventBombDefused(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (!IsValidClient(client)) {
    return;
  }

  giveExpForBombDefuse(client);
}
