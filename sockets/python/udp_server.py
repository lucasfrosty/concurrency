import socket

def main():
  host = '127.0.0.1'
  port = 3000

  # by default a socket is TCP, so now we need to set it as a UDP
  s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  s.bind((host, port))
  print('UDP server started')
  
  while True:
    data, addr = s.recvfrom(1024)
    data = data.decode('utf-8')
    
    print('Mensagem de: ', str(addr))
    print('Mensagem recebida: ', data)

    data_to_upper_case = data.upper()
    print('Sending: ', data_to_upper_case)

    s.sendto(data_to_upper_case.encode('utf-8'), addr)
  
  s.close()

if __name__ == '__main__':
  main()


