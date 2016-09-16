static int clientLvl[MAXPLAYERS + 1];
static int clientExp[MAXPLAYERS + 1];

void ClientRank_onLvlUp(int client, int lvl) {
  char nameBuffer[MAX_RANK_NAME_LENGTH + 1];
  Rank_getName(lvl, nameBuffer, sizeof(nameBuffer));
  CPrintToChat(client, "%s %t", MOD_NAME, "bfmod_promote_rank", nameBuffer);
}

void ClientRank_checkLvl(int client) {
  while (clientExp[client] >= Rank_getExp(clientLvl[client])) {
    clientExp[client] -= Rank_getExp(clientLvl[client]);
    ++clientLvl[client];
    onLvlUp(client, clientLvl[client]);
  }
}

int ClientRank_getLvl(int client) {
  return clientLvl[client];
}

int ClientRank_getExp(int client) {
  return clientExp[client];
}

void ClientRank_setLvl(int client, int lvl) {
  clientLvl[client] = lvl;
}

void ClientRank_setExp(int client, int exp) {
  clientExp[client] = exp;
}

int ClientRank_giveExp(int client, int exp) {
  return clientExp[client] += exp;
}

int ClientRank_giveExpWithMSG(int client, int exp, const char[] msg, any ...) {
    int len = strlen(msg) + 255;
    char[] formattedMSG = new char[len];
    VFormat(formattedMSG, len, msg, 4);
    int value = ClientRank_giveExp(client, exp);
    CPrintToChat(client, "%t", "bfmod_exp_msg", value, msg);
    return value;
}
