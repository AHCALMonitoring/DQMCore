/*
 *
 * DQMMonitorElementCollector.h header template automatically generated by a class generator
 * Creation date : ven. mai 8 2015
 *
 * This file is part of DQM4HEP libraries.
 * 
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQMMONITORELEMENTCOLLECTOR_H
#define DQMMONITORELEMENTCOLLECTOR_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"
#include "dqm4hep/DQMPath.h"
#include "dqm4hep/DQMDataStream.h"
#include "dqm4hep/DQMPerformance.h"

// -- dim headers
#include "dis.hxx"

namespace dqm4hep
{

class DQMMonitorElementCollector;
class DQMStorage;

class ME_FULL_NAME_COMPARE
{
public:
	ME_FULL_NAME_COMPARE(const DQMPath &fullPathToCompare);
	bool operator ()(DQMMonitorElement *pMonitorElement);
private:
	DQMPath        m_pathToCompare;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

class DQMMonitorElementNameListRpc : public DimRpc
{
public:
	DQMMonitorElementNameListRpc(char *rpcName, DQMMonitorElementCollector *pCollector);
	void rpcHandler();

private:
	DQMMonitorElementCollector   *m_pCollector;
	DQMDataStream                 m_dataStream;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

class DQMMonitorElementPacketRpc : public DimRpc
{
public:
	DQMMonitorElementPacketRpc(char *rpcName, DQMMonitorElementCollector *pCollector);
	void rpcHandler();

private:
	DQMMonitorElementCollector   *m_pCollector;
	DQMDataStream                 m_dataStream;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

class DQMMonitorElementCollectorInfoRpc : public DimRpc
{
public:
	DQMMonitorElementCollectorInfoRpc(char *rpcName, DQMMonitorElementCollector *pCollector);
	void rpcHandler();

private:
	DQMMonitorElementCollector   *m_pCollector;
	DQMDataStream                 m_dataStream;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

/** DQMCollectorCommandHandler class
 *  Handles commands to receive from the clients
 */
class DQMCollectorCommandHandler : public DimCommandHandler
{
public:
	/** Constructor
	 */
	DQMCollectorCommandHandler(DQMMonitorElementCollector *pCollector);

	/** Destructor
	 */
	~DQMCollectorCommandHandler();

	/** The command handler
	 */
	void commandHandler();

	// from module applications
	DimCommand           *m_pMEPacketReceptionCommand;

	// the collector
	DQMMonitorElementCollector        *m_pCollector;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

/** DQMMonitorElementCollector class
 */ 
class DQMMonitorElementCollector
{
public:
	/** Constructor
	 */
	DQMMonitorElementCollector();

	/** Destructor
	 */
	~DQMMonitorElementCollector();

	/** Set the collector name. Can be set only if the collector is not running.
	 *  The collector name is used to build the service and command names over the network
	 */
	StatusCode setCollectorName(const std::string &collectorName);

	/** Get the collector name
	 */
	const std::string &getCollectorName() const;

	/** Start the collector. Allocate services and commands
	 */
	StatusCode start();

	/** Stop the collector. Destroy the commands and services
	 */
	StatusCode stop();

	/** Get the collector state. See DQMState enum (DQM4HEP.h)
	 */
	DQMState getState() const;

	/** Whether the collector is running
	 */
	bool isRunning() const;

	/** Reset the collector, returning back to its empty state
	 */
	void reset();

public:
	typedef std::map<std::string, DQMMonitorElementList> DQMMonitorElementListMap; ///< Module name to element list map

	static const std::string         m_emptyBufferStr;

private:
	/** Handle the monitor element packet reception from a module application
	 */
	StatusCode handleMEPacketReception(DimCommand *pCommand);

	/** Handle the monitor element name list request
	 */
	StatusCode handleMENameListRequest(DimCommand *pCommand);

	/** Handle the monitor element packet request
	 */
	StatusCode handleMEPacketRequest(DimCommand *pCommand);

	/** Handle the collector info request
	 */
	StatusCode handleCollectorInfoRequest(DimCommand *pCommand);

	// collector name
	std::string                        m_collectorName;

	DQMMonitorElementNameListRpc      *m_pMonitorElementNameListRpc;
	DQMMonitorElementPacketRpc        *m_pMonitorElementPacketRpc;
	DQMMonitorElementCollectorInfoRpc *m_pMonitorElementCollectorInfoRpc;

	DQMCollectorCommandHandler        *m_pCommandHandler;

	DQMStatisticsService              *m_pStatisticsService;

	// runtime
	DQMState                           m_collectorState;

	// storage
	DQMMonitorElementListMap           m_monitorElementListMap;
	DQMDataStream                      m_dataStream;    ///< To deserialize incoming monitor elements from modules

	float                              m_receptionTimerValue;
	DQMPerformanceService             *m_pReceptionTimerService;

	float                              m_queryTimerValue;
	DQMPerformanceService             *m_pQueryTimerService;

	friend class DQMCollectorCommandHandler;
	friend class DQMMonitorElementNameListRpc;
	friend class DQMMonitorElementPacketRpc;
	friend class DQMMonitorElementCollectorInfoRpc;
}; 

} 

#endif  //  DQMMONITORELEMENTCOLLECTOR_H
