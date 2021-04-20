#include "connection.h"
#include <iostream>
#include <boost/asio.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>
#include <functional>
#include <GameStateManager.h>
#include <connectionHandler.h>

typedef websocketpp::server<websocketpp::config::asio> server;
typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

//typedef websocketpp::client<websocketpp::config::asio_client> client;

connection::connection(int connectionType, GameStateManager &gsm) {
	type = connectionType;
	gameStateManager = gsm;
}

void connection::init() {
	if (type == 1) {
		startServer();
	}
	else {
		startClient();
	}
}

void connection::startClient() {
	client.set_access_channels(websocketpp::log::alevel::all);
	client.clear_access_channels(websocketpp::log::alevel::frame_payload);
	client.set_error_channels(websocketpp::log::elevel::all);

	client.init_asio();
}

void connection::startServer() {
	server.set_error_channels(websocketpp::log::elevel::all);
	server.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
	server.clear_access_channels(websocketpp::log::alevel::frame_payload);
	server.init_asio();
	server.listen(8080);
	std::cout << "LISTENING ON PORT 8080";
	server.start_accept();
	server.run();
	server.set_open_handler([](websocketpp::connection_hdl hdl) {
		std::cout << "connection open" << '\n';
		});
}

static void connectionOpen(websocketpp::connection_hdl hdl) {
	std::cout << "connection open" << '\n';
}
