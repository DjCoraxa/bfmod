int clientCash[MAXPLAYERS + 1];

char weaponList[][] = {
  "weapon_awp",
  "weapon_ak47",
  "weapon_mag7",
  "weapon_negev",
  "weapon_m4a1",
  "weapon_famas"
};

void initShop() {
  RegConsoleCmd("sm_shop", cmd_sm_shop);
}

public Action cmd_sm_shop(int client, int args) {
  openShopMenu(client);
}

bool buy(int client, int cost) {
  if ((clientCash[client] - cost) < 0)
    return false;
  clientCash[client] -= cost;
  return true;
}

void openShopMenu(int client) {
  Menu menu = new Menu(shopMenuHandler);
  menu.SetTitle("Shop");
  menu.AddItem("pweapon","Random weapon [20Cash]");
  menu.AddItem("lowexp","Low exp (1xp - 200xp)[100Cash]");
  menu.AddItem("medexp","Medium exp (1xp - 500xp)[200Cash]");
  menu.AddItem("bigexp","Big exp (1xp - 3000xp)[300Cash]");
  menu.Display(client, 60);
}

public int shopMenuHandler(Menu menu, MenuAction action, int param1, int param2) {
  if (action == MenuAction_Select) {
    if (IsValidClient(param1)) {
      switch (param2) {
        case 0: {
          if (buy(param1, 20)) {
            GivePlayerItem(param1, weaponList[GetRandomInt(0, sizeof(weaponList))]);
          } else {
            CPrintToChat(param1, "%s {green}Nie posiadasz wystarczających środków", MOD_NAME);
          }
        }
        case 1: {
          if (buy(param1, 100)) {
            CPrintToChat(param1, "%s {purple}Otrzymałeś {green}%d xp", MOD_NAME, giveExp(param1, GetRandomInt(1, 100)));
            checkLvl(param1);
          } else {
            CPrintToChat(param1, "%s {green}Nie posiadasz wystarczających środków", MOD_NAME);
          }
        }
        case 2: {
          if (buy(param1, 200)) {
            CPrintToChat(param1, "%s {purple}Otrzymałeś {green}%d xp", MOD_NAME, giveExp(param1, GetRandomInt(1, 500)));
            checkLvl(param1);
          } else {
            CPrintToChat(param1, "%s {green}Nie posiadasz wystarczających środków", MOD_NAME);
          }
        }
        case 3: {
          if (buy(param1, 300)) {
            CPrintToChat(param1, "%s {purple}Otrzymałeś {green}%d xp", MOD_NAME, giveExp(param1, GetRandomInt(1, 3000)));
            checkLvl(param1);
          } else {
            CPrintToChat(param1, "%s {green}Nie posiadasz wystarczających środków", MOD_NAME);
          }
        }
      }
    }
  } else if (action == MenuAction_End) {
		delete menu;
	}
}
