#ifndef SDKELI_LS1207DE_PARSER__
#define SDKELI_LS1207DE_PARSER__

#include <sdkeli_ls_udp/parser_base.h>

namespace sdkeli_ls_udp
{
class CSDKeliLs1207DEParser : public CParserBase
{
public:
    CSDKeliLs1207DEParser();
    virtual ~CSDKeliLs1207DEParser();

    virtual int Parse(char *data, size_t data_length, SDKeliLsConfig &config, sensor_msgs::LaserScan &msg);

    void SetRangeMin(float minRange);
    void SetRangeMax(float maxRange);
    void SetTimeIncrement(float time);
    void SetFrameId(std::string str);

private:
    float fRangeMin;
    float fRangeMax;
    float fTimeIncrement;
    std::string fFrame_id;
};
} /*namespace sdkeli_ls_udp*/

#endif /*SDKELI_LS1207DE_PARSER__*/
