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

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) {
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

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& conditions) {
        for (const auto& [column, value] : conditions) {
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
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::string query = query_builder.BuildQuery();
    std::cout << "Generated query: " << query << std::endl;

    return 0;
}