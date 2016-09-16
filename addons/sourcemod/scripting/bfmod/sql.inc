char DATABASE_NAME[] = "bfmod_4"

char queryCreate[] = "\
  CREATE TABLE IF NOT EXISTS bfmod(\
    steamid VARCHAR PRIMARY KEY UNIQUE,\
    name VARCHAR NOT NULL,\
    lvl INT NOT NULL,\
    exp INT NOT NULL,\
    cash INT NOT NULL\
  )\
";

static Database db;
static char db_error[256];

void Sql_init() {
  db = SQLite_UseDatabase(DATABASE_NAME, db_error, sizeof(db_error));

  if (db == INVALID_HANDLE) {
    SetFailState("DB error: %s", db_error);
  }

  SQL_Query(db, queryCreate);
}

void Sql_onClientPutInServer(int client) {
  Sql_loadClientData(client);
}

public Action Sql_eventOnRoundEnd() {
  for (int client = 1; client <= MaxClients; ++client) {
    if (IsValidClient(client)) {
      Sql_saveClientData(client);
    }
  }
}

static void Sql_loadClientData(int client) {
  char steamid[256];
  GetClientAuthId(client, AuthId_Steam3, steamid, sizeof(steamid));

  char queryLoad[256];
  Format(queryLoad, sizeof(queryLoad), "SELECT lvl, exp, cash FROM bfmod WHERE steamid = '%s'", steamid);

  #if defined TEST_MODE
    PrintToServer("[BFMod:TestMode:Sql] %s", queryLoad);
  #endif

  DBResultSet query = SQL_Query(db, queryLoad);

  if (query == null) {
    char error[255];
    SQL_GetError(db, error, sizeof(error));
    PrintToServer("[BFMod] Failed to query (error: %s)", error);
  } else {
    PrintToServer("[BFMod] client: %N RowCount %d", client, query.RowCount);
    if (query.RowCount && query.FetchRow()) {
      PrintToServer("[BFMod][Load] client: %N lvl: %d exp: %d", client, query.FetchInt(0), query.FetchInt(1));
      ClientRank_setLvl(client, query.FetchInt(0));
      ClientRank_setExp(client, query.FetchInt(1));
      ClientCash_set(client, query.FetchInt(2));
    } else {
      PrintToServer("[BFMod] client: %N not found in DB, load default data", client);
      ClientRank_setLvl(client, 1);
      ClientRank_setExp(client, 0);
      ClientCash_set(client, 0);
    }
  }
}

static void Sql_saveClientData(int client) {
  char steamid[256];
  GetClientAuthId(client, AuthId_Steam3, steamid, sizeof(steamid));

  char nick[256];
  GetClientName(client, nick, sizeof(nick));

  char buffer[513];
  SQL_EscapeString(db, nick, buffer, sizeof(buffer));

  char querySave[256];
  Format(querySave, sizeof(querySave), "INSERT OR REPLACE INTO bfmod(steamid, lvl, exp, name, cash) VALUES(\"%s\", %d, %d, \"%s\", %d)", steamid, ClientRank_getLvl(client), ClientRank_getExp(client), buffer, ClientCash_get(client));
  db.Query(saveQuertCB, querySave);

  #if defined TEST_MODE
    PrintToServer("[BFMod:TestMode:Sql] %s", querySave);
  #endif
}

void Sql_getTopClients(int count, SQLQueryCallback callback) {
  char queryTop[256];
  Format(queryTop, sizeof(queryTop), "SELECT name, lvl, exp, cash FROM bfmod ORDER BY lvl DESC, exp DESC LIMIT %d;", count);
  db.Query(callback, queryTop);

  #if defined TEST_MODE
    PrintToServer("[BFMod:TestMode:Sql] %s", queryTop);
  #endif
}

public void saveQuertCB(Handle owner, Handle hndl, const char[] error, any data) {}
