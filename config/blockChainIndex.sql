USE listener;
select 'Creating blocks index' AS ' ';
ALTER TABLE blocks ADD INDEX (hash);

select 'Creating transactions index' AS ' ';
ALTER TABLE transactions ADD INDEX (hash), ADD INDEX(blockID);

select 'Creating outputs index' AS ' ';
ALTER TABLE outputs ADD INDEX (dstAddress), ADD INDEX(txHash), ADD INDEX(txHash, offset);

select 'Creating inputs index' AS ' ';
ALTER TABLE inputs ADD INDEX (txHash), ADD INDEX(outputHash,outputN);
