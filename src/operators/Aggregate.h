#ifndef HUSTLE_AGGREGATE_H
#define HUSTLE_AGGREGATE_H

#include <string>
#include <table/block.h>
#include <table/table.h>
#include <arrow/compute/api.h>

#include "Operator.h"

namespace hustle {
namespace operators {

enum AggregateKernels {
  SUM,
  COUNT,
  MEAN
};

class Aggregate : public Operator{
public:
    Aggregate(AggregateKernels aggregate_kernel, std::string column_name,
          std::string group_by_column_name);

    std::unordered_map<std::string, std::shared_ptr<arrow::ChunkedArray>>
    get_groups(std::shared_ptr<Table> table);
    // Operator.h
    std::shared_ptr<Table> run_operator(std::vector<std::shared_ptr<Table>>
    tables) override;

    std::shared_ptr<Table> run_operator_no_group_by
            (std::shared_ptr<Table> table);
    std::shared_ptr<Table> run_operator_with_group_by
            (std::shared_ptr<Table> table);
    arrow::compute::Datum compute_aggregate(
            std::shared_ptr<arrow::ChunkedArray> aggregate_col,
            std::shared_ptr<arrow::ChunkedArray> group_indices);

private:
    AggregateKernels aggregate_kernel_;
    std::string aggregate_column_name_;
    std::string group_by_column_name_;


    };

} // namespace operators
} // namespace hustle

#endif //HUSTLE_AGGREGATE_H