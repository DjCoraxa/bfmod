enum Perk {
  PERK_NONE,
  PERK_DAMAGE,
  PERK_HEALTH,
  PERK_SPEED,
  PERK_KNIFE,
  PERK_JUMPER,
  PERK_SNIPER,
  PERK_GUN,
  PERK_GOD,
  PERK_COUNT
};


char perkName[][] = {
  "None",
  "Damage++",
  "Health++",
  "Speed++",
  "Lucky knife",
  "Jumper",
  "Sniper secret",
  "Free gun",
  "GOD Secret"
};

char perkDesc[][] = {
  "None",
  "Zadajesz 5DMG więcej",
  "Otrzymujesz dodatkowe 25hp na spawnie",
  "Poruszasz się o 20% szybciej",
  "1/3 na natychmiastowe zabójstwo z noża (prawy)",
  "Otrzymujesz DoubleJump",
  "1/2 na natychmiastowe zabójstwo z SSG08",
  "1/4 na darmową broń gdy się zrespisz",
  "Otrzymujesz dodatkowe 30hp na spawnie oraz zadajesz 10DMG więcej"
}

int perkLvlMin[] = {
  0,
  5,
  10,
  15,
  20,
  25,
  30,
  35,
  40,
  45
};

Perk clientPerk[MAXPLAYERS + 1];
Perk clientNextPerk[MAXPLAYERS + 1];

void Perk_hook(int client) {
  SDKHook(client, SDKHook_OnTakeDamage, Perk_onTakeDamage);
  SDKHook(client, SDKHook_SpawnPost, Perk_onSpawn);
  clientPerk[client] = PERK_NONE;
  clientNextPerk[client] = PERK_NONE;
}

void Perk_unhook(int client) {
  SDKUnhook(client, SDKHook_OnTakeDamage, Perk_onTakeDamage);
  SDKUnhook(client, SDKHook_SpawnPost, Perk_onSpawn);
}

public Action Perk_onTakeDamage(int victim, int& attacker, int& inflictor, float& damage, int& damagetype) {
  if(!IsValidClient(attacker))
  	return Plugin_Continue;

  if (victim == attacker)
    return Plugin_Continue;

  char weaponName[64];
  GetClientWeapon(attacker, weaponName, sizeof(weaponName));

  switch (clientPerk[attacker]) {
    case PERK_DAMAGE: {
      damage += 5.0
      return Plugin_Changed;
    }

    case PERK_KNIFE:
      if (GetRandomInt(1, 3) == 1 && StrEqual(weaponName, "weapon_knife") && GetClientButtons(attacker) & IN_ATTACK2) {
        SetEntProp(victim, Prop_Data, "m_ArmorValue", 0, 1);
        damage = float(GetClientHealth(victim) + 1);
        return Plugin_Changed;
      }

    case PERK_SNIPER:
      if (GetRandomInt(1, 2) == 1 && StrEqual(weaponName, "weapon_ssg08")) {
        SetEntProp(victim, Prop_Data, "m_ArmorValue", 0, 1);
        damage = float(GetClientHealth(victim) + 1);
        return Plugin_Changed;
      }

    case PERK_GOD: {
      damage += 10.0;
      return Plugin_Changed;
    }
  }
  return Plugin_Continue;
}

public void Perk_onSpawn(int client) {
  if (!IsValidClient(client))
    return;

  if (clientNextPerk[client]) {
    clientPerk[client] = clientNextPerk[client];
    clientNextPerk[client] = PERK_NONE;
  }

  switch (clientPerk[client]) {
    case PERK_HEALTH:
      SetEntityHealth(client, GetClientHealth(client) + 25);

    case PERK_SPEED:
      SetEntPropFloat(client, Prop_Send, "m_flLaggedMovementValue", 1.2);

    case PERK_GOD:
      SetEntityHealth(client, GetClientHealth(client) + 30);
  }
}

void Perk_change(int client, Perk perk) {
  if (clientPerk[client]) {
    clientNextPerk[client] = perk;
  } else {
    clientPerk[client] = perk;
  }
}
