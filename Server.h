#ifndef SERVER_H_
#define SERVER_H_ \
// The header file socket.h includes a number of definitions of structures needed for sockets.


#include <sys/socket.h>  // The header file socket.h includes a number of definitions of structures needed for sockets.
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#include<signal.h>
#include <sstream>
#include <netinet/in.h>  // The header file in.h contains constants and structures needed for internet domain addresses.
#include <iostream>
#include "CLI.h"


using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file
class DioWithSocket:public DefaultIO{
    int client_socket;
public:
    DioWithSocket(int c_socket){
        client_socket = c_socket;
    }
    string read() override;
    void write(string text) override;
    void write(float f) override;
    void read(float *f) override;
};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
        DioWithSocket dioWithSocket(clientID);
        CLI cli(&dioWithSocket);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    bool is_clients_end;
    int server_socket;
    // sockaddr is a structure describing an Internet socket address.
    sockaddr_in client_addr;
    sockaddr_in server_addr;
    // the thread to run the start() method in
	thread* start_thread;

public:
	Server(int port)throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */

