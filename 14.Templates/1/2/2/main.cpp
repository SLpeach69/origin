#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

class SqlSelectQueryBuilder {
private:
    std::vector<std::string> columns;
    std::string from_table;
    std::map<std::string, std::string> where_conditions;

public:
    SqlSelectQueryBuilder() = default;

    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        columns.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (const auto& column : columns) {
            this->columns.push_back(column);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        from_table = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        where_conditions[column] = value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [column, value] : kv) {
            where_conditions[column] = value;
        }
        return *this;
    }

    std::string BuildQuery() const {
        std::string query = "SELECT ";

        if (columns.empty()) {
            query += "*";
        }
        else {
            for (size_t i = 0; i < columns.size(); ++i) {
                query += columns[i];
                if (i != columns.size() - 1) {
                    query += ", ";
                }
            }
        }

        if (!from_table.empty()) {
            query += " FROM " + from_table;
        }

        if (!where_conditions.empty()) {
            query += " WHERE ";
            size_t count = 0;
            for (const auto& [column, value] : where_conditions) {
                query += column + "=" + value;
                if (++count != where_conditions.size()) {
                    query += " AND ";
                }
            }
        }

        query += ";";
        return query;
    }

    void Clear() {
        columns.clear();
        from_table.clear();
        where_conditions.clear();
    }
};

int main() {
    SqlSelectQueryBuilder query_builder1;
    std::vector<std::string> columns = { "name", "phone", "email", "age" };
    query_builder1.AddColumns(columns);
    query_builder1.AddFrom("users");

    std::cout << "Test 1: " << query_builder1.BuildQuery() << std::endl;

    SqlSelectQueryBuilder query_builder2;
    query_builder2.AddColumn("id");
    query_builder2.AddFrom("orders");

    std::map<std::string, std::string> conditions = {
        {"status", "completed"},
        {"amount", "1000"},
        {"date", "2023-01-01"}
    };
    query_builder2.AddWhere(conditions);

    std::cout << "Test 2: " << query_builder2.BuildQuery() << std::endl;

    SqlSelectQueryBuilder query_builder3;
    std::vector<std::string> user_columns = { "first_name", "last_name" };
    query_builder3.AddColumns(user_columns);
    query_builder3.AddFrom("customers");

    query_builder3.AddWhere("city", "Moscow");

    std::map<std::string, std::string> additional_conditions = {
        {"age", "30"},
        {"status", "active"}
    };
    query_builder3.AddWhere(additional_conditions);

    std::cout << "Test 3: " << query_builder3.BuildQuery() << std::endl;

    SqlSelectQueryBuilder query_builder4;
    query_builder4.AddColumn("name").AddColumn("phone");
    query_builder4.AddFrom("students");
    query_builder4.AddWhere("id", "42").AddWhere("name", "John");

    std::cout << "Test 4: " << query_builder4.BuildQuery() << std::endl;

    return 0;
}