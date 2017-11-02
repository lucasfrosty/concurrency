import socket

def main():
  host = '127.0.0.1'
  port = 8080

  s = socket.socket()
  s.connect((host, port))

  message = input("Digite alguma mensagem: ")


  # message != q is to set that if you send a message saying 'q', the client will close.
  while message != 'q':
    # encoding again our message into utf-8
    s.send(message.encode('utf-8'))

    # we will get the message sent back and decode it using utf-8
    data = s.recv(1024).decode('utf-8')
    print('O servidor respondeu: ', data)
    message = input("Digite outra mensagem (para fechar digite 'q'):  ")
  
  s.close()

if __name__ == '__main__':
  main()