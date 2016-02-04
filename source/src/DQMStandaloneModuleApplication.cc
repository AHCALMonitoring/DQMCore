  /// \file DQMStandaloneModuleApplication.cc
/*
 *
 * DQMStandaloneModuleApplication.cc source template automatically generated by a class generator
 * Creation date : mer. ao�t 26 2015
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

// -- dqm4hep headers
#include "dqm4hep/DQMStandaloneModuleApplication.h"
#include "dqm4hep/DQMPluginManager.h"
#include "dqm4hep/DQMFileHandler.h"
#include "dqm4hep/DQMFileHandlerFactory.h"
#include "dqm4hep/DQMMonitorElementManager.h"
#include "dqm4hep/DQMStandaloneModule.h"
#include "dqm4hep/DQMMonitorElementSender.h"
#include "dqm4hep/DQMTimerCycle.h"
#include "dqm4hep/DQMArchiver.h"
#include "dqm4hep/DQMXmlHelper.h"
#include "dqm4hep/tinyxml.h"

// -- std headers
#include <fstream>
#include <stdexcept>

// -- dim headers
#include "dis.hxx"
#include "dic.hxx"

namespace dqm4hep
{

DQMStandaloneModuleApplication::DQMStandaloneModuleApplication() :
		DQMModuleApplication(),
		m_pTimerCycle(NULL),
		m_type("StandaloneModule"),
		m_name("Unknown"),
		m_returnStatusCode(STATUS_CODE_SUCCESS)
{
	m_pArchiver = new DQMArchiver();
}

//-------------------------------------------------------------------------------------------------

DQMStandaloneModuleApplication::~DQMStandaloneModuleApplication() 
{
	if(m_pTimerCycle)
		delete m_pTimerCycle;

	delete m_pArchiver;
}

//-------------------------------------------------------------------------------------------------

const std::string &DQMStandaloneModuleApplication::getType() const
{
	return m_type;
}

//-------------------------------------------------------------------------------------------------

const std::string &DQMStandaloneModuleApplication::getName() const
{
	return m_name;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMStandaloneModuleApplication::readSettings( const std::string &settingsFileName )
{
	if(this->isInitialized())
		return STATUS_CODE_ALREADY_INITIALIZED;

	size_t splitterPosition = settingsFileName.find(":");

	std::string fileHandlerType;
	std::string filePattern;

	if(splitterPosition != std::string::npos)
	{
		fileHandlerType = settingsFileName.substr(0, splitterPosition);
		filePattern = settingsFileName.substr(splitterPosition+1);
	}
	else
	{
		fileHandlerType = "";
		filePattern = settingsFileName;
	}

	streamlog_out(DEBUG) << "File handler type : " << fileHandlerType << std::endl;

	DQMFileHandlerFactory fileHandlerFactory;
	DQMFileHandler *pFileHandler = fileHandlerFactory.createFileHandler(fileHandlerType);

	if(!pFileHandler)
		return STATUS_CODE_FAILURE;

	StatusCode statusCode = pFileHandler->download(filePattern);

	if(statusCode != STATUS_CODE_SUCCESS)
	{
		delete pFileHandler;
		return statusCode;
	}

	m_settings.m_settingsFileName = pFileHandler->getLocalFileName();
	delete pFileHandler;

    TiXmlDocument xmlDocument(m_settings.m_settingsFileName);

    if (!xmlDocument.LoadFile())
    {
        std::cout << "DQMAnalysisModuleApplication::readSettings - Invalid xml file." << std::endl;
        return STATUS_CODE_FAILURE;
    }

    const TiXmlHandle xmlDocumentHandle(&xmlDocument);
    const TiXmlHandle xmlHandle = TiXmlHandle(xmlDocumentHandle.FirstChildElement().Element());



    // monitor element sender
	TiXmlElement *const pMeCollectorElement = xmlHandle.FirstChildElement("monitorelementcollector").Element();

	if(NULL == pMeCollectorElement)
	{
		streamlog_out(ERROR) << "<monitorelementcollector> element not found !" << std::endl;
		return STATUS_CODE_NOT_FOUND;
	}

	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pMeCollectorElement, "name", m_settings.m_monitorElementCollector));

	this->getMonitorElementSender()->setCollectorName(m_settings.m_monitorElementCollector);
	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getMonitorElementSender()->connectToService());


	// cycle
	TiXmlElement *const pCycleElement = xmlHandle.FirstChildElement("cycle").Element();

	if(pCycleElement)
	{
		RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pCycleElement, "sleep", m_settings.m_sleepTime));
		RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pCycleElement, "period", m_settings.m_cyclePeriod));
	}

	m_pTimerCycle = new DQMTimerCycle();
	m_pTimerCycle->setCycleValue(m_settings.m_cyclePeriod);
	m_pTimerCycle->setTimeout(0);
	m_pTimerCycle->addListener(this);




	// module
	TiXmlElement *const pXmlElement = xmlHandle.FirstChildElement("module").Element();

	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "type", m_settings.m_moduleType));
	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "name", m_settings.m_moduleName));

	if(this->getModuleType().empty())
		this->setModuleType(m_settings.m_moduleType);

	if(this->getModuleName().empty())
		this->setModuleName(m_settings.m_moduleName);

	streamlog_out( MESSAGE ) << "Query standalone module to PluginManager ... " << std::endl;

	DQMStandaloneModule *pStandaloneModule = DQMPluginManager::instance()->createPluginClass<DQMStandaloneModule>(this->getModuleType());

	if(!pStandaloneModule)
		return STATUS_CODE_FAILURE;

	this->setModule(pStandaloneModule);

	streamlog_out( MESSAGE ) << "Query standalone module to PluginManager ... OK" << std::endl;

	TiXmlHandle moduleHandle(pXmlElement);

	streamlog_out( MESSAGE ) << "Reading settings of active module '" << this->getModule()->getName() << "' ..." << std::endl;
	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getModule()->readSettings(moduleHandle));
	streamlog_out( MESSAGE ) << "Reading settings of active module '" << this->getModule()->getName() << "' ... OK" << std::endl;

	streamlog_out( MESSAGE ) << "Initializing active module '" << this->getModule()->getName() << "' ..." << std::endl;
	RETURN_RESULT_IF( STATUS_CODE_SUCCESS, !=, this->getModule()->initModule() );
	streamlog_out( MESSAGE ) << "Initializing active module '" << this->getModule()->getName() << "' ... OK" << std::endl;



	try
	{
		streamlog_out(MESSAGE) << "Configuring archiver ..." << std::endl;

		const TiXmlElement *const pXmlElement = xmlHandle.FirstChildElement("archiver").Element();

		THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "open", m_settings.m_openArchive));
		THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "directory", m_settings.m_archiveDirectory));

		streamlog_out(MESSAGE) << "Configuring archiver ... OK" << std::endl;
	}
	catch(const StatusCodeException &exception)
	{
		return exception.getStatusCode();
	}



	m_name = this->getModule()->getName();

	DimBrowser browser;
	int nServers = browser.getServers();

	std::string moduleServerName = "DQM4HEP/Module/" + this->getModule()->getName();

	if(nServers)
	{
		char *serverName;
		char *node;

		while(browser.getNextServer(serverName, node))
		{
			if(moduleServerName == serverName)
			{
				streamlog_out(ERROR) << "Module '" << this->getModule()->getName() << "' already registered over the network.\n"
						<< "Please, change the module name or stop the other module application with the same name !" << std::endl;
				return STATUS_CODE_ALREADY_PRESENT;
			}
		}
	}

	DimServer::start( moduleServerName.c_str() );

	RETURN_RESULT_IF( STATUS_CODE_SUCCESS, !=, this->getMonitorElementSender()->connectToService() );

	this->setInitialized(true);

	m_settings.print();

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMStandaloneModuleApplication::run()
{
	if(!this->isInitialized())
		return STATUS_CODE_NOT_INITIALIZED;

	bool callStartOfCycle = true;

	// get casted module for easier manipulation
	DQMStandaloneModule *pStandaloneModule = dynamic_cast<DQMStandaloneModule *>(this->getModule());


	// open an archive
	if(m_settings.m_openArchive)
	{
		std::stringstream archiveFileName;
		std::string directory =
				m_settings.m_archiveDirectory.at(m_settings.m_archiveDirectory.size() - 1) == '/' ?
						m_settings.m_archiveDirectory : m_settings.m_archiveDirectory + "/";

		archiveFileName << directory
				<< "DQMArchive"
				<< "_M" << m_settings.m_moduleName;

		RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, m_pArchiver->open(archiveFileName.str(), "RECREATE"));
		streamlog_out(MESSAGE) << "Archive '" << m_pArchiver->getFileName() << "' opened" << std::endl;
	}


	while(!this->shouldStopApplication())
	{
		// process a cycle
		streamlog_out(MESSAGE) << "**************************************************" << std::endl;
		streamlog_out(MESSAGE) << "***                Start of cycle              ***" << std::endl;
		streamlog_out(MESSAGE) << "**************************************************" << std::endl;
		m_pTimerCycle->startCycle();

		while(1)
		{
			if( m_pTimerCycle->isEndOfCycleReached() )
				break;

			if( this->shouldStopApplication() )
				break;

			RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pStandaloneModule->process());

			usleep(m_settings.m_sleepTime);
		}

		m_pTimerCycle->stopCycle();

		streamlog_out(MESSAGE) << "**************************************************" << std::endl;
		streamlog_out(MESSAGE) << "***            End of cycle reached            ***" << std::endl;
		streamlog_out(MESSAGE) << "**************************************************" << std::endl;

		streamlog_out(MESSAGE) << "Sending monitor elements to collector" << std::endl;

		RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getMonitorElementSender()->sendMonitorElements());

		// archive publication if user asked for
		if(m_settings.m_openArchive)
			RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, m_pArchiver->archive(pStandaloneModule));
	}

	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pStandaloneModule->endModule());

	// archive the monitor element if archive is opened
	if(m_settings.m_openArchive)
		RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, m_pArchiver->close());

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

void DQMStandaloneModuleApplication::onCycleStarted(const DQMCycle *const /*pCycle*/)
{
	THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getModule()->startOfCycle());
}

//-------------------------------------------------------------------------------------------------

void DQMStandaloneModuleApplication::onCycleStopped(const DQMCycle *const /*pCycle*/)
{
	THROW_RESULT_IF(STATUS_CODE_SUCCESS, !=, this->getModule()->endOfCycle());
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

DQMStandaloneModuleApplication::Settings::Settings() :
		m_sleepTime(10),   // in ms
		m_cyclePeriod(5.f),
		m_monitorElementCollector("DEFAULT"),
		m_archiveDirectory("/tmp"),
		m_openArchive(false)
{
	/* nop */
}

//-------------------------------------------------------------------------------------------------

void DQMStandaloneModuleApplication::Settings::print()
{
	std::string openArchive = m_openArchive ? "yes" : "no";
	streamlog_out(MESSAGE) << "**************************************" << std::endl;
	streamlog_out(MESSAGE) << "******* Application parameters *******" << std::endl;
	streamlog_out(MESSAGE) << "*** Settings file name :             " << m_settingsFileName << std::endl;
	streamlog_out(MESSAGE) << "*** Module type :                    " << m_moduleType << std::endl;
	streamlog_out(MESSAGE) << "*** Module name :                    " << m_moduleName << std::endl;
	streamlog_out(MESSAGE) << "*** Cycle period :                   " << m_cyclePeriod << std::endl;
	streamlog_out(MESSAGE) << "*** Open archive ?                   " << openArchive << std::endl;
	streamlog_out(MESSAGE) << "*** Archive directory :              " << m_archiveDirectory << std::endl;
	streamlog_out(MESSAGE) << "*** Monitor element collector name : " << m_monitorElementCollector << std::endl;
	streamlog_out(MESSAGE) << "**************************************" << std::endl;
}

} 

