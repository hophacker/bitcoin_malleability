#include "txipdb.h"
#include "leveldb/db.h"
#include <iostream>
#include "rpcserver.h"

#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include "json/json_spirit_value.h"
#include <fstream>

using namespace json_spirit;


typedef boost::unique_lock< boost::shared_mutex > WriteLock;
typedef boost::shared_lock< boost::shared_mutex > ReadLock;

boost::shared_mutex myLock;

using namespace std;

//key value storage - transaction / IP
leveldb::DB* txDb;

boost::int64_t numKeys = 0;

// Init Level DB for transaction - IP

bool TxDbInit()
{
    // Set up database connection information and open database
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "./txipdb", &txDb);

    if (false == status.ok())
    {
        cerr << "Unable to open/create transaction/ip database './txdbip'" << endl;
        cerr << status.ToString() << endl;
        return false;
    }

    // Iterate over all items to calculate number of it
    leveldb::Iterator* it = txDb->NewIterator(leveldb::ReadOptions());

    numKeys = 0;
    for (it->SeekToFirst(); it->Valid(); it->Next())
	++numKeys;	

    return true;
}

void TxDbClose()
{
    delete txDb;
}

bool AddValueToTxIpDb(const std::string &key, const std::string &value)
{
	WriteLock w_lock(myLock);

	bool flag = false;
	std::string writeValue;
        leveldb::Status status = txDb->Get(leveldb::ReadOptions(), key, &writeValue);

	if (status.ok()) {
		flag = true;
		writeValue += "!" + value;
	}
	else
		writeValue = value;

        leveldb::WriteOptions writeOptions;
        status = txDb->Put(writeOptions, key, writeValue);

        if (status.ok()){
		if (false == flag)
			++numKeys;
                return true;
	}
        else
                return false;
}

bool GetValueFromTxIpDb(const std::string &key, std::string &value)
{
	ReadLock r_lock(myLock);
	
	leveldb::Status status = txDb->Get(leveldb::ReadOptions(), key, &value);

        if (status.ok())
		return true;
	else
		return false;
}

//get the number of tx in ip database
Value gettxcount(const Array& params, bool fHelp)
{
    if (fHelp) {
        throw runtime_error(
            "gettxcount\n"
            "\nreturns number all transactions .\n"
        );
    }

    Value ret = numKeys;

    return ret;
}

//get transactions saved in database in a ragne
Value gettxs(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 1) {
        throw runtime_error(
            "gettxs\n"
            "\nreturns id transaction from TX/IP database .\n"
        );
    }

    ReadLock r_lock(myLock);

    Value ret = numKeys;

    // Iterate over each item in the database and print them
    leveldb::Iterator* it = txDb->NewIterator(leveldb::ReadOptions());

    ofstream fileOutput;
    fileOutput.open (params[0].get_str().c_str());

    for (it->SeekToFirst(); it->Valid(); it->Next())
         fileOutput << it->key().ToString() << endl;

    fileOutput.close();

    return ret;
}

// get array of ipaddresses for specified tx
Value gettxip(const Array& params, bool fHelp) {
    if (fHelp || params.size() != 1 ) {
        throw runtime_error(
            "gettxip\n"
            "\nreturns all ip addresses for transaction .\n"
        );
    }

    Array ret;
    std::string value;
    std::string key = params[0].get_str();

    if (true != GetValueFromTxIpDb(key, value))
	throw runtime_error(
		"gettxip\n"
		"\nGetValueFromTxIpDb failed .\n"
	);

    std::string delimiter = "!";

    size_t pos = 0;
    Value token;

    while ((pos = value.find(delimiter)) != std::string::npos) {
        token = value.substr(0, pos);
        ret.push_back(token);
        value.erase(0, pos + delimiter.length());
    }

    token = value;
    ret.push_back(token);

    return ret;
}
