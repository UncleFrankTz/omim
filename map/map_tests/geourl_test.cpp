#include "../../testing/testing.hpp"

#include "../geourl_process.hpp"

using namespace url_scheme;

UNIT_TEST(ProcessURL_Smoke)
{
  Info info;
  ParseGeoURL("geo:53.666,27.666", info);
  TEST(info.IsValid(), ());
  TEST_ALMOST_EQUAL(info.m_lat, 53.666, ());
  TEST_ALMOST_EQUAL(info.m_lon, 27.666, ());

  info.Reset();
  ParseGeoURL("geo://point/?lon=27.666&lat=53.666&zoom=10", info);
  TEST(info.IsValid(), ());
  TEST_ALMOST_EQUAL(info.m_lat, 53.666, ());
  TEST_ALMOST_EQUAL(info.m_lon, 27.666, ());
  TEST_ALMOST_EQUAL(info.m_zoom, 10.0, ());

  info.Reset();
  ParseGeoURL("geo:53.666", info);
  TEST(!info.IsValid(), ());

  info.Reset();
  ParseGeoURL("mapswithme:123.33,32.22/showmethemagic", info);
  TEST(!info.IsValid(), ());

}
