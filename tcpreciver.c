#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET servidor, cliente;
    struct sockaddr_in servidor_addr, cliente_addr;
    char mensagem[1024];
    int tamanho_cliente, tamanho_mensagem, i;

    // Inicializa o Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Erro ao inicializar o Winsock: %d\n", WSAGetLastError());
        return 1;
    }

    // Cria o socket TCP
    if ((servidor = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Erro ao criar o socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Define o endereço do servidor
    servidor_addr.sin_family = AF_INET;
    servidor_addr.sin_addr.s_addr = INADDR_ANY;
    servidor_addr.sin_port = htons(atoi(argv[1]));

    // Vincula o socket ao endereço do servidor
    if (bind(servidor, (struct sockaddr *)&servidor_addr, sizeof(servidor_addr)) == SOCKET_ERROR) {
        printf("Erro ao vincular o socket ao endereço do servidor: %d\n", WSAGetLastError());
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    // Aguarda conexões de clientes
    listen(servidor, SOMAXCONN);
    printf("Servidor aguardando conexoes na porta %s...\n", argv[1]);

    // Aceita conexões de clientes
    tamanho_cliente = sizeof(cliente_addr);
    if ((cliente = accept(servidor, (struct sockaddr *)&cliente_addr, &tamanho_cliente)) == INVALID_SOCKET) {
        printf("Erro ao aceitar conexao de cliente: %d\n", WSAGetLastError());
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    printf("Cliente conectado!\n");

    // Recebe mensagens do cliente e imprime no console
    while ((tamanho_mensagem = recv(cliente, mensagem, 1024, 0)) > 0) {
        mensagem[tamanho_mensagem] = '\0';
        printf("Mensagem recebida: %s", mensagem);
    }

    // Verifica se houve erro no recebimento da mensagem
    if (tamanho_mensagem == SOCKET_ERROR) {
        printf("Erro ao receber mensagem: %d\n", WSAGetLastError());
        closesocket(cliente);
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    printf("Conexao encerrada.\n");

    // Fecha os sockets e limpa o Winsock
    closesocket(cliente);
    closesocket(servidor);
    WSACleanup();

    return 0;
}

