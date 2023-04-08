using System;
using System.Net;
using System.Net.Sockets;

class Program
{
    static void Main(string[] args)
    {
        if (args.Length < 2)
        {
            Console.WriteLine("Usage: sendstring <ip address> <port> <string>");
            return;
        }

        string ipAddress = args[0];
        int port = int.Parse(args[1]);
        string message = args[2];

        try
        {
            TcpClient client = new TcpClient(ipAddress, port);
            NetworkStream stream = client.GetStream();

            byte[] data = System.Text.Encoding.ASCII.GetBytes(message);
            stream.Write(data, 0, data.Length);

            Console.WriteLine("Sent: {0}", message);

            stream.Close();
            client.Close();
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error: {0}", ex.Message);
        }
    }
}
