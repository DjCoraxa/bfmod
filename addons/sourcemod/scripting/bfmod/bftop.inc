Menu topMenu;

void initBFTop() {
  prepareTopMenu();
  RegConsoleCmd("sm_bftop", cmd_sm_bftop);
}

public Action cmd_sm_bftop(int client, int args) {
  openTopMenu(client);
}

void prepareTopMenu() {
  getTopClients(15, prepareTopMenuCB);
}

void openTopMenu(int client) {
  topMenu.Display(client, 60);
}

public void prepareTopMenuCB(Database db, DBResultSet results, const char[] error, any data) {
  if (results == null) {
    LogError("[BFMod][TopRank] Query failed! %s", error);
    return;
  }

  topMenu = new Menu(topMenuHandler);
  topMenu.SetTitle("BFMod TOP15")
  char buffer[4096];
  char name [64];
  for (int i = 1; results.FetchRow(); ++i) {
    results.FetchString(0, name, sizeof(name));
    Format(buffer, sizeof(buffer), "[Pos %d] %s [Rank %d][Exp %d / %d][Cash %d]", i, name, results.FetchInt(1), results.FetchInt(2), expTable[results.FetchInt(1)], results.FetchInt(3));
    topMenu.AddItem("top", buffer);
  }
}

public int topMenuHandler(Menu menu, MenuAction action, int param1, int param2) {}
