#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

using tcp = boost::asio::ip::tcp;       
namespace http = boost::beast::http;    

int main(int argc, char** argv)
{
	try
	{
		auto const host = "47.108.192.203";
		auto const port = "8080";
		auto const target = "/calculator?expression=1*2*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18*19*20";
		int version = 11;

		boost::asio::io_context ioc;

		tcp::resolver resolver{ ioc };
		tcp::socket socket{ ioc };

		auto const results = resolver.resolve(host, port);

		boost::asio::connect(socket, results.begin(), results.end());

		http::request<http::string_body> req{ http::verb::get, target, version };
		req.set(http::field::host, host);
		req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

		http::write(socket, req);

		boost::beast::flat_buffer buffer;

		http::response<http::string_body> res;

		http::read(socket, buffer, res);

		std::cout << res.body() << std::endl;

		boost::system::error_code ec;
		socket.shutdown(tcp::socket::shutdown_both, ec);

		if (ec && ec != boost::system::errc::not_connected)
			throw boost::system::system_error{ ec };
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}