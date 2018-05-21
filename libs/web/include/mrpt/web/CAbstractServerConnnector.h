#include <jsonrpccpp/server/iclientconnectionhandler.h>
#include <string>
#include <cstdlib>
#include <jsonrpccpp/common/specificationwriter.h>

namespace jsonrpc {

class CAbstractServerConnector {
public:
  CAbstractServerConnector() {
      this->handler = NULL;
  }
  virtual ~CAbstractServerConnector() {}

  /**
   * This method should signal the Connector to start waiting for requests, in
   * any way that is appropriate for the derived connector class.
   * If something went wrong, this method should return false, otherwise true.
   */
  virtual bool StartListening() = 0;
  /**
   * This method should signal the Connector to stop waiting for requests, in
   * any way that is appropriate for the derived connector class.
   * If something went wrong, this method should return false, otherwise true.
   */
  virtual bool StopListening() = 0;

  void ProcessRequest(const std::string &request, std::string &response) {

      if(this->handler != NULL) {
          this->handler->HandleRequest(request, response);
      }
  }

  void SetHandler(IClientConnectionHandler *handler)
  {
      this->handler = handler;
  }

  IClientConnectionHandler *GetHandler(){
      return this->handler;
  }

private:
  IClientConnectionHandler *handler;
};

} /* namespace jsonrpc */
