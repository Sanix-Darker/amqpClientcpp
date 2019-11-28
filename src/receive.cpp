#include <iostream>
#include "SimplePocoHandler.h"


// Command test : ./receive 127.0.0.1 guest guest / queue_test


int main(int argc, char** argv)
{

    std::string HOST = argv[1]; // "localhost"
    std::int16_t PORT = 5672; // 5672
    std::string LOGIN = argv[2]; // guest
    std::string PASSWORD = argv[3]; // guest
    std::string VIRTUAL_HOST = argv[4]; // /

    std::string QUEUE = argv[5]; // "queue_test"

    // std::cout << "You have entered " << argc
    //      << " arguments:" << "\n";

    // std::cout << HOST << "|" << PORT << "|" << LOGIN << "|" << PASSWORD << "|" << VIRTUAL_HOST << "|" << QUEUE << "|" << MESSAGE;

    // for (int i = 0; i < argc; ++i)
    //     std::cout << argv[i] << "\n";

    SimplePocoHandler handler(HOST, PORT);
    AMQP::Connection connection(&handler, AMQP::Login(LOGIN, PASSWORD), VIRTUAL_HOST);
    AMQP::Channel channel(&connection);

    channel.declareQueue(QUEUE);
    channel.consume(QUEUE, AMQP::noack).onReceived(
            [](const AMQP::Message &message,
                    uint64_t deliveryTag,
                    bool redelivered)
            {

                std::cout <<" [x] Received "<<message.message() << std::endl;
            });

    std::cout << " [*] Waiting for messages. To exit press CTRL-C\n";
    handler.loop();
    return 0;
}
