#include "mrpt/web/CWebSocketUtility.hpp"

#include <CRPCRawLogAbstract.h>
#include <mrpt/web/CWebSocketJsonRpcServer.h>
// #include <mrpt/web/CWebSocketAdvanced.h>

#include <cstdlib>
#include <functional>
#include <thread>
#include <string>
#include <mutex>

std::mutex mtx;
class CRPCRawLog : public CRPCRawLogAbstract
{
public:
  Json::Value Playlist_GetPlaylists() override
  {

  }
  Json::Value Playlist_GetItems() override
  {

  }
};
void function(const std::string& text)
{
  mtx.lock();
  

  mtx.unlock();
}
int main(int argc,char* argv[])
{
  //Check the command line arguments,
  if (argc != 5)
  {
      std::cerr <<
          "Usage: mrpt-ws-rpc <address> <port> <doc_root> <threads>\n" <<
          "Example:\n" <<
          "    mrpt-ws-rpc 127.0.0.1 8080 . 1\n";
      return EXIT_FAILURE;
  }
  auto const address = boost::asio::ip::make_address(argv[1]);
  auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
  auto const doc_root = std::make_shared<std::string>(argv[3]);
  auto const threads = std::max<int>(1, std::atoi(argv[4]));
  try{
    // CWebSocketAdvanced server(address , ssl::context::sslv23 , port , doc_root , threads);
    CWebSocketJsonRpcServer server(address, port);
    server.StartListening();
    getchar();
    server.StopListening();
  }
  catch(const std::exception& e)
  {
    std::cerr <<"Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}