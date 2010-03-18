#pragma once

#include "Common.h"
#include "Inventory.h"
#include "ServerState.h"

namespace TLMP {

  extern PVOID EntityManager;
  extern bool ClientAllowSpawn;
  extern bool ServerAllowSpawn;

  void _entity_initialize_pre STDARG;

  struct c_entity {
    uint id;
    unsigned long long guid;
    int level;
    void*e;
    char*ce;
    float dst[2];
    uint32_t last_pos_send;
    bool is_running;
    float hp, mana;
    void*last_target;
    bool last_moving;
    bool is_player;
    Vector3 test;
    Vector3 pos_update, pos_update_src;
    unsigned int pos_update_time;
    bool noitems;
    //slist<index_t> equipped_items;

    static const int hp_offset = 0x394;
    static const int mana_offset = 0x3b8;
    static const int destroy_offset = 0x158;

    bool m_bInitialized;

    c_entity();
    void init();
    template<typename t> t& offset(int offset) const;
    Vector3* GetPosition() const;
    void SetPosition(const Vector3 & pos);
    Vector3* GetDestination() const;
    void SetDestination(const Vector3 & pos);
    float& get_hp();
    float& get_mana();
    void destroy();
    void*& target();
    bool& attack_midair();
    bool& running();
    bool& moving();
    c_inventory*& inventory();

    unsigned int& GetLevel() const;
    unsigned long long& GetGUID() const;
  };

  extern vector<c_entity *> *ServerEntities;

};