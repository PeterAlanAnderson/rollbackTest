#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

using boost::asio::ip::udp;
class udpServer {
public:
	udpServer(boost::asio::io_service& io_service, short port)
		: socket_(io_service, udp::endpoint(udp::v4(), port))
	{
		udp_receive();
	}

	void udp_receive() {
		std::cout << "in receive\n" << socket_.local_endpoint() << std::endl;
		socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_,
			[this](boost::system::error_code ec, std::size_t recvd_bytes) {
				if (!ec && recvd_bytes > 0) {
					std::cout << data_ << std::endl;
					udp_send_back();
				}
				else {
					udp_receive();
				}
			});
	}
	void udp_send_back() {
		std::string message = "Sender endpoint : ";
		message += sender_endpoint_.address().to_string().c_str();
		message += " Port ";
		message += std::to_string((int)sender_endpoint_.port());
		message += "Message : ";
		message += data_;
		socket_.async_send_to(boost::asio::buffer(message.c_str(), message.length()), sender_endpoint_,
			[this](boost::system::error_code ec, std::size_t recvd_bytes) {
				udp_receive();
			});
	}
private:
	udp::socket socket_;
	udp::endpoint sender_endpoint_;
	enum { max_length = 1024 };
	char data_[max_length];
};