# ImportBigobjectWin
Sample code for Win32 to import into [Bigobject](http://www.bigobject.io) with csv file or 'INSERT INTO' sql statement.

## Bigobject data management
BigObject supports SQL like language to manage data. Please refer to [Basic Data Management](http://docs.bigobject.io/Basic_Data_Management/index.html).

## Data Import
BigObject supports a bunch of interfaces to import data. Please refer to [Data Import](http://docs.bigobject.io/Data_Import/index.html).

## About this sample code
The sample code can be compiled by [Microsoft Visual Studio](https://www.visualstudio.com) 2012 or other versions. It demonstrates two data import interfaces, csv file and [MySQL](https://www.mysql.com) client.

### Import csv file by Bigobject streaming interface
Bigobject streaming interface is a proprietary TCP base protocol, please refer to the protocol [detail](http://docs.bigobject.io/Data_Import/Streaming_Bulk_Import.html). The sample code utilizes Windows Sockets API to send TCP packets. Of course, you can use other library to send TCP packets.

### Insert data by MySQL ODBC connector
To execute SQL statement in the sample code, you've to install [MySQL Connector/ODBC 5.3.9](https://dev.mysql.com/downloads/connector/odbc). Surely, you can use other version, just search "MySQL ODBC 5.3 ANSI Driver" from source code, replace with your MySQL ODBC driver, and re-compile.

### How to run
This is a simple MFC dialog base application. You'll know how to run it after you compile and launch it.
