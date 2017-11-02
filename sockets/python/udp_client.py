import socket

def main():
  host = '127.0.0.1'
  port = 3001

  server = (host, 3000)

  s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  s.bind((host, port))

  message = input('Envie sua msg: ')

  while message != 'q':
    s.sendto(message.encode('utf-8'), server)
    data, addr = s.recvfrom(1024)
    data = data.decode('utf-8')

    print('Mensagem recebida pelo servidor: ', data)
    message = input('Envie outra mensagem: ')
  
  s.close()

if __name__ == '__main__':
  main()
