Menu topMenu;

void BFTop_init() {
  BFTop_prepareMenu();
  RegConsoleCmd("sm_bftop", cmd_sm_bftop);
}

void BFTop_onMapStart() {
  BFTop_prepareMenu();
}

public Action cmd_sm_bftop(int client, int args) {
  BFTop_openMenu(client);
}

void BFTop_prepareMenu() {
  Sql_getTopClients(15, BFTop_prepareMenuCB);
}

void BFTop_openMenu(int client) {
  topMenu.Display(client, 60);
}

public void BFTop_prepareMenuCB(Database db, DBResultSet results, const char[] error, any data) {
  if (results == null) {
    LogError("[BFMod][TopRank] Query failed! %s", error);
    return;
  }

  topMenu = new Menu(BFTopm_menuHandler);
  topMenu.SetTitle("BFMod TOP15")
  char buffer[4096];
  char name [64];
  for (int i = 1; results.FetchRow(); ++i) {
    results.FetchString(0, name, sizeof(name));
    Format(buffer, sizeof(buffer), "[Pos %d] %s [Rank %d][Exp %d / %d][Cash %d]", i, name, results.FetchInt(1), results.FetchInt(2), expTable[results.FetchInt(1)], results.FetchInt(3));
    topMenu.AddItem("top", buffer);
  }
}

public int BFTopm_menuHandler(Menu menu, MenuAction action, int param1, int param2) {}
