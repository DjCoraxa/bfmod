char DATABASE_NAME[] = "bfmod_3"

char queryCreate[] = "\
  CREATE TABLE IF NOT EXISTS bfmod(\
    steamid VARCHAR PRIMARY KEY UNIQUE,\
    name VARCHAR NOT NULL,\
    lvl INT NOT NULL,\
    exp INT NOT NULL\
  )\
";

static Database db;
static char db_error[256];

void sqlInit() {
  db = SQLite_UseDatabase(DATABASE_NAME, db_error, sizeof(db_error));

  if (db == INVALID_HANDLE) {
    SetFailState("DB error: %s", db_error);
  }

  SQL_Query(db, queryCreate);
  HookEvent("round_end", sqlRoundEnd);
}

public Action sqlRoundEnd(Event event, const char[] name, bool dontBroadcast) {
  for (int client = 1; client <= MaxClients; ++client) {
    if (IsValidClient(client)) {
      saveClientData(client);
    }
  }
}

void loadClientData(int client) {
  char steamid[256];
  GetClientAuthId(client, AuthId_Steam3, steamid, sizeof(steamid));

  char queryLoad[256];
  Format(queryLoad, sizeof(queryLoad), "SELECT lvl, exp FROM bfmod WHERE steamid = '%s'", steamid);

  DBResultSet query = SQL_Query(db, queryLoad);

  if (query == null) {
    char error[255];
    SQL_GetError(db, error, sizeof(error));
    PrintToServer("[BFMod] Failed to query (error: %s)", error);
  } else {
    PrintToServer("[BFMod] client: %N RowCount %d", client, query.RowCount);
    if (query.RowCount && query.FetchRow()) {
      PrintToServer("[BFMod][Load] client: %N lvl: %d exp: %d", client, query.FetchInt(0), query.FetchInt(1));
      clientLvl[client] = query.FetchInt(0);
      clientExp[client] = query.FetchInt(1);
    } else {
      PrintToServer("[BFMod] client: %N not found in DB, load default data", client);
      clientLvl[client] = 1;
      clientExp[client] = 0;
    }
  }
}

void saveClientData(int client) {
  char steamid[256];
  GetClientAuthId(client, AuthId_Steam3, steamid, sizeof(steamid));

  char nick[256];
  GetClientName(client, nick, sizeof(nick));

  char buffer[513];
  SQL_EscapeString(db, nick, buffer, sizeof(buffer));

  char querySave[256];
  Format(querySave, sizeof(querySave), "INSERT OR REPLACE INTO bfmod(steamid, lvl, exp, name) VALUES(\"%s\", %d, %d, \"%s\")", steamid, clientLvl[client], clientExp[client], buffer);
  db.Query(saveQuertCB, querySave);

  PrintToServer("[BFMod][Save] client: %N lvl: %d exp: %d", client, clientLvl[client], clientExp[client]);
}

void getTopClients(int count, SQLQueryCallback callback) {
  char queryTop[256];
  Format(queryTop, sizeof(queryTop), "SELECT name, lvl, exp FROM bfmod ORDER BY lvl DESC, exp DESC LIMIT %d;", count);
  db.Query(callback, queryTop);
}

public void saveQuertCB(Handle owner, Handle hndl, const char[] error, any data) {}
