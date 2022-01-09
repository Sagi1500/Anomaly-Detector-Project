
#include "Server.h"
/**
 * constructor.
 * @param port is the server's port.
 */
Server::Server(int port) throw(const char *) {
    //initialize the server's socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        throw "invalid socket";
    }
    //internet address
    server_addr.sin_addr.s_addr = INADDR_ANY;
    //the address family for the transport address.
    server_addr.sin_family = AF_INET;
    //port address
    server_addr.sin_port = htons(port);
    // bind the socket to the address and port number.
    int bind_value = bind(server_socket,
                          (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (bind_value < 0) {
        throw "invalid bind";
    }
    // listen on the socket, with 4 max connection requests queued
    int listen_value = listen(server_socket, 4);
    if (listen_value < 0) {
        throw "invalid listen";
    }
    is_clients_end = false;
}
/**
 * sigHandler for handling if tere is a signal problem.
 * @param sigNum
 */
void sigHandler(int sigNum) {
    //if there is a signal problem
    exit(sigNum);
}
/**
 * starting the server and the ClientHandler which it received
 * for connecting with all the clients that want to connect.
 * @param ch is the ClientHandler
 */
void Server::start(ClientHandler &ch) throw(const char *) {
    //define a thread for start method and initialize the server's thread
    start_thread = new thread([&ch, this]() {
        //check the signal
        signal(SIGALRM, sigHandler);
        //loop that runs all the clients
        while (!is_clients_end) {
            // the size of the client's address.
            socklen_t client_addr_size = sizeof(client_addr);
            //set alarm for 1 second (wait to accept a client for 3 second)
            alarm(1);
            //accept a client
            int new_client_socket = accept(server_socket,
                                           (struct sockaddr *) &client_addr,
                                           &client_addr_size);
            // if accept succeeded
            if (new_client_socket >= 0) {
                ch.handle(new_client_socket);
                close(new_client_socket);
            }
            // reset alarm (canceled the current alarm)
            alarm(0);
        }
        // after finishing with all the clients
        close(server_socket);
    });

}

/**
 * stop the connection with the clients (there isn't more clients).
 */
void Server::stop() {
    //no more clients
    is_clients_end = true;
    start_thread->join(); // do not delete this!
}

Server::~Server() {}


// the 4 functions below are override functions for DfaultIO with socket.
string DioWithSocket::read() {
    char c;
    string data = "";
    //if received the last data or character
    while (c!='\n'&&data != "done") {
        //received a character from client's socket
        recv(client_socket, &c, sizeof(char), 0);
        data += c;
    }
    return data;
}

void DioWithSocket:: write(string text) {
    //initialize text to be a const
    const char *data = text.c_str();
    // send the data to client by the client's socket
    send(client_socket, data, strlen(data), 0);
}

void DioWithSocket::write(float f) {
    ostringstream ss;
    ss <<f;
    string s(ss.str());
    write(s);
    //need to implement this methode
}

void DioWithSocket::read(float *f) {
    //need to implement this methode
}

