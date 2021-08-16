#pragma once
#include <functional>

#include <boost/asio.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>

#include <GameStateManager.h>

typedef websocketpp::server<websocketpp::config::asio> Server;
typedef websocketpp::client<websocketpp::config::asio_client> Client;

class connection {
public:
    connection(int connectionType, GameStateManager& gameStateManager);
    GameStateManager gameStateManager;
    void init();
    int type;
    Server server;
    Client client;
    void startClient();
    void startServer();
    void connectionOpen(websocketpp::connection_hdl hdl);
};
