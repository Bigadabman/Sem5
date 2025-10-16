#include <iostream>
#include "Winsock2.h"
#include <string>      
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")
//#define GET_IP_AND_PORT
//#define GET_FIRST_HELLO
//#define GET_1000

#define GET_AND_SEND

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string text, int code);


int main(int argc, TCHAR* argv[])
{


    WSADATA wsaData;
    SOCKET sS;

    char in_buffer[50];
    int in_buffer_length = 0;
    string complete_message;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw SetErrorMsgText("Startup: ", WSAGetLastError());
        cout << "Server started\n";

        if ((sS = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
            throw SetErrorMsgText("Socket: ", WSAGetLastError());
        cout << "Socket created\n";


        SOCKADDR_IN serv;
        serv.sin_family = AF_INET;
        serv.sin_port = htons(2000);
        serv.sin_addr.s_addr = INADDR_ANY;

        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
            throw SetErrorMsgText("Bind: ", WSAGetLastError());
        cout << "Bind successful\n";

        if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
            throw SetErrorMsgText("Listen: ", WSAGetLastError());
        cout << "Now listening...\n";

  

#ifdef GET_IP_AND_PORT
        SOCKET cS;
        SOCKADDR_IN clnt;
        memset(&clnt, 0, sizeof(clnt));
        int lclnt = sizeof(clnt);

        if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET)
            throw SetErrorMsgText("Accept: ", WSAGetLastError());
        cout << "Acccepted connection creation\n";



        char ip_buffer[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &clnt.sin_addr, ip_buffer, sizeof(ip_buffer)) == nullptr) {
            cerr << "Error converting IP address" << WSAGetLastError() << endl;
        }
        cout << "----------Client info----------" << endl;
        cout << "Client's IP address: " << ip_buffer << endl;
        cout << "Client's port: " << ntohs(clnt.sin_port) << endl;

#endif



#ifdef GET_FIRST_HELLO
        cout << "------------------------------------------------" << endl;


        in_buffer_length = recv(cS, in_buffer, sizeof(in_buffer) - 1, NULL);
        if (in_buffer_length == SOCKET_ERROR)
            throw SetErrorMsgText("Receive: ", WSAGetLastError());
        in_buffer[in_buffer_length] = '\0';
        cout << "Received from client: " << in_buffer << endl;


        if (closesocket(cS) == SOCKET_ERROR)
            throw SetErrorMsgText("Client closesocket: ", WSAGetLastError());


        cout << "------------------------------------------------" << endl;
#endif


  #ifdef GET_1000
        cout << "-------------------1000 Mesages---------------------\n\n";
        
        for (int i = 0; i < 1000; i++) {
            
            in_buffer_length = recv(cS, in_buffer, sizeof(in_buffer) - 1, NULL);

            if (in_buffer_length == SOCKET_ERROR) {
                cerr << "Recv error: " << WSAGetLastError() << endl;
                break;
         }
            else if (in_buffer == 0) {
                cout << "Client disconnected";
               break;
           }
           else {
                in_buffer[in_buffer_length] = '\0';
                complete_message += in_buffer;

                size_t pos;

                while ((pos = complete_message.find('\n')) != string::npos) {
                    string msg = complete_message.substr(0, pos);
                  cout << "Received from client: " << msg << endl;
                    complete_message.erase(0, pos + 1);
                }


            }


        }
        
        if (closesocket(cS) == SOCKET_ERROR)
            throw SetErrorMsgText("Client closesocket: ", WSAGetLastError());


          /*  int iterator = 0;
            while (true) {
                in_buffer_length = recv(cS, in_buffer, sizeof(in_buffer) - 1, NULL);
                if (in_buffer_length == SOCKET_ERROR) {
                    cerr << "Recv error: " << WSAGetLastError() << endl;
                    break;
                }
                else if (in_buffer_length == 0) {
                    cout << "Client disconnected" << endl;
                    break;
                }
                else {
                    in_buffer[in_buffer_length] = '\0';
                    complete_message += in_buffer;

                    size_t pos;
                    while ((pos = complete_message.find('\n')) != string::npos) {
                        string msg = complete_message.substr(0, pos);
                        cout << "Got from client: " << msg << endl;
                        complete_message.erase(0, pos + 1);
                    }

                    continue;
                }
            }

            if (closesocket(cS) == SOCKET_ERROR)
                throw SetErrorMsgText("Client Closesocket: ", WSAGetLastError());*/

#endif



#ifdef GET_AND_SEND


        while(true)
        {

            SOCKET cS;
            SOCKADDR_IN clnt;
            memset(&clnt, 0, sizeof(clnt));
            int lclnt = sizeof(clnt);
            

            if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET) {
                throw SetErrorMsgText("Accept: ", WSAGetLastError());
            }
            
            cout << "Acccepted connection creation\n";



            while (true) {

                in_buffer_length = recv(cS, in_buffer, sizeof(in_buffer) - 1, NULL);

                if (in_buffer_length == SOCKET_ERROR) {
                    throw SetErrorMsgText("Failed to recv message from a client", WSAGetLastError());
                    break;
                }
                else if (in_buffer_length <= 0) {
                    cout << "Client disconnected" << endl;
                    break;
                }

                in_buffer[in_buffer_length] = '\0';

                cout << "Received from client: " << in_buffer << endl;

                if (send(cS, in_buffer, sizeof(in_buffer), NULL) == SOCKET_ERROR) {
                    throw SetErrorMsgText("Failed to send back message to client", WSAGetLastError());
                    break;
                }
                else {
                    cout << "Send back to client: " << in_buffer << endl;
                }

            }

            if (closesocket(cS) == SOCKET_ERROR)
                throw SetErrorMsgText("Client Closesocket: ", WSAGetLastError());

        }

       
#endif
            system("pause");


        if (closesocket(sS) == SOCKET_ERROR)
            throw SetErrorMsgText("Server Closesocket: ", WSAGetLastError());
        cout << "Socket closed\n";

        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Clenup: ", WSAGetLastError());
        cout << "Cleanup succesful\n";
    }

    catch (string err)
    {
        cout << "\n" + err;
    }
    return 0;
}


string SetErrorMsgText(string text, int code) {
    char code_chr = static_cast<char>(code);
    return text + GetErrorMsgText(code) + "(" + code_chr + ")";
}

string GetErrorMsgText(int code) {

    string message;

        switch (code) {
        case WSAEINTR:
            message = "Function was stopped in the working process";
            break;
        case WSAEACCES:
            message = "Access denied";
            break;
        case WSAEFAULT:
            message = "Wring Address";
            break;
        case WSAEINVAL:
            message = "Argument Error";
            break;
        case WSAEMFILE:
            message = "Too many files opened";
            break;
        case WSAEWOULDBLOCK:
            message = "The resource is temporary unavailable";
            break;
        case WSAEINPROGRESS:
            message = "Operation is in development process";
            break;
        case WSAEALREADY:
            message = "Operation is already in execution process";
            break;
        case WSAENOTSOCK:
            message = "Socket set incorrectly";
            break;
        case WSAEDESTADDRREQ:
            message = "Address required";
            break;
        case WSAEMSGSIZE:
            message = "The message is too long";
            break;
        case WSAEPROTOTYPE:
            message = "Wring protocol type for a socket";
            break;
        case WSAENOPROTOOPT:
            message = "Error in a protocol option";
            break;
        case WSAEPROTONOSUPPORT:
            message = "Protocol is not supported";
            break;
        case WSAESOCKTNOSUPPORT:
            message = "Socket type is not supported";
            break;
        case WSAEOPNOTSUPP:
            message = "Operation is not supported";
            break;
        case WSAEPFNOSUPPORT:
            message = "Protocol type is not supported";
            break;
        case WSAEAFNOSUPPORT:
            message = "Address type is not supported";
            break;
        case WSAEADDRINUSE:
            message = "Address is already in use";
            break;
        case WSAEADDRNOTAVAIL:
            message = "Requested address could not be used";
            break;
        case WSAENETDOWN:
            message = "Network disconnected";
            break;
        case WSAENETUNREACH:
            message = "Could not reach the network";
            break;
        case WSAENETRESET:
            message = "The network shot down the connection";
            break;
        case WSAECONNABORTED:
            message = "Program denial of network";
            break;
        case WSAECONNRESET:
            message = "Connection restored";
            break;
        case WSAENOBUFS:
            message = "Not enough memory for buffers";
            break;
        case WSAEISCONN:
            message = "Socket is already connected";
            break;
        case WSAENOTCONN:
            message = "Socket disconnected";
            break;
        case WSAESHUTDOWN:
            message = "Could not execute send(): socket shut down";
            break;
        case WSAETIMEDOUT:
            message = "Connection timed out";
            break;
        case WSAECONNREFUSED:
            message = "Connection refused";
            break;
        case WSAEHOSTDOWN:
            message = "Host shut down";
            break;
        case WSAEHOSTUNREACH:
            message = "No route for host";
            break;
        case WSAEPROCLIM:
            message = "Too many processes";
            break;
        case WSASYSNOTREADY:
            message = "Network unreachable";
            break;
        case WSAVERNOTSUPPORTED:
            message = "This version is not supported";
            break;
        case WSANOTINITIALISED:
            message = "WS2_32.DLL was not initialized";
            break;
        case WSAEDISCON:
            message = "Shut down is in process";
            break;
        case WSATYPE_NOT_FOUND:
            message = "Type not found";
            break;
        case WSAHOST_NOT_FOUND:
            message = "Host not found";
            break;
        case WSATRY_AGAIN:
            message = "Unautharized host not found";
            break;
        case WSANO_RECOVERY:
            message = "Undefined error";
            break;
        case WSANO_DATA:
            message = "No record by a requiered type";
            break;
        case WSA_INVALID_HANDLE:
            message = "Descriptor came in with an error";
            break;
        case WSA_INVALID_PARAMETER:
            message = "One or more parameters came in with an error";
            break;
        case WSA_IO_INCOMPLETE:
            message = "I/O object is not is a signal state";
            break;
        case WSA_IO_PENDING:
            message = "Operation is to be completed lately";
            break;
        case WSA_NOT_ENOUGH_MEMORY:
            message = "Not enough memory";
            break;
        case WSA_OPERATION_ABORTED:
            message = "Operation aborted";
            break;
        case WSAEINVALIDPROCTABLE:
            message = "Invalid service";
            break;
        case WSAEINVALIDPROVIDER:
            message = "Invalid service version";
            break;
        case WSAEPROVIDERFAILEDINIT:
            message = "Failed to initialize a service";
            break;
        case WSASYSCALLFAILURE:

                message = "System call was aborted";
            break;

        }


    return message;
}