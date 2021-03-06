  /// \file DQMModuleApi.h
/*
 *
 * DQMModuleApi.h header template automatically generated by a class generator
 * Creation date : ven. oct. 31 2014
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


#ifndef DQMMODULEAPI_H
#define DQMMODULEAPI_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"
#include "dqm4hep/DQMModule.h"
#include "dqm4hep/DQMAnalysisModule.h"
#include "dqm4hep/DQMMonitorElement.h"
#include "dqm4hep/DQMMonitorElementManager.h"
#include "dqm4hep/DQMModuleApplication.h"

namespace dqm4hep
{

class DQMQualityTestFactory;
class DQMQualityTest;
class DQMArchiver;
class TiXmlElement;

/** DQMModuleApi class.
 *
 *  Responsible for direct operation on module application and modules such as monitor
 *  element booking and directory navigation. Monitor element booking should be done via
 *  a DQMModule.
 *
 *  Example :
 *
 *  \code
 *    DQMMonitorElement *pMyRealHistogram1DElement = NULL;
 *    DQMModuleApi::bookRealHistogram1D(this, pMyRealHistogram1DElement, "MyHisto", "My histo title", 10, 1, 10);
 *  \endcode
 */ 
class DQMModuleApi
{
public:

	/////////////////////////
	// DIRECTORY INTERFACE //
	/////////////////////////

	/** Go back to root directory
	 */
	static void cd(const DQMModule *const pModule);

	/** Go to directory 'dirName'
	 */
	static StatusCode cd(const DQMModule *const pModule, const std::string &dirName);

	/** Create the directory 'dirName'
	 */
	static StatusCode mkdir(const DQMModule *const pModule, const std::string &dirName);

	/** List the current directory content
	 */
	static void ls(const DQMModule *const pModule, bool recursive = false);

	/** Get the current directory name
	 */
	static const std::string &pwd(const DQMModule *const pModule);

	/** Navigate backward in the directory structure
	 */
	static StatusCode goUp(const DQMModule *const pModule);

	/** Remove the directory 'dirName'
	 */
	static StatusCode rmdir(const DQMModule *const pModule, const std::string &dirName);

	/** Whether the directory exists
	 */
	static bool dirExists(const DQMModule *const pModule, const std::string &dirName);

public:

	///////////////////////
	// BOOKING INTERFACE //
	///////////////////////

	/** Book a 1D float histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookRealHistogram1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title, int nBins, float minimum, float maximum);

	/** Book a 1D integer histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookIntHistogram1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title, int nBins, float minimum, float maximum);

	/** Book a 1D char histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookCharHistogram1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title, int nBins, float minimum, float maximum);

	/** Book a 1D short histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookShortHistogram1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title, int nBins, float minimum, float maximum);

	/** Book a 2D float histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookRealHistogram2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax);

	/** Book a 2D integer histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookIntHistogram2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax);

	/** Book a 2D char histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookCharHistogram2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax);

	/** Book a 2D short histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookShortHistogram2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax);

	/** Book a 3D real histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookRealHistogram3D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax,
			int nZBins, float zMin, float zMax);

	/** Book a 3D int histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookIntHistogram3D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax,
			int nZBins, float zMin, float zMax);

	/** Book a 1D profile. The profile is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookProfile1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax, float yMin, float yMax);

	/** Book a 2D profile. The profile is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookProfile2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax,
			float zMin, float zMax);

	/** Book an integer scalar element. The scalar is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookInt(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title, const int &value);

	/** Book a float scalar element. The scalar is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookFloat(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title, const float &value);

	/** Book a short scalar element. The scalar is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookShort(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title, const short &value);

	/** Book a std::string scalar element. The scalar is encapsulated in the DQMMonitorElement
	 *  and added to monitor element list of the module.
	 *  Such a function should be used in DQMModule implementation by passing 'this' as first argument
	 */
	static StatusCode bookString(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title, const std::string &value);

	/** Book a generic TObject. The class name must be a valid built-in ROOT one or
	 *  a user defined class inheriting from TObject and providing a dictionary.
	 */
	template <typename ObjectType, typename... Args>
	static StatusCode bookObject(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
			allocator_helper<TObject, ObjectType, Args...> allocator, Args ...args);




	/** Book a 1D float histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookRealHistogram1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title, int nBins, float minimum, float maximum);

	/** Book a 1D integer histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookIntHistogram1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title, int nBins, float minimum, float maximum);

	/** Book a 1D char histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookCharHistogram1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title, int nBins, float minimum, float maximum);

	/** Book a 1D short histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookShortHistogram1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title, int nBins, float minimum, float maximum);

	/** Book a 2D float histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookRealHistogram2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax);

	/** Book a 2D integer histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookIntHistogram2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax);

	/** Book a 2D char histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookCharHistogram2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax);

	/** Book a 2D short histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookShortHistogram2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax);

	/** Book a 3D real histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookRealHistogram3D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax,
			int nZBins, float zMin, float zMax);

	/** Book a 3D int histogram. The histogram is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookIntHistogram3D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax,
			int nZBins, float zMin, float zMax);

	/** Book a 1D profile. The profile is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookProfile1D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax, float yMin, float yMax);

	/** Book a 2D profile. The profile is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookProfile2D(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			int nXBins, float xMin, float xMax,
			int nYBins, float yMin, float yMax,
			float zMin, float zMax);

	/** Book an integer scalar element. The scalar is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookInt(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title, const int &value);

	/** Book a float scalar element. The scalar is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookFloat(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title, const float &value);

	/** Book a short scalar element. The scalar is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookShort(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title, const short &value);

	/** Book a std::string scalar element. The scalar is encapsulated in the DQMMonitorElement
	 *  Such a function should be used in DQMModule implementation
	 */
	static StatusCode bookString(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title, const std::string &value);

	/** Book a generic TObject. The class name must be a valid built-in ROOT one or
	 *  a user defined class inheriting from TObject and providing a dictionary.
	 */
	template <typename ObjectType, typename... Args>
	static StatusCode bookObject(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &directory, const std::string &name, const std::string &title,
			allocator_helper<TObject, ObjectType, Args...> allocator, Args ...args);


	///////////////////////
	// GETTERS INTERFACE //
	///////////////////////

	/** Get all the monitor elements already booked by this module in all the directories
	 */
	static StatusCode getAllMonitorElements(const DQMModule *const pModule, DQMMonitorElementPtrList &monitorElementList);

	/** Get the monitor element in the current directory (result by ptr reference)
	 */
	static StatusCode getMonitorElement(const DQMModule *const pModule, const std::string &monitorElementName, DQMMonitorElementPtr &monitorElement);

	/** Get the monitor element in the given directory (result by ptr reference)
	 */
	static StatusCode getMonitorElement(const DQMModule *const pModule, const std::string &dirName, const std::string &monitorElementName, DQMMonitorElementPtr &monitorElement);

	/** Get the monitor element in the current directory.
	 *  The element is directly returned without any ptr check
	 */
	static DQMMonitorElementPtr getMonitorElement(const DQMModule *const pModule, const std::string &monitorElementName);

	/** Get the monitor element in the given directory.
	 *  The element is directly returned without any ptr check
	 */
	static DQMMonitorElementPtr getMonitorElement(const DQMModule *const pModule, const std::string &dirName, const std::string &monitorElementName);


	////////////////////////
	// DELETION INTERFACE //
	////////////////////////

	/** Delete the monitor element (by element ptr)
	 */
	static StatusCode deleteMonitorElement(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement);

public:

	////////////////////////////
	// QUALITY TEST INTERFACE //
	////////////////////////////

	/** Register a new quality test factory.
	 *
	 *  Must be called while reading module settings and before
	 *  calling DQMModuleApi::createQualityTest()
	 */
	static StatusCode registerQualityTestFactory(const DQMModule *const pModule, const std::string &qualityTestFactoryName, const DQMQualityTestFactory *const pQualityTestFactory);

 	/** Create a quality test from the xml element.
 	 *  The xml element must contain the attribute 'type' and 'name'
	 */
	static StatusCode createQualityTest(const DQMModule *const pModule, TiXmlElement *const pXmlElement);

	/** Add a quality test to a given monitor element.
	 *
	 *  The quality test must have been registered in the framework before
	 *  calling this method.
	 */
	static StatusCode addQualityTest(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &qualityTestName);

	/** Run all the quality test attached to this monitor element
	 */
	static StatusCode runQualityTests(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement);

	/** Run a specific quality test attached to this monitor element
	 */
	static StatusCode runQualityTest(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &qualityTestName);

	/** Run all the quality test of all the monitor elements of this module
	 */
	static StatusCode runQualityTests(const DQMModule *const pModule);

public:

	////////////////////////////
	// ALERT SYSTEM INTERFACE //
	////////////////////////////

	/** Send an alert to all listeners - type and message
	 */
	static StatusCode sendAlert(const DQMModule *const pModule, DQMAlertType type, const std::string &message);

	/** Send an alert to all listeners - type, message and monitor element
	 */
	static StatusCode sendAlert(const DQMModule *const pModule, DQMAlertType type, const std::string &message, const DQMMonitorElementPtr &monitorElement);

public:

	////////////////////////
	// UITILITY FUNCTIONS //
	////////////////////////

	/** Reset all the monitor elements that have the given reset policy
	 */
	static StatusCode resetMonitorElements(const DQMModule *const pModule, DQMResetPolicy policy);

	/** Reset all the monitor elements of this module
	 */
	static StatusCode resetMonitorElements(const DQMModule *const pModule);

//	/** Archive the current state of this module.
//	 *
//	 *  Simply write the directory structure with the monitor elements
//	 *  in a root file
//	 */
//	static StatusCode archive(DQMModule *const pModule, DQMArchiver *pArchiver);

public:

	///////////////////////
	// RUNTIME FUNCTIONS //
	///////////////////////

	/** Get the elapsed time since start of current run.
	 *  Valid only within run
	 */
	static StatusCode getTimeSinceStartOfRun(const DQMAnalysisModule *const pModule, DQMTimeDuration &duration);

	/** Get the elapsed time since start of current cycle.
	 *  Valid only within cycle
	 */
	static StatusCode getTimeSinceStartOfCycle(const DQMAnalysisModule *const pModule, DQMTimeDuration &duration);

private:
	/** Book a monitor element from the xml element
	 */
	static StatusCode bookMonitorElement(const DQMModule *const pModule, const TiXmlElement *const pXmlElement,
			const std::string &meName, DQMMonitorElementPtr &monitorElement);

	friend class DQMXmlHelper;
};

//-------------------------------------------------------------------------------------------------

template <typename ObjectType, typename... Args>
inline StatusCode DQMModuleApi::bookObject(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &name, const std::string &title,
		allocator_helper<TObject, ObjectType, Args...> allocator, Args ...args)
{
	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
			USER_DEFINED_ELEMENT_TYPE, ".", name, title, pModule->getName(), allocator, args...));

	pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

template <typename ObjectType, typename... Args>
inline StatusCode DQMModuleApi::bookObject(const DQMModule *const pModule, DQMMonitorElementPtr &monitorElement, const std::string &dirName, const std::string &name, const std::string &title,
		allocator_helper<TObject, ObjectType, Args...> allocator, Args ...args)
{
	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pModule->getModuleApplication()->getMonitorElementManager()->bookObject(monitorElement,
			USER_DEFINED_ELEMENT_TYPE, dirName, name, title, pModule->getName(), allocator, args...));

	pModule->getModuleApplication()->getMonitorElementSender()->addAvailableMonitorElement(monitorElement);

	return STATUS_CODE_SUCCESS;
}

} 

#endif  //  DQMMODULEAPI_H
