// #pragma once

// #include <atomic>
// #include <string>
// #include <thread>
// #include <mutex>
// #include <unordered_set>
// #include <jsonrpccpp/server/abstractserverconnector.h>
// namespace dev
// {
// template <class S> class CWsRpcServerBase: public jsonrpc::AbstractServerConnector
// {
// public:
//     CWsRpcServerBase(std::string const& _path);
//     virtual bool StartListening();
//     virtual bool StopListening();
//     virtual bool SendReponse(std::string const& _response, void* _addInfo = nullptr);

// protected:
//     virtual void Listen() = 0;
//     virtual void CloseConnection(S _socket) = 0;
//     virtual size_t Write(S _connection, std::string const& _data) = 0;
//     void GenerateResponse(S _connection);

// protected:
//     std::atomic<bool> m_running{false};
//     std::string m_path;
//     std::unordered_set<S> m_sockets;
//     std::mutex x_sockets;
//     std::thread m_listeningThread;
// };
// }