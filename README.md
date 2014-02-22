lusin
=====

Lusin is an attempt to create something for flexible traffic accounting with minimal costs.
It is full compatible with BPF (http://en.wikipedia.org/wiki/Berkeley_Packet_Filter)

Currently lusin consists of  counter and storage server.

Counter counts network traffic according to BPF rules and send all data to storage server via UDP . 
Store server collects and stores incoming data into mysql server or predefined *.sql backup file.

Probably, there are more efficient ways to do job like this. 
Please, do not hesitate to comment or report about bugs
