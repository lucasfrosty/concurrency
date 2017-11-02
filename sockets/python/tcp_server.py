import socket

def main():
  host = '127.0.0.1'
  port = 8080

  # iniciating the socket
  s = socket.socket()

  # binding the address into the socket
  s.bind((host, port))

  # tell our socket to listen to 1 connection at time
  s.listen(1)

  # accept the connection and store the client and the address that it came from
  c, addr = s.accept()

  print('Conexão recebida por: ', str(addr))

  # make the server to run infinitely
  while True:
    # we are going start transfering data between client and server

    # data received from the client in the size of 1024 bytes (decoded using utf-8) at time
    data = c.recv(1024).decode('utf-8')
    
    # if it haves no data, break the while loop
    if (not data):
      break

    print('Mensagem recebida pelo client: ', data)

    # now we going to send the data but, but upper cased
    data_upper_cased = data.upper()
    c.send(data_upper_cased.encode('utf-8')) # notice that we encoded it back using utf-8
  
  c.close()

if __name__ == '__main__':
  main()



