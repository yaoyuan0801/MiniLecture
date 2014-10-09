USE mysqldb;
CREATE TABLE events (
       event_id BIGINT NOT NULL PRIMARY KEY,
       calendar_id BIGINT NOT NULL FOREIGN KEY,
       event_status TEXT,
       event_location TEXT,
       event_name TEXT,
       start_time TIMESTAMP,
       end_time TIMESTAMP,
       creation_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       modified_time TIMESTAMP
);
