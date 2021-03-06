  /// \file DQMCycle.h
/*
 *
 * DQMCycle.h header template automatically generated by a class generator
 * Creation date : mar. oct. 7 2014
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


#ifndef DQMCYCLE_H
#define DQMCYCLE_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"

#include "TTime.h"

namespace dqm4hep
{

class DQMCycle;

/** DQMCycleListener class
 */
class DQMCycleListener
{
public:
	/** Destructor
	 */
	virtual ~DQMCycleListener() {};

	/** Call back function when an event is processed by the framework
	 */
	virtual void onEventProcessed(const DQMCycle *const pCycle, const DQMEvent *const pEvent) = 0;

	/** Call back function when the cycle is started by the framework
	 */
	virtual void onCycleStarted(const DQMCycle *const pCycle) = 0;

	/** Call back function when the cycle is stopped by the framework
	 */
	virtual void onCycleStopped(const DQMCycle *const pCycle) = 0;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

/** DQMCycle class.
 *
 *  Process a cycle of processEvent(evt) call for a DQMAnalysisModule.
 *  See implementation for cycle types.
 *
 *  The cycle value is the value for which the cycle should normally ends.
 *
 *  The timeout value is the maximum time between two processEvent(evt) call
 *  When the timeout is reached, the cycle ends. The default timeout value
 *  is 10 seconds and can be changed via the method setTimeout(secs)
 */
class DQMCycle
{
public:
	/** Constructor
	 */
	DQMCycle();

	/** Destructor
	 */
	virtual ~DQMCycle();

	/** Get the cycle value (time, nb of events, event size)
	 */
	float getCycleValue() const;

	/** Set the cycle value
	 */
	void setCycleValue(float value);

	/** Get the cycle timeout (in seconds)
	 *  Maximum time between two processEvent(evt) call.
	 *  When the timeout is reached, the cycle ends
	 */
	unsigned int getTimeout() const;

	/** Set the timeout
	 */
	void setTimeout(unsigned int timeout);

	/** Get the processing rate. May be called after stopCycle()
	 *  to get the correct value
	 */
	float getProcessingRate() const;

	/** Get the number of processed events at the end of cycle
	 */
	unsigned int getNProcessedEvents() const;

	/** Get the total time spent to process the last cycle
	 */
	DQMTimeDuration getTotalCycleTime() const;

	/** Called back when the application has processed an event
	 */
	void eventProcessed(const DQMEvent *const pEvent);

	/** Get the start time of the current cycle
	 */
	const DQMTimePoint &getStartTime() const;

	/** Get the end time of the last cycle.
	 *  Valid only between two cycle after stopCycle() call
	 */
	const DQMTimePoint &getEndTime() const;

	/** Start the cycle
	 */
	void startCycle();

	/** Stop the cycle
	 */
	void stopCycle();

	/** Get the cycle state (running, stopped)
	 */
	DQMState getState() const;

	/** Whether the timeout is reached
	 */
	bool isTimeoutReached() const;

	/** Add a cycle listener
	 */
	void addListener(DQMCycleListener *pListener);

	/** Remove a cycle listener
	 */
	void removeListener(DQMCycleListener *pListener);

	/** Specific call back function when a cycle is stopped
	 */
	virtual void onCycleStarted() = 0;

	/** Specific call back function when a cycle is stopped
	 */
	virtual void onCycleStopped() = 0;

	/** Specific call back function when an event is processed, depends on cycle type
	 */
	virtual void onEventProcessed(const DQMEvent *const pEvent) = 0;

	/** Specific function to tell the application to know
	 *  whether the cycle has reached the end
	 */
	virtual bool isEndOfCycleReached() const = 0;

private:
	float                            m_processingRate;
	float                            m_cycleValue;
	unsigned int                     m_cycleTimeout;
	unsigned int                     m_nProcessedEvents;
	DQMTimePoint                     m_startTime;
	DQMTimePoint                     m_endTime;
	DQMTimePoint                     m_lastEventProcessedTime;
	std::set<DQMCycleListener*>      m_listeners;
	DQMState                         m_state;
};

} 

#endif  //  DQMCYCLE_H
