#include "Winsock2.h" // заголовок WS2_32.dll
#include <string>
#include <Windows.h>
#include <tchar.h>
#include <cstdlib>
#include <iostream>
#include <ws2tcpip.h>
#pragma comment(lib, "WS2_32.lib") // экспорт WS2_32.dll
//#define SEND_FIRST_HELLO
//#define SEND_1000
#define SEND_AND_GET


using namespace std;

string SetErrorMsgText(string text, int code);
string GetErrorMsgText(int code);

int _tmain(int argc, _TCHAR* argv[]) {

	
	int out_buffer_lenght = 0;
	WSADATA WSDPointer;
	try
	{

		if (WSAStartup(MAKEWORD(2, 0), &WSDPointer) != 0)
			throw SetErrorMsgText("Startup:", WSAGetLastError());

		cout << "Client started\n"; 


		SOCKET cC;
		
		if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == SOCKET_ERROR)
			throw SetErrorMsgText("Socket:", WSAGetLastError());

		cout << "Client socket created\n";


		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		
		if (inet_pton(AF_INET, "10.14.10.96", &serv.sin_addr) <= 0)
			throw SetErrorMsgText("Invalid IP:", WSAGetLastError());



		if(connect(cC, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw SetErrorMsgText("Connect:", WSAGetLastError());

		cout << "Connected\n";


#ifdef SEND_FIRST_HELLO

		const char* message = "Hello from client!\n";

		if ((out_buffer_lenght = send(cC, message, strlen(message), NULL)) == SOCKET_ERROR)
			throw SetErrorMsgText("Send Error:", WSAGetLastError());

		cout << "Message sent\n";

#endif

#ifdef SEND_1000
		cout << "-------------------1000 Mesages---------------------\n\n";


		string complete_message;

		for (int i = 0; i < 1000; i++) {
			string message_xxx = "Hello from client " + to_string(i) + "\n";
			Sleep(1);
			if ((out_buffer_lenght = send(cC, message_xxx.c_str(), sizeof(message_xxx), NULL)) == SOCKET_ERROR) {
				throw SetErrorMsgText("Send Error: ", WSAGetLastError());
				break;
			}
			
			else {
				cout << "Sent: " << message_xxx << "\n";
			}



		}




	
#endif

		


	#ifdef SEND_AND_GET


		int msg_amount;
		cout << "Enter the amount of messages to be sent: ";
		cin >> msg_amount;


		clock_t start_time = clock();

		string messageus;

		



		for (int i = 0; i < msg_amount; i++) {

			if (i == 0) {
				messageus = "Hello from client " + static_cast<char>(i) + '\n';
			}

			if (send(cC, messageus.c_str(), messageus.size(), NULL) == SOCKET_ERROR) {
				cerr << "Send error: " << WSAGetLastError() << endl;
				break;
			}

			else {
				cout << "Message sent: " << messageus << endl;

			}


			char in_buffer[50];

			if (recv(cC, in_buffer, sizeof(in_buffer), NULL) == SOCKET_ERROR) {
				cerr << "Failed to receive message from server: "<< WSAGetLastError() << endl;
				break;
			}

			else {
				cout << "Received from server: " << in_buffer << endl;

			}



			int iterator = i + 1;
			string tmp = "";
			messageus = "";
			tmp += in_buffer;
			messageus = "Hello from client" + to_string(iterator) + "\n";

		}



		string final_message = "";
		if (send(cC, final_message.c_str(), final_message.size(), NULL) == SOCKET_ERROR) {
			cerr << "Final message error: " << WSAGetLastError() << endl;
		}

		clock_t end_time = clock();

		double time_duration = static_cast<double>(end_time - start_time);

		cout << "Tiem taken to send " << msg_amount << " messages: " << time_duration << "ms" << endl;






		/*int msg_amount;
		cout << "Enter the amount of messages to be transmitted: ";
		cin >> msg_amount;


		clock_t start_time = clock();
		string messageus;
		for (int i = 0; i < msg_amount; i++) {
			if (i == 0) {
				messageus = "Hello from client" + static_cast<char>(i) + '\n';
			}

			if (send(cC, messageus.c_str(), messageus.size(), NULL) == SOCKET_ERROR) {
				cerr << "Failed to send a message: " << WSAGetLastError() << endl;
				break;
			}
			else {
				cout << "Message sent: " << messageus << endl;
			}

			char in_buffer[50];
			if (recv(cC, in_buffer, sizeof(in_buffer), NULL) == SOCKET_ERROR) {
				cerr << "Failed to recv a message: " << WSAGetLastError() << endl;
				break;
			}
			else {
				cout << "Received from server: " << in_buffer << endl;
			}

			int iterator = i + 1;
			string tmp = "";
			messageus = "";
			tmp += in_buffer;
			messageus = "Hello from client" + to_string(iterator) + "\n";
		}


		string final_message = "";

		if (send(cC, final_message.c_str(), final_message.size(), NULL) == SOCKET_ERROR) {
			cerr << "Failed to send the last message: " << WSAGetLastError() << endl;
		}
		else {
			cout << "Last message sent. Disconnecting" << endl;
		}

		clock_t end_time = clock();

		double time_duration = static_cast<double>(end_time - start_time);

		cout << "Time taken for " << msg_amount << " messages: " << time_duration << "ms" << endl;*/



	#endif



		if (closesocket(cC) == SOCKET_ERROR)
			throw SetErrorMsgText("Close client:", WSAGetLastError());

		cout << "Client socket closed\n";


		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());

		cout << "WSACleanup\n";


	}
	catch (string error_text) {
		cout << endl << error_text;
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
