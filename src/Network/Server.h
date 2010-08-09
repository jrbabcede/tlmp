#pragma once

#include "Common.h"

namespace TLMP {

  namespace Network {

    class Server {
    public:
      typedef void (*OnListening)(void *);
      typedef void (*OnShutdown)(void *);
      typedef void (*OnClientConnect)(void *);
      typedef void (*OnClientDisconnect)(void *);
      

      static Server& getSingleton();

      void Listen(u16 port, u16 maxconnections);
      void Shutdown();

      void SetCallback_OnListening(OnListening callback);
      void SetCallback_OnShutdown(OnShutdown callback);
      void SetCallback_OnClientConnect(OnClientConnect callback);
      void SetCallback_OnClientDisconnect(OnClientDisconnect callback);

      inline void SetGameStarted(bool value)  { m_bGameStarted = value; if (m_bGameStarted) m_bWaitingForGame = true; }
      inline bool GetGameStarted()            { return m_bGameStarted; }
      inline bool HasGameStarted()            { return m_bWaitingForGame; }

      void ReceiveMessages();

      template<typename T>
      void SendMessage(Message msg, ::google::protobuf::Message *message);

    protected:
      Server();
      Server(const Server&);
      Server& operator=(const Server&);
      ~Server();

    private:
      template<typename T>
      T* ParseMessage(RakNet::BitStream *bitStream);

      void WorkMessage(Message msg, RakNet::BitStream *bitStream);

      void SendClientEntities();

      RakPeerInterface *m_pServer;
      RakNet::BitStream *m_pBitStream;
      
      OnListening         m_pOnListening;
      OnShutdown          m_pOnShutdown;
      OnClientConnect     m_pOnClientConnect;
      OnClientDisconnect  m_pOnClientDisconnect;

      bool m_bWaitingForGame;
      bool m_bGameStarted;
    };

  };

};

// Template parameterization, needs to be defined after above declarations
#include "Server.cpp.h"