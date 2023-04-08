using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        if (args.Length < 1)
        {
            Console.WriteLine("Usage: tcplistener <port>");
            return;
        }

        int port = int.Parse(args[0]);

        TcpListener listener = new TcpListener(IPAddress.Any, port);
        listener.Start();

        Console.WriteLine("Waiting for connections...");

        while (true)
        {
            TcpClient client = listener.AcceptTcpClient();

            Console.WriteLine("Client connected: {0}", client.Client.RemoteEndPoint);

            NetworkStream stream = client.GetStream();

            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);

            string message = Encoding.ASCII.GetString(buffer, 0, bytesRead);

            Console.WriteLine("Received: {0}", message);

            stream.Close();
            client.Close();
        }
    }
}
