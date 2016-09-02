float HUD_INTERVAL = 1.0;
float TIME_ELEMENTS_IN_HUD = 4.0;
const int HUD_STACK_BLOCKSIZE = 90;

ArrayStack clientHudStack[MAXPLAYERS + 1];
char clientHudElements[MAXPLAYERS + 1][4][HUD_STACK_BLOCKSIZE + 1];
int clientHudElementsCount[MAXPLAYERS + 1];
Handle clientHudElementsTimer[MAXPLAYERS + 1];
Handle clientHudTimer[MAXPLAYERS + 1];


void createHud(int client) {
  clientHudStack[client] = new ArrayStack(HUD_STACK_BLOCKSIZE);
  clientHudTimer[client] = CreateTimer(HUD_INTERVAL, timerShowHud, client, TIMER_REPEAT);
}

void removeHud(int client) {
  CloseHandle(clientHudStack[client]);
  KillTimer(clientHudTimer[client]);

  if (IsValidHandle(clientHudElementsTimer[client])) {
    KillTimer(clientHudElementsTimer[client]);
    clientHudElementsTimer[client] = INVALID_HANDLE;
  }

  removeHudElements(INVALID_HANDLE, client);
}

void incAllHudElement(int client) {
  strcopy(clientHudElements[client][3], sizeof(clientHudElements[][]), clientHudElements[client][2]);
  strcopy(clientHudElements[client][2], sizeof(clientHudElements[][]), clientHudElements[client][1]);
  strcopy(clientHudElements[client][1], sizeof(clientHudElements[][]), clientHudElements[client][0]);

  if (clientHudElementsCount[client] > 3) {
    --clientHudElementsCount[client];
  }
}

void addHudElement(int client, char[] content) {
  incAllHudElement(client);
  strcopy(clientHudElements[client][0], sizeof(clientHudElements[][]), content);
  ++clientHudElementsCount[client];
}

void createHudElementsTimer(int client) {
  if (IsValidHandle(clientHudElementsTimer[client])) {
    KillTimer(clientHudElementsTimer[client]);
    clientHudElementsTimer[client] = INVALID_HANDLE;
  }

  clientHudElementsTimer[client] = CreateTimer(TIME_ELEMENTS_IN_HUD, removeHudElements, client);
}

public Action removeHudElements(Handle timer, any client) {
  clientHudSpriteTimer[client] = INVALID_HANDLE;
  clientHudElementsCount[client] = 0;
  for (int i = 0; i < sizeof(clientHudElements[]); ++i) {
    strcopy(clientHudElements[client][i], sizeof(clientHudElements[][]), "");
  }
}

void printHudMSG(int client, const char[] msg, any ...) {
  int len = strlen(msg) + 255;
  char[] formattedMSG = new char[len];
  VFormat(formattedMSG, len, msg, 3);

  if (clientHudElementsCount[client] > 3) {
    clientHudStack[client].PushString(formattedMSG);
  } else {
    addHudElement(client, formattedMSG);
  }

  createHudElementsTimer(client);
}

void checkElementsStack(int client) {
  if (clientHudStack[client].Empty) {
    return;
  }

  char buffer[HUD_STACK_BLOCKSIZE + 1];
  clientHudStack[client].PopString(buffer, sizeof(buffer));
  addHudElement(client, buffer);
  createHudElementsTimer(client);
}

public Action timerShowHud(Handle timer, any client) {
  if (!IsClientInGame(client) || !IsPlayerAlive(client))
    return;

  if (clientHudElementsCount[client]) {
    checkElementsStack(client);
    PrintHintText(client, "<font size='15'>%s\n%s\n%s\n%s</font>", clientHudElements[client][0], clientHudElements[client][1], clientHudElements[client][2], clientHudElements[client][3])
  } else {
    PrintHintText(client, "<font size='15'>[<font color='#345FA9'>Propaganda-</font><font color='#262E73'>GO</font><font color='#345FA9'>.pl</font>]\n[Rank: %d - %s]\n[Exp: %d / %d]\n[Perk: %s]</font>", clientLvl[client], rankName[clientLvl[client]], clientExp[client], expTable[clientLvl[client]], perkName[clientPerk[client]]);
  }
}
