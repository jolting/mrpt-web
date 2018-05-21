#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <cstdlib>
#include <functional>
#include <thread>
#include <string>

using tcp = boost::asio::ip::tcp;				//from <boost/asio/ip/tcp.hpp
namespace websocket = boost::beast::websocket; //from <boost/beast/websocket.hpp>
class CWebSocketServer
{
public:
	CWebSocketServer(const std::string &bind, uint16_t port);
	
	/*
	template <typename T>
	operator<<(T &&t)
	{

	}
	*/
private:
	static void do_session(tcp::socket& socket);
};

CWebSocketServer::CWebSocketServer(const std::string &bind, uint16_t port_number)
{
	try
	{
		auto const address = boost::asio::ip::make_address(bind);
		auto const port = static_cast<unsigned short>(port_number);

		//The io_context is required for all I/O
		boost::asio::io_context ioc{1};

		//The acceptor receives incoming connections
		tcp::acceptor acceptor{ioc, {address, port}};
		for(;;)
		{
			//This will receive the new connnection
			tcp::socket socket{ioc};

			//Block until we get a connection
			acceptor.accept(socket);

			//Launch the session, transferring the ownership of the socket
			std::thread{std::bind(
				&do_session,
				std::move(socket))}.detach();
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() <<std::endl;

	}
}

void CWebSocketServer::do_session(tcp::socket& socket)
{
	try
	{
		// Construct the stream by moving in the socket
		websocket::stream<tcp::socket> ws{std::move(socket)};

		// Accept the websocket handshake
		ws.accept();

		for(;;)
		{
			// This buffer holds the incomming message
			boost::beast::multi_buffer buffer;

			//Read a message
			ws.read(buffer);

			// Echo the message back
			ws.text(ws.got_text());
			ws.write(buffer.data());
		}
	}
	catch(boost::system::system_error const& se)
	{
		//This indicates that the session was closed
		if(se.code() != websocket::error::closed)
			std::cerr << "Error: " << se.code().message() << std::endl; 
	}
	catch(std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}