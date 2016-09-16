static char weaponList[][] = {
  "weapon_awp",
  "weapon_ak47",
  "weapon_mag7",
  "weapon_negev",
  "weapon_m4a1",
  "weapon_famas"
};

void Shop_init() {
  RegConsoleCmd("sm_shop", cmd_sm_shop);
}

public Action cmd_sm_shop(int client, int args) {
  Shop_openMenu(client);
}

static bool Shop_buy(int client, int cost) {
  if (ClientCash_canBuy(client, cost)) {
    ClientCash_set(client, ClientCash_get(client) - cost);
    return true;
  }
  return false;
}

void Shop_openMenu(int client) {
  Menu menu = new Menu(Shop_menuHandler);
  menu.SetTitle("Shop");
  menu.AddItem("pweapon","Random weapon [20Cash]");
  menu.AddItem("lowexp","Low exp (1xp - 200xp)[100Cash]");
  menu.AddItem("medexp","Medium exp (1xp - 500xp)[200Cash]");
  menu.AddItem("bigexp","Big exp (1xp - 3000xp)[300Cash]");
  menu.Display(client, 60);
}

public int Shop_menuHandler(Menu menu, MenuAction action, int param1, int param2) {
  if (action == MenuAction_Select) {
    if (IsValidClient(param1)) {
      switch (param2) {
        case 0: {
          if (Shop_buy(param1, 20)) {
            GivePlayerItem(param1, weaponList[GetRandomInt(0, sizeof(weaponList))]);
          } else {
            CPrintToChat(param1, "%t", "bfmod_shop_deny");
          }
        }
        case 1: {
          if (Shop_buy(param1, 100)) {
            CPrintToChat(param1, "%t", "bfmod_shop_exp", ClientRank_giveExp(param1, GetRandomInt(1, 100)));
            ClientRank_checkLvl(param1);
          } else {
            CPrintToChat(param1, "%t", "bfmod_shop_deny");
          }
        }
        case 2: {
          if (Shop_buy(param1, 200)) {
            CPrintToChat(param1, "%t", "bfmod_shop_exp", ClientRank_giveExp(param1, GetRandomInt(1, 500)));
            ClientRank_checkLvl(param1);
          } else {
            CPrintToChat(param1, "%t", "bfmod_shop_deny");
          }
        }
        case 3: {
          if (Shop_buy(param1, 300)) {
            CPrintToChat(param1, "%t", "bfmod_shop_exp", ClientRank_giveExp(param1, GetRandomInt(1, 3000)));
            ClientRank_checkLvl(param1);
          } else {
            CPrintToChat(param1, "%t", "bfmod_shop_deny");
          }
        }
      }
    }
  } else if (action == MenuAction_End) {
		delete menu;
	}
}
