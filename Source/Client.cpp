#include "Client.h"

using namespace TLMP::Network;

Client& Client::getSingleton()
{
  static Client m_pSingleton;
  return m_pSingleton;
}

Client::Client()
{
  m_pClient = NULL;
  m_pBitStream = new RakNet::BitStream(1024);

  m_pOnConnected = NULL;
  m_pOnDisconnected = NULL;
  m_pOnConnectFailed = NULL;
}

Client::~Client()
{
  delete m_pBitStream;
}

void Client::Connect(const char* address, u16 port)
{
  log("Client connecting to %s (%i)", address, port);

  if (m_pClient) {
    m_pClient->Shutdown(0);
  }

  m_pClient = RakNetworkFactory::GetRakPeerInterface();

  SocketDescriptor socketDescriptor(0, 0);
  m_pClient->Startup(1, 30, &socketDescriptor, 1);
  m_pClient->Connect(address, port, 0, 0);
}

void Client::Disconnect()
{
  log("Client disconnecting");

  if (m_pClient) {
    m_pClient->Shutdown(0);
    m_pClient = NULL;
  }
}

void Client::SetCallback_OnConnected(OnConnected callback)
{
  m_pOnConnected = callback;
}

void Client::SetCallback_OnDisconnected(OnDisconnected callback)
{
  m_pOnDisconnected = callback;
}

void Client::SetCallback_OnConnectFailed(OnConnectFailed callback)
{
  m_pOnConnectFailed = callback;
}

void Client::ReceiveMessages()
{
  if (!m_pClient)
    return;

  Packet *packet = m_pClient->Receive();
  while (packet)
  {
    switch(packet->data[0])
    {
    case ID_CONNECTION_REQUEST_ACCEPTED:
      if (m_pOnConnected) {
        m_pOnConnected(NULL);
      }
      OnConnect(NULL);
      break;
    case ID_NO_FREE_INCOMING_CONNECTIONS:
      if (m_pOnConnectFailed) {
        m_pOnConnectFailed(NULL);
      }
      break;
    case ID_DISCONNECTION_NOTIFICATION:
      if (m_pOnDisconnected) {
        m_pOnDisconnected(NULL);
      }
      break;
    case ID_CONNECTION_LOST:
      if (m_pOnDisconnected) {
        m_pOnDisconnected(NULL);
      }
      break;
    case ID_CONNECTION_ATTEMPT_FAILED:
      if (m_pOnConnectFailed) {
        m_pOnConnectFailed(NULL);
      }
      break;
    case ID_USER_PACKET_ENUM+1:
      u32 msg;
      m_pBitStream->Reset();
      m_pBitStream->Write((const char *)packet->data, packet->length);
      m_pBitStream->IgnoreBits(8);
      m_pBitStream->Read<u32>(msg);

      WorkMessage((Message)msg, m_pBitStream);

      break;
    }

    m_pClient->DeallocatePacket(packet);
    packet = m_pClient->Receive();
  }
}

void Client::OnConnect(void *args)
{
  TLMP::NetworkMessages::Player player;

  // Init player
  player.set_id((u64)15);
  player.set_name("drivehappy");
  player.set_type(NetworkMessages::Player_ClassType_ALCHEMIST);

  SendMessage<NetworkMessages::Player>(C_PLAYER_INFO, &player);

  log("[CLIENT] Connected.");
}

void Client::WorkMessage(Message msg, RakNet::BitStream *bitStream)
{
  //log("Message Received: %x", msg);

  switch (msg) {
  case S_GAME_JOIN:
    {
      NetworkMessages::Entity *message = ParseMessage<NetworkMessages::Entity>(m_pBitStream);

      // Create player on the client instance
      log("Player Joined Game:");
      log("  guid: %016I64X", message->guid());
      log("  level: %i", message->level());
      log("  position: %f %f %f", message->position().Get(0).x(), message->position().Get(0).y(), message->position().Get(0).z());
      log("  commonId: %i", message->id());

      Vector3 position;
      position.x = message->position().Get(0).x();
      position.y = message->position().Get(0).y();
      position.z = message->position().Get(0).z();

      ClientAllowSpawn = true;
      otherPlayer = SpawnPlayer(message->guid(), message->level(), position);
      ClientAllowSpawn = false;

      // Store the monster ptr in our shared network list
      NetworkEntity *networkItem = new NetworkEntity(otherPlayer, message->id());

      if (!NetworkSharedEntities)
        NetworkSharedEntities = new vector<NetworkEntity*>();
      NetworkSharedEntities->push_back(networkItem);
    }
    break;

  case S_PLAYER_INFO:
    {
      NetworkMessages::Player *player = ParseMessage<NetworkMessages::Player>(m_pBitStream);

      log("Player Info Received:");
      log("  id = %016I64X", player->id());
      log("  name = %s", player->name().c_str());
      log("  type = %i", player->type());
    }
    break;

  case S_SPAWN_MONSTER:
    {
      // !!!!!!
      // Skip this for now, GUID looks bad
      /*

      NetworkMessages::Entity *entity = ParseMessage<NetworkMessages::Entity>(m_pBitStream);
      Vector3 position;
      
      position.x = entity->position().Get(0).x();
      position.y = entity->position().Get(0).y();
      position.z = entity->position().Get(0).z();

      log("[CLIENT] Received Monster Spawn");
      log("         Level = %i", entity->level());
      log("         GUID  = %016I64X", entity->guid());
      log("         NoItems = %i", entity->noitems());
      log("         CommonId = %i", entity->id());
      log("         Position = %f %f %f", position.x, position.y, position.z);

      // Unlock suppressed entity creation and create the monster
      ClientAllowSpawn = true;
      PVOID newEntity = SpiderSomeCreate(EntityManager, entity->guid(), entity->level(), entity->noitems());
      ClientAllowSpawn = false;

      log("New entity: (pre-Init) %p\n", newEntity);
      newEntity = EntityInitialize(*(void**)(((char*)EntityManager)+0x0c), newEntity, &position, entity->level());
      log("New entity: %p\n", newEntity);

      // Store the monster ptr in our shared network list
      NetworkEntity *networkEntity = new NetworkEntity(newEntity, entity->id());

      if (!NetworkSharedEntities)
        NetworkSharedEntities = new vector<NetworkEntity*>();
      NetworkSharedEntities->push_back(networkEntity);
      */
    }
    break;

  case S_ENTITY_SETDEST:
    {
      NetworkMessages::Position *destination = ParseMessage<NetworkMessages::Position>(m_pBitStream);

      //log("[CLIENT] SetDest received from server");

      if (otherPlayer) {
        //log("  Getting destination...");
        //PVOID otherDest = GetDestination(otherPlayer);

        // Convert otherPlayer into an entity
        c_entity otherPlayerEntity;
        otherPlayerEntity.e = otherPlayer;
        otherPlayerEntity.init();

        Vector3* otherDest = (Vector3*)GetDestination(otherPlayer);

        //log("  Retrieved destination");
        //log("  Dest ptr = %p", otherDest);
        //log("  Dest = %f %f %f", otherDest->x, otherDest->y, otherDest->z);
        //log("  Setting destination...");
        SetDestination(otherPlayer, otherDest, destination->x(), destination->z());
        //log("  Done.");

        /*
        log("Set Destination Info:");
        log("  x: %f", destination->x());
        log("  y: %f", destination->y());
        log("  z: %f", destination->z());
        */
      }
    }
    break;

  case S_ITEM_CREATE:
    {
      NetworkMessages::Item *item = ParseMessage<NetworkMessages::Item>(m_pBitStream);

      log("[CLIENT] Received item creation:");
      log("         guid = %016I64X", item->guid());
      log("         id = %i", item->id());

      if (UnitManager) {
        ClientAllowSpawn = true;
        PVOID itemCreated = ItemCreate(UnitManager, item->guid(), item->level(), item->unk0(), item->unk1());
        //ItemInitialize(itemCreated, 
        log("Created: %p", itemCreated);
        ClientAllowSpawn = false;

        NetworkEntity *networkItem = new NetworkEntity(itemCreated, item->id());

        if (!NetworkSharedItems)
          NetworkSharedItems = new vector<NetworkEntity *>();
        NetworkSharedItems->push_back(networkItem);
      } else {
        log("[ERROR] Could not create item: UnitManager is null!");
      }
    }
    break;

  case S_ITEM_DROP:
    {
      NetworkMessages::ItemDrop *itemDropped = ParseMessage<NetworkMessages::ItemDrop>(m_pBitStream);
      Vector3 *itemPosition = new Vector3();
      itemPosition->x = itemDropped->position().Get(0).x();
      itemPosition->y = itemDropped->position().Get(0).y();
      itemPosition->z = itemDropped->position().Get(0).z();

      log("[CLIENT] Received ItemDrop:");
      log("         id: %p", itemDropped->id());
      log("         pos: %f, %f, %f", itemPosition->x, itemPosition->y, itemPosition->z);
      log("         unk: %i", itemDropped->unk0());

      if (UnitManager) {
        PVOID item = NULL;
        vector<NetworkEntity *>::iterator itr;

        if (NetworkSharedItems) {
          // Ensure that the item has been created before we attempt to drop it
          for (itr = NetworkSharedItems->begin(); itr != NetworkSharedItems->end(); itr++) {
            if ((*itr)->getCommonId() == itemDropped->id()) {
              item = (*itr)->getInternalObject();
              log("[CLIENT] Found item to drop (commonId = %i): %p", itemDropped->id(), item);

              // Drop the item
              // SUPPRESSED for now, it's not quite working right and causes crash
              if (drop_item_this) {
                /* We don't know who's inventory this was dropped from
                c_entity ne;
                ne.e = me;
                ne.init();
                c_inventory *inv = ne.inventory();

                ItemUnequip(inv, item);
                */
                ItemDrop(drop_item_this, item, *itemPosition, 1);
              } else {
                log("[ERROR] drop_item_this is null (drivehappy - This is a ptr to a CLevel object)");
              }

              break;
            }
          }
        } else {
          log("[ERROR] NetworkSharedItems is null.");
        }
      } else {
        log("[ERROR] Could not drop item: UnitManager is null!");
      }
    }
    break;

  case S_ITEM_PICKUP:
    {
      NetworkMessages::ItemPickup *itemPickup = ParseMessage<NetworkMessages::ItemPickup>(m_pBitStream);

      log("[CLIENT] Received ItemPickup:");
      log("         id: %p", itemPickup->id());
      log("         owner: %i", itemPickup->ownerid());

      if (UnitManager) {
        PVOID item = NULL;
        PVOID owner = NULL;
        vector<NetworkEntity *>::iterator itr;

        if (NetworkSharedItems) {
          // Ensure that the item has been created before we attempt to pick it up
          for (itr = NetworkSharedItems->begin(); itr != NetworkSharedItems->end(); itr++) {
            if ((*itr)->getCommonId() == itemPickup->id()) {
              item = (*itr)->getInternalObject();
              log("[CLIENT] Found item to pickup (commonId = %x): %p", itemPickup->id(), item);
              break;
            }
          }

          // Ensure that the entity picking up the item has been created before we use it
          for (itr = NetworkSharedEntities->begin(); itr != NetworkSharedEntities->end(); itr++) {
            log("[CLIENT] Searching %p == %p  ?", (*itr)->getCommonId(), itemPickup->ownerid());
            if ((*itr)->getCommonId() == itemPickup->ownerid()) {
              owner = (*itr)->getInternalObject();
              log("[CLIENT] Found owner of equip (commonId = %i): %p", itemPickup->ownerid(), owner);
          }

          if (item && owner) {
            // Pickup the item
            ItemPickup(owner, item, drop_item_this);
          } else {
            log("[ERROR] owner or item is null (drop_item_this = CLevel object");
          }
        }
        } else {
          log("[ERROR] NetworkSharedItems is null.");
        }
      } else {
        log("[ERROR] Could not pickup item: UnitManager is null!");
      }
    }
    break;

  case S_ITEM_EQUIP:
    {
      NetworkMessages::ItemEquip *itemEquipped = ParseMessage<NetworkMessages::ItemEquip>(m_pBitStream);
      PVOID item = NULL;
      PVOID owner = NULL;
      int slot = itemEquipped->slot();
      vector<NetworkEntity *>::iterator itr;

      log("[CLIENT] Received item equip:");
      log("         id: %i", itemEquipped->id());
      log("         ownerid: %i", itemEquipped->ownerid());

      if (NetworkSharedItems) {
        // Ensure that the item has been created before we attempt to unequip it
        for (itr = NetworkSharedItems->begin(); itr != NetworkSharedItems->end(); itr++) {
          if ((*itr)->getCommonId() == itemEquipped->id()) {
            item = (*itr)->getInternalObject();
            log("[CLIENT] Found item to equip (commonId = %i): %p", itemEquipped->id(), item);
          }
        }

        // Ensure that the entity unequipping the item has been created before we use it
        for (itr = NetworkSharedEntities->begin(); itr != NetworkSharedEntities->end(); itr++) {
          log("[CLIENT] Searching %p == %p  ?", (*itr)->getCommonId(), itemEquipped->ownerid());
          if ((*itr)->getCommonId() == itemEquipped->ownerid()) {
            owner = (*itr)->getInternalObject();
            log("[CLIENT] Found owner of equip (commonId = %i): %p", itemEquipped->ownerid(), owner);
          }
        }

        // If the owner and item are valid, unequip
        if (owner && item) {
          log("[SUPRESSED] Equipping item...");
          //ItemEquip(owner, item, slot, 0);
        }
      }
    }
    break;

    
  case S_ITEM_UNEQUIP:
    {
      NetworkMessages::ItemUnequip *itemUnequipped = ParseMessage<NetworkMessages::ItemUnequip>(m_pBitStream);
      PVOID item = NULL;
      PVOID owner = NULL;
      vector<NetworkEntity *>::iterator itr;

      log("[CLIENT] Received item unequip:");
      log("         id: %i", itemUnequipped->id());
      log("         ownerid: %i", itemUnequipped->ownerid());

      if (NetworkSharedItems) {
        // Ensure that the item has been created before we attempt to unequip it
        for (itr = NetworkSharedItems->begin(); itr != NetworkSharedItems->end(); itr++) {
          if ((*itr)->getCommonId() == itemUnequipped->id()) {
            item = (*itr)->getInternalObject();
            log("[CLIENT] Found item to unequip (commonId = %i): %p", itemUnequipped->id(), item);
          }
        }

        // Ensure that the entity unequipping the item has been created before we use it
        for (itr = NetworkSharedEntities->begin(); itr != NetworkSharedEntities->end(); itr++) {
          log("[CLIENT] Searching %p == %p  ?", (*itr)->getCommonId(), itemUnequipped->ownerid());
          if ((*itr)->getCommonId() == itemUnequipped->ownerid()) {
            owner = (*itr)->getInternalObject();
            log("[CLIENT] Found owner of unequip (commonId = %i): %p", itemUnequipped->ownerid(), owner);
          }
        }

        // If the owner and item are valid, unequip
        if (owner && item) {
          ItemUnequip(owner, item);
        }
      }

    }
    break;

  }     
}