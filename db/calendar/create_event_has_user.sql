USE mysqldb;
CREATE TABLE event_has_users (
       event_has_user_id BIGINT NOT NULL PRIMARY KEY,
       event_id BIGINT NOT NULL FOREIGN KEY,
       user_id BIGINT NOT NULL FOREIGN KEY,
       creation_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       modified_time TIMESTAMP
);
