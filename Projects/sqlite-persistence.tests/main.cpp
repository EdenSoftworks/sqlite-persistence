
#pragma once

#define CATCH_CONFIG_MAIN // < Tell catch to provide main.
#define CATCH_CONFIG_RUNNER

#include <DbConnectionState.hpp>
#include <DbConnectionString.hpp>
#include <DbConnectionOptions.hpp>
#include <DbConnection.hpp>
#include <DbQuery.hpp>
#include <DbTransaction.hpp>
#include <Sqlite3Helper.hpp>

#include <catch/catch.hpp>

#include <iostream>
#include <string>
#include <vector>

class Tests
{
public:

    Tests(void)
        : pCommand(nullptr), pQuery(nullptr)
    {
        pConnection = new DbConnection(
            DbConnectionString("./", "test.db")
            , DbConnectionOptions());

        pConnection->Open();

        pTransaction = pConnection->BeginTransaction("parent");
    }

    ~Tests(void)
    {
        pTransaction->Rollback("parent");

        delete pTransaction;
        pTransaction = nullptr;

        delete pQuery;
        pQuery = nullptr;

        delete pCommand;
        pCommand = nullptr;

        pConnection->Close();

        delete pConnection;
        pConnection = nullptr;
    }

    DbCommand* pCommand;
    IDbConnection* pConnection;
    IDbQuery* pQuery;
    IDbTransaction* pTransaction;

};

SCENARIO_METHOD(Tests, "Create table", "[]")
{
    GIVEN("a new open DbConnection")
    {
        CHECK(pConnection != nullptr);
        CHECK(pConnection->HasConnectionState(CONNECTION_OPEN));

        pTransaction->Begin("child");

        GIVEN("a new DbQuery")
        {
            pQuery = new DbQuery("CREATE TABLE Test (Id INTEGER PRIMARY KEY NOT NULL);");

            CHECK(pQuery != nullptr);

            GIVEN("a new DbCommand")
            {
                pCommand = pConnection->CreateCommand(pQuery);

                CHECK(pCommand != nullptr);

                GIVEN("a prepared DbCommand")
                {
                    pCommand->Prepare();

                    CHECK(pCommand->isPrepared());

                    WHEN("the DbCommand is executed")
                    {
                        pCommand->ExecuteNonQuery();

                        THEN("a table is created")
                        {
                            CHECK(TableExists(pConnection->Database(), "Test") == true);
                        }
                    }
                }
            }
        }

        pTransaction->Commit("child");
    }

} // < end scenario.