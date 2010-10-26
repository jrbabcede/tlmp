#pragma once

#pragma comment(lib, "ws2_32.lib")

#if (_MSC_VER == 1500)
#pragma comment(lib, "../ExternalLibs/google/lib/libprotobuf.lib")
#pragma comment(lib, "../ExternalLibs/raknet/lib/RakNetLibStatic.lib")
#else
#error Your compiler isn't supported - the libraries to build will need to be built manually.
#endif

#include "raknet/include/RakPeerInterface.h"
#include "raknet/include/RakNetworkFactory.h"
#include "raknet/include/MessageIdentifiers.h"
#include "raknet/include/BitStream.h"

#include "LobbyMessages.h"
#include <string>
using std::wstring;
using std::string;

#include "lobby.pb.h"
using namespace TLMP::LobbyMessages;

#include <map>
using std::map;


namespace TLMP {
  namespace Network {
    namespace Lobby {

      class LobbyServer
      {
      public:
        LobbyServer();
        ~LobbyServer();

        void Initialize(unsigned short port, unsigned short maxconnections);
        void Process();

        template<typename T>
        void BroadcastMessage(LobbyMessage msg, ::google::protobuf::Message *message);
        template<typename T>
        void BroadcastMessage(const AddressOrGUID systemIdentifier, LobbyMessage msg, ::google::protobuf::Message *message);
        template<typename T>
        void SendMessage(const AddressOrGUID systemIdentifier, LobbyMessage msg, ::google::protobuf::Message *message);

      private:
        template<typename T>
        T* ParseMessage(RakNet::BitStream *bitStream);

        // Helpers when receiving messages
        void HandleVersion(const SystemAddress address, LobbyMessages::Version *msgVersion);
        void HandlePlayerName(const SystemAddress address, LobbyMessages::ClientPlayerName *);
        void HandleChatMessage(LobbyMessages::ChatMessage *msgChat);
        void HandlePlayerDisconnect(const SystemAddress address);


        /** Work on received packet data. */
        void WorkMessage(const SystemAddress clientAddress, LobbyMessage msg, RakNet::BitStream *bitStream);

        map<SystemAddress, string> m_PlayerNames;
        RakPeerInterface* m_pServer;
        RakNet::BitStream *m_pBitStream;
        unsigned short m_iPort;
        unsigned short m_iMaxConnections;
      };

    };
  };
};

// Template parameterization
#include "LobbyServer.cpp.h"