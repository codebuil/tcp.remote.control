#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in servidor;
    char mensagem[1024], resposta[1024];
    int tamanho_resposta, i;

    // Inicializa o Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Erro ao inicializar o Winsock: %d\n", WSAGetLastError());
        return 1;
    }

    // Cria o socket TCP
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Erro ao criar o socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Define o endereço do servidor
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = inet_addr(argv[1]);
    servidor.sin_port = htons(atoi(argv[2]));

    // Conecta ao servidor
    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        printf("Erro ao conectar ao servidor: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Envia a mensagem para o servidor
    sprintf(mensagem, "%s\n", argv[3]);
    if (send(sock, mensagem, strlen(mensagem), 0) < 0) {
        printf("Erro ao enviar mensagem para o servidor: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Mensagem enviada: %s", mensagem);

    // Recebe a resposta do servidor
    if ((tamanho_resposta = recv(sock, resposta, 1024, 0)) == SOCKET_ERROR) {
        printf("Erro ao receber resposta do servidor: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    resposta[tamanho_resposta] = '\0';
    printf("Resposta do servidor: %s", resposta);

    // Fecha o socket e limpa o Winsock
    closesocket(sock);
    WSACleanup();

    return 0;
}

