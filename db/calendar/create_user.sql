USE mysqldb;
CREATE TABLE users (
       user_id BIGINT NOT NULL PRIMARY KEY,
       user_name TEXT NOT NULL,
       email_address TEXT NOT NULL,
       first_name TEXT,
       last_name TEXT,
       creation_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       modified_time TIMESTAMP
);
