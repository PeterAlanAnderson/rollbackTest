#include "connection.h"
#include <iostream>
#include <boost/asio.hpp>
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

#include <iostream>

#define IPADDRESS "127.0.0.1" // "192.168.1.64"
#define UDP_PORT 13251

using boost::asio::ip::udp;
using boost::asio::ip::address;

void Sender(std::string in) {
    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint remote_endpoint = udp::endpoint(address::from_string(IPADDRESS), UDP_PORT);
    socket.open(udp::v4());

    boost::system::error_code err;
    auto sent = socket.send_to(boost::asio::buffer(in), remote_endpoint, 0, err);
    socket.close();
    std::cout << "Sent Payload --- " << sent << "\n";
}

class Connection {
    boost::asio::io_service io_service;
    udp::socket socket{ io_service };
    boost::array<char, 1024> recv_buffer;
    udp::endpoint remote_endpoint;

    int count = 3;

    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred) {
        if (error) {
            std::cout << "Receive failed: " << error.message() << "\n";
            return;
        }
        std::cout << "Received: '" << std::string(recv_buffer.begin(), recv_buffer.begin() + bytes_transferred) << "' (" << error.message() << ")\n";

        if (--count > 0) {
            std::cout << "Count: " << count << "\n";
            wait();
        }
    }

    void wait() {
        socket.async_receive_from(boost::asio::buffer(recv_buffer),
            remote_endpoint,
            boost::bind(&Client::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void Receiver()
    {
        socket.open(udp::v4());
        socket.bind(udp::endpoint(address::from_string(IPADDRESS), UDP_PORT));

        wait();

        std::cout << "Receiving\n";
        io_service.run();
        std::cout << "Receiver exit\n";
    }
};

int main(int argc, char* argv[])
{
    Client client;
    std::thread r([&] { client.Receiver(); });

    std::string input = argc > 1 ? argv[1] : "hello world";
    std::cout << "Input is '" << input.c_str() << "'\nSending it to Sender Function...\n";

    for (int i = 0; i < 3; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        Sender(input);
    }

    r.join();
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
