#include <opencv2/opencv.hpp>
#include <zmq.hpp>

int main(int argc, char **argv) {
    zmq::context_t context(1);
    zmq::socket_t server(context, ZMQ_PUB);
    server.bind("tcp://*:5555");

    cv::VideoCapture capture(0);
    if(!capture.isOpened())
    {
        std::cout << "Error: capture.isOpened()" << std::endl;
        return 0;
    }

    while (true) {
        cv::Mat frame, result;

        if (!capture.read(frame)) {
            std::cout << "Error: capture.read()" << std::endl;
            break;
        }

        std::vector<uchar> buffer;
        cv::imencode(".jpg", frame, buffer);
        server.send((void*)(buffer.data()), buffer.size());
    }

    capture.release();
}