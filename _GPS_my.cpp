/*
 * _GPS.cpp
 *
 *  Created on: Jan 6, 2017
 *      Author: yankai
 */

#include "_GPS_my.h"


namespace kai
{

_GPS_my::_GPS_my()
{
	m_pMavlink = NULL;
	//m_initLL.init();
	m_LL.init();
	//m_UTM.init();
	m_mavDSfreq = 30;
	m_tStarted = 0;
	m_tNow = 0;
}

_GPS_my::~_GPS_my()
{
}

bool _GPS_my::init(void* pKiss)
{
	IF_F(!_ThreadBase::init(pKiss));
	Kiss* pK = (Kiss*) pKiss;
	pK->m_pInst = this;

	F_INFO(pK->v("mavDSfreq", &m_mavDSfreq));
	
	m_tStarted = getTimeUsec();

    std::ifstream fin(logfile.c_str());
    if (fin) {
        std::cout << "deleting file..." << std::endl;
        system("rm /home/nvidia/Desktop/ZEDlog.txt");
    }
    std::ofstream filestream(logfile.c_str());
    filestream<<"Start running ZED programme..."<<std::endl;

	//reset();
	return true;
}

bool _GPS_my::link(void)
{
	IF_F(!this->_ThreadBase::link());
	Kiss* pK = (Kiss*) m_pKiss;

	string iName;

	iName = "";
	F_INFO(pK->v("_Mavlink", &iName));
	m_pMavlink= (_Mavlink*) (pK->root()->getChildInstByName(&iName));

	return true;
}

bool _GPS_my::start(void)
{
	m_bThreadON = true;
	int retCode = pthread_create(&m_threadID, 0, getUpdateThread, this);
	if (retCode != 0)
	{
		m_bThreadON = false;
		return false;
	}

	return true;
}

void _GPS_my::update(void)
{
	while (m_bThreadON)
	{
		this->autoFPSfrom();

		m_tNow = getTimeUsec();
		detect();

		this->autoFPSto();
	}
}

void _GPS_my::detect(void)
{
	NULL_(m_pMavlink);

	if(m_tNow - m_pMavlink->m_msg.time_stamps.global_position_int > USEC_1SEC)
	{
		m_pMavlink->requestDataStream(MAV_DATA_STREAM_POSITION, m_mavDSfreq);
		m_pMavlink->requestDataStream(MAV_DATA_STREAM_EXTRA1, m_mavDSfreq);
		return;
	}

	m_LL.m_hdg = ((double)m_pMavlink->m_msg.global_position_int.hdg) * 0.01;
	m_LL.m_lat = ((double)m_pMavlink->m_msg.global_position_int.lat) * 0.0000001;
    m_LL.m_lng = ((double)m_pMavlink->m_msg.global_position_int.lon) * 0.0000001;


}

bool _GPS_my::draw(void)
{
	IF_F(!this->_ThreadBase::draw());
	Window* pWin = (Window*)this->m_pWindow;
	Mat* pMat = pWin->getFrame()->getCMat();
	string msg;

	pWin->tabNext();
	msg = "Pos: lat=" + f2str(m_LL.m_lat) + ", lng=" + f2str(m_LL.m_lng) + ", alt=" + f2str(m_LL.m_alt) + ", hdg=" + f2str(m_LL.m_hdg);
        
    std::ofstream filestream(logfile.c_str(), std::ofstream::out | std::ofstream::app);
    filestream<<msg.c_str()<<std::endl;

	pWin->addMsg(&msg);
	//msg = "Dist: X=" + f2str(dX) + ", Y=" + f2str(dY) + ", Z=" + f2str(dZ);
	pWin->addMsg(&msg);
	pWin->tabPrev();

	return true;
}

}
