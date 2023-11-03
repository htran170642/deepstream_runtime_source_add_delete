#include "mysql_client.h"

MySQLCRUD::MySQLCRUD(const std::string& host, const std::string& user, const std::string& password, const std::string& database) {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://" + host, user, password);
    con->setSchema(database);
}

MySQLCRUD::~MySQLCRUD() {
    delete con;
}

bool MySQLCRUD::connect() {
    return (con != nullptr);
}

bool MySQLCRUD::disconnect() {
    delete con;
    con = nullptr;
    return true;
}

bool MySQLCRUD::createCamera(const std::string& rtspUrl, bool streamState, const std::string& useCase, const std::string& location, bool taken) {
    if (!connect()) {
        return false;
    }

    try {
        sql::PreparedStatement *stmt;
        stmt = con->prepareStatement("INSERT INTO cameras (rtsp_url, stream_state, use_case, camera_location, taken) VALUES (?, ?, ?, ?, ?)");
        stmt->setString(1, rtspUrl);
        stmt->setBoolean(2, streamState);
        stmt->setString(3, useCase);
        stmt->setString(4, location);
        stmt->setBoolean(5, taken);
        stmt->executeUpdate();
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool MySQLCRUD::readCameras() {
    if (!connect()) {
        return false;
    }

    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM cameras");
        while (res->next()) {
            std::cout << "Source ID: " << res->getInt("source_id") << "\tRTSP URL: " << res->getString("rtsp_url") 
                      << "\tStream State: " << res->getBoolean("stream_state") << "\tUse Case: " << res->getString("use_case") 
                      << "\tLocation: " << res->getString("camera_location") << "\tTaken: " << res->getBoolean("taken") << std::endl;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

std::vector<Camera> MySQLCRUD::getAllCameras() {
    std::vector<Camera> cameras;
    if (!connect()) {
        return cameras;
    }

    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM cameras");
        while (res->next()) {
            Camera camera;
            camera.source_id = res->getInt("source_id");
            camera.rtsp_url = res->getString("rtsp_url");
            camera.stream_state = res->getInt("stream_state");
            camera.use_case = res->getString("use_case");
            camera.camera_location = res->getString("camera_location");
            camera.taken = res->getInt("taken");

            cameras.push_back(camera);
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }

    return cameras;
}

std::vector<Camera> MySQLCRUD::getActiveCameras() {
    std::vector<Camera> cameras;

    if (!connect()) {
        return cameras;
    }

    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM cameras WHERE stream_state = 1 AND taken = 0");

        while (res->next()) {
            Camera camera;
            camera.source_id = res->getInt("source_id");
            camera.rtsp_url = res->getString("rtsp_url");
            camera.stream_state = res->getInt("stream_state");
            camera.use_case = res->getString("use_case");
            camera.camera_location = res->getString("camera_location");
            camera.taken = res->getInt("taken");

            cameras.push_back(camera);
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }

    return cameras;
}

std::vector<Camera> MySQLCRUD::getInactiveCameras() {
    std::vector<Camera> cameras;

    if (!connect()) {
        return cameras;
    }

    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM cameras WHERE stream_state = 0");

        while (res->next()) {
            Camera camera;
            camera.source_id = res->getInt("source_id");
            camera.rtsp_url = res->getString("rtsp_url");
            camera.stream_state = res->getInt("stream_state");
            camera.use_case = res->getString("use_case");
            camera.camera_location = res->getString("camera_location");
            camera.taken = res->getInt("taken");

            cameras.push_back(camera);
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }

    return cameras;
}

bool MySQLCRUD::updateCamera(int sourceId, const std::string& rtspUrl, bool streamState, const std::string& useCase, const std::string& location, bool taken) {
    if (!connect()) {
        return false;
    }

    try {
        sql::PreparedStatement *stmt;
        stmt = con->prepareStatement("UPDATE cameras SET rtsp_url = ?, stream_state = ?, use_case = ?, camera_location = ?, taken = ? WHERE source_id = ?");
        stmt->setString(1, rtspUrl);
        stmt->setBoolean(2, streamState);
        stmt->setString(3, useCase);
        stmt->setString(4, location);
        stmt->setBoolean(5, taken);
        stmt->setInt(6, sourceId);
        stmt->executeUpdate();
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool MySQLCRUD::deleteCamera(int sourceId) {
    if (!connect()) {
        return false;
    }

    try {
        sql::PreparedStatement *stmt;
        stmt = con->prepareStatement("DELETE FROM cameras WHERE source_id = ?");
        stmt->setInt(1, sourceId);
        stmt->executeUpdate();
        delete stmt;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

// int main() {

//     const std::string host = "192.168.1.6:3306";
//     const std::string user = "root";
//     const std::string password = "admin";
//     const std::string database = "ds_streams";
//     MySQLCRUD crud(host, user, password, database);
    
    // if (!crud.createCamera("rtsp://camera1", true, "Security", "Entrance", false)) {
    //     std::cerr << "Failed to create a camera record." << std::endl;
    // }

    // if (crud.readCameras()) {
    //     std::cerr << "Failed to read camera records." << std::endl;
    // }

    // if (!crud.updateCamera(4, "rtsp://camera2", false, "Surveillance", "Backyard", true)) {
    //     std::cerr << "Failed to update a camera record." << std::endl;
    // }

    // if (!crud.deleteCamera(4)) {
    //     std::cerr << "Failed to delete a camera record." << std::endl;
    // }

    // if (!crud.readCameras()) {
    //     std::cerr << "Failed to read camera records." << std::endl;
    // }

//     return 0;
// }