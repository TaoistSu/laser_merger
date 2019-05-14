#include <sdkeli_ls_udp/sdkeli_ls_common_udp.h>
#include <sdkeli_ls_udp/sdkeli_ls1207de_parser.h>

#include <ros/ros.h>
#include <nodelet/nodelet.h>

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

namespace sdkeli_ls_udp
{
class SDKeliLs1207DENodelet: public nodelet::Nodelet
{
private:
    boost::shared_ptr<boost::thread> publish_scan_thread_;
    bool enabled_;
public:
    virtual void onInit()
    {
        ROS_INFO("Bringup SDKeliLs1207DE nodelet");
        enabled_ = true;
        publish_scan_thread_ = boost::make_shared<boost::thread>(boost::bind(&SDKeliLs1207DENodelet::publishScan, this));
    }

    void publishScan()
    {
        ros::NodeHandle nh  = getNodeHandle();
        ros::NodeHandle pnh = getPrivateNodeHandle();

        /*Check whether hostname is provided*/
        bool isTcpConnection = false;
        std::string strHostName;
        std::string strPort;

        if(pnh.getParam("hostname", strHostName))
        {
            isTcpConnection = true;
            pnh.param<std::string>("port", strPort, "2112");
        }

        /*Get configured time limit*/
        int iTimeLimit = 5;
        pnh.param("timelimit", iTimeLimit, 5);

        bool isDataSubscribed = false;
        pnh.param("subscribe_datagram", isDataSubscribed, false);

        int iDeviceNumber = 0;
        pnh.param("device_number", iDeviceNumber, 0);

        /*Create and initialize parser*/
        sdkeli_ls_udp::CSDKeliLs1207DEParser *pParser = new sdkeli_ls_udp::CSDKeliLs1207DEParser();
        double param;
        std::string frame_id;

        if(pnh.getParam("range_min", param))
        {
            ROS_INFO("range_min: %f", param);
            pParser->SetRangeMin(param);
        }
        if(pnh.getParam("range_max", param))
        {
            ROS_INFO("range_max: %f", param);
            pParser->SetRangeMax(param);
        }
        if(pnh.getParam("time_increment", param))
        {
            ROS_INFO("time_increment: %f", param);
            pParser->SetTimeIncrement(param);
        }

        if(pnh.getParam("frame_id", frame_id))
        {
            ROS_INFO("frame_id: %s", frame_id.c_str());
            pParser->SetFrameId(frame_id);
        }

        /*Setup TCP connection and attempt to connect/reconnect*/
        sdkeli_ls_udp::CSDKeliLsCommon *pSDKeliLs = NULL;
        int result = sdkeli_ls_udp::ExitError;
        while(ros::ok() && enabled_ == true)
        {
            if(pSDKeliLs != NULL)
            {
                delete pSDKeliLs;
            }

            pSDKeliLs = new sdkeli_ls_udp::CSDKeliLsCommonUdp(strHostName, strPort, iTimeLimit, pParser, nh, pnh);
            result = pSDKeliLs->Init();

            /*Device has been initliazed successfully*/
            while(ros::ok() && (result == sdkeli_ls_udp::ExitSuccess) && enabled_ == true)
            {
                ros::spinOnce();
                result = pSDKeliLs->LoopOnce();
            }

            if(result == sdkeli_ls_udp::ExitFatal)
            {
                ROS_ERROR("Grab laser data error:ExitFatal");
                return ;
            }
        }

        if(pSDKeliLs != NULL)
        {
            delete pSDKeliLs;
        }

        if(pParser != NULL)
        {
            delete pParser;
        }
    }

    ~SDKeliLs1207DENodelet()
    {
        enabled_ = false;
        publish_scan_thread_->join();
    }
};
}/*sdkeli_ls_udp*/

// watch the capitalization carefully
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(sdkeli_ls_udp::SDKeliLs1207DENodelet, nodelet::Nodelet)
