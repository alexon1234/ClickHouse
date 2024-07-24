#pragma once

#include <Common/Arena.h>
#include <Storages/Statistics/Statistics.h>
#include <AggregateFunctions/AggregateFunctionFactory.h>

namespace DB
{

class StatisticsUniq : public IStatistics
{
public:
    StatisticsUniq(const SingleStatisticsDescription & stat_, const DataTypePtr & data_type);
    ~StatisticsUniq() override;

    UInt64 estimateCardinality() const override;

    void update(const ColumnPtr & column) override;

    void serialize(WriteBuffer & buf) override;
    void deserialize(ReadBuffer & buf) override;

private:
    std::unique_ptr<Arena> arena;
    AggregateFunctionPtr collector;
    AggregateDataPtr data;

};

void uniqValidator(const SingleStatisticsDescription &, DataTypePtr data_type);
StatisticsPtr uniqCreator(const SingleStatisticsDescription & stat, DataTypePtr data_type);

}
