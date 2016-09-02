int VIP_BONUS_EXP = 20;

char rankName[][] = {
  "None",
  "Private First Class",
  "Private First Class 1 Star",
  "Private First Class 2 Stars",
  "Private First Class 3 Stars",
  "Lance Corporal",
  "Lance Corporal 1 Star",
  "Lance Corporal 2 Stars",
  "Lance Corporal 3 Stars",
  "Corporal",
  "Corporal 1 Star",
  "Corporal 2 Stars",
  "Corporal 3 Stars",
  "Sergeant",
  "Sergeant 1 Star",
  "Sergeant 2 Stars",
  "Sergeant 3 Stars",
  "Staff Sergeant",
  "Staff Sergeant 1 Star",
  "Staff Sergeant 2 Stars",
  "Gunnery Sergeant",
  "Gunnery Sergeant 1 Star",
  "Gunnery Sergeant 2 Star",
  "Master Sergeant",
  "Master Sergeant 1 Star",
  "Master Sergeant 2 Star",
  "First Sergeant",
  "First Sergeant 1 Star",
  "First Sergeant 2 Stars",
  "Master Gunnery Sergeant",
  "Master Gunnery Sergeant 1 Star",
  "Master Gunnery Sergeant 2 Stars",
  "Sergeant Major",
  "Sergeant Major 1 Star",
  "Sergeant Major 2 Stars",
  "Warrant Officer One",
  "Chief Warrant Officer Two",
  "Chief Warrant Officer Three",
  "Chief Warrant Officer Four",
  "Chief Warrant Officer Five",
  "Second Lieutenant",
  "First Lieutenant",
  "Captain",
  "Major",
  "Lieutenant Colonel",
  "Colonel"
};

int expTable[] = {
  3000,
  8000,
  11000,
  13000,
  17000,
  18000,
  21000,
  24000,
  25000,
  28000,
  29000,
  32000,
  33000,
  35000,
  37000,
  39000,
  40000,
  42000,
  46000,
  47000,
  48000,
  51000,
  52000,
  54000,
  55000,
  56000,
  58000,
  60000,
  62000,
  66000,
  69000,
  70000,
  80000,
  90000,
  100000,
  150000,
  200000,
  250000,
  300000,
  350000,
  400000,
  450000,
  500000,
  550000,
  600000,
  3650000
};

char rankSprite[][] = {
  "bfmod/rank/1",
  "bfmod/rank/1",
  "bfmod/rank/2",
  "bfmod/rank/3",
  "bfmod/rank/4",
  "bfmod/rank/5",
  "bfmod/rank/6",
  "bfmod/rank/7",
  "bfmod/rank/8",
  "bfmod/rank/9",
  "bfmod/rank/10",
  "bfmod/rank/11",
  "bfmod/rank/12",
  "bfmod/rank/13",
  "bfmod/rank/14",
  "bfmod/rank/15",
  "bfmod/rank/16",
  "bfmod/rank/17",
  "bfmod/rank/18",
  "bfmod/rank/19",
  "bfmod/rank/20",
  "bfmod/rank/21",
  "bfmod/rank/22",
  "bfmod/rank/23",
  "bfmod/rank/24",
  "bfmod/rank/25",
  "bfmod/rank/26",
  "bfmod/rank/27",
  "bfmod/rank/28",
  "bfmod/rank/29",
  "bfmod/rank/30",
  "bfmod/rank/31",
  "bfmod/rank/32",
  "bfmod/rank/33",
  "bfmod/rank/34",
  "bfmod/rank/35",
  "bfmod/rank/36",
  "bfmod/rank/37",
  "bfmod/rank/38",
  "bfmod/rank/39",
  "bfmod/rank/40",
  "bfmod/rank/41",
  "bfmod/rank/42",
  "bfmod/rank/43",
  "bfmod/rank/44",
  "bfmod/rank/45"
};

int clientLvl[MAXPLAYERS + 1];
int clientExp[MAXPLAYERS + 1];

void precacheRankHudSprite() {
  for (int i = 1; i < sizeof(rankSprite); ++i) {
    char buffer[256];
    Format(buffer, sizeof(buffer), "%s.vtf", rankSprite[i]);
    PrecacheDecal(buffer, true);
    Format(buffer, sizeof(buffer), "materials/%s.vtf", rankSprite[i]);
    AddFileToDownloadsTable(buffer);
    Format(buffer, sizeof(buffer), "%s.vmt", rankSprite[i]);
    PrecacheDecal(buffer, true);
    Format(buffer, sizeof(buffer), "materials/%s.vmt", rankSprite[i]);
    AddFileToDownloadsTable(buffer);
  }
}

void checkLvl(int client) {
  if (clientExp[client] >= expTable[clientLvl[client]]) {
    clientExp[client] -= expTable[clientLvl[client]];
    ++clientLvl[client];
    onLvlUp(client, clientLvl[client]);
  }
}

int giveExp(int client, int exp) {
  int value = exp
  if (GetUserFlagBits(client) & ADMFLAG_RESERVATION) {
    value += VIP_BONUS_EXP;
  }
  clientExp[client] += value;
  return value;
}
