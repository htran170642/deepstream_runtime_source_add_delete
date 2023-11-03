#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <vector>

struct Camera {
    int source_id;
    std::string rtsp_url;
    int stream_state;
    std::string use_case;
    std::string camera_location;
    int taken;
};

class MySQLCRUD {
public:
    MySQLCRUD(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    ~MySQLCRUD();

    bool connect();
    bool disconnect();

    bool createCamera(const std::string& rtspUrl, bool streamState, const std::string& useCase, const std::string& location, bool taken);
    bool readCameras();
    std::vector<Camera> getAllCameras();
    std::vector<Camera> getActiveCameras();
    std::vector<Camera> getInactiveCameras();
    bool updateCamera(int sourceId, const std::string& rtspUrl, bool streamState, const std::string& useCase, const std::string& location, bool taken);
    bool deleteCamera(int sourceId);

private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
};
