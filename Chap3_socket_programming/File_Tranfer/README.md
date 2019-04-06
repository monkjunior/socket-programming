# Basic file tranfer concept
For example, we will use TCP socket.
Our socket will bind to an address and port then listen for connections.
When the connection is created, the client will send the name of file to server.
Server will read the name of the file, retrieve the file from disk, and send a file back to client.

