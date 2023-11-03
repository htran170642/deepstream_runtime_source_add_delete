CREATE DATABASE IF NOT EXISTS ds_streams;

USE ds_streams;

CREATE TABLE IF NOT EXISTS cameras (
    source_id       INT AUTO_INCREMENT PRIMARY KEY,
    rtsp_url        VARCHAR(256)             NOT NULL,
    stream_state    boolean,
    use_case        VARCHAR(16),
    camera_location VARCHAR(16),
    taken           boolean
);

INSERT INTO cameras (rtsp_url, stream_state, use_case, camera_location, taken)
VALUES 
    ('rtsp://example.com/camera1', TRUE, 'Security', 'Office', FALSE),
    ('rtsp://example.com/camera2', FALSE, 'Surveillance', 'Entrance', TRUE),
    ('rtsp://example.com/camera3', TRUE, 'Traffic', 'Street', TRUE);
