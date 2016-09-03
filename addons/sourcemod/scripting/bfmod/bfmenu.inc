void initBFMenu() {
  RegConsoleCmd("sm_bfmenu", cmd_sm_bfmenu);
}

public Action cmd_sm_bfmenu(int client, int args) {
  openBFMenu(client);
}

void openBFMenu(int client) {
  Menu menu = new Menu(BFMenuHandler);
  menu.SetTitle("BFMod menu");
  menu.AddItem("perk", "Choose perk [!perk]");
  menu.AddItem("perkdesc", "Perk desc [!perks]");
  menu.AddItem("bonus", "Bonus list [!bonus]");
  menu.AddItem("top", "Top15 rank [!bftop]");
  menu.AddItem("shop", "Shop menu [!shop]");
  menu.Display(client, 60);
}

public int BFMenuHandler(Menu menu, MenuAction action, int param1, int param2) {
  if (action == MenuAction_Select) {
    if (IsValidClient(param1)) {
      switch (param2) {
        case 0: openPerkMenu(param1);
        case 1: openPerkDescMenu(param1);
        case 2: openBonusMenu(param1);
        case 3: openTopMenu(param1);
        case 4: openShopMenu(param1);
      }
    }
  } else if (action == MenuAction_End) {
		delete menu;
	}
}
