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
  HeadSprite_eventOnPlayerSpawn(client);
  SpawnBonus_eventOnPlayerSpawn(client);
  Tag_eventOnPlayerSpawn(client);
  Hud_eventOnPlayerSpawn(client);
}

public Action Event_onPlayerTeam(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  Tag_eventOnPlayerTeam(client);
}

public Action Event_onPlayerDeath(Event event, const char[] name, bool dontBroadcast) {
  int victim = GetClientOfUserId(event.GetInt("userid"));
  int attacker = GetClientOfUserId(event.GetInt("attacker"));
  int assister = GetClientOfUserId(event.GetInt("assister"));
  char weaponBuffer[64];
  event.GetString("weapon", weaponBuffer, sizeof(weaponBuffer));
  bool hs = event.GetBool("headshot");

  HeadSprite_eventOnPlayerDeath(victim);
  ExpEvent_eventOnPlayerDeath(victim, attacker, assister, weaponBuffer, hs);
  Ribbon_eventOnPlayerDeath(attacker, weaponBuffer);
}

public Action Event_onBombPlant(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  ExpEvent_eventOnBombPlant(client);
}

public Action Event_onBombDefuse(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  ExpEvent_eventOnBombDefuse(client);
}

public Action Event_onRoundEnd(Event event, const char[] name, bool dontBroadcast) {
  int winnerTeam = event.GetInt("winner");
  ExpEvent_eventOnRoundEnd(winnerTeam);
  Sql_eventOnRoundEnd();
}
