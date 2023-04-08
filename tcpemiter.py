import socket
import sys

# Obtém a string a ser enviada da linha de comando
mensagem = ' '.join(sys.argv[1:])

# Define o endereço IP e a porta do servidor
endereco_servidor = ('192.168.1.3', 8081)

# Cria o socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conecta o socket ao endereço do servidor
sock.connect(endereco_servidor)

# Envia a mensagem para o servidor
sock.sendall(mensagem.encode())

# Espera pela resposta do servidor
#resposta = sock.recv(1024).decode()
#print(f'Resposta do servidor: {resposta}')

# Fecha a conexão
sock.close()
