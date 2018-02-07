/*
 * _GPS_my.h
 *
 *  Created on: Jan 6, 2017
 *      Author: yankai
 */

#ifndef SRC_NAVIGATION_GPS_MY_H_
#define SRC_NAVIGATION_GPS_MY_H_

#include "../Base/common.h"
#include "../Base/_ThreadBase.h"
#include "../Filter/FilterBase.h"
#include "../Vision/_ZED.h"
#include "../Sensor/_Lightware_SF40.h"
#include "../Protocol/_Mavlink.h"
#include "../include/UTM.h"
#include <iostream>

const std::string logfile = "/home/nvidia/Desktop/ZEDlog.txt";


/*
APM setting to use MAV_GPS
GPS_TYPE = MAV (not GPS2_TYPE)
EK2_GPS_TYPE = 2
BRD_SER2_RTSCTS = 0
SERIAL2_BAUD = 115
SERIAL2_PROTOCOL = 1
*/

namespace kai
{

struct LL_POS_my
{
	double	m_lat;
	double	m_lng;
	double	m_alt;
	double	m_hdg;

	void init(void)
	{
		m_lat = 0.0;
		m_lng = 0.0;
		m_alt = 0.0;
		m_hdg = 0.0;
	}
};


class _GPS_my: public _ThreadBase
{
public:
	_GPS_my(void);
	virtual ~_GPS_my();

	bool init(void* pKiss);
	bool link(void);
	bool start(void);
	bool draw(void);

	//void reset(void);

private:
	void detect(void);
	void update(void);
	static void* getUpdateThread(void* This)
	{
		((_GPS_my *) This)->update();
		return NULL;
	}

public:
	_Mavlink* m_pMavlink;
	int	m_mavDSfreq;

	uint64_t m_tStarted;
	uint64_t m_tNow;

	LL_POS_my	m_LL;
    //std::ofstream* filestream;
};

}

#endif
