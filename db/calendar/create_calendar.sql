USE mysqldb;
CREATE TABLE calendars (
       calendar_id BIGINT NOT NULL PRIMARY KEY,
       user_id BIGINT NOT NULL FOREIGN KEY,
       calendar_name TEXT,
       creation_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       modified_time TIMESTAMP
);
