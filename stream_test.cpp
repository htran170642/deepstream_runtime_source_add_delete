#include "mysql_client.h"
#include <thread>
#include <chrono>

int main() {

    const std::string host = "192.168.1.6:3306";
    const std::string user = "root";
    const std::string password = "admin";
    const std::string database = "ds_streams";
    MySQLCRUD crud(host, user, password, database);
    
    std::cout << "Starting streams crud..." <<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(20));

    // add new cam to db 
    if (!crud.createCamera("rtsp://127.0.0.1:5554/stream_1", true, "Security", "Entrance", false)) {
        std::cerr << "Failed to create a camera record." << std::endl;
    }

    if (!crud.readCameras()) {
        std::cerr << "Failed to read camera records." << std::endl;
    }
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(20));
    // add new cam to db 
    if (!crud.createCamera("rtsp://127.0.0.1:5554/stream_1", true, "Security", "Entrance", false)) {
        std::cerr << "Failed to create a camera record." << std::endl;
    }

    if (!crud.readCameras()) {
        std::cerr << "Failed to read camera records." << std::endl;
    }
    std::cout << std::endl;

    // update cam source id = 1 to state = 1 and taken = 0 - turn camera on
    if (!crud.updateCamera(1, "rtsp://127.0.0.1:5554/stream_1", true, "Surveillance", "Backyard", false)) {
        std::cerr << "Failed to update a camera record." << std::endl;
    }

    std::cout << std::endl;

    if (!crud.readCameras()) {
        std::cerr << "Failed to read camera records." << std::endl;
    }
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(20));
    // update cam source id = 1 to state = 0 and taken = 0 - turn camera off
    if (!crud.updateCamera(1, "rtsp://127.0.0.1:5554/stream_1", false, "Surveillance", "Backyard", false)) {
        std::cerr << "Failed to update a camera record." << std::endl;
    }

    std::cout << std::endl;

    if (!crud.readCameras()) {
        std::cerr << "Failed to read camera records." << std::endl;
    }
    std::cout << std::endl;
    
    
    // if (!crud.deleteCamera(6)) {
    //     std::cerr << "Failed to delete a camera record." << std::endl;
    // }

    // std::cout << std::endl;

    // if (!crud.readCameras()) {
    //     std::cerr << "Failed to read camera records." << std::endl;
    // }

    return 0;
}