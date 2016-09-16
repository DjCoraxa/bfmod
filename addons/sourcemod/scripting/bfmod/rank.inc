const int MAX_RANK_NAME_LENGTH = 256;
const int MAX_RANK_SPRITE_PATH_LENGTH = 256;

char RANK_PATH[] = "configs/bfmod/rank.kv";

static ArrayList rankName;
static ArrayList rankSprite;
static ArrayList rankExp;

static int rankCount;

void Rank_init() {
  rankName = new ArrayList(MAX_RANK_NAME_LENGTH + 1);
  rankSprite = new ArrayList(MAX_RANK_SPRITE_PATH_LENGTH + 1);
  rankExp = new ArrayList();
  Rank_parseRank();
}

void Rank_onMapStart() {
  Rank_precacheSprites();
}

static void Rank_add(char[] name, char[] sprite, int exp) {
  rankName.PushString(name);
  rankSprite.PushString(sprite);
  rankExp.Push(exp);
  ++rankCount;

  #if defined TEST_ENABLE
    PrintToServer("[BFMod:TestMode:Rank] Add rank #%d Name=\"%s\" sprite=\"%s\" exp=%d", rankCount, name, sprite, exp);
  #endif
}

static void Rank_parseRank() {
  char pathToKV[PLATFORM_MAX_PATH + 1];
  BuildPath(Path_SM, pathToKV, sizeof(pathToKV), RANK_PATH);
  KeyValues kv = new KeyValues("bfrank");

  if (!kv.ImportFromFile(pathToKV)) {
    SetFailState("[BFMod:Rank] Can't load rank file \'%s\'", pathToKV);
  }

  char nameBuffer[MAX_RANK_NAME_LENGTH + 1];
  char spriteBuffer[MAX_RANK_SPRITE_PATH_LENGTH + 1];

  if (!kv.GotoFirstSubKey()) {
    return;
  }

  do {
    kv.GetString("name", nameBuffer, sizeof(nameBuffer), "");
    kv.GetString("sprite", spriteBuffer, sizeof(spriteBuffer), "");
    Rank_add(nameBuffer, spriteBuffer, kv.GetNum("exp"));
  } while (kv.GotoNextKey());

  delete kv;
}

static void Rank_precacheSprites() {
  for (int i = 0; i < rankCount; ++i) {
    char spriteBuffer[MAX_RANK_SPRITE_PATH_LENGTH + 1];
    rankSprite.GetString(i, spriteBuffer, sizeof(spriteBuffer));
    Helper_precacheSprite(spriteBuffer);
  }
}

void Rank_getName(int rank, char[] buffer, int maxLength) {
  rankName.GetString(rank, buffer, maxLength);
}

void Rank_getSprite(int rank, char[] buffer, int maxLength) {
  rankSprite.GetString(rank, buffer, maxLength);
}

int Rank_getExp(int rank) {
  return rankExp.Get(rank);
}

int Rank_getCount() {
  return rankCount;
}
