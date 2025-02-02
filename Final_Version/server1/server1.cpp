#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
#include<vector>
#include<thread> // Include the thread header for thread usage
#include<sstream>
#include<fstream>


using namespace std;

#pragma comment(lib, "ws2_32.lib")


vector<SOCKET> clients;
vector<string> vec_sendername;
vector<string> vec_recievername;
vector<string> vec_function;

bool Initialize_server()
{
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void InteractWithClient(SOCKET clientSocket)
{
    cout << "Client connected" << endl;
    
    int i = 0;
    string temp_sendername;
    string temp_recivername;
    string temp_function;
    string filename;

    char buffer[4096];

    while (1) 
    {
            
            int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer), 0);

            if (bytesrecvd <= 0)
            {
                cout << "Client disconnected" << endl;
                // Remove client from the client list after disconnect
                for (int i = 0;i < clients.size();i++)
                {
                    if (clients[i] == clientSocket)
                    {
                        clients.erase(clients.begin() + i);
                        vec_sendername.erase(vec_sendername.begin() + i);
                        vec_recievername.erase(vec_recievername.begin() + i);
                        vec_function.erase(vec_function.begin() + i);
                        break;
                    }
                }


                closesocket(clientSocket); // Close the client socket
                break;
            }
            else
            {
                if (i == 0)
                {
                    string line(buffer, bytesrecvd),value;
                    istringstream data(line);
                    data >> value;
                    vec_sendername.push_back(value);
                    temp_sendername = value;
                    data >> value;
                    vec_recievername.push_back(value);
                    temp_recivername= value;
                    data >> value;
                    vec_function.push_back(value);
                    temp_function= value;
                    ++i;
                }
                else
                {
                    string message(buffer, bytesrecvd);

                    if (message == "quit")
                    {
                        cout << "Client disconnected Now" << endl;
                        send(clientSocket, message.c_str(), message.length(), 0);
                        for (int i = 0;i < clients.size();i++)
                        {
                            if (clients[i] == clientSocket)
                            {
                                clients.erase(clients.begin() + i);
                                vec_sendername.erase(vec_sendername.begin() + i);
                                vec_recievername.erase(vec_recievername.begin() + i);
                                vec_function.erase(vec_function.begin() + i);
                                break;
                            }
                        }
                        closesocket(clientSocket); // Close the client socket
                        break;
                    }

                    cout << "Message from client: " << message << endl;

                    if (temp_function == "Friend")
                    {
                        for (int i = 0;i < clients.size();i++)
                        {
                            if (temp_recivername == vec_sendername[i]   &&  temp_sendername==vec_recievername[i]    &&  temp_function==vec_function[i])
                            {
                                send(clients[i], message.c_str(), message.length(), 0);
                            }
                        }
                    }
                    else if (temp_function == "Group")
                    {
                        for (int i = 0;i < clients.size();i++)
                        {
                            if ((temp_recivername == vec_recievername[i] && temp_function == vec_function[i])   &&  (vec_sendername[i]!=temp_sendername))
                            {
                                send(clients[i], message.c_str(), message.length(), 0);
                            }
                        }
                    }
                }
            }       
    }
}

int main()
{
    if (!Initialize_server())
    {
        cout << "\nWinsock initialization failed " << endl;
        return 1;
    }

    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_socket == INVALID_SOCKET)
    {
        cout << "\nSocket Creation Failed" << endl;
        return 1;
    }

    // Create Address Structure
    sockaddr_in serveraddr;

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(1234);

    // Convert IP address in binary form (0.0.0.0)
    if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1)
    {
        cout << "\nSetting Address Structure Failed" << endl;
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

    // Bind
    if (bind(listen_socket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)))
    {
        cout << "\nBind Failed" << endl;
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

    // Listen
    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "\nListen Failed" << endl;
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

    cout << "Server has listening on port 8080" << endl;

    while (1)
    {
        // Accept
        SOCKET clientSocket = accept(listen_socket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
        {
            cout << "\nInvalid Client Socket" << endl;
            continue; // Skip to next iteration if accept fails
        }

        clients.push_back(clientSocket);

        // Start a new thread to handle the interaction with the client
        thread t1(InteractWithClient, clientSocket);
        t1.detach();
    }

    closesocket(listen_socket); // Close the listen_socket
    WSACleanup(); // Cleanup the socket API
    cin.get(); // Wait for user input to close the program
    return 0;
}
