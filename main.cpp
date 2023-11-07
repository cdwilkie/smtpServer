#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>


int main() {

   int sock = socket(AF_INET, SOCK_STREAM, 0);

   if (sock == -1) {
      perror("Socket creation failed");
      return 1;
   }

   struct sockaddr_in server;
   server.sin_family = AF_INET;
   server.sin_port = htons(25);
   inet_pton(AF_INET, "", &server.sin_addr);

   if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == -1){
      perror("Connection failed");
      close(sock);
      return 1;
   }


   /********** Message Functionality **********/
   const std::string message = "HELO example.com\r\n";
   send(sock, message.c_str(), message.size(), 0);

   char buffer[1024];
   int bytes_received = recv(sock, buffer, sizeof(buffer), 0);
   if (bytes_received == -1) {
      perror("Receive failed");
   } 
   else {
      buffer[bytes_received] = '\0';
      std::cout << "Received: " << buffer << std::endl;
   }
   /********** ---------- ---------- **********/
   close(sock);
   return 0;
}