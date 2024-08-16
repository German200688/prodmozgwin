
#include <iostream>
#include <cstdlib>
#include <librdkafka/rdkafka.h>
#include <csignal>
#include "common.cpp"
#include "serial/serial.h"

 // Настройки для операционки
#ifdef _WIN32
#include <windows.h>
#else

#endif

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;


static volatile std::sig_atomic_t run = 1;

void my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds); // 100 ms - по умолчанию
#else
    usleep(milliseconds * 1000); //  по умолчанию
#endif
}

void enumerate_ports()
{
    vector<serial::PortInfo> devices_found = serial::list_ports();

    vector<serial::PortInfo>::iterator iter = devices_found.begin();

    while (iter != devices_found.end())
    {
        serial::PortInfo device = *iter++;
        printf("(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
            device.hardware_id.c_str());
    }
}

void print_usage()
{
    cerr << "Usage: test_serial {-e|<serial port address>} ";
    cerr << "<baudrate> [test string]" << endl;
}

int run1(int argc, char** argv)
{


    if (argc < 3) {
        cerr << "Usage: test_serial <serial port address> ";
        cerr << "<baudrate> [test string]" << endl;
        return 0;
    }
    // Argument 1 is the serial port
    const char* port_my = "COM10";
    const char* baud_my = "9600";



    const char* value_my = "0070001P";
    std::cout << value_my << std::endl;
    string port(port_my);

    // Argument 2 is the baudrate
    unsigned long baud = 0;
    sscanf(baud_my, "%lu", &baud);

    // port, baudrate, timeout in milliseconds
    serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(1000));

    cout << "Is the serial port open?";
    if (my_serial.isOpen())
        cout << " Yes." << endl;
    else
        cout << " No." << endl;

    // Get the Test string
    int count = 0;
    string com_string;
    string test_string1 = "0";
    if (argc == 4) {
        std::cout << "value_my = ";
        com_string = value_my;
    //    std::cout << value_my << std::endl;
        std::cout << com_string << std::endl;
     //   std::cout << test_string1 << std::endl;
    }
    else {
        std::cout << "value_my999" << std::endl;
        com_string = "1234567";
    }

    // Test the timeout, there should be 1 second between prints

    cout << "Timeout == 1000ms, asking for 1 more byte than written." << endl;
   

 //   cout << "Timeout == 250ms, asking for 1 more byte than written." << endl;
    count = 0;
    while (count < 2) { 

        size_t bytes_wrote = my_serial.write(com_string);

        string result = my_serial.read(com_string.length() - 1);

        cout << result;



        count += 1;
    }
    com_string = "0";
 

}

 /**
 * @brief Signal termination of program
 */
static void stop(int sig) {
    run = 0;
}

int main(int argc, char** argv) {
    try {

        argc = 4;
        std::cout << "argc = " << argc << std::endl;


        vector<serial::PortInfo> devices_found = serial::list_ports();

    }
    catch (exception& e) {
        std::cout << "81" << std::endl;
        cerr << "Unhandled Exception: " << e.what() << endl;
    }

    ;
    rd_kafka_t *consumer; 
    rd_kafka_conf_t* conf;
    rd_kafka_resp_err_t err;
    char errstr[512];
    // Create client configuration
    conf = rd_kafka_conf_new();
    // User-specific properties that you must set
    set_config(conf, "bootstrap.servers", "localhost:19092");

    // Fixed properties


    set_config(conf, "group.id", "romb1"); 
    set_config(conf, "auto.offset.reset", "earliest");



    // Create the Consumer instance.
    consumer = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));

    if (!consumer) {

        std::cout << "Failed to create new consumer: %s" << errstr << std::endl;
        return 1;
    }
    rd_kafka_poll_set_consumer(consumer); // cxvxv

    // Convert the list of topics to a format suitable for librdkafka. ТОПИК
    const char *topic = "prodmozgromb"; 
    rd_kafka_topic_partition_list_t *subscription = rd_kafka_topic_partition_list_new(1);  
    rd_kafka_topic_partition_list_add(subscription, topic, RD_KAFKA_PARTITION_UA);
    // Subscribe to the list of topics.
    err = rd_kafka_subscribe(consumer, subscription); 
    if (err) {
        std::cout << "Failed to subscribe to " << subscription->cnt << " topics: " << rd_kafka_err2str(err) << std::endl;
        rd_kafka_topic_partition_list_destroy(subscription);
        rd_kafka_destroy(consumer);

        return 1;
    }

    rd_kafka_topic_partition_list_destroy(subscription);
    // Install a signal handler for clean shutdown.
    signal(SIGINT, stop);

    // Start polling for messages.
    while (run) {
        rd_kafka_message_t *consumer_message; 
        consumer_message = rd_kafka_consumer_poll(consumer, 3000);
        std::cout << consumer_message << std::endl;
        std::cout << rd_kafka_consumer_poll(consumer, 3000) << std::endl;
        if (!consumer_message) {
            std::cout << consumer_message << std::endl;
            std::cout << "Waiting..." << std::endl;
            rd_kafka_commit(consumer, NULL, 0); 
            continue;
        }

        if (consumer_message->err) {
            if (consumer_message->err == RD_KAFKA_RESP_ERR__PARTITION_EOF) {
                /* We can ignore this error - it just means we've read
                 * everything and are waiting for more data.
                 */
            }
            else {
                std::cout << "Consumer error: " << rd_kafka_message_errstr(consumer_message) << std::endl;
                return 1;
            }
        }
        else {
            std::cout << "Consumed event from topic " << rd_kafka_topic_name(consumer_message->rkt) << ": key = " << (int)consumer_message->key_len << ", " << (char*)consumer_message->key << " value = " << (char*)consumer_message->payload << std::endl;
            char* a853 = (char*)consumer_message->payload;


            if (argc < 3) {
                cerr << "Usage: test_serial <serial port address> ";
                cerr << "<baudrate> [test string]" << endl;
                return 0;
            }
            // Argument 1 is the serial port
            const char* port_my = "COM10";
            const char* baud_my = "9600";


            //   const char* value_my = "1";
            char* a852 = "P";
            const char* value_my = strcat(a853, a852);


       //     const char* value_my = "0070001P";
            std::cout << value_my << std::endl;


            string port(port_my);

            // Argument 2 is the baudrate
            unsigned long baud = 0;
            sscanf(baud_my, "%lu", &baud);

            // port, baudrate, timeout in milliseconds
            serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(1000));

            cout << "Is the serial port open?";
            if (my_serial.isOpen())
                cout << " Yes." << endl;
            else
                cout << " No." << endl;

            // Get the Test string
            int count = 0;
            string test_string;
            string test_string1 = "0";
            if (argc == 4) {
                std::cout << "value_my104" << std::endl;
                test_string = value_my;
                std::cout << value_my << std::endl;
                std::cout << test_string << std::endl;
                std::cout << test_string1 << std::endl;
            }
            else {
                std::cout << "value_my999" << std::endl;
                test_string = "1234567";
            }

            // Test the timeout, there should be 1 second between prints

            cout << "Timeout == 1000ms, asking for 1 more byte than written." << endl;
           


            count = 0;
            while (count < 2) { 

                size_t bytes_wrote = my_serial.write(test_string);
               
                string result = my_serial.read(test_string.length() - 1);

                cout << result;
               


                count += 1;
            }
            test_string = "0";
            std::cout << "220" << std::endl;
        }

        // Free the message when we're done.
        rd_kafka_message_destroy(consumer_message);
    }

    // Close the consumer: commit final offsets and leave the group.
    std::cout << "Closing consumer" << std::endl;
    rd_kafka_consumer_close(consumer);

    // Destroy the consumer.
    rd_kafka_destroy(consumer);

    return 0;
};





