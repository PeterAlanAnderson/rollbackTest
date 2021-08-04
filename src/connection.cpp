#include "connection.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>
#include <functional>
#include <GameStateManager.h>
#include <connectionHandler.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <updServer.h>

#include <iostream>

#define IPADDRESS "127.0.0.1" // "192.168.1.64"
#define UDP_PORT 13251

#pragma comment(lib,"ws2_32.lib")

connection::connection(int connType, GameStateManager& gsm) {
	gameStateManager = gsm;
	type = connType;
}

void connection::init() {
	const char* port = "8080";
	//std::cout << "doing init\n";
	//boost::system::error_code ec;
	//std::cout << "doing init2\n";

	//boost::asio::io_context context;
	//std::cout << "doing init3\n";
	std::cout << "doing init4\n";
	boost::asio::io_service io_service;
	udpServer server(io_service, std::atoi(port));
	//boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("93.184.216.34", ec), 80);


	//boost::asio::ip::tcp::socket socket(context);
	std::cout << "doing init5\n";
	io_service.run();

	//socket.connect(endpoint, ec);
	std::cout << "doing init6\n";

	//if (!ec) {
	//	std::cout << "CONNECTED!" << std::endl;
	//}
	//else {
	//	std::cout << "failed to connect to address:\n" << ec.message() << std::endl;
 //	}
	//system("pause");

}

//typedef websocketpp::server<websocketpp::config::asio> server;
//typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;
//
////typedef websocketpp::client<websocketpp::config::asio_client> client;
//
//connection::connection(int connectionType, GameStateManager &gsm) {
//	type = connectionType;
//	gameStateManager = gsm;
//}
//
//void connection::init() {
//	if (type == 1) {
//		startServer();
//	}
//	else {
//		startClient();
//	}
//}
//
//void connection::startClient() {
//	client.set_access_channels(websocketpp::log::alevel::all);
//	client.clear_access_channels(websocketpp::log::alevel::frame_payload);
//	client.set_error_channels(websocketpp::log::elevel::all);
//
//	client.init_asio();
//}
//
//void connection::startServer() {
//	server.set_error_channels(websocketpp::log::elevel::all);
//	server.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
//	server.clear_access_channels(websocketpp::log::alevel::frame_payload);
//	server.init_asio();
//	server.listen(8080);
//	std::cout << "LISTENING ON PORT 8080";
//	server.set_open_handler([](websocketpp::connection_hdl hdl) {
//		std::cout << "connection open" << '\n';
//		});
//	server.set_message_handler([](websocketpp::connection_hdl hdl) {
//		std::cout << "connection open" << '\n';
//		});
//	server.start_accept();
//	server.run();
//
//}
//
//static void connectionOpen(websocketpp::connection_hdl hdl) {
//	std::cout << "connection open" << '\n';
//}
