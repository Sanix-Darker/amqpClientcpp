
#include <iostream>
#include <string>

#include "SimplePocoHandler.h"

// Command test : ./send 127.0.0.1 guest guest / queue_test "Bonjour tout le monde"

int main(int argc, char** argv)
{

    std::string HOST = argv[1]; // "localhost"
    std::int16_t PORT = 5672; // 5672
    std::string LOGIN = argv[2]; // guest
    std::string PASSWORD = argv[3]; // guest
    std::string VIRTUAL_HOST = argv[4]; // /

    std::string QUEUE = argv[5]; // "queue_test"
    std::string MESSAGE = argv[6]; // "Ceci est un message test !"

    // std::cout << "You have entered " << argc
    //      << " arguments:" << "\n";
    // std::cout << HOST << "|" << PORT << "|" << LOGIN << "|" << PASSWORD << "|" << VIRTUAL_HOST << "|" << QUEUE << "|" << MESSAGE;
    // for (int i = 0; i < argc; ++i)
    //     std::cout << argv[i] << "\n";

    SimplePocoHandler handler(HOST, PORT);
    AMQP::Connection connection(&handler, AMQP::Login(LOGIN, PASSWORD), VIRTUAL_HOST);
    AMQP::Channel channel(&connection);

    channel.onReady([&]()
    {
        if(handler.connected())
        {
            channel.publish("", QUEUE, MESSAGE);
            std::cout << " [x] Sent '"+MESSAGE+"' in '"+QUEUE+"'" << std::endl;
            handler.quit();
        }
    });
    handler.loop();

    return 0;
}
