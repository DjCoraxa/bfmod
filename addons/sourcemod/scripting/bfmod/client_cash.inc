static int clientCash[MAXPLAYERS + 1];

void ClientCash_eventOnPlayerDeath(int attacker, bool hs) {
  if (IsValidClient(attacker)) {
    ClientCash_add(attacker, 1);
    if (hs) {
      ClientCash_add(attacker, 1);
    }
  }
}

stock void ClientCash_set(int client, int cash) {
  clientCash[client] = cash;
}

stock int ClientCash_get(int client) {
  return clientCash[client];
}

stock void ClientCash_add(int client, int cash) {
  clientCash[client] += cash;
}

stock bool ClientCash_canBuy(int client, int cost) {
  if ((clientCash[client] - cost) < 0)
    return false;
  return true;
}
