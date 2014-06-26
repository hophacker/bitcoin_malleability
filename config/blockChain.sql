USE listener;
DROP TABLE IF EXISTS transactions;
DROP TABLE IF EXISTS outputs;
DROP TABLE IF EXISTS inputs;
DROP TABLE IF EXISTS blocks;

CREATE TABLE blocks(

    id BIGINT PRIMARY KEY,

    hash CHAR(64),

    time BIGINT

);



CREATE TABLE transactions(

    id BIGINT PRIMARY KEY,

    hash CHAR(64),

    blockID BIGINT

);



CREATE TABLE outputs(

    id BIGINT PRIMARY KEY,

    dstAddress CHAR(36),

    value BIGINT,

    txHash CHAR(64),

    offset INT

);



CREATE TABLE inputs(

    id BIGINT PRIMARY KEY,
    
	txHash CHAR(64),

    outputHash CHAR(64),
    
    outputN	INT,

    offset INT

);

