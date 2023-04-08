import socket

# Define o endereço IP e a porta do servidor
endereco_servidor = ('', 8081)

# Cria o socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Liga o socket ao endereço do servidor
sock.bind(endereco_servidor)

# Escuta por conexões entrantes
sock.listen(1)

print(f'Aguardando conexões em {endereco_servidor[0]}:{endereco_servidor[1]}...')

while True:
    # Espera por uma conexão
    conexao, endereco_cliente = sock.accept()

    print(f'Conexão recebida de {endereco_cliente[0]}:{endereco_cliente[1]}')

    # Recebe a mensagem do cliente
    mensagem = conexao.recv(1024).decode()
    print(f'Mensagem recebida: {mensagem}')

    # Fecha a conexão com o cliente
    conexao.close()
