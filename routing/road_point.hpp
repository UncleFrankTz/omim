#pragma once

#include "std/cstdint.hpp"
#include "std/limits.hpp"
#include "std/sstream.hpp"
#include "std/string.hpp"

namespace routing
{
// RoadPoint in unique identifier for any road point in mwm file.
//
// Contains feature id and point id.
// Point id is the ordinal number of point in the road.
class RoadPoint final
{
public:
  RoadPoint() : m_featureId(0), m_pointId(0) {}

  RoadPoint(uint32_t featureId, uint32_t pointId) : m_featureId(featureId), m_pointId(pointId) {}

  bool operator==(RoadPoint const & roadPoint) const
  {
    return m_featureId == roadPoint.m_featureId && m_pointId == roadPoint.m_pointId;
  }

  bool operator!=(RoadPoint const & roadPoint) const { return !(*this == roadPoint); }

  bool operator<(RoadPoint const & roadPoint) const
  {
    if (m_featureId == roadPoint.m_featureId)
      return m_pointId < roadPoint.m_pointId;
    return m_featureId < roadPoint.m_featureId;
  }

  uint32_t GetFeatureId() const { return m_featureId; }

  uint32_t GetPointId() const { return m_pointId; }

private:
  uint32_t m_featureId;
  uint32_t m_pointId;
};

inline string DebugPrint(RoadPoint const & roadPoint)
{
  ostringstream out;
  out << "RoadPoint[" << roadPoint.GetFeatureId() << ", " << roadPoint.GetPointId() << "]";
  return out.str();
}
}  // namespace routing