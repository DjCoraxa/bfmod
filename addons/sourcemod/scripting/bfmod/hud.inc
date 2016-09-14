const int HUD_STACK_BLOCKSIZE = 90;

static ConVar cvarHudInterval;
static ConVar cvarTimeElementsInHud;

static ArrayStack clientHudStack[MAXPLAYERS + 1];
static char clientHudElements[MAXPLAYERS + 1][4][HUD_STACK_BLOCKSIZE + 1];
static int clientHudElementsCount[MAXPLAYERS + 1];
static Handle clientHudElementsTimer[MAXPLAYERS + 1];
static Handle clientHudTimer[MAXPLAYERS + 1];
static char clientRankName[MAXPLAYERS + 1][MAX_RANK_NAME_LENGTH + 1];

void Hud_init() {
  cvarHudInterval = CreateConVar("bfmod_hud_interval", "1.0", "");
  cvarTimeElementsInHud = CreateConVar("bfmod_time_hud_elements", "5.0", "");
}

void Hud_onClientPutInServer(int client) {
  Hud_create(client);
}

void Hud_onClientDisconnect(int client) {
  Hud_remove(client);
}

void Hud_eventOnPlayerSpawn(int client) {
  Rank_getName(ClientRank_getLvl(client), clientRankName[client], sizeof(clientRankName[]));
}

static void Hud_create(int client) {
  clientHudStack[client] = new ArrayStack(HUD_STACK_BLOCKSIZE);
  clientHudTimer[client] = CreateTimer(cvarHudInterval.FloatValue, Hud_showTimer, client, TIMER_REPEAT);
}

static void Hud_remove(int client) {
  CloseHandle(clientHudStack[client]);
  KillTimer(clientHudTimer[client]);

  if (clientHudElementsTimer[client] != INVALID_HANDLE) {
    KillTimer(clientHudElementsTimer[client]);
    clientHudElementsTimer[client] = INVALID_HANDLE;
  }

  Hud_removeElements(INVALID_HANDLE, client);
}

static void Hud_incAllElements(int client) {
  strcopy(clientHudElements[client][3], sizeof(clientHudElements[][]), clientHudElements[client][2]);
  strcopy(clientHudElements[client][2], sizeof(clientHudElements[][]), clientHudElements[client][1]);
  strcopy(clientHudElements[client][1], sizeof(clientHudElements[][]), clientHudElements[client][0]);

  if (clientHudElementsCount[client] > 3) {
    --clientHudElementsCount[client];
  }
}

static void Hud_addElement(int client, char[] content) {
  Hud_incAllElements(client);
  strcopy(clientHudElements[client][0], sizeof(clientHudElements[][]), content);
  ++clientHudElementsCount[client];
}

static void Hud_createElementsTimer(int client) {
  if (clientHudElementsTimer[client] != INVALID_HANDLE) {
    KillTimer(clientHudElementsTimer[client]);
    clientHudElementsTimer[client] = INVALID_HANDLE;
  }

  clientHudElementsTimer[client] = CreateTimer(cvarTimeElementsInHud.FloatValue, Hud_removeElements, client);
}

public Action Hud_removeElements(Handle timer, any client) {
  clientHudElementsTimer[client] = INVALID_HANDLE;
  clientHudElementsCount[client] = 0;
  for (int i = 0; i < sizeof(clientHudElements[]); ++i) {
    strcopy(clientHudElements[client][i], sizeof(clientHudElements[][]), "");
  }
}

void Hud_print(int client, const char[] msg, any ...) {
  int len = strlen(msg) + 255;
  char[] formattedMSG = new char[len];
  VFormat(formattedMSG, len, msg, 3);

  if (clientHudElementsCount[client] > 3) {
    clientHudStack[client].PushString(formattedMSG);
  } else {
    Hud_addElement(client, formattedMSG);
  }

  Hud_createElementsTimer(client);
}

static void Hud_checkElementsStack(int client) {
  if (clientHudStack[client].Empty) {
    return;
  }

  char buffer[HUD_STACK_BLOCKSIZE + 1];
  clientHudStack[client].PopString(buffer, sizeof(buffer));
  Hud_addElement(client, buffer);
  Hud_createElementsTimer(client);
}

public Action Hud_showTimer(Handle timer, any client) {
  if (!IsClientInGame(client) || !IsPlayerAlive(client))
    return;

  if (clientHudElementsCount[client]) {
    Hud_checkElementsStack(client);
    PrintHintText(client, "<font size='15'>%s\n%s\n%s\n%s</font>", clientHudElements[client][0], clientHudElements[client][1], clientHudElements[client][2], clientHudElements[client][3])
  } else {
    PrintHintText(client, "%t", "bfmod_hud", ClientRank_getLvl(client), clientRankName[client], ClientRank_getExp(client), Rank_getExp(ClientRank_getLvl(client)), perkName[clientPerk[client]], clientCash[client]);
  }
}
