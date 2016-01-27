  /// \file DQMTimerCycle.h
/*
 *
 * DQMTimerCycle.h header template automatically generated by a class generator
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


#ifndef DQMTIMERCYCLE_H
#define DQMTIMERCYCLE_H

// -- dqm4hep headers
#include "dqm4hep/DQMCycle.h"
#include "dqm4hep/DQMPerformance.h"

namespace dqm4hep
{

/** DQMTimerCycle class.
 *  DQMCycle based on a time cycle in seconds.
 *  processCycle() called during n seconds
 */ 
class DQMTimerCycle : public DQMCycle 
{
public:
	/** Constructor
	 */
	DQMTimerCycle();

	/** Destructor
	 */
	~DQMTimerCycle();

	/** Process a cycle
	 */
	StatusCode processCycle();

	/** Allocate a clone of this cycle
	 */
	DQMPlugin *clone() const;

private:

	float                      m_timerValue;
	DQMPerformanceService     *m_pProcessEventTimerService;
}; 

} 

#endif  //  DQMTIMERCYCLE_H
