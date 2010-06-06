#pragma once

#include "Common.h"
#include "Entity.h"
#include "Network.h"
#include "NetworkEntity.h"

#include "network.pb.h"

#include "CItem.h"
#include "CInventory.h"
#include "CEquipment.h"

namespace TLMP {

  extern CLevel *Level;
  extern bool   ServerSendClientItemSpawn;
  extern bool   ClientSendServerItemSpawn;

  const int     CLIENT_COMMON_BASE_ID = 0x1000;

  // Hold the equipped items here
  struct EquippedItem {
    PVOID         item;
    int           slot;
    PVOID         pinv;
  };
  extern vector<EquippedItem> *EquippedItems;

  // New item structure
  class CItemOld {
  public:
    u32 id;
    u64 guid;
    u32 level;
    u32 unk0, unk1;
    union {
      void*e;
      char*ce;
    };

    /*
    u64 getCEquipmentGUID() {
      char *ce = (char*)this;
      u64* guidptr = (u64*)(ce + 0x168);
      return *guidptr;
    }*/
  };

  //

  /*
  // Item Structure
  struct CItem {
    uint id;
    unsigned long long guid;
    int level;
    int unk0, unk1;
    union {
      void*e;
      char*ce;
    };
    //index_t equipped_entity;
    //int equipped_slot;
    CItem() {
      //equipped_entity = -1;
    }
  };
  */

  // Network Item-specific Callbacks
  void NetItem_OnItemCreated(u64 guid, u32 level, u32 unk0, u32 unk1);


  // Hooked Functions
  void _item_initialize_pre STDARG;

  void _item_create_pre STDARG;
  void _item_create_post STDARG;

  void _item_drop_pre STDARG;

  void _item_pick_up_pre STDARG;
  void _item_pick_up_post STDARG;

  void _item_equip_pre STDARG;
  void _item_equip_post STDARG;

  void _item_unequip_pre STDARG;

  void SendItemListToPlayer();

  bool CheckNetworkList_HasExisting(vector<NetworkEntity *> *list, int commonId);
};
