void Event_init() {
    HookEvent("player_spawn", Event_onPlayerSpawn);
    HookEvent("player_team", Event_onPlayerTeam);
    HookEvent("player_death", Event_onPlayerDeath);
    HookEvent("bomb_planted", Event_onBombPlant);
    HookEvent("bomb_defused", Event_onBombDefuse);
    HookEvent("round_end", Event_onRoundEnd);
}

public Action Event_onPlayerSpawn(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (!IsValidClient(client) || !IsPlayerAlive(client)) {
    return;
  }

  CreateTimer(0.1, HeadSprite_createModel, client);
  SpawnBonus_giveSpawnBonus(client);
  Tag_setRankTag(client);
}

public Action Event_onPlayerTeam(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (!IsValidClient(client)) {
    return;
  }

  Tag_setRankTag(client);
}

public Action Event_onPlayerDeath(Event event, const char[] name, bool dontBroadcast) {
  int victim = GetClientOfUserId(event.GetInt("userid"));
  int attacker = GetClientOfUserId(event.GetInt("attacker"));
  int assister = GetClientOfUserId(event.GetInt("assister"));
  char weaponBuffer[64];
  event.GetString("weapon", weaponBuffer, sizeof(weaponBuffer));
  int hs = event.GetInt("headshot");

  HeadSprite_safeDelete(headSprite[victim]);

  if (!IsValidClient(attacker)) {
    return;
  }

  ExpEvent_giveExpForKill(attacker, victim, weaponBuffer);

  if (hs) {
    ExpEvent_giveBonusExpForHS(attacker);
  }

  if (!IsValidClient(assister)) {
    return;
  }

  ExpEvent_giveExpForAssist(assister);
}

public Action Event_onBombPlant(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (!IsValidClient(client)) {
    return;
  }

  ExpEvent_giveExpForBombPlant(client);
}

public Action Event_onBombDefuse(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (!IsValidClient(client)) {
    return;
  }

  ExpEvent_giveExpForBombDefuse(client);
}

public Action Event_onRoundEnd(Event event, const char[] name, bool dontBroadcast) {
  int winnerTeam = event.GetInt("winner");
  for (int client = 1; client <= MaxClients; client++) {
    if(IsValidClient(client) && GetClientTeam(client) == winnerTeam) {
      giveExpForWinRound(client);
    }
  }
}
