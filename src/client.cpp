#include <opencv2/opencv.hpp>
#include <zmq.hpp>

int main(int argc, char **argv) {
    bool show_image = false;

    zmq::context_t context(1);
    zmq::socket_t client(context, ZMQ_SUB);
    client.connect("tcp://localhost:5555");
    client.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    while (true) {
        zmq::message_t buffer;
        client.recv(&buffer);
        cv::Mat image = cv::imdecode(cv::Mat(buffer.size(), 1, 0, buffer.data()), 3);

        if (show_image) {
            cv::imshow("image", image);
            const int key = cv::waitKey(1);
            if (key == 'q') {
                break;
            }
        }
        else {
            std::cout << "Received:" << image.size() << std::endl;
        }
    }

    client.close();
    cv::destroyAllWindows();
    return 0;
}