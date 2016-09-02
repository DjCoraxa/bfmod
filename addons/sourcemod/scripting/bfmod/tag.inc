void tagInit() {
  HookEvent("player_spawn", tagEvent);
  HookEvent("player_team", tagEvent);
}

public Action tagEvent(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  setTag(client);
}

void setTag(int client) {
  char tag[64];
  Format(tag, sizeof(tag), "[Rank %d]", clientLvl[client]);
  CS_SetClientClanTag(client, tag);
}
