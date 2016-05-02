  /// \file DQMXmlHelper.cc
/*
 *
 * DQMXmlHelper.cc source template automatically generated by a class generator
 * Creation date : mar. juil. 1 2014
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


#include "dqm4hep/DQMXmlHelper.h"
#include "dqm4hep/DQMModuleApi.h"
#include "dqm4hep/DQMModule.h"

namespace dqm4hep
{

//----------------------------------------------------------------------------------------------------

void DQMXmlHelper::tokenizeString(const std::string &inputString, StringVector &tokens, const std::string &delimiter)
{
    std::string::size_type lastPos = inputString.find_first_not_of(delimiter, 0);
    std::string::size_type pos     = inputString.find_first_of(delimiter, lastPos);

    while ((std::string::npos != pos) || (std::string::npos != lastPos))
    {
        tokens.push_back(inputString.substr(lastPos, pos - lastPos));
        lastPos = inputString.find_first_not_of(delimiter, pos);
        pos = inputString.find_first_of(delimiter, lastPos);
    }
}

//----------------------------------------------------------------------------------------------------

StatusCode DQMXmlHelper::createQualityTest(const DQMModule *const pModule, const TiXmlHandle &xmlHandle, const std::string &qualityTestName)
{
    for (TiXmlElement *pXmlElement = xmlHandle.FirstChild("qualitytest").Element(); NULL != pXmlElement;
        pXmlElement = pXmlElement->NextSiblingElement("qualitytest"))
    {
    	std::string name;
    	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "name", name));

    	if(name != qualityTestName)
    		continue;

    	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMModuleApi::createQualityTest(pModule, pXmlElement));

    	return STATUS_CODE_SUCCESS;
    }

    return STATUS_CODE_NOT_FOUND;
}

//----------------------------------------------------------------------------------------------------

StatusCode DQMXmlHelper::bookMonitorElement(const DQMModule *const pModule, const TiXmlHandle &xmlHandle, const std::string &meStringId,
		DQMMonitorElementPtr &monitorElement)
{
	return DQMXmlHelper::bookMonitorElement(pModule, xmlHandle, meStringId, "", monitorElement);
}

//----------------------------------------------------------------------------------------------------

StatusCode DQMXmlHelper::bookMonitorElement(const DQMModule *const pModule, const TiXmlHandle &xmlHandle, const std::string &meStringId,
		const std::string &strSuffix, DQMMonitorElementPtr &monitorElement)
{
    for (TiXmlElement *pXmlElement = xmlHandle.FirstChild("monitorElement").Element(); NULL != pXmlElement;
        pXmlElement = pXmlElement->NextSiblingElement("monitorElement"))
    {
    	std::string meId;
    	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "ID", meId));

    	if(meId != meStringId)
    		continue;

    	std::string meName;
    	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "name", meName));

    	meName += strSuffix;

    	return DQMModuleApi::bookMonitorElement(pModule, pXmlElement, meName, monitorElement);
    }

	return STATUS_CODE_NOT_FOUND;
}

//----------------------------------------------------------------------------------------------------

StatusCode DQMXmlHelper::bookMonitorElement(const DQMModule *const pModule, const TiXmlHandle &xmlHandle, const std::string &meStringId,
		unsigned int suffix, DQMMonitorElementPtr &monitorElement)
{
	std::stringstream ss;
	ss << suffix;

	return DQMXmlHelper::bookMonitorElement(pModule, xmlHandle, meStringId, ss.str(), monitorElement);
}

//----------------------------------------------------------------------------------------------------

StatusCode DQMXmlHelper::replaceAllXmlAttributes(TiXmlElement *pXmlElement, const DQMParameters &parameters)
{
	for(auto paramIter = parameters.begin(), endParamIter = parameters.end() ;
			endParamIter != paramIter ; ++paramIter)
	{
		std::string key(paramIter->first);
		std::string value(paramIter->second);

		StringVector xmlElementNames;
		tokenizeString(key, xmlElementNames, ".");

		TiXmlElement *pCurrentElement = pXmlElement;
		bool keyIsParameter = false;

		for(unsigned int e=0 ; e<xmlElementNames.size() ; e++)
		{
			std::string subKey(xmlElementNames.at(e));

			// last sub key
			if( e == xmlElementNames.size()-1 )
			{
				if( keyIsParameter )
				{
					if( ! pCurrentElement->NoChildren() )
						pCurrentElement->Clear();

					TiXmlText *pText = new TiXmlText( value );
					pCurrentElement->LinkEndChild(pText);

					LOG4CXX_DEBUG( dqmMainLogger, "Parameter key '" << key << "' set to " << value );
				}
				else
				{
					pCurrentElement->SetAttribute( subKey , value );
					LOG4CXX_DEBUG( dqmMainLogger, "Key attribute '" << key << "' set to " << value );
				}
			}
			else
			{
				if( e == xmlElementNames.size()-2 && subKey == "parameter" )
				{
					bool found = false;
					std::string parameterName( xmlElementNames.at(e+1) );

				    for (TiXmlElement *pXmlElement = pCurrentElement->FirstChildElement("parameter"); NULL != pXmlElement;
				        pXmlElement = pXmlElement->NextSiblingElement("parameter"))
				    {
				    	std::string name;
				    	RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::getAttribute(pXmlElement, "name", name));

				    	if( name == parameterName )
				    	{
				    		pCurrentElement = pXmlElement;
				    		found = true;
				    		break;
				    	}
				    }

				    if( ! found )
				    {
				    	LOG4CXX_ERROR( dqmMainLogger , "Key '" << key << "' , subKey '" << subKey << "' xml element not found !" );
				    	return STATUS_CODE_NOT_FOUND;
				    }

					keyIsParameter = true;
				}
				else
					pCurrentElement = pCurrentElement->FirstChildElement( subKey );

				if( NULL == pCurrentElement )
				{
					LOG4CXX_ERROR( dqmMainLogger , "Key '" << key << "' , subKey '" << subKey << "' xml element not found !" );
					return STATUS_CODE_NOT_FOUND;
				}
			}
		}
	}

	return STATUS_CODE_SUCCESS;
}








}
