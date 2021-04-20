#pragma once
#include <boost/asio.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>
#include <functional>
#include <GameStateManager.h>

typedef websocketpp::server<websocketpp::config::asio> server;
typedef websocketpp::client<websocketpp::config::asio_client> client;

class connection {
public:
    connection(int connectionType, GameStateManager &gameStateManager);
    GameStateManager gameStateManager;
    void init();
    int type;
    server server;
    client client;
    void startClient();
    void startServer();
    void connectionOpen(websocketpp::connection_hdl hdl);
};
