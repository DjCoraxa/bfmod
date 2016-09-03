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
  char buffer[256];
  char name [64];
  while (results.FetchRow()) {
    results.FetchString(0, name, sizeof(name));
    Format(buffer, sizeof(buffer), "%s [Rank %d][Exp %d / %d]", name, results.FetchInt(1), results.FetchInt(2), expTable[results.FetchInt(1)]);
    topMenu.AddItem("top", buffer);
  }
}

public int topMenuHandler(Menu menu, MenuAction action, int param1, int param2) {}
