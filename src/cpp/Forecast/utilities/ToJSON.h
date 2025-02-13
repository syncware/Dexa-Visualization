#pragma once

#include <napi.h>
// #include "node_modules/node-addon-api/napi.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <exception>
#include <tuple>
#include "../../nlohmann/json.hpp"
#include "../ProductionForecast/Forecast.h"
#include "../ProductionForecast/Decline_Curve_Analysis.h"
#include "../../MathematicsLibrary/Integration.h"
#include "../ProductionForecast/FractionalFlow.h"
#include "../ProductionForecast/DateCreation.h"
#include "../../MathematicsLibrary/MainSimplex.h"
#include "../../MathematicsLibrary/Arithmetic.h"
#include "../../MathematicsLibrary/Interpolation.h"
#include "../ProductionForecast/Inputdeck.h"
#include "../ProductionForecast/dataPivoting.h"
#include "ToJSON2.h"
#include "AllWellsYearlyResultNewAsyncT.h"

using namespace std;
using namespace std::placeholders;
using json = nlohmann::json;

class ReportJSON
{

public:
	dataPivoting _dataPivoting2;
	Napi::Object FacilitiesObject;
	Napi::Object FacilitiesObjectYealy;
	DateCreation dateCreation2;
	vector<FacilityStructExternal> FacilityTable2;
	double myZero2 = 0.00000001;
	FractionalFlow fractionalFlow2;
	Decline_Curve_Analysis decline_Curve_Analysis2;
	Inputdeck inputdeck2;
	RunParameter runParameter2;
	Arithmetic arithmetic2;
	Interpolation interpolation2;
	int nValidatedDecks2;
	ReportJSON2 reportJSON2;
	AllWellsYearlyResultNewAsyncT allWellsYearlyResultNewAsyncT;

	vector<InputDeckStruct> getDecks(Napi::Array &wrappedDecks,
									 Napi::Array wrappedProdPrioritization,
									 int nWrappedDecks, int nWrappedProdPrioritization, Napi::Env &env);

	// void GetFacilityList(Napi::Array& wrappedFacilities, int nWrappedFacilities, Napi::Env& env);

	vector<ForecastResult> GetForecastProfiles(Napi::Array &wrappedForecastProfiles,
											   int nWrappedForecastProfiles, Napi::Env &env);

	void GetRunParameters(Napi::Object &wrappedRunParameters, Napi::Env &env);

	void GetForecastOutput(Napi::Env &env, int &scenario, Date &stopDate);
	void GetForecastOutput(int &scenario,
						   vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies,
						   vector<Date> &dateTimes, vector<string> Facilities, Napi::Env &env);

	Napi::Array getDeclineParameters(vector<InputDeckStruct> &InputDecks, Napi::Env &env);
	Napi::Array getUpdatedInputDecks(Napi::Array &wrappedDecks, Napi::Env &env,
									 bool &isDefault, int nWrappedDecks);

	vector<ForecastResult> GetYearlyForcastResultModuleLevel(Napi::Object &wrappedSelectedModule, Napi::Env &env);
	Napi::Object SetRowResult(ForecastResult &r, Napi::Env &env);
	Napi::Object GetForecastOutput(Napi::Env &env, vector<ForecastResult> &results);
	vector<vector<ForecastResult>> GetYearlyForcastResultModules(Napi::Array &wellsForecastResults,
																 Napi::Env &env, int nWells);
	Napi::Array GetForecastOutputWWells(Napi::Env &env, vector<vector<ForecastResult>> &results);
	Napi::Array GetForecastOutputWWellsNEW(Napi::Env &env, vector<vector<ForecastResult>> &results);

	vector<vector<vector<ForecastResult>>> GetYearlyForcastResultFacilitiesLevel(
		Napi::Array &wellsForecastResults, Napi::Env &env,
		int nFacilities);

	InterpParams GetInterpParams(Napi::Object &wrappedInterpParams, Napi::Env &env);

	Napi::Object GetInterpResult(Napi::Env &env, vector<double> &result);
	Napi::Array getWellPriorizations(Napi::Array &wrappedDecks, Napi::Env &env);
	vector<vector<ForecastResultForChart>> GetYearlyForcastResultModulesForChart(Napi::Array &wellsForecastResults, Napi::Env &env);
	vector<ForecastResultForChart> GetYearlyForcastResultModuleLevelChart(Napi::Object &wrappedSelectedModule, Napi::Env &env);
	Napi::Array GetForecastOutputWWellsForChart(Napi::Env &env, vector<vector<ForecastResultForChart>> &results);
	Napi::Object GetForecastOutputForChart(Napi::Env &env, vector<ForecastResultForChart> &results);
	Napi::Object SetRowResultForChart(ForecastResultForChart &r, Napi::Env &env);
	string GetRow(Napi::Object &r, Napi::Env &env, bool &isLastRow);
	void GetForecastFacilityOutput(int &k, int &scenario, vector<Date> &datesNew, Napi::Env &env);
	Napi::Array validateInputDecks(Napi::Array &wrappedDecks, Napi::Env &env,
								   bool &isDefault, int nWrappedDecks);

	vector<WellReroute> getWellRerouteDecks(Napi::Array &wrappedDecks,
											int nWellRerouteDecks, Napi::Env &env);
	vector<WellRampUp> getWellRampUpDecks(Napi::Array &wrappedDecks,
										  int nWellRampUpDecks, Napi::Env &env);
	vector<ShutInOpenUp> getWellShutInOpenUpDecks(Napi::Array &wrappedDecks,
												  int nWellShutInOpenUpDecks, Napi::Env &env);
	vector<InternalExternalEquipmentName> GetInternalExternalEquipmentNames(Napi::Array &wrappedDecks,
																			int nInternalExternalFacilitiesNames, Napi::Env &env);
	vector<FacilityStructExternal> GetDefermentsSheetData(Napi::Array &wrappedDecks,
														  int nInternalExternalFacilitiesNames, Napi::Env &env);
	vector<FacilityStructExternal> GetCrudeOilLossesSheetData(Napi::Array &wrappedDecks,
															  int nCrudeOilLosses, Napi::Env &env);
	Prioritization getWrappedTypeOfPrioritization(Napi::Object wrappedTypeOfPrioritization,
												Napi::Env &env);
	vector<vector<string>> GetEquipmentConnections(Napi::Array &wrappedDecks,
												   int nEquipmentConnections, int numberOfNodes, Napi::Env &env);
	vector<FacilityStructExternal> GetFlaredGasesSheetData(Napi::Array &wrappedDecks,
														   int nCrudeOilLosses, Napi::Env &env);
	vector<FacilityStructExternal> GetOwnUseSheetData(Napi::Array &wrappedDecks,
													  int nCrudeOilLosses, Napi::Env &env);
	void GetForecastOutputAllFacilities(int &scenario,
										vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies,
										vector<Date> &dateTimes, Napi::Env &env);
	void GetFacilityList(vector<FacilityStructExternal> &wrappedFacilities);
	vector<InputDeckStruct> getUpdatedInputDecks2(Napi::Array &wrappedDecks, Napi::Env &env,
												  int nWrappedDecks);
	vector<Prioritization> getWrappedNodalPrioritization(Napi::Array wrappedNodalPrioritization,
													   int nWrappedNodalPrioritization, Napi::Env &env);
	vector<string> GetForecastsolutionSpaces(Napi::Array &wrappedForecastsolutionSpaces,
											 int nForecastsolutionSpaces, Napi::Env &env);
	vector<bool> GetForecastsolutionSpacesIsDURConstrained(Napi::Array &wrappedForecastsolutionSpacesIsDURConstrained,
														   int nForecastsolutionSpacesIsDURConstrained, Napi::Env &env);
	vector<FacilityStructExternal> GetCrudeEquipmentCapacitiesSheetData(Napi::Array &wrappedDecks,
																		int nEquipmentCapacities, Napi::Env &env);
	json NapiObjectToJson(const Napi::Object &obj);
	Napi::Array ConvertVectorToNapiArray(Napi::Env env, const vector<double> &vec);
	Napi::Array ConvertVectorToNapiArray(Napi::Env env, const vector<string> &vec);
	Napi::Object ConvertYObjToNapiObject(Napi::Env env, const YObj &yObj);
	Napi::Object ConvertMapToNapiObject(Napi::Env env, const map<string,
																 map<string, map<string, YObj>>> &nestedMap);
	Napi::Object PlotChartAsync(Napi::Env env,
								const Napi::Array &wrappedForecastResults,
								const Napi::Object &wrappedChatInputData);
	Napi::Array ConvertYObjVectorToNapiArray(Napi::Env env, const vector<YObj> &yObjVec);
	Napi::Object ConvertMapToNapiObject(Napi::Env env,
										const map<string, map<string, map<std::string, vector<YObj>>>> &nestedMap);
	json NapiValueToJson(const Napi::Value &value);
	json ConvertNapiArrayToJsonString(const Napi::Array &array);
	ChartInputPayload ConvertToChartInputPayload(const Napi::Object &obj);
	ForecastResultsByModule ConvertToForecastResultsByModule(const Napi::Object &obj);
	std::vector<ForecastResultsByModule> ConvertArrayToVector(const Napi::Array &arr);

	vector<vector<vector<ForecastResult>>> results;

	ReportJSON();
	~ReportJSON();
};

ReportJSON::ReportJSON()
{
}

ReportJSON::~ReportJSON()
{
}

// Helper function to convert a vector of doubles to Napi::Array
Napi::Array ReportJSON::ConvertVectorToNapiArray(Napi::Env env, const vector<double> &vec)
{
	Napi::Array result = Napi::Array::New(env, vec.size());
	for (size_t i = 0; i < vec.size(); ++i)
	{
		result.Set(i, Napi::Number::New(env, vec[i]));
	}
	return result;
}

// Helper function to convert a vector of strings to Napi::Array
Napi::Array ReportJSON::ConvertVectorToNapiArray(Napi::Env env, const vector<string> &vec)
{
	Napi::Array result = Napi::Array::New(env, vec.size());
	for (size_t i = 0; i < vec.size(); ++i)
	{
		result.Set(i, Napi::String::New(env, vec[i]));
	}
	return result;
}

// Function to convert YObj to Napi::Object
Napi::Object ReportJSON::ConvertYObjToNapiObject(Napi::Env env, const YObj &yObj)
{
	Napi::Object obj = Napi::Object::New(env);
	obj.Set("forecastResultId", Napi::String::New(env, yObj.forecastResultId));
	obj.Set("id", Napi::String::New(env, yObj.id));
	obj.Set("name", Napi::String::New(env, yObj.name));
	obj.Set("title", Napi::String::New(env, yObj.title));
	obj.Set("path", Napi::String::New(env, yObj.path));
	obj.Set("y", ConvertVectorToNapiArray(env, yObj.y));
	obj.Set("x", ConvertVectorToNapiArray(env, yObj.x));
	return obj;
}

// Recursive function to convert nested map to Napi::Object
Napi::Object ReportJSON::ConvertMapToNapiObject(Napi::Env env, const map<string,
																		 map<string, map<string, YObj>>> &nestedMap)
{
	Napi::Object result = Napi::Object::New(env);

	for (const auto &[key1, map2] : nestedMap)
	{
		Napi::Object map2Obj = Napi::Object::New(env);

		for (const auto &[key2, map3] : map2)
		{
			Napi::Object map3Obj = Napi::Object::New(env);

			for (const auto &[key3, yObj] : map3)
			{
				map3Obj.Set(key3, ConvertYObjToNapiObject(env, yObj));
			}

			map2Obj.Set(key2, map3Obj);
		}

		result.Set(key1, map2Obj);
	}

	return result;
}

// Function to convert a vector of YObj to Napi::Array
Napi::Array ReportJSON::ConvertYObjVectorToNapiArray(Napi::Env env, const vector<YObj> &yObjVec)
{
	Napi::Array arr = Napi::Array::New(env, yObjVec.size());
	for (size_t i = 0; i < yObjVec.size(); ++i)
	{
		arr.Set(i, ConvertYObjToNapiObject(env, yObjVec[i]));
	}
	return arr;
}

// Recursive function to convert nested map to Napi::Object
Napi::Object ReportJSON::ConvertMapToNapiObject(Napi::Env env,
												const map<string, map<string, map<std::string, vector<YObj>>>> &nestedMap)
{
	Napi::Object result = Napi::Object::New(env);

	for (const auto &[key1, map2] : nestedMap)
	{
		Napi::Object map2Obj = Napi::Object::New(env);

		for (const auto &[key2, map3] : map2)
		{
			Napi::Object map3Obj = Napi::Object::New(env);

			for (const auto &[key3, yObjVec] : map3)
			{
				map3Obj.Set(key3, ConvertYObjVectorToNapiArray(env, yObjVec));
			}

			map2Obj.Set(key2, map3Obj);
		}

		result.Set(key1, map2Obj);
	}

	return result;
}

ChartInputPayload ReportJSON::ConvertToChartInputPayload(const Napi::Object &obj)
{
	ChartInputPayload payload;

	// Convert forecastResultsIds
	Napi::Array forecastResultsIdsArray = obj.Get("forecastResultsIds").As<Napi::Array>();
	for (size_t i = 0; i < forecastResultsIdsArray.Length(); i++)
	{
		payload.forecastResultsIds.push_back(forecastResultsIdsArray.Get(i).As<Napi::String>());
	}

	// Convert selectedModulePaths
	Napi::Array selectedModulePathsArray = obj.Get("selectedModulePaths").As<Napi::Array>();
	for (size_t i = 0; i < selectedModulePathsArray.Length(); i++)
	{
		payload.selectedModulePaths.push_back(selectedModulePathsArray.Get(i).As<Napi::String>());
	}

	// Convert selectedVariables
	Napi::Array selectedVariablesArray = obj.Get("selectedVariables").As<Napi::Array>();
	for (size_t i = 0; i < selectedVariablesArray.Length(); i++)
	{
		payload.selectedVariables.push_back(selectedVariablesArray.Get(i).As<Napi::String>());
	}

	// Convert shouldAggregate
	payload.shouldAggregate = obj.Get("shouldAggregate").As<Napi::Boolean>();

	// Convert forecastSolutionSpaces
	Napi::Array forecastsolutionSpacesArray = obj.Get("forecastSolutionSpaces").As<Napi::Array>();
	for (size_t i = 0; i < forecastsolutionSpacesArray.Length(); i++)
	{
		payload.forecastSolutionSpaces.push_back(forecastsolutionSpacesArray.Get(i).As<Napi::String>());
	}

	return payload;
}

ForecastResultsByModule ReportJSON::ConvertToForecastResultsByModule(const Napi::Object &obj)
{
	ForecastResultsByModule result;
	result.forecastResultsId = obj.Get("forecastResultsId").As<Napi::String>();
	result.moduleName = obj.Get("moduleName").As<Napi::String>();
	result.facilityName = obj.Get("facilityName").As<Napi::String>();
	result.scenarioName = obj.Get("scenarioName").As<Napi::String>();
	result.moduleKey = obj.Get("moduleKey").As<Napi::String>();
	result.solutionSpace = obj.Get("solutionSpace").As<Napi::String>();
	result.forecastResults = obj.Get("forecastResults").As<Napi::String>();
	result.forecastInputId = obj.Get("forecastInputId").As<Napi::String>();
	return result;
}

std::vector<ForecastResultsByModule> ReportJSON::ConvertArrayToVector(const Napi::Array &arr)
{
	std::vector<ForecastResultsByModule> results;
	for (uint32_t i = 0; i < arr.Length(); ++i)
	{
		Napi::Object obj = arr.Get(i).As<Napi::Object>();
		results.push_back(ConvertToForecastResultsByModule(obj));
	}
	return results;
}

Napi::Object ReportJSON::PlotChartAsync(Napi::Env env,
										const Napi::Array &wrappedForecastResults,
										const Napi::Object &wrappedChatInputData)
{

	std::cout << "chartInputPayload read befroe " << std::endl;
	ChartInputPayload chartInputPayload = ConvertToChartInputPayload(wrappedChatInputData);
	std::cout << "chartInputPayload read after " << std::endl;
	std::cout << "forecastResultsByModule read before" << std::endl;
	vector<ForecastResultsByModule> forecastResultsByModule =
		ConvertArrayToVector(wrappedForecastResults);
	std::cout << "forecastResultsByModule read after" << std::endl;

	vector<string> selectedModulePaths = chartInputPayload.selectedModulePaths;
	vector<string> selectedVariables = chartInputPayload.selectedVariables;
	bool isMonthly = false;
	vector<string> forecastSolutionSpaceNames = chartInputPayload.forecastSolutionSpaces;
	string forecastResultsId = chartInputPayload.forecastResultsIds[0];
	bool shouldAggregate = chartInputPayload.shouldAggregate;

	map<string, map<string, map<string, vector<YObj>>>> _scenarioObjects;

	json jsonChartDataOutput;
	Napi::Object napiObject = Napi::Object::New(env);

	if (chartInputPayload.shouldAggregate == false)
	{
		_scenarioObjects =
			allWellsYearlyResultNewAsyncT.chartDataByModulesOrAggregate(
				selectedModulePaths,
				selectedVariables,
				isMonthly,
				forecastSolutionSpaceNames,
				forecastResultsByModule,
				forecastResultsId,
				shouldAggregate);

		napiObject = ConvertMapToNapiObject(env, _scenarioObjects);
	}
	else
	{
		_scenarioObjects =
			allWellsYearlyResultNewAsyncT.chartDataByModulesOrAggregate(
				selectedModulePaths,
				selectedVariables,
				isMonthly,
				forecastSolutionSpaceNames,
				forecastResultsByModule,
				forecastResultsId,
				shouldAggregate);

		map<string, map<string, map<string, YObj>>> aggregatedScenarioObjects =
			allWellsYearlyResultNewAsyncT.chartDataByModulesOrAggregate2(
				forecastResultsId,
				_scenarioObjects);

		napiObject = ConvertMapToNapiObject(env, aggregatedScenarioObjects);
	}

	return napiObject;
}

json ReportJSON::NapiValueToJson(const Napi::Value &value)
{
	if (value.IsArray())
	{
		Napi::Array array = value.As<Napi::Array>();
		json jsonArray = json::array();

		for (size_t i = 0; i < array.Length(); ++i)
		{
			// std::cout << i << " before "<< std::endl;
			jsonArray.push_back(NapiValueToJson(array[i]));
			// std::cout << i << " after "<< std::endl;
		}
		return jsonArray;
	}
	else if (value.IsObject())
	{
		Napi::Object object = value.As<Napi::Object>();
		json jsonObject;

		Napi::Array propertyNames = object.GetPropertyNames();
		for (size_t i = 0; i < propertyNames.Length(); ++i)
		{
			string key = propertyNames.Get(i).As<Napi::String>();
			jsonObject[key] = NapiValueToJson(object.Get(key));
		}
		return jsonObject;
	}
	else if (value.IsString())
	{
		return value.As<Napi::String>().Utf8Value();
	}
	else if (value.IsNumber())
	{
		return value.As<Napi::Number>().DoubleValue();
	}
	else if (value.IsBoolean())
	{
		return value.As<Napi::Boolean>().Value();
	}
	else if (value.IsNull() || value.IsUndefined())
	{
		return nullptr;
	}
	else
	{
		throw runtime_error("Unsupported Napi::Value type");
	}
}

json ReportJSON::ConvertNapiArrayToJsonString(const Napi::Array &array)
{
	json jsonArray = NapiValueToJson(array);
	return jsonArray;
}

json ReportJSON::NapiObjectToJson(const Napi::Object &obj)
{
	json jsonObj;

	// Get the property names (keys) of the Napi::Object
	Napi::Array keys = obj.GetPropertyNames();

	for (uint32_t i = 0; i < keys.Length(); ++i)
	{
		std::string key = keys.Get(i).As<Napi::String>();

		Napi::Value value = obj.Get(key);

		if (value.IsString())
		{
			jsonObj[key] = value.As<Napi::String>().Utf8Value();
		}
		else if (value.IsNumber())
		{
			jsonObj[key] = value.As<Napi::Number>().DoubleValue();
		}
		else if (value.IsBoolean())
		{
			jsonObj[key] = value.As<Napi::Boolean>().Value();
		}
		else if (value.IsObject())
		{
			jsonObj[key] = NapiObjectToJson(value.As<Napi::Object>());
		}
		else if (value.IsArray())
		{
			Napi::Array array = value.As<Napi::Array>();
			json jsonArray = json::array();
			for (uint32_t j = 0; j < array.Length(); ++j)
			{
				Napi::Value arrayValue = array.Get(j);
				if (arrayValue.IsObject())
				{
					jsonArray.push_back(NapiObjectToJson(arrayValue.As<Napi::Object>()));
				}
				else if (arrayValue.IsString())
				{
					jsonArray.push_back(arrayValue.As<Napi::String>().Utf8Value());
				}
				else if (arrayValue.IsNumber())
				{
					jsonArray.push_back(arrayValue.As<Napi::Number>().DoubleValue());
				}
				else if (arrayValue.IsBoolean())
				{
					jsonArray.push_back(arrayValue.As<Napi::Boolean>().Value());
				}
			}
			jsonObj[key] = jsonArray;
		}
		// Handle other types as needed
	}

	return jsonObj;
}

Prioritization ReportJSON::getWrappedTypeOfPrioritization(Napi::Object wrappedTypeOfPrioritization,
														Napi::Env &env)
{

	Prioritization prioritization;
	prioritization.typeOfPrioritization = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "typeOfPrioritization"))).As<Napi::String>();
	prioritization.methodOfPrioritization = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "methodOfPrioritization"))).As<Napi::String>();
	prioritization.targetFluid = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "targetFluid"))).As<Napi::String>();
	Napi::Array parameterNamesWeights = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "parameterNamesWeights"))).As<Napi::Array>();
	Napi::Number nParameterNamesWeights = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "nParameterNamesWeights"))).As<Napi::Number>();
	int count = (int)nParameterNamesWeights;
	int i = 0;
	for (i = 0; i < count; i++)
	{
		Napi::Object parameterNamesWeightsObject = ((Napi::Value)parameterNamesWeights[i]).As<Napi::Object>();
		string parameterName = (parameterNamesWeightsObject.Get(Napi::String::New(env, "parameterName"))).As<Napi::String>();
		double parameterWeight = (parameterNamesWeightsObject.Get(Napi::String::New(env, "parameterWeight"))).As<Napi::Number>();
		prioritization.prioritizationModel.ParameterNames.push_back(parameterName);
		prioritization.prioritizationModel.ParameterWeights.push_back(parameterWeight);
	}

	std::cout << "getWrappedTypeOfPrioritization completed " << "\n";

	return prioritization;
}

vector<Prioritization> ReportJSON::getWrappedNodalPrioritization(Napi::Array wrappedNodalPrioritization,
															   int nWrappedNodalPrioritization, Napi::Env &env)
{

	int lent = nWrappedNodalPrioritization;
	std::cout << "getWrappedNodalPrioritization started" << std::endl;

	vector<Prioritization> nodalPrioritizations;

	for (int j = 0; j < lent; j++)
	{
		Napi::Object wrappedTypeOfPrioritization = ((Napi::Value)wrappedNodalPrioritization[j]).As<Napi::Object>();
		Prioritization prioritization;
		prioritization.facilityName = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "productionEquipment"))).As<Napi::String>();
		prioritization.typeOfPrioritization = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "typeOfPrioritization"))).As<Napi::String>();
		prioritization.methodOfPrioritization = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "methodOfPrioritization"))).As<Napi::String>();
		prioritization.targetFluid = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "targetFluid"))).As<Napi::String>();
		Napi::Array parameterNamesWeights = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "parameterNamesWeights"))).As<Napi::Array>();
		Napi::Number nParameterNamesWeights = (wrappedTypeOfPrioritization.Get(Napi::String::New(env, "nParameterNamesWeights"))).As<Napi::Number>();
		int count = (int)nParameterNamesWeights;
		int i = 0;
		for (i = 0; i < count; i++)
		{
			Napi::Object parameterNamesWeightsObject = ((Napi::Value)parameterNamesWeights[i]).As<Napi::Object>();
			string parameterName = (parameterNamesWeightsObject.Get(Napi::String::New(env, "parameterName"))).As<Napi::String>();
			double parameterWeight = (parameterNamesWeightsObject.Get(Napi::String::New(env, "parameterWeight"))).As<Napi::Number>();
			prioritization.prioritizationModel.ParameterNames.push_back(parameterName);
			prioritization.prioritizationModel.ParameterWeights.push_back(parameterWeight);
		}
		nodalPrioritizations.push_back(prioritization);
	}

	std::cout << "getWrappedNodalPrioritization completed " << "\n";

	return nodalPrioritizations;
}

vector<InputDeckStruct> ReportJSON::getDecks(Napi::Array &wrappedDecks,
											 Napi::Array wrappedProdPrioritization,
											 int nWrappedDecks, int nWrappedProdPrioritization, Napi::Env &env)
{

	int lent = nWrappedDecks;
	std::cout << "getDecks started" << std::endl;

	vector<InputDeckStruct> InputDecks;

	for (int i = 0; i < lent; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		InputDeckStruct deck;
		deck.Version_Name = (wrappedDeck.Get(Napi::String::New(env, "forecastVersion"))).As<Napi::String>();
		deck.Asset_Team = (wrappedDeck.Get(Napi::String::New(env, "asset"))).As<Napi::String>();
		deck.Field = (wrappedDeck.Get(Napi::String::New(env, "field"))).As<Napi::String>();
		deck.Reservoir = (wrappedDeck.Get(Napi::String::New(env, "reservoir"))).As<Napi::String>();
		deck.Drainage_Point = (wrappedDeck.Get(Napi::String::New(env, "drainagePoint"))).As<Napi::String>();
		deck.Production_String = (wrappedDeck.Get(Napi::String::New(env, "string"))).As<Napi::String>();
		deck.Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		deck.PEEP_Project = (wrappedDeck.Get(Napi::String::New(env, "projectCode"))).As<Napi::String>();
		deck.Activity_Entity = (wrappedDeck.Get(Napi::String::New(env, "projectName"))).As<Napi::String>();
		deck.Flow_station = (wrappedDeck.Get(Napi::String::New(env, "facilities"))).As<Napi::String>();
		deck.Hydrocarbon_Stream = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonStream"))).As<Napi::String>();
		inputdeck.ToLower(deck.Hydrocarbon_Stream);
		deck.hydrocarbonType = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonType"))).As<Napi::String>();
		inputdeck.ToLower(deck.hydrocarbonType);
		deck.terminal = (wrappedDeck.Get(Napi::String::New(env, "terminal"))).As<Napi::String>();
		inputdeck.ToLower(deck.terminal);

		deck.Resource_Class = (wrappedDeck.Get(Napi::String::New(env, "resourceClass"))).As<Napi::String>();
		inputdeck.ToLower(deck.Resource_Class);
		deck.URo_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "oilUR1P1C"))).As<Napi::Number>();
		deck.URo_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "oilUR2P2C"))).As<Napi::Number>();
		deck.URo_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "oilUR3P3C"))).As<Napi::Number>();
		deck.Np = (wrappedDeck.Get(Napi::String::New(env, "Np"))).As<Napi::Number>();
		deck.URg_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "gasUR1P1C"))).As<Napi::Number>();
		deck.URg_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "gasUR2P2C"))).As<Napi::Number>();
		deck.URg_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "gasUR3P3C"))).As<Napi::Number>();
		deck.Gp = (wrappedDeck.Get(Napi::String::New(env, "Gp"))).As<Napi::Number>();
		// std::cout << "getDecks Called 2" << std::endl;

		deck.Init_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate1P1C"))).As<Napi::Number>();
		deck.Init_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate2P2C"))).As<Napi::Number>();
		deck.Init_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate3P3C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate1P1C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate2P2C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate3P3C"))).As<Napi::Number>();

		deck.Init_BSW_WGR = (wrappedDeck.Get(Napi::String::New(env, "initBSWWGR"))).As<Napi::Number>();
		if (deck.Init_BSW_WGR == 0)
			deck.Init_BSW_WGR = 0.00000001;
		deck.Aband_BSW_WGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR1P1C"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR2P2C"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR3P3C"))).As<Napi::Number>();
		deck.Init_GOR_CGR = (wrappedDeck.Get(Napi::String::New(env, "initGORCGR"))).As<Napi::Number>();
		if (deck.Init_GOR_CGR == 0)
			deck.Init_GOR_CGR = 0.00000001;
		deck.Aband_GOR_CGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR1P1C"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR2P2C"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR3P3C"))).As<Napi::Number>();
		deck.Plateau_Oil_Gas = (wrappedDeck.Get(Napi::String::New(env, "plateauPeriod"))).As<Napi::Number>();

		if (nWrappedProdPrioritization > 0 && nWrappedProdPrioritization == lent)
		{
			Napi::Object prodPrioritizationRow = ((Napi::Value)wrappedProdPrioritization[i]).As<Napi::Object>();
			string optimizationWeight = (prodPrioritizationRow.Get(Napi::String::New(env, "optimizationWeight"))).As<Napi::String>();
			// std::cout << "optimizationWeight: "  << optimizationWeight << std::endl;
			deck.optimizationWeight2 = optimizationWeight;
			inputdeck.ToLower(deck.optimizationWeight2);
		}
		else
		{
			deck.optimizationWeight2 = "normal";
		}

		// std::cout << "getDecks Called 3" << std::endl;
		deck.On_stream_Date_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate1P1C"))).As<Napi::String>();
		deck.On_stream_Date_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate2P2C"))).As<Napi::String>();
		deck.On_stream_Date_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate3P3C"))).As<Napi::String>();
		deck.Remarks = (wrappedDeck.Get(Napi::String::New(env, "remarks"))).As<Napi::String>();
		deck.TRANCHE = (wrappedDeck.Get(Napi::String::New(env, "developmentTranche"))).As<Napi::String>();

		// std::cout << "rateofChangeRate1P1C" << std::endl;
		deck.Rate_of_Change_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "rateofChangeRate1P1C"))).As<Napi::Number>();
		deck.Rate_of_Change_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "rateofChangeRate2P2C"))).As<Napi::Number>();
		deck.Rate_of_Change_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "rateofChangeRate3P3C"))).As<Napi::Number>();

		// std::cout << "rateofChangeRate3P3C" << std::endl;

		deck.DeclineExponent_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "declineExponent1P1C"))).As<Napi::Number>();
		deck.DeclineExponent_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "declineExponent2P2C"))).As<Napi::Number>();
		deck.DeclineExponent_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "declineExponent3P3C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_GOR_CGR_1P1C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeGORCGR1P1C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_GOR_CGR_2P2C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeGORCGR2P2C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_GOR_CGR_3P3C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeGORCGR3P3C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_BSW_WGR_1P1C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeBSWWGR1P1C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_BSW_WGR_2P2C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeBSWWGR2P2C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_BSW_WGR_3P3C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeBSWWGR3P3C"))).As<Napi::Number>();

		string DeclineMethod = (wrappedDeck.Get(Napi::String::New(env, "declineMethod"))).As<Napi::String>();
		inputdeck.ToLower(DeclineMethod);

		if (DeclineMethod == "exponential")
		{
			deck.DeclineMethod = 1;
		}
		else if (DeclineMethod == "hyperbolic")
		{
			deck.DeclineMethod = 2;
		}
		else
		{
			deck.DeclineMethod = 3;
		}

		deck.day_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "day1P1C"))).As<Napi::Number>();
		deck.day_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "day2P2C"))).As<Napi::Number>();
		deck.day_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "day3P3C"))).As<Napi::Number>();

		deck.month_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "month1P1C"))).As<Napi::Number>();
		deck.month_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "month2P2C"))).As<Napi::Number>();
		deck.month_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "month3P3C"))).As<Napi::Number>();

		deck.year_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "year1P1C"))).As<Napi::Number>();
		deck.year_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "year2P2C"))).As<Napi::Number>();
		deck.year_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "year3P3C"))).As<Napi::Number>();

		deck.PlateauUR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "plateauUR1P1C"))).As<Napi::Number>();
		deck.PlateauUR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "plateauUR2P2C"))).As<Napi::Number>();
		deck.PlateauUR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "plateauUR3P3C"))).As<Napi::Number>();

		deck.Date_1P_1C.day = deck.day_1P_1C;
		deck.Date_1P_1C.month = deck.month_1P_1C;
		deck.Date_1P_1C.year = deck.year_1P_1C;
		deck.Date_2P_2C.day = deck.day_2P_2C;
		deck.Date_2P_2C.month = deck.month_2P_2C;
		deck.Date_2P_2C.year = deck.year_2P_2C;
		deck.Date_3P_3C.day = deck.day_3P_3C;
		deck.Date_3P_3C.month = deck.month_3P_3C;
		deck.Date_3P_3C.year = deck.year_3P_3C;

		deck.Description = (wrappedDeck.Get(Napi::String::New(env, "description"))).As<Napi::String>();

		if (deck.Description == "no error")
		{
			InputDecks.push_back(deck);
		}
	}

	std::cout << "getDecks completed" << std::endl;

	return InputDecks;
}

vector<string> ReportJSON::GetForecastsolutionSpaces(Napi::Array &wrappedForecastsolutionSpaces,
													 int nForecastsolutionSpaces, Napi::Env &env)
{

	vector<string> forecastSolutionSpaces;

	for (int i = 0; i < nForecastsolutionSpaces; i++)
	{
		string forecastsolutionSpace = ((Napi::Value)wrappedForecastsolutionSpaces[i]).As<Napi::String>();
		inputdeck.ToLower(forecastsolutionSpace);
		forecastSolutionSpaces.push_back(forecastsolutionSpace);
	}

	return forecastSolutionSpaces;
}

vector<bool> ReportJSON::GetForecastsolutionSpacesIsDURConstrained(Napi::Array &wrappedForecastsolutionSpacesIsDURConstrained,
																   int nForecastsolutionSpacesIsDURConstrained, Napi::Env &env)
{

	vector<bool> forecastsolutionSpacesIsDURConstrained;

	for (int i = 0; i < nForecastsolutionSpacesIsDURConstrained; i++)
	{
		bool forecastsolutionSpaceIsDURConstrained = ((Napi::Value)wrappedForecastsolutionSpacesIsDURConstrained[i]).As<Napi::Boolean>();
		forecastsolutionSpacesIsDURConstrained.push_back(forecastsolutionSpaceIsDURConstrained);
	}

	return forecastsolutionSpacesIsDURConstrained;
}

vector<InternalExternalEquipmentName> ReportJSON::GetInternalExternalEquipmentNames(Napi::Array &wrappedDecks,
																					int nInternalExternalFacilitiesNames, Napi::Env &env)
{

	vector<InternalExternalEquipmentName> internalExternalEquipmentNames;

	for (int i = 0; i < nInternalExternalFacilitiesNames; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		InternalExternalEquipmentName internalExternalEquipmentName;
		internalExternalEquipmentName.externalEquipmentName = (wrappedDeck.Get(Napi::String::New(env, "externalEquipmentName"))).As<Napi::String>();
		internalExternalEquipmentName.internalEquipmentName = (wrappedDeck.Get(Napi::String::New(env, "internalEquipmentName"))).As<Napi::String>();
		internalExternalEquipmentName.equipmentType = (wrappedDeck.Get(Napi::String::New(env, "equipmentType"))).As<Napi::String>();
		inputdeck.ToLower(internalExternalEquipmentName.equipmentType);
		internalExternalEquipmentNames.push_back(internalExternalEquipmentName);
	}

	return internalExternalEquipmentNames;
}

vector<vector<string>> ReportJSON::GetEquipmentConnections(Napi::Array &wrappedDecks,
														   int nEquipmentConnections, int numberOfNodes, Napi::Env &env)
{

	vector<vector<string>> equipmentConnections;

	for (int i = 0; i < nEquipmentConnections; i++)
	{
		// Object = { "0": "FS1", "1", "Oil_pipeline", ...}
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();
		vector<string> row;
		for (int j = 0; j < numberOfNodes; j++)
		{
			string nodeIndex = "node" + to_string(j + 1);
			string value = wrappedDeck.Get(Napi::String::New(env, nodeIndex)).As<Napi::String>();
			row.push_back(value);
		}
		equipmentConnections.push_back(row);
	}

	return equipmentConnections;
}

vector<FacilityStructExternal> ReportJSON::GetDefermentsSheetData(Napi::Array &wrappedDecks,
																  int nInternalExternalFacilitiesNames, Napi::Env &env)
{

	vector<FacilityStructExternal> equpmentDefermentsData;

	for (int i = 0; i < nInternalExternalFacilitiesNames; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		FacilityStructExternal facilityStructExternal;
		facilityStructExternal.Primary_Facility = (wrappedDeck.Get(Napi::String::New(env, "Primary_Facility"))).As<Napi::String>();
		facilityStructExternal.FDate1P = (wrappedDeck.Get(Napi::String::New(env, "FDate1P"))).As<Napi::String>();
		facilityStructExternal.FDate2P = (wrappedDeck.Get(Napi::String::New(env, "FDate2P"))).As<Napi::String>();
		facilityStructExternal.FDate3P = (wrappedDeck.Get(Napi::String::New(env, "FDate3P"))).As<Napi::String>();
		facilityStructExternal.Scheduled_Deferment1P = (wrappedDeck.Get(Napi::String::New(env, "Scheduled_Deferment1P"))).As<Napi::Number>();
		facilityStructExternal.Scheduled_Deferment2P = (wrappedDeck.Get(Napi::String::New(env, "Scheduled_Deferment2P"))).As<Napi::Number>();
		facilityStructExternal.Scheduled_Deferment3P = (wrappedDeck.Get(Napi::String::New(env, "Scheduled_Deferment3P"))).As<Napi::Number>();
		facilityStructExternal.Unscheduled_Deferment1P = (wrappedDeck.Get(Napi::String::New(env, "Unscheduled_Deferment1P"))).As<Napi::Number>();
		facilityStructExternal.Unscheduled_Deferment2P = (wrappedDeck.Get(Napi::String::New(env, "Unscheduled_Deferment2P"))).As<Napi::Number>();
		facilityStructExternal.Unscheduled_Deferment3P = (wrappedDeck.Get(Napi::String::New(env, "Unscheduled_Deferment3P"))).As<Napi::Number>();
		facilityStructExternal.Thirdparty_Deferment1P = (wrappedDeck.Get(Napi::String::New(env, "Thirdparty_Deferment1P"))).As<Napi::Number>();
		facilityStructExternal.Thirdparty_Deferment2P = (wrappedDeck.Get(Napi::String::New(env, "Thirdparty_Deferment2P"))).As<Napi::Number>();
		facilityStructExternal.Thirdparty_Deferment3P = (wrappedDeck.Get(Napi::String::New(env, "Thirdparty_Deferment3P"))).As<Napi::Number>();

		tm tm1, tm2, tm3;
		sscanf(facilityStructExternal.FDate1P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate2P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate3P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		facilityStructExternal.FacilityDate1P.day = tm1.tm_mday;
		facilityStructExternal.FacilityDate1P.month = tm1.tm_mon;
		facilityStructExternal.FacilityDate1P.year = tm1.tm_year;

		facilityStructExternal.FacilityDate2P.day = tm2.tm_mday;
		facilityStructExternal.FacilityDate2P.month = tm2.tm_mon;
		facilityStructExternal.FacilityDate2P.year = tm2.tm_year;

		facilityStructExternal.FacilityDate3P.day = tm3.tm_mday;
		facilityStructExternal.FacilityDate3P.month = tm3.tm_mon;
		facilityStructExternal.FacilityDate3P.year = tm3.tm_year;

		equpmentDefermentsData.push_back(facilityStructExternal);
	}

	return equpmentDefermentsData;
}

vector<FacilityStructExternal> ReportJSON::GetCrudeOilLossesSheetData(Napi::Array &wrappedDecks,
																	  int nCrudeOilLosses, Napi::Env &env)
{

	vector<FacilityStructExternal> equpmentCrudeOilLossesData;

	for (int i = 0; i < nCrudeOilLosses; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		FacilityStructExternal facilityStructExternal;
		facilityStructExternal.Primary_Facility = (wrappedDeck.Get(Napi::String::New(env, "Primary_Facility"))).As<Napi::String>();
		facilityStructExternal.FDate1P = (wrappedDeck.Get(Napi::String::New(env, "FDate1P"))).As<Napi::String>();
		facilityStructExternal.FDate2P = (wrappedDeck.Get(Napi::String::New(env, "FDate2P"))).As<Napi::String>();
		facilityStructExternal.FDate3P = (wrappedDeck.Get(Napi::String::New(env, "FDate3P"))).As<Napi::String>();
		facilityStructExternal.Crudeoil_Lossess1P = (wrappedDeck.Get(Napi::String::New(env, "Crudeoil_Lossess1P"))).As<Napi::Number>();
		facilityStructExternal.Crudeoil_Lossess2P = (wrappedDeck.Get(Napi::String::New(env, "Crudeoil_Lossess2P"))).As<Napi::Number>();
		facilityStructExternal.Crudeoil_Lossess3P = (wrappedDeck.Get(Napi::String::New(env, "Crudeoil_Lossess3P"))).As<Napi::Number>();

		tm tm1, tm2, tm3;
		sscanf(facilityStructExternal.FDate1P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate2P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate3P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		facilityStructExternal.FacilityDate1P.day = tm1.tm_mday;
		facilityStructExternal.FacilityDate1P.month = tm1.tm_mon;
		facilityStructExternal.FacilityDate1P.year = tm1.tm_year;

		facilityStructExternal.FacilityDate2P.day = tm2.tm_mday;
		facilityStructExternal.FacilityDate2P.month = tm2.tm_mon;
		facilityStructExternal.FacilityDate2P.year = tm2.tm_year;

		facilityStructExternal.FacilityDate3P.day = tm3.tm_mday;
		facilityStructExternal.FacilityDate3P.month = tm3.tm_mon;
		facilityStructExternal.FacilityDate3P.year = tm3.tm_year;

		equpmentCrudeOilLossesData.push_back(facilityStructExternal);
	}

	return equpmentCrudeOilLossesData;
}

vector<FacilityStructExternal> ReportJSON::GetFlaredGasesSheetData(Napi::Array &wrappedDecks,
																   int nCrudeOilLosses, Napi::Env &env)
{

	vector<FacilityStructExternal> equpmentsFlaredGasData;

	double MM = 1000000.0;
	double M = 1000.0;

	for (int i = 0; i < nCrudeOilLosses; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		FacilityStructExternal facilityStructExternal;
		facilityStructExternal.Primary_Facility = (wrappedDeck.Get(Napi::String::New(env, "Primary_Facility"))).As<Napi::String>();
		facilityStructExternal.FDate1P = (wrappedDeck.Get(Napi::String::New(env, "FDate1P"))).As<Napi::String>();
		facilityStructExternal.FDate2P = (wrappedDeck.Get(Napi::String::New(env, "FDate2P"))).As<Napi::String>();
		facilityStructExternal.FDate3P = (wrappedDeck.Get(Napi::String::New(env, "FDate3P"))).As<Napi::String>();
		facilityStructExternal.GasFlared1P = (wrappedDeck.Get(Napi::String::New(env, "GasFlared1P"))).As<Napi::Number>();
		facilityStructExternal.GasFlared2P = (wrappedDeck.Get(Napi::String::New(env, "GasFlared2P"))).As<Napi::Number>();
		facilityStructExternal.GasFlared3P = (wrappedDeck.Get(Napi::String::New(env, "GasFlared3P"))).As<Napi::Number>();

		tm tm1, tm2, tm3;
		sscanf(facilityStructExternal.FDate1P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate2P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate3P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		facilityStructExternal.FacilityDate1P.day = tm1.tm_mday;
		facilityStructExternal.FacilityDate1P.month = tm1.tm_mon;
		facilityStructExternal.FacilityDate1P.year = tm1.tm_year;

		facilityStructExternal.FacilityDate2P.day = tm2.tm_mday;
		facilityStructExternal.FacilityDate2P.month = tm2.tm_mon;
		facilityStructExternal.FacilityDate2P.year = tm2.tm_year;

		facilityStructExternal.FacilityDate3P.day = tm3.tm_mday;
		facilityStructExternal.FacilityDate3P.month = tm3.tm_mon;
		facilityStructExternal.FacilityDate3P.year = tm3.tm_year;

		//=====================Conversion===========================//

		facilityStructExternal.GasFlared1P = facilityStructExternal.GasFlared1P * MM;
		facilityStructExternal.GasFlared2P = facilityStructExternal.GasFlared2P * MM;
		facilityStructExternal.GasFlared3P = facilityStructExternal.GasFlared3P * MM;

		//===================================================//

		equpmentsFlaredGasData.push_back(facilityStructExternal);
	}

	return equpmentsFlaredGasData;
}

vector<FacilityStructExternal> ReportJSON::GetOwnUseSheetData(Napi::Array &wrappedDecks,
															  int nCrudeOilLosses, Napi::Env &env)
{

	vector<FacilityStructExternal> equpmentsOwnUseGasData;

	double MM = 1000000.0;
	double M = 1000.0;

	for (int i = 0; i < nCrudeOilLosses; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		FacilityStructExternal facilityStructExternal;
		facilityStructExternal.Primary_Facility = (wrappedDeck.Get(Napi::String::New(env, "Primary_Facility"))).As<Napi::String>();
		facilityStructExternal.FDate1P = (wrappedDeck.Get(Napi::String::New(env, "FDate1P"))).As<Napi::String>();
		facilityStructExternal.FDate2P = (wrappedDeck.Get(Napi::String::New(env, "FDate2P"))).As<Napi::String>();
		facilityStructExternal.FDate3P = (wrappedDeck.Get(Napi::String::New(env, "FDate3P"))).As<Napi::String>();
		facilityStructExternal.GasOwnUse1P = (wrappedDeck.Get(Napi::String::New(env, "GasOwnUse1P"))).As<Napi::Number>();
		facilityStructExternal.GasOwnUse2P = (wrappedDeck.Get(Napi::String::New(env, "GasOwnUse2P"))).As<Napi::Number>();
		facilityStructExternal.GasOwnUse3P = (wrappedDeck.Get(Napi::String::New(env, "GasOwnUse3P"))).As<Napi::Number>();

		tm tm1, tm2, tm3;
		sscanf(facilityStructExternal.FDate1P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate2P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate3P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		facilityStructExternal.FacilityDate1P.day = tm1.tm_mday;
		facilityStructExternal.FacilityDate1P.month = tm1.tm_mon;
		facilityStructExternal.FacilityDate1P.year = tm1.tm_year;

		facilityStructExternal.FacilityDate2P.day = tm2.tm_mday;
		facilityStructExternal.FacilityDate2P.month = tm2.tm_mon;
		facilityStructExternal.FacilityDate2P.year = tm2.tm_year;

		facilityStructExternal.FacilityDate3P.day = tm3.tm_mday;
		facilityStructExternal.FacilityDate3P.month = tm3.tm_mon;
		facilityStructExternal.FacilityDate3P.year = tm3.tm_year;

		//=====================Conversion===========================//

		facilityStructExternal.GasOwnUse1P = facilityStructExternal.GasOwnUse1P * MM;
		facilityStructExternal.GasOwnUse2P = facilityStructExternal.GasOwnUse2P * MM;
		facilityStructExternal.GasOwnUse3P = facilityStructExternal.GasOwnUse3P * MM;

		//===================================================//

		equpmentsOwnUseGasData.push_back(facilityStructExternal);
	}

	return equpmentsOwnUseGasData;
}

vector<FacilityStructExternal> ReportJSON::GetCrudeEquipmentCapacitiesSheetData(Napi::Array &wrappedDecks,
																				int nEquipmentCapacities, Napi::Env &env)
{

	vector<FacilityStructExternal> equpmentCapacitiesData;

	double MM = 1000000.0;
	double M = 1000.0;

	for (int i = 0; i < nEquipmentCapacities; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		FacilityStructExternal facilityStructExternal;
		facilityStructExternal.Primary_Facility = (wrappedDeck.Get(Napi::String::New(env, "Primary_Facility"))).As<Napi::String>();
		facilityStructExternal.FDate1P = (wrappedDeck.Get(Napi::String::New(env, "FDate1P"))).As<Napi::String>();
		facilityStructExternal.FDate2P = (wrappedDeck.Get(Napi::String::New(env, "FDate2P"))).As<Napi::String>();
		facilityStructExternal.FDate3P = (wrappedDeck.Get(Napi::String::New(env, "FDate3P"))).As<Napi::String>();
		facilityStructExternal.Liquid_Capacity1P = (wrappedDeck.Get(Napi::String::New(env, "Liquid_Capacity1P"))).As<Napi::Number>();
		facilityStructExternal.Liquid_Capacity2P = (wrappedDeck.Get(Napi::String::New(env, "Liquid_Capacity2P"))).As<Napi::Number>();
		facilityStructExternal.Liquid_Capacity3P = (wrappedDeck.Get(Napi::String::New(env, "Liquid_Capacity3P"))).As<Napi::Number>();
		facilityStructExternal.AG_Capacity1P = (wrappedDeck.Get(Napi::String::New(env, "AG_Capacity1P"))).As<Napi::Number>();
		facilityStructExternal.AG_Capacity2P = (wrappedDeck.Get(Napi::String::New(env, "AG_Capacity2P"))).As<Napi::Number>();
		facilityStructExternal.AG_Capacity3P = (wrappedDeck.Get(Napi::String::New(env, "AG_Capacity3P"))).As<Napi::Number>();
		facilityStructExternal.NAG_Capacity1P = (wrappedDeck.Get(Napi::String::New(env, "NAG_Capacity1P"))).As<Napi::Number>();
		facilityStructExternal.NAG_Capacity2P = (wrappedDeck.Get(Napi::String::New(env, "NAG_Capacity2P"))).As<Napi::Number>();
		facilityStructExternal.NAG_Capacity3P = (wrappedDeck.Get(Napi::String::New(env, "NAG_Capacity3P"))).As<Napi::Number>();
		facilityStructExternal.Gas_Capacity1P = (wrappedDeck.Get(Napi::String::New(env, "Gas_Capacity1P"))).As<Napi::Number>();
		facilityStructExternal.Gas_Capacity2P = (wrappedDeck.Get(Napi::String::New(env, "Gas_Capacity2P"))).As<Napi::Number>();
		facilityStructExternal.Gas_Capacity3P = (wrappedDeck.Get(Napi::String::New(env, "Gas_Capacity3P"))).As<Napi::Number>();
		double equityPercentage1P = (wrappedDeck.Get(Napi::String::New(env, "ProductionShareLow"))).As<Napi::Number>();
		double equityPercentage2P = (wrappedDeck.Get(Napi::String::New(env, "ProductionShareBase"))).As<Napi::Number>();
		double equityPercentage3P = (wrappedDeck.Get(Napi::String::New(env, "ProductionShareHigh"))).As<Napi::Number>();

		facilityStructExternal.equityPercentage = equityPercentage2P;
		facilityStructExternal.GasDemand1P =
			facilityStructExternal.Gas_Capacity1P * equityPercentage1P;

		if (facilityStructExternal.Gas_Capacity1P <= 0)
		{
			facilityStructExternal.GasDemand1P =
				(facilityStructExternal.AG_Capacity1P + facilityStructExternal.NAG_Capacity1P) *
				equityPercentage1P;
		}

		facilityStructExternal.GasDemand2P =
			facilityStructExternal.Gas_Capacity2P * equityPercentage2P;
		if (facilityStructExternal.Gas_Capacity2P <= 0)
		{
			facilityStructExternal.GasDemand2P =
				(facilityStructExternal.AG_Capacity2P + facilityStructExternal.NAG_Capacity2P) *
				equityPercentage2P;
		}

		facilityStructExternal.GasDemand3P =
			facilityStructExternal.Gas_Capacity3P * equityPercentage3P;
		if (facilityStructExternal.Gas_Capacity3P <= 0)
		{
			facilityStructExternal.GasDemand3P =
				(facilityStructExternal.AG_Capacity3P + facilityStructExternal.NAG_Capacity3P) *
				equityPercentage3P;
		}

		facilityStructExternal.GasOwnUse1P = 0;
		facilityStructExternal.GasOwnUse2P = 0;
		facilityStructExternal.GasOwnUse3P = 0;

		tm tm1, tm2, tm3;
		sscanf(facilityStructExternal.FDate1P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate2P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(facilityStructExternal.FDate3P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		facilityStructExternal.FacilityDate1P.day = tm1.tm_mday;
		facilityStructExternal.FacilityDate1P.month = tm1.tm_mon;
		facilityStructExternal.FacilityDate1P.year = tm1.tm_year;

		facilityStructExternal.FacilityDate2P.day = tm2.tm_mday;
		facilityStructExternal.FacilityDate2P.month = tm2.tm_mon;
		facilityStructExternal.FacilityDate2P.year = tm2.tm_year;

		facilityStructExternal.FacilityDate3P.day = tm3.tm_mday;
		facilityStructExternal.FacilityDate3P.month = tm3.tm_mon;
		facilityStructExternal.FacilityDate3P.year = tm3.tm_year;

		//=====================Conversion===========================//

		facilityStructExternal.Liquid_Capacity1P = facilityStructExternal.Liquid_Capacity1P * M;
		facilityStructExternal.Gas_Capacity1P = facilityStructExternal.Gas_Capacity1P * MM;
		facilityStructExternal.GasOwnUse1P = facilityStructExternal.GasOwnUse1P * MM;
		facilityStructExternal.GasDemand1P = facilityStructExternal.GasDemand1P * MM;
		facilityStructExternal.Liquid_Capacity2P = facilityStructExternal.Liquid_Capacity2P * M;
		facilityStructExternal.Gas_Capacity2P = facilityStructExternal.Gas_Capacity2P * MM;
		facilityStructExternal.GasOwnUse2P = facilityStructExternal.GasOwnUse2P * MM;
		facilityStructExternal.GasDemand2P = facilityStructExternal.GasDemand2P * MM;
		facilityStructExternal.Liquid_Capacity3P = facilityStructExternal.Liquid_Capacity3P * M;
		facilityStructExternal.Gas_Capacity3P = facilityStructExternal.Gas_Capacity3P * MM;
		facilityStructExternal.GasOwnUse3P = facilityStructExternal.GasOwnUse3P * MM;
		facilityStructExternal.GasDemand3P = facilityStructExternal.GasDemand3P * MM;

		facilityStructExternal.AG_Capacity1P = facilityStructExternal.AG_Capacity1P * MM;
		facilityStructExternal.AG_Capacity2P = facilityStructExternal.AG_Capacity2P * MM;
		facilityStructExternal.AG_Capacity3P = facilityStructExternal.AG_Capacity3P * MM;

		facilityStructExternal.NAG_Capacity1P = facilityStructExternal.NAG_Capacity1P * MM;
		facilityStructExternal.NAG_Capacity2P = facilityStructExternal.NAG_Capacity2P * MM;
		facilityStructExternal.NAG_Capacity3P = facilityStructExternal.NAG_Capacity3P * MM;

		facilityStructExternal.GasFlared1P = facilityStructExternal.GasFlared1P * MM;
		facilityStructExternal.GasFlared2P = facilityStructExternal.GasFlared2P * MM;
		facilityStructExternal.GasFlared3P = facilityStructExternal.GasFlared3P * MM;

		//===================================================//

		equpmentCapacitiesData.push_back(facilityStructExternal);
	}

	return equpmentCapacitiesData;
}

vector<WellReroute> ReportJSON::getWellRerouteDecks(Napi::Array &wrappedDecks,
													int nWellRerouteDecks, Napi::Env &env)
{

	vector<WellReroute> InputDecks;

	for (int i = 0; i < nWellRerouteDecks; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		WellReroute deck;
		deck.Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		deck.Flow_station = (wrappedDeck.Get(Napi::String::New(env, "rerouteDestination"))).As<Napi::String>();
		deck.dcaStrategy = (wrappedDeck.Get(Napi::String::New(env, "dcaStrategy"))).As<Napi::String>();
		inputdeck.ToLower(deck.dcaStrategy);
		deck.declineType = (wrappedDeck.Get(Napi::String::New(env, "declineType"))).As<Napi::String>();
		inputdeck.ToLower(deck.declineType);
		deck.startupRate = (wrappedDeck.Get(Napi::String::New(env, "startupRate"))).As<Napi::Number>();
		deck.startupRatePlateau = (wrappedDeck.Get(Napi::String::New(env, "startupRatePlateau"))).As<Napi::Number>();
		deck.declineRate = (wrappedDeck.Get(Napi::String::New(env, "declineExponent"))).As<Napi::Number>();
		deck.hyperbolicExponent = (wrappedDeck.Get(Napi::String::New(env, "hyperbolicExponent"))).As<Napi::Number>();

		string rerouteDate = (wrappedDeck.Get(Napi::String::New(env, "rerouteDate"))).As<Napi::String>();

		tm tm1;
		sscanf(rerouteDate.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		deck.Date_1P_1C.day = tm1.tm_mday;
		deck.Date_1P_1C.month = tm1.tm_mon;
		deck.Date_1P_1C.year = tm1.tm_year;

		deck.Date_2P_2C.day = tm1.tm_mday;
		deck.Date_2P_2C.month = tm1.tm_mon;
		deck.Date_2P_2C.year = tm1.tm_year;

		deck.Date_3P_3C.day = tm1.tm_mday;
		deck.Date_3P_3C.month = tm1.tm_mon;
		deck.Date_3P_3C.year = tm1.tm_year;

		InputDecks.push_back(deck);
	}

	return InputDecks;
}

vector<ForecastResult> ReportJSON::GetForecastProfiles(Napi::Array &wrappedForecastProfiles,
													   int nWrappedForecastProfiles, Napi::Env &env)
{

	vector<ForecastResult> results;
	int wrappedForecastProfilesLength = nWrappedForecastProfiles;

	for (int i = 0; i < wrappedForecastProfilesLength; i++)
	{
		Napi::Object wrappedForecastProfile = ((Napi::Value)wrappedForecastProfiles[i]).As<Napi::Object>();
		ForecastResult deck;
		deck.GOR = (wrappedForecastProfile.Get(Napi::String::New(env, "GOR"))).As<Napi::Number>();
		deck.CGR = (wrappedForecastProfile.Get(Napi::String::New(env, "CGR"))).As<Napi::Number>();
		deck.BSW = (wrappedForecastProfile.Get(Napi::String::New(env, "BSW"))).As<Napi::Number>();
		deck.WGR = (wrappedForecastProfile.Get(Napi::String::New(env, "WGR"))).As<Napi::Number>();
		deck.Cum_Oil_Prod = (wrappedForecastProfile.Get(Napi::String::New(env, "cumOilProd"))).As<Napi::Number>();
		deck.Cum_Gas_Prod = (wrappedForecastProfile.Get(Napi::String::New(env, "cumGasProd"))).As<Napi::Number>();
		deck.moduleName = (wrappedForecastProfile.Get(Napi::String::New(env, "moduleName"))).As<Napi::String>();
		deck.Oil_rate = (wrappedForecastProfile.Get(Napi::String::New(env, "oilRate"))).As<Napi::Number>();
		deck.Gas_Rate = (wrappedForecastProfile.Get(Napi::String::New(env, "gasRate"))).As<Napi::Number>();
		deck.HyrocarbonStream = (wrappedForecastProfile.Get(Napi::String::New(env, "hydrocarbonStream"))).As<Napi::String>();

		results.push_back(deck);
	}

	return results;
}

void ReportJSON::GetRunParameters(Napi::Object &wrappedRunParameters, Napi::Env &env)
{

	runParameter2.StopDay = (wrappedRunParameters.Get(Napi::String::New(env, "stopDay"))).As<Napi::Number>();
	runParameter2.StopMonth = (wrappedRunParameters.Get(Napi::String::New(env, "stopMonth"))).As<Napi::Number>();
	runParameter2.StopYear = (wrappedRunParameters.Get(Napi::String::New(env, "stopYear"))).As<Napi::Number>();
	// runParameter.TimeFrequency = (wrappedRunParameters.Get(Napi::String::New(env, "timeFrequency"))).As<Napi::String>();
	// runParameter.TargetFluid = (wrappedRunParameters.Get(Napi::String::New(env, "targetFluid"))).As<Napi::String>();
	// runParameter.isDeferred = (wrappedRunParameters.Get(Napi::String::New(env, "isDeferred"))).As<Napi::Number>();
}

string ReportJSON::GetRow(Napi::Object &wrappedDeck, Napi::Env &env, bool &isLastRow)
{

	string row = "";
	string columnDelimeter = "@#$%";
	string rowDelimeter = "@#*$%";

	string uniqueId = (wrappedDeck.Get(Napi::String::New(env, "uniqueId"))).As<Napi::String>();
	string Version_Name = (wrappedDeck.Get(Napi::String::New(env, "forecastVersion"))).As<Napi::String>();
	string Field = (wrappedDeck.Get(Napi::String::New(env, "field"))).As<Napi::String>();
	string Reservoir = (wrappedDeck.Get(Napi::String::New(env, "reservoir"))).As<Napi::String>();
	string Drainage_Point = (wrappedDeck.Get(Napi::String::New(env, "drainagePoint"))).As<Napi::String>();
	string Production_String = (wrappedDeck.Get(Napi::String::New(env, "string"))).As<Napi::String>();
	string TRANCHE = (wrappedDeck.Get(Napi::String::New(env, "developmentTranche"))).As<Napi::String>();
	string Asset_Team = (wrappedDeck.Get(Napi::String::New(env, "asset"))).As<Napi::String>();
	string Flow_station = (wrappedDeck.Get(Napi::String::New(env, "facilities"))).As<Napi::String>();
	string moduleName = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
	double Day = (wrappedDeck.Get(Napi::String::New(env, "day"))).As<Napi::Number>();
	double Month = (wrappedDeck.Get(Napi::String::New(env, "month"))).As<Napi::Number>();
	double Year = (wrappedDeck.Get(Napi::String::New(env, "year"))).As<Napi::Number>();
	double Oil_rate = (wrappedDeck.Get(Napi::String::New(env, "oilRate"))).As<Napi::Number>();
	double Gas_Rate = (wrappedDeck.Get(Napi::String::New(env, "gasRate"))).As<Napi::Number>();
	double Water_Rate = (wrappedDeck.Get(Napi::String::New(env, "waterRate"))).As<Napi::Number>();
	double Cum_Oil_Prod = (wrappedDeck.Get(Napi::String::New(env, "cumOilProd"))).As<Napi::Number>();
	double Cum_Gas_Prod = (wrappedDeck.Get(Napi::String::New(env, "cumGasProd"))).As<Napi::Number>();
	double Cum_Water_Prod = (wrappedDeck.Get(Napi::String::New(env, "cumWaterProd"))).As<Napi::Number>();
	double GOR = (wrappedDeck.Get(Napi::String::New(env, "gOR"))).As<Napi::Number>();
	double BSW = (wrappedDeck.Get(Napi::String::New(env, "bSW"))).As<Napi::Number>();
	double CGR = (wrappedDeck.Get(Napi::String::New(env, "cGR"))).As<Napi::Number>();
	double WGR = (wrappedDeck.Get(Napi::String::New(env, "wGR"))).As<Napi::Number>();
	double CutBack = (wrappedDeck.Get(Napi::String::New(env, "cutBack"))).As<Napi::Number>();
	string HyrocarbonStream = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonStream"))).As<Napi::String>();
	string hydrocarbonType = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonType"))).As<Napi::String>();
	string terminal = (wrappedDeck.Get(Napi::String::New(env, "terminal"))).As<Napi::String>();
	double URo = (wrappedDeck.Get(Napi::String::New(env, "uRo"))).As<Napi::Number>();
	double URg = (wrappedDeck.Get(Napi::String::New(env, "uRg"))).As<Napi::Number>();
	double Gas_Own_Use = (wrappedDeck.Get(Napi::String::New(env, "ownUseGas"))).As<Napi::Number>();
	double Gas_Demand = (wrappedDeck.Get(Napi::String::New(env, "gasDemand"))).As<Napi::Number>();
	double Gas_Flared = (wrappedDeck.Get(Napi::String::New(env, "flareGas"))).As<Napi::Number>();
	double Crude_Oil_Lossess = (wrappedDeck.Get(Napi::String::New(env, "crudeOilLossess"))).As<Napi::Number>();
	double DeclineRate = (wrappedDeck.Get(Napi::String::New(env, "declineRate"))).As<Napi::Number>();
	string projectCode = (wrappedDeck.Get(Napi::String::New(env, "projectCode"))).As<Napi::String>();
	string projectName = (wrappedDeck.Get(Napi::String::New(env, "projectName"))).As<Napi::String>();
	string resourceClass = (wrappedDeck.Get(Napi::String::New(env, "resourceClass"))).As<Napi::String>();

	double liquid = Oil_rate + Water_Rate;
	string lastrow = std::to_string(DeclineRate) + rowDelimeter;
	if (isLastRow == true)
	{
		lastrow = std::to_string(DeclineRate); // no new line
	}

	row = uniqueId + columnDelimeter + Version_Name + columnDelimeter + Field + columnDelimeter + Reservoir + columnDelimeter + Drainage_Point + columnDelimeter + Production_String + columnDelimeter + TRANCHE + columnDelimeter + Asset_Team + columnDelimeter + Flow_station + columnDelimeter + moduleName + columnDelimeter + std::to_string(Day) + columnDelimeter + std::to_string(Month) + columnDelimeter + std::to_string(Year) + columnDelimeter + std::to_string(Oil_rate) + columnDelimeter + std::to_string(Gas_Rate) + columnDelimeter + std::to_string(Water_Rate) + columnDelimeter + std::to_string(liquid) + columnDelimeter + std::to_string(Cum_Oil_Prod) + columnDelimeter + std::to_string(Cum_Gas_Prod) + columnDelimeter + std::to_string(Cum_Water_Prod) + columnDelimeter + std::to_string(GOR) + columnDelimeter + std::to_string(BSW) + columnDelimeter + std::to_string(CGR) + columnDelimeter + std::to_string(WGR) + columnDelimeter + std::to_string(CutBack) + columnDelimeter + HyrocarbonStream + columnDelimeter + hydrocarbonType + columnDelimeter + terminal + columnDelimeter + std::to_string(URo) + columnDelimeter + std::to_string(URg) + columnDelimeter + std::to_string(Gas_Own_Use) + columnDelimeter + std::to_string(Gas_Demand) + columnDelimeter + std::to_string(Gas_Flared) + columnDelimeter + std::to_string(Crude_Oil_Lossess) + columnDelimeter + std::to_string(CutBack) + columnDelimeter + projectCode + columnDelimeter + projectName + columnDelimeter + resourceClass + columnDelimeter + lastrow;

	return row;
}

void ReportJSON::GetForecastFacilityOutput(int &k, int &scenario, vector<Date> &datesNew, Napi::Env &env)
{

	int j = -1;

	Napi::Object decksPerFacility = Napi::Object::New(env);
	Napi::Object decksPerFacilityYearly = Napi::Object::New(env);
	int noOfWells = results[k].size();
	string facilityName = "";

	for (j = 0; j < noOfWells; j++)
	{
		vector<ForecastResult> resultsWellNew;
		string table = "";
		reportJSON2.GetForecastWellMonthOutput(k, j, scenario, table, resultsWellNew);

		string tableYearly = "";
		string moduleName = "";
		reportJSON2.GetForecastWellYearlyOutput(tableYearly, resultsWellNew,
												datesNew, moduleName, facilityName, scenario);

		Napi::Object deckObject = Napi::Object::New(env);
		Napi::Object deckObjectYearly = Napi::Object::New(env);

		if (table != "" && tableYearly != "")
		{
			// std::cout << "Module: " << moduleName << std::endl;
			deckObject.Set(Napi::String::New(env, "resultWells"), Napi::String::New(env, table));
			deckObjectYearly.Set(Napi::String::New(env, "resultWells"), Napi::String::New(env, tableYearly));
			decksPerFacility.Set(Napi::String::New(env, moduleName), deckObject);
			decksPerFacilityYearly.Set(Napi::String::New(env, moduleName), deckObjectYearly);
		}
	}

	Napi::Array keys = decksPerFacility.GetPropertyNames();
	int nKeys = (int)keys.Length();

	if (nKeys > 0)
	{
		// std::cout << "FACILITY: " << facilityName << std::endl;
		FacilitiesObject.Set(Napi::String::New(env, facilityName), decksPerFacility);
		FacilitiesObjectYealy.Set(Napi::String::New(env, facilityName), decksPerFacilityYearly);
	}
}

void ReportJSON::GetForecastOutput(Napi::Env &env, int &scenario, Date &stopDate)
{

	int k = -1;

	FacilitiesObject = Napi::Object::New(env);
	FacilitiesObjectYealy = Napi::Object::New(env);
	bool isByYear = true;
	vector<Date> datesNew = _dataPivoting2.GetListOfYears(results, isByYear);

	// try {

	int FacilitiesSize = results.size();

	for (k = 0; k < FacilitiesSize; k++)
	{
		GetForecastFacilityOutput(k, scenario, datesNew, env);
	}

	/* }
	catch (exception e)
	{
		std::cout << e.what() << std::endl;
	} */
}

void ReportJSON::GetForecastOutputAllFacilities(int &scenario,
												vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies,
												vector<Date> &dateTimes, Napi::Env &env)
{
	int mkdirretval = 0;
	int nDates = dateTimes.size();
	int j = nDates - 1, facilityIndex = 0;
	int wellIndex = 0;
	int nFacilities = facilityWellsIndicies[j].size();
	FacilitiesObject = Napi::Object::New(env);
	for (facilityIndex = 0; facilityIndex < nFacilities; facilityIndex++)
	{
		facilityWellsIndicies[j][facilityIndex].Facility;

		int nWells = facilityWellsIndicies[j][facilityIndex].WellNames.size();
		Napi::Object decksPerFacility = Napi::Object::New(env);
		for (wellIndex = 0; wellIndex < nWells; wellIndex++)
		{
			string table = reportJSON2.GetForecastOutput(scenario, facilityWellsIndicies, dateTimes,
														 facilityIndex, wellIndex,
														 facilityWellsIndicies[j][facilityIndex].WellNames[wellIndex],
														 facilityWellsIndicies[j][facilityIndex].Facility);

			Napi::Object deckObject = Napi::Object::New(env);
			deckObject.Set(Napi::String::New(env, "resultWells"),
						   Napi::String::New(env, table));
			decksPerFacility.Set(Napi::String::New(env,
												   facilityWellsIndicies[j][facilityIndex].WellNames[wellIndex]),
								 deckObject);
		}

		FacilitiesObject.Set(Napi::String::New(env,
											  facilityWellsIndicies[j][facilityIndex].Facility),
							decksPerFacility);
	}
}

void ReportJSON::GetForecastOutput(int &scenario,
								   vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies,
								   vector<Date> &dateTimes, vector<string> Facilities, Napi::Env &env)
{

	int j = 0, ii = 0, k = 0, mkdirretval = 0;
	int nFacilities = 0, nWells = 0;
	// string FolderName = "./Demo Data";
	// string filePath = FolderName + "/Reroute Wells Result/Scenarios";
	FacilitiesObject = Napi::Object::New(env);
	FacilitiesObjectYealy = Napi::Object::New(env);

	int nDates = dateTimes.size();
	for (j = 0; j < nDates; j++)
	{
		nFacilities = facilityWellsIndicies[j].size();
		for (ii = 0; ii < nFacilities; ii++)
		{
			vector<string> wellNames = facilityWellsIndicies[j][ii].WellNames;
			vector<int> WellIndicies = facilityWellsIndicies[j][ii].WellIndicies;
			nWells = WellIndicies.size();
			if (j > 0)
			{

				if (facilityWellsIndicies[j - 1][ii].tables.size() <
					facilityWellsIndicies[j][ii].tables.size())
				{
					facilityWellsIndicies[j][ii].tables = facilityWellsIndicies[j - 1][ii].tables;
					facilityWellsIndicies[j][ii].tables.push_back("");
				}
				else
				{
					facilityWellsIndicies[j][ii].tables = facilityWellsIndicies[j - 1][ii].tables;
				}
			}

			for (k = 0; k < nWells; k++)
			{
				facilityWellsIndicies[j][ii].tables[k] = facilityWellsIndicies[j][ii].tables[k] +
														 reportJSON2.GetRow(results[j][ii][k], scenario, j, dateTimes);
			}
		}
	}

	// string filePath1 = filePath + "/" + "Scenario" + std::to_string(scenario);
	//========================================================================//
	// mkdirretval=mkpath(filePath1,0755);
	//==========================================================================//

	j = nDates - 1;

	Date currentDate;
	nFacilities = facilityWellsIndicies[j].size();
	for (ii = 0; ii < nFacilities; ii++)
	{

		Napi::Object decksPerFacility = Napi::Object::New(env);
		Napi::Object decksPerFacilityYearly = Napi::Object::New(env);
		string facilityName = Facilities[ii];

		vector<string> wellNames = facilityWellsIndicies[j][ii].WellNames;
		vector<int> WellIndicies = facilityWellsIndicies[j][ii].WellIndicies;
		nWells = WellIndicies.size();
		for (k = 0; k < nWells; k++)
		{

			Napi::Object deckObject = Napi::Object::New(env);

			// string filePath3 = filePath2 + "/" + wellNames[k] + ".txt";
			// WriteToAFile(filePath3, facilityWellsIndicies[j][ii].tables[k]);
			deckObject.Set(Napi::String::New(env, "resultWells"),
						   Napi::String::New(env, facilityWellsIndicies[j][ii].tables[k]));
			decksPerFacility.Set(Napi::String::New(env, wellNames[k]), deckObject);
		}
		FacilitiesObject.Set(Napi::String::New(env, facilityName), decksPerFacility);
	}
}

Napi::Array ReportJSON::getDeclineParameters(vector<InputDeckStruct> &InputDecks, Napi::Env &env)
{

	int nWellDecks = InputDecks.size();

	Napi::Array declineParametersList = Napi::Array::New(env);

	for (int i = 0; i < nWellDecks; i++)
	{
		InputDeckStruct InputDeckRow = InputDecks[i];

		inputdeck.CalculateDeclineParameters(InputDeckRow);

		Napi::Object declineParameters = Napi::Object::New(env);
		declineParameters.Set(Napi::String::New(env, "forecastVersion"), Napi::String::New(env, InputDeckRow.Version_Name));
		declineParameters.Set(Napi::String::New(env, "asset"), Napi::String::New(env, InputDeckRow.Asset_Team));
		declineParameters.Set(Napi::String::New(env, "field"), Napi::String::New(env, InputDeckRow.Field));
		declineParameters.Set(Napi::String::New(env, "reservoir"), Napi::String::New(env, InputDeckRow.Reservoir));
		declineParameters.Set(Napi::String::New(env, "drainagePoint"), Napi::String::New(env, InputDeckRow.Drainage_Point));
		declineParameters.Set(Napi::String::New(env, "string"), Napi::String::New(env, InputDeckRow.Production_String));
		declineParameters.Set(Napi::String::New(env, "module"), Napi::String::New(env, InputDeckRow.Module));
		declineParameters.Set(Napi::String::New(env, "hydrocarbonStream"), Napi::String::New(env, InputDeckRow.Hydrocarbon_Stream));
		declineParameters.Set(Napi::String::New(env, "hydrocarbonType"), Napi::String::New(env, InputDeckRow.hydrocarbonType));

		declineParameters.Set(Napi::String::New(env, "initOilGasRate1P1C"), Napi::Number::New(env, InputDeckRow.Init_Liquid_Gas_Rate_1P_1C));
		declineParameters.Set(Napi::String::New(env, "initOilGasRate2P2C"), Napi::Number::New(env, InputDeckRow.Init_Liquid_Gas_Rate_2P_2C));
		declineParameters.Set(Napi::String::New(env, "initOilGasRate3P3C"), Napi::Number::New(env, InputDeckRow.Init_Liquid_Gas_Rate_3P_3C));

		declineParameters.Set(Napi::String::New(env, "rateofChangeRate1P1C"), Napi::Number::New(env, InputDeckRow.Rate_of_Change_Rate_1P_1C));
		declineParameters.Set(Napi::String::New(env, "rateofChangeRate2P2C"), Napi::Number::New(env, InputDeckRow.Rate_of_Change_Rate_2P_2C));
		declineParameters.Set(Napi::String::New(env, "rateofChangeRate3P3C"), Napi::Number::New(env, InputDeckRow.Rate_of_Change_Rate_3P_3C));

		declineParameters.Set(Napi::String::New(env, "rateOfChangeGORCGR1P1C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_GOR_CGR_1P1C));
		declineParameters.Set(Napi::String::New(env, "rateOfChangeGORCGR2P2C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_GOR_CGR_2P2C));
		declineParameters.Set(Napi::String::New(env, "rateOfChangeGORCGR3P3C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_GOR_CGR_3P3C));

		declineParameters.Set(Napi::String::New(env, "rateOfChangeBSWWGR1P1C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_BSW_WGR_1P1C));
		declineParameters.Set(Napi::String::New(env, "rateOfChangeBSWWGR2P2C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_BSW_WGR_2P2C));
		declineParameters.Set(Napi::String::New(env, "rateOfChangeBSWWGR3P3C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_BSW_WGR_3P3C));

		double zro = 0.0;
		declineParameters.Set(Napi::String::New(env, "declineExponent1P1C"), Napi::Number::New(env, zro));
		declineParameters.Set(Napi::String::New(env, "declineExponent2P2C"), Napi::Number::New(env, zro));
		declineParameters.Set(Napi::String::New(env, "declineExponent3P3C"), Napi::Number::New(env, zro));

		string declineMethod = "exponential";
		if (InputDeckRow.DeclineMethod == 1)
		{
			declineMethod = "exponential";
		}
		else if (InputDeckRow.DeclineMethod == 2)
		{
			declineMethod = "hyperbolic";
		}
		else
		{
			declineMethod = "harmonic";
		}

		declineParameters.Set(Napi::String::New(env, "declineMethod"), Napi::String::New(env, declineMethod));

		declineParametersList.Set(Napi::Number::New(env, i), declineParameters);
	}

	return declineParametersList;
}

Napi::Array ReportJSON::getWellPriorizations(Napi::Array &wrappedDecks, Napi::Env &env)
{

	vector<InputDeckStruct> InputDecks;

	Napi::Array WellProductionPriorizations = Napi::Array::New(env);
	int wrappedDecksLength = nValidatedDecks2;
	for (int i = 0; i < wrappedDecksLength; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();
		string Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		string optimizationWeight = "Normal";

		Napi::Object WellProductionPriorization = Napi::Object::New(env);
		WellProductionPriorization.Set(Napi::String::New(env, "module"), Napi::String::New(env, Module));
		WellProductionPriorization.Set(Napi::String::New(env, "optimizationWeight"), Napi::String::New(env, optimizationWeight));
		WellProductionPriorizations.Set(Napi::Number::New(env, i), WellProductionPriorization);
	}

	return WellProductionPriorizations;
}

Napi::Array ReportJSON::validateInputDecks(Napi::Array &wrappedDecks, Napi::Env &env,
										   bool &isDefault, int nWrappedDecks)
{

	vector<InputDeckStruct> InputDecks;

	double MM = 1000000.0;
	double M = 1000.0;

	int nSize = nWrappedDecks;
	// std::cout << "Size " << nSize << std::endl;

	for (int i = 0; i < nSize; i++)
	{
		// std::cout << "Seen 1111 " << std::endl;
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();
		InputDeckStruct deck;
		deck.Version_Name = (wrappedDeck.Get(Napi::String::New(env, "forecastVersion"))).As<Napi::String>();
		deck.Asset_Team = (wrappedDeck.Get(Napi::String::New(env, "asset"))).As<Napi::String>();
		deck.Field = (wrappedDeck.Get(Napi::String::New(env, "field"))).As<Napi::String>();
		deck.Reservoir = (wrappedDeck.Get(Napi::String::New(env, "reservoir"))).As<Napi::String>();
		deck.Drainage_Point = (wrappedDeck.Get(Napi::String::New(env, "drainagePoint"))).As<Napi::String>();
		deck.Production_String = (wrappedDeck.Get(Napi::String::New(env, "string"))).As<Napi::String>();
		deck.Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		deck.PEEP_Project = (wrappedDeck.Get(Napi::String::New(env, "projectCode"))).As<Napi::String>();
		deck.Activity_Entity = (wrappedDeck.Get(Napi::String::New(env, "projectName"))).As<Napi::String>();
		deck.Flow_station = (wrappedDeck.Get(Napi::String::New(env, "facilities"))).As<Napi::String>();
		deck.Hydrocarbon_Stream = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonStream"))).As<Napi::String>();
		inputdeck.ToLower(deck.Hydrocarbon_Stream);
		deck.hydrocarbonType = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonType"))).As<Napi::String>();
		inputdeck.ToLower(deck.hydrocarbonType);
		deck.terminal = (wrappedDeck.Get(Napi::String::New(env, "terminal"))).As<Napi::String>();
		inputdeck.ToLower(deck.terminal);

		deck.Resource_Class = (wrappedDeck.Get(Napi::String::New(env, "resourceClass"))).As<Napi::String>();
		// deck.Change_Category = (wrappedDeck.Get(Napi::String::New(env, "changeCategory"))).As<Napi::String>();
		// deck.Technique_1P = (wrappedDeck.Get(Napi::String::New(env, "technique1P"))).As<Napi::String>();
		deck.URo_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "oilUR1P1C"))).As<Napi::Number>();
		// deck.URo_Low = (wrappedDeck.Get(Napi::String::New(env, "URoLow"))).As<Napi::Number>();
		deck.URo_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "oilUR2P2C"))).As<Napi::Number>();
		deck.URo_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "oilUR3P3C"))).As<Napi::Number>();
		deck.Np = (wrappedDeck.Get(Napi::String::New(env, "Np"))).As<Napi::Number>();
		deck.URg_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "gasUR1P1C"))).As<Napi::Number>();
		// deck.URg_Low = (wrappedDeck.Get(Napi::String::New(env, "URgLow"))).As<Napi::Number>();
		deck.URg_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "gasUR2P2C"))).As<Napi::Number>();
		deck.URg_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "gasUR3P3C"))).As<Napi::Number>();
		deck.Gp = (wrappedDeck.Get(Napi::String::New(env, "Gp"))).As<Napi::Number>();

		/* 		if(deck.URg_1P_1C > myZero){
					deck.URg_1P_1C = deck.URg_1P_1C * 1000.0;
				}

				if(deck.URg_Low > myZero){
					deck.URg_Low = deck.URg_Low * 1000.0;
				}

				if(deck.URg_2P_2C > myZero){
					deck.URg_2P_2C = deck.URg_2P_2C * 1000.0;
				}

				if(deck.URg_3P_3C > myZero){
					deck.URg_3P_3C = deck.URg_3P_3C * 1000.0;
				}

				if(deck.Gp > myZero){
					deck.Gp = deck.Gp * 1000.0;
				} */

		if (deck.Hydrocarbon_Stream == "oil")
		{
			deck.Init_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate1P1C"))).As<Napi::Number>();
			// deck.Init_Oil_Gas_Rate_Low = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRateLow"))).As<Napi::Number>();
			deck.Init_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate2P2C"))).As<Napi::Number>();
			deck.Init_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate3P3C"))).As<Napi::Number>();
			deck.Aband_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate1P1C"))).As<Napi::Number>();
			deck.Aband_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate2P2C"))).As<Napi::Number>();
			deck.Aband_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate3P3C"))).As<Napi::Number>();
		}
		else
		{
			deck.Init_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate1P1C"))).As<Napi::Number>();
			// deck.Init_Oil_Gas_Rate_Low = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRateLow"))).As<Napi::Number>();
			deck.Init_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate2P2C"))).As<Napi::Number>();
			deck.Init_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate3P3C"))).As<Napi::Number>();
			deck.Aband_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate1P1C"))).As<Napi::Number>();
			deck.Aband_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate2P2C"))).As<Napi::Number>();
			deck.Aband_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate3P3C"))).As<Napi::Number>();
		}

		deck.Init_BSW_WGR = (wrappedDeck.Get(Napi::String::New(env, "initBSWWGR"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR1P1C"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR2P2C"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR3P3C"))).As<Napi::Number>();
		deck.Init_GOR_CGR = (wrappedDeck.Get(Napi::String::New(env, "initGORCGR"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR1P1C"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR2P2C"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR3P3C"))).As<Napi::Number>();

		if (deck.Hydrocarbon_Stream == "gas")
		{
			deck.URg_1P_1C = deck.URg_1P_1C * M;
			deck.URg_2P_2C = deck.URg_2P_2C * M;
			deck.URg_3P_3C = deck.URg_3P_3C * M;
			deck.Gp = deck.Gp * M;

			deck.Init_Liquid_Gas_Rate_1P_1C = deck.Init_Liquid_Gas_Rate_1P_1C * MM;
			deck.Init_Liquid_Gas_Rate_2P_2C = deck.Init_Liquid_Gas_Rate_2P_2C * MM;
			deck.Init_Liquid_Gas_Rate_3P_3C = deck.Init_Liquid_Gas_Rate_3P_3C * MM;
			deck.Aband_Liquid_Gas_Rate_1P_1C = deck.Aband_Liquid_Gas_Rate_1P_1C * MM;
			deck.Aband_Liquid_Gas_Rate_2P_2C = deck.Aband_Liquid_Gas_Rate_2P_2C * MM;
			deck.Aband_Liquid_Gas_Rate_3P_3C = deck.Aband_Liquid_Gas_Rate_3P_3C * MM;

			/* deck.Init_BSW_WGR = deck.Init_BSW_WGR * MM;
			deck.Aband_BSW_WGR_1P_1C = deck.Aband_BSW_WGR_1P_1C * MM;

			deck.Aband_BSW_WGR_1P_1C = deck.Aband_BSW_WGR_1P_1C * MM;
			deck.Aband_BSW_WGR_2P_2C = deck.Aband_BSW_WGR_2P_2C * MM;
			deck.Aband_BSW_WGR_3P_3C = deck.Aband_BSW_WGR_3P_3C * MM;

			deck.Aband_GOR_CGR_1P_1C = deck.Aband_GOR_CGR_1P_1C * MM;
			deck.Aband_GOR_CGR_2P_2C = deck.Aband_GOR_CGR_2P_2C * MM;
			deck.Aband_GOR_CGR_3P_3C = deck.Aband_GOR_CGR_3P_3C * MM;  */
		}
		// deck.lift_Gas_Rate = (wrappedDeck.Get(Napi::String::New(env, "liftGasRate"))).As<Napi::Number>();
		deck.Plateau_Oil_Gas = (wrappedDeck.Get(Napi::String::New(env, "plateauPeriod"))).As<Napi::Number>();

		// deck.In_year_Booking = (wrappedDeck.Get(Napi::String::New(env, "inYearBooking"))).As<Napi::String>();
		// deck.LE_LV = (wrappedDeck.Get(Napi::String::New(env, "LELV"))).As<Napi::String>();
		// deck.PRCS = (wrappedDeck.Get(Napi::String::New(env, "PRCS"))).As<Napi::String>();
		deck.On_stream_Date_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate1P1C"))).As<Napi::String>();
		deck.On_stream_Date_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate2P2C"))).As<Napi::String>();
		deck.On_stream_Date_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate3P3C"))).As<Napi::String>();
		deck.Remarks = (wrappedDeck.Get(Napi::String::New(env, "remarks"))).As<Napi::String>();
		deck.TRANCHE = (wrappedDeck.Get(Napi::String::New(env, "developmentTranche"))).As<Napi::String>();

		tm tm1, tm2, tm3;
		sscanf(deck.On_stream_Date_1P_1C.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(deck.On_stream_Date_2P_2C.c_str(), "%d/%d/%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year);
		sscanf(deck.On_stream_Date_3P_3C.c_str(), "%d/%d/%d", &tm3.tm_mday, &tm3.tm_mon, &tm3.tm_year);

		deck.Date_1P_1C.day = tm1.tm_mday;
		deck.Date_1P_1C.month = tm1.tm_mon;
		deck.Date_1P_1C.year = tm1.tm_year;
		deck.Date_2P_2C.day = tm1.tm_mday;
		deck.Date_2P_2C.month = tm1.tm_mon;
		deck.Date_2P_2C.year = tm1.tm_year;
		deck.Date_3P_3C.day = tm1.tm_mday;
		deck.Date_3P_3C.month = tm1.tm_mon;
		deck.Date_3P_3C.year = tm1.tm_year;

		deck.day_1P_1C = deck.Date_1P_1C.day;
		deck.day_2P_2C = deck.Date_2P_2C.day;
		deck.day_3P_3C = deck.Date_3P_3C.day;

		deck.month_1P_1C = deck.Date_1P_1C.month;
		deck.month_2P_2C = deck.Date_2P_2C.month;
		deck.month_3P_3C = deck.Date_3P_3C.month;

		deck.year_1P_1C = deck.Date_1P_1C.year;
		deck.year_2P_2C = deck.Date_2P_2C.year;
		deck.year_3P_3C = deck.Date_3P_3C.year;

		if (isDefault == true)
		{
			deck.DeclineMethod = 1;
		}
		else
		{
			deck.DeclineMethod = 1;
			string declineMethod = (wrappedDeck.Get(Napi::String::New(env, "declineMethod"))).As<Napi::String>();

			if (declineMethod == "exponential")
			{
				deck.DeclineMethod = 1;
			}
			else if (declineMethod == "hyperbolic")
			{
				deck.DeclineMethod = 2;
			}
			else
			{
				deck.DeclineMethod = 3;
			}
		}

		inputdeck.ValidateDeck(deck);

		if (deck.Description != "no error")
		{
			InputDecks.push_back(deck);
		}

		/* std::cout << deck.Module << std::endl;
		std::cout << "Init_Oil_Gas_Rate_1P_1C: " << deck.Init_Oil_Gas_Rate_1P_1C << std::endl;
		std::cout << "Init_GOR_CGR: " << deck.Init_GOR_CGR << std::endl;
		std::cout << "Init_BSW_WGR: " << deck.Init_BSW_WGR << std::endl;
		std::cout << "Aband_GOR_CGR_1P_1C: " << deck.Aband_GOR_CGR_1P_1C << std::endl;
		std::cout << "Aband_BSW_WGR_1P_1C: " << deck.Aband_BSW_WGR_1P_1C << std::endl;
		std::cout << "Rate_of_Change_Rate_1P_1C: " << deck.Rate_of_Change_Rate_1P_1C << std::endl;
		std::cout << "Rate_Of_Rate_GOR_CGR_1P1C: " << deck.Rate_Of_Rate_GOR_CGR_1P1C << std::endl;
		std::cout << "Rate_Of_Rate_BSW_WGR_1P1C: " << deck.Rate_Of_Rate_BSW_WGR_1P1C << std::endl << std::endl;  */
	}

	// std::cout << "Seen 2222 " << std::endl;
	int nWellDecks = InputDecks.size();

	Napi::Array wellDeckList = Napi::Array::New(env);

	for (int i = 0; i < nWellDecks; i++)
	{
		InputDeckStruct InputDeckRow = InputDecks[i];

		Napi::Object wellDeck = Napi::Object::New(env);

		wellDeck.Set(Napi::String::New(env, "forecastVersion"), Napi::String::New(env, InputDeckRow.Version_Name));
		wellDeck.Set(Napi::String::New(env, "asset"), Napi::String::New(env, InputDeckRow.Asset_Team));
		wellDeck.Set(Napi::String::New(env, "field"), Napi::String::New(env, InputDeckRow.Field));
		wellDeck.Set(Napi::String::New(env, "reservoir"), Napi::String::New(env, InputDeckRow.Reservoir));
		wellDeck.Set(Napi::String::New(env, "drainagePoint"), Napi::String::New(env, InputDeckRow.Drainage_Point));
		wellDeck.Set(Napi::String::New(env, "string"), Napi::String::New(env, InputDeckRow.Production_String));
		wellDeck.Set(Napi::String::New(env, "module"), Napi::String::New(env, InputDeckRow.Module));
		wellDeck.Set(Napi::String::New(env, "projectCode"), Napi::String::New(env, InputDeckRow.PEEP_Project));
		wellDeck.Set(Napi::String::New(env, "projectName"), Napi::String::New(env, InputDeckRow.Activity_Entity));
		wellDeck.Set(Napi::String::New(env, "facilities"), Napi::String::New(env, InputDeckRow.Flow_station));
		wellDeck.Set(Napi::String::New(env, "hydrocarbonStream"), Napi::String::New(env, InputDeckRow.Hydrocarbon_Stream));
		wellDeck.Set(Napi::String::New(env, "hydrocarbonType"), Napi::String::New(env, InputDeckRow.hydrocarbonType));
		wellDeck.Set(Napi::String::New(env, "terminal"), Napi::String::New(env, InputDeckRow.terminal));

		//------------Calculated Variable-------------------------------------------
		wellDeck.Set(Napi::String::New(env, "description"), Napi::String::New(env, InputDeckRow.Description));

		//--------------------------------------------------------------

		wellDeckList.Set(Napi::Number::New(env, i), wellDeck);
	}

	return wellDeckList;
}

Napi::Array ReportJSON::getUpdatedInputDecks(Napi::Array &wrappedDecks, Napi::Env &env,
											 bool &isDefault, int nWrappedDecks)
{

	vector<InputDeckStruct> InputDecks;

	// double MM = 1000000.0;
	// double M = 1000.0;

	int nSize = nWrappedDecks;

	// std::cout << "Size " << nSize << std::endl;

	for (int i = 0; i < nSize; i++)
	{
		// std::cout << "Seen 1111 " << std::endl;
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();
		InputDeckStruct deck;
		deck.Version_Name = (wrappedDeck.Get(Napi::String::New(env, "forecastVersion"))).As<Napi::String>();
		/* std::cout << "forecastVersion " << deck.Version_Name << std::endl; */
		deck.Asset_Team = (wrappedDeck.Get(Napi::String::New(env, "asset"))).As<Napi::String>();
		/* std::cout << "Asset_Team " << deck.Asset_Team << std::endl; */
		deck.Field = (wrappedDeck.Get(Napi::String::New(env, "field"))).As<Napi::String>();
		/* std::cout << "Field " << deck.Field << std::endl; */
		deck.Reservoir = (wrappedDeck.Get(Napi::String::New(env, "reservoir"))).As<Napi::String>();
		/* std::cout << "Reservoir " << deck.Reservoir << std::endl; */
		deck.Drainage_Point = (wrappedDeck.Get(Napi::String::New(env, "drainagePoint"))).As<Napi::String>();
		/* std::cout << "Drainage_Point " << deck.Drainage_Point << std::endl; */
		deck.Production_String = (wrappedDeck.Get(Napi::String::New(env, "string"))).As<Napi::String>();
		/* std::cout << "Production_String " << deck.Production_String << std::endl; */
		deck.Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		/* std::cout << "Module " << deck.Module << std::endl; */
		deck.PEEP_Project = (wrappedDeck.Get(Napi::String::New(env, "projectCode"))).As<Napi::String>();
		/* std::cout << "PEEP_Project " << deck.PEEP_Project << std::endl; */
		deck.Activity_Entity = (wrappedDeck.Get(Napi::String::New(env, "projectName"))).As<Napi::String>();
		/* std::cout << "Activity_Entity " << deck.Activity_Entity << std::endl; */
		deck.Flow_station = (wrappedDeck.Get(Napi::String::New(env, "facilities"))).As<Napi::String>();
		/* std::cout << "Flow_station " << deck.Flow_station << std::endl; */
		deck.Hydrocarbon_Stream = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonStream"))).As<Napi::String>();
		/* std::cout << "Hydrocarbon_Stream " << deck.Hydrocarbon_Stream << std::endl; */
		inputdeck.ToLower(deck.Hydrocarbon_Stream);
		deck.hydrocarbonType = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonType"))).As<Napi::String>();
		/* std::cout << "hydrocarbonType " << deck.hydrocarbonType << std::endl; */
		inputdeck.ToLower(deck.hydrocarbonType);
		deck.terminal = (wrappedDeck.Get(Napi::String::New(env, "terminal"))).As<Napi::String>();
		/* std::cout << "terminal " << deck.terminal << std::endl; */
		inputdeck.ToLower(deck.terminal);

		deck.Resource_Class = (wrappedDeck.Get(Napi::String::New(env, "resourceClass"))).As<Napi::String>();
		/* std::cout << "Resource_Class " << deck.Resource_Class << std::endl; */
		// deck.Change_Category = (wrappedDeck.Get(Napi::String::New(env, "changeCategory"))).As<Napi::String>();
		// deck.Technique_1P = (wrappedDeck.Get(Napi::String::New(env, "technique1P"))).As<Napi::String>();
		deck.URo_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "oilUR1P1C"))).As<Napi::Number>();
		/* std::cout << "URo_1P_1C " << deck.URo_1P_1C << std::endl; */
		// deck.URo_Low = (wrappedDeck.Get(Napi::String::New(env, "URoLow"))).As<Napi::Number>();
		deck.URo_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "oilUR2P2C"))).As<Napi::Number>();
		/* std::cout << "URo_2P_2C " << deck.URo_2P_2C << std::endl; */
		deck.URo_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "oilUR3P3C"))).As<Napi::Number>();
		/* std::cout << "URo_3P_3C " << deck.URo_3P_3C << std::endl; */
		deck.Np = (wrappedDeck.Get(Napi::String::New(env, "Np"))).As<Napi::Number>();
		/* std::cout << "Np " << deck.Np << std::endl; */
		deck.URg_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "gasUR1P1C"))).As<Napi::Number>();
		/* std::cout << "URg_1P_1C " << deck.URg_1P_1C << std::endl; */
		// deck.URg_Low = (wrappedDeck.Get(Napi::String::New(env, "URgLow"))).As<Napi::Number>();
		deck.URg_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "gasUR2P2C"))).As<Napi::Number>();
		/* std::cout << "URg_2P_2C " << deck.URg_2P_2C << std::endl; */
		deck.URg_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "gasUR3P3C"))).As<Napi::Number>();
		/* std::cout << "URg_3P_3C " << deck.URg_3P_3C << std::endl; */
		deck.Gp = (wrappedDeck.Get(Napi::String::New(env, "Gp"))).As<Napi::Number>();
		/* std::cout << "Gp " << deck.Gp << std::endl; */

		/* 		if(deck.URg_1P_1C > myZero){
					deck.URg_1P_1C = deck.URg_1P_1C * 1000.0;
				}

				if(deck.URg_Low > myZero){
					deck.URg_Low = deck.URg_Low * 1000.0;
				}

				if(deck.URg_2P_2C > myZero){
					deck.URg_2P_2C = deck.URg_2P_2C * 1000.0;
				}

				if(deck.URg_3P_3C > myZero){
					deck.URg_3P_3C = deck.URg_3P_3C * 1000.0;
				}

				if(deck.Gp > myZero){
					deck.Gp = deck.Gp * 1000.0;
				} */

		if (deck.Hydrocarbon_Stream == "oil")
		{
			deck.Init_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate1P1C"))).As<Napi::Number>();
			/* std::cout << "Init_Oil_Gas_Rate_1P_1C " << deck.Init_Oil_Gas_Rate_1P_1C << std::endl; */
			deck.Init_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate2P2C"))).As<Napi::Number>();
			/* std::cout << "Init_Oil_Gas_Rate_2P_2C " << deck.Init_Oil_Gas_Rate_2P_2C << std::endl; */
			deck.Init_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate3P3C"))).As<Napi::Number>();
			/* std::cout << "Init_Oil_Gas_Rate_3P_3C " << deck.Init_Oil_Gas_Rate_3P_3C << std::endl; */
			deck.Aband_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate1P1C"))).As<Napi::Number>();
			/* std::cout << "Aband_Oil_Gas_Rate_1P_1C " << deck.Aband_Oil_Gas_Rate_1P_1C << std::endl; */
			deck.Aband_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate2P2C"))).As<Napi::Number>();
			/* std::cout << "Aband_Oil_Gas_Rate_2P_2C " << deck.Aband_Oil_Gas_Rate_2P_2C << std::endl; */
			deck.Aband_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate3P3C"))).As<Napi::Number>();
			/* std::cout << "Aband_Oil_Gas_Rate_3P_3C " << deck.Aband_Oil_Gas_Rate_3P_3C << std::endl; */
		}
		else
		{
			deck.Init_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate1P1C"))).As<Napi::Number>();
			/* std::cout << "Init_Oil_Gas_Rate_1P_1C " << deck.Init_Oil_Gas_Rate_1P_1C << std::endl; */
			deck.Init_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate2P2C"))).As<Napi::Number>();
			/* std::cout << "Init_Oil_Gas_Rate_2P_2C " << deck.Init_Oil_Gas_Rate_2P_2C << std::endl; */
			deck.Init_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate3P3C"))).As<Napi::Number>();
			/* std::cout << "Init_Oil_Gas_Rate_3P_3C " << deck.Init_Oil_Gas_Rate_3P_3C << std::endl; */
			deck.Aband_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate1P1C"))).As<Napi::Number>();
			/* std::cout << "Aband_Oil_Gas_Rate_1P_1C " << deck.Aband_Oil_Gas_Rate_1P_1C << std::endl; */
			deck.Aband_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate2P2C"))).As<Napi::Number>();
			/* std::cout << "Aband_Oil_Gas_Rate_2P_2C " << deck.Aband_Oil_Gas_Rate_2P_2C << std::endl; */
			deck.Aband_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate3P3C"))).As<Napi::Number>();
			/* std::cout << "Aband_Oil_Gas_Rate_3P_3C " << deck.Aband_Oil_Gas_Rate_3P_3C << std::endl; */
		}

		deck.Init_BSW_WGR = (wrappedDeck.Get(Napi::String::New(env, "initBSWWGR"))).As<Napi::Number>();
		/* std::cout << "Init_BSW_WGR " << deck.Init_BSW_WGR << std::endl; */
		deck.Aband_BSW_WGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR1P1C"))).As<Napi::Number>();
		/* std::cout << "Aband_BSW_WGR_1P_1C " << deck.Aband_BSW_WGR_1P_1C << std::endl; */
		deck.Aband_BSW_WGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR2P2C"))).As<Napi::Number>();
		/* std::cout << "Aband_BSW_WGR_2P_2C " << deck.Aband_BSW_WGR_2P_2C << std::endl; */
		deck.Aband_BSW_WGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR3P3C"))).As<Napi::Number>();
		/* std::cout << "Aband_BSW_WGR_3P_3C " << deck.Aband_BSW_WGR_3P_3C << std::endl; */
		deck.Init_GOR_CGR = (wrappedDeck.Get(Napi::String::New(env, "initGORCGR"))).As<Napi::Number>();
		/* std::cout << "Init_GOR_CGR " << deck.Init_GOR_CGR << std::endl; */
		deck.Aband_GOR_CGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR1P1C"))).As<Napi::Number>();
		/* std::cout << "Aband_GOR_CGR_1P_1C " << deck.Aband_GOR_CGR_1P_1C << std::endl; */
		deck.Aband_GOR_CGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR2P2C"))).As<Napi::Number>();
		/* std::cout << "Aband_GOR_CGR_2P_2C " << deck.Aband_GOR_CGR_2P_2C << std::endl; */
		deck.Aband_GOR_CGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR3P3C"))).As<Napi::Number>();
		/* std::cout << "Aband_GOR_CGR_3P_3C " << deck.Aband_GOR_CGR_3P_3C << std::endl; */

		if (deck.Hydrocarbon_Stream == "gas")
		{
			deck.URg_1P_1C = deck.URg_1P_1C;
			deck.URg_2P_2C = deck.URg_2P_2C;
			deck.URg_3P_3C = deck.URg_3P_3C;
			deck.Gp = deck.Gp;

			deck.Init_Liquid_Gas_Rate_1P_1C = deck.Init_Liquid_Gas_Rate_1P_1C;
			deck.Init_Liquid_Gas_Rate_2P_2C = deck.Init_Liquid_Gas_Rate_2P_2C;
			deck.Init_Liquid_Gas_Rate_3P_3C = deck.Init_Liquid_Gas_Rate_3P_3C;
			deck.Aband_Liquid_Gas_Rate_1P_1C = deck.Aband_Liquid_Gas_Rate_1P_1C;
			deck.Aband_Liquid_Gas_Rate_2P_2C = deck.Aband_Liquid_Gas_Rate_2P_2C;
			deck.Aband_Liquid_Gas_Rate_3P_3C = deck.Aband_Liquid_Gas_Rate_3P_3C;

			/* deck.Init_BSW_WGR = deck.Init_BSW_WGR * MM;
			deck.Aband_BSW_WGR_1P_1C = deck.Aband_BSW_WGR_1P_1C * MM;

			deck.Aband_BSW_WGR_1P_1C = deck.Aband_BSW_WGR_1P_1C * MM;
			deck.Aband_BSW_WGR_2P_2C = deck.Aband_BSW_WGR_2P_2C * MM;
			deck.Aband_BSW_WGR_3P_3C = deck.Aband_BSW_WGR_3P_3C * MM;

			deck.Aband_GOR_CGR_1P_1C = deck.Aband_GOR_CGR_1P_1C * MM;
			deck.Aband_GOR_CGR_2P_2C = deck.Aband_GOR_CGR_2P_2C * MM;
			deck.Aband_GOR_CGR_3P_3C = deck.Aband_GOR_CGR_3P_3C * MM;  */
		}
		// deck.lift_Gas_Rate = (wrappedDeck.Get(Napi::String::New(env, "liftGasRate"))).As<Napi::Number>();
		deck.Plateau_Oil_Gas = (wrappedDeck.Get(Napi::String::New(env, "plateauPeriod"))).As<Napi::Number>();
		/* std::cout << "Plateau_Oil_Gas " << deck.Plateau_Oil_Gas << std::endl; */
		// deck.In_year_Booking = (wrappedDeck.Get(Napi::String::New(env, "inYearBooking"))).As<Napi::String>();
		// deck.LE_LV = (wrappedDeck.Get(Napi::String::New(env, "LELV"))).As<Napi::String>();
		// deck.PRCS = (wrappedDeck.Get(Napi::String::New(env, "PRCS"))).As<Napi::String>();
		deck.On_stream_Date_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate1P1C"))).As<Napi::String>();
		/* std::cout << "On_stream_Date_1P_1C " << deck.On_stream_Date_1P_1C << std::endl; */
		deck.On_stream_Date_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate2P2C"))).As<Napi::String>();
		/* std::cout << "On_stream_Date_2P_2C " << deck.On_stream_Date_2P_2C << std::endl; */
		deck.On_stream_Date_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate3P3C"))).As<Napi::String>();
		/* std::cout << "On_stream_Date_3P_3C " << deck.On_stream_Date_3P_3C << std::endl; */
		deck.Remarks = (wrappedDeck.Get(Napi::String::New(env, "remarks"))).As<Napi::String>();
		/* std::cout << "Remarks " << deck.Remarks << std::endl; */
		deck.TRANCHE = (wrappedDeck.Get(Napi::String::New(env, "developmentTranche"))).As<Napi::String>();
		/* std::cout << "TRANCHE " << deck.TRANCHE << std::endl; */

		tm tm1, tm2, tm3;
		sscanf(deck.On_stream_Date_1P_1C.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(deck.On_stream_Date_2P_2C.c_str(), "%d/%d/%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year);
		sscanf(deck.On_stream_Date_3P_3C.c_str(), "%d/%d/%d", &tm3.tm_mday, &tm3.tm_mon, &tm3.tm_year);

		deck.Date_1P_1C.day = tm1.tm_mday;
		deck.Date_1P_1C.month = tm1.tm_mon;
		deck.Date_1P_1C.year = tm1.tm_year;
		deck.Date_2P_2C.day = tm1.tm_mday;
		deck.Date_2P_2C.month = tm1.tm_mon;
		deck.Date_2P_2C.year = tm1.tm_year;
		deck.Date_3P_3C.day = tm1.tm_mday;
		deck.Date_3P_3C.month = tm1.tm_mon;
		deck.Date_3P_3C.year = tm1.tm_year;

		deck.day_1P_1C = deck.Date_1P_1C.day;
		deck.day_2P_2C = deck.Date_2P_2C.day;
		deck.day_3P_3C = deck.Date_3P_3C.day;

		deck.month_1P_1C = deck.Date_1P_1C.month;
		deck.month_2P_2C = deck.Date_2P_2C.month;
		deck.month_3P_3C = deck.Date_3P_3C.month;

		deck.year_1P_1C = deck.Date_1P_1C.year;
		deck.year_2P_2C = deck.Date_2P_2C.year;
		deck.year_3P_3C = deck.Date_3P_3C.year;

		if (isDefault == true)
		{
			deck.DeclineMethod = 1;
		}
		else
		{
			deck.DeclineMethod = 1;
			string declineMethod = (wrappedDeck.Get(Napi::String::New(env, "declineMethod"))).As<Napi::String>();

			if (declineMethod == "exponential")
			{
				deck.DeclineMethod = 1;
			}
			else if (declineMethod == "hyperbolic")
			{
				deck.DeclineMethod = 2;
			}
			else
			{
				deck.DeclineMethod = 3;
			}
		}

		inputdeck.ValidateDeck(deck);

		/* std::cout << "deck.Description " << deck.Description << std::endl; */
		if (deck.Description == "no error")
		{
			/* std::cout << "row Added " << i << std::endl; */
			InputDecks.push_back(deck);
		}

		/* std::cout << deck.Module << std::endl;
		std::cout << "Init_Oil_Gas_Rate_1P_1C: " << deck.Init_Oil_Gas_Rate_1P_1C << std::endl;
		std::cout << "Init_GOR_CGR: " << deck.Init_GOR_CGR << std::endl;
		std::cout << "Init_BSW_WGR: " << deck.Init_BSW_WGR << std::endl;
		std::cout << "Aband_GOR_CGR_1P_1C: " << deck.Aband_GOR_CGR_1P_1C << std::endl;
		std::cout << "Aband_BSW_WGR_1P_1C: " << deck.Aband_BSW_WGR_1P_1C << std::endl;
		std::cout << "Rate_of_Change_Rate_1P_1C: " << deck.Rate_of_Change_Rate_1P_1C << std::endl;
		std::cout << "Rate_Of_Rate_GOR_CGR_1P1C: " << deck.Rate_Of_Rate_GOR_CGR_1P1C << std::endl;
		std::cout << "Rate_Of_Rate_BSW_WGR_1P1C: " << deck.Rate_Of_Rate_BSW_WGR_1P1C << std::endl << std::endl;  */
	}

	int nWellDecks = InputDecks.size();
	nValidatedDecks2 = nWellDecks;

	std::cout << "nWellDecks " << nWellDecks << std::endl;

	Napi::Array wellDeckList = Napi::Array::New(env);

	for (int i = 0; i < nWellDecks; i++)
	{
		InputDeckStruct InputDeckRow = InputDecks[i];

		Napi::Object wellDeck = Napi::Object::New(env);

		wellDeck.Set(Napi::String::New(env, "forecastVersion"), Napi::String::New(env, InputDeckRow.Version_Name));
		wellDeck.Set(Napi::String::New(env, "asset"), Napi::String::New(env, InputDeckRow.Asset_Team));
		wellDeck.Set(Napi::String::New(env, "field"), Napi::String::New(env, InputDeckRow.Field));
		wellDeck.Set(Napi::String::New(env, "reservoir"), Napi::String::New(env, InputDeckRow.Reservoir));
		wellDeck.Set(Napi::String::New(env, "drainagePoint"), Napi::String::New(env, InputDeckRow.Drainage_Point));
		wellDeck.Set(Napi::String::New(env, "string"), Napi::String::New(env, InputDeckRow.Production_String));
		wellDeck.Set(Napi::String::New(env, "module"), Napi::String::New(env, InputDeckRow.Module));
		wellDeck.Set(Napi::String::New(env, "projectCode"), Napi::String::New(env, InputDeckRow.PEEP_Project));
		wellDeck.Set(Napi::String::New(env, "projectName"), Napi::String::New(env, InputDeckRow.Activity_Entity));
		wellDeck.Set(Napi::String::New(env, "facilities"), Napi::String::New(env, InputDeckRow.Flow_station));
		wellDeck.Set(Napi::String::New(env, "hydrocarbonStream"), Napi::String::New(env, InputDeckRow.Hydrocarbon_Stream));
		wellDeck.Set(Napi::String::New(env, "hydrocarbonType"), Napi::String::New(env, InputDeckRow.hydrocarbonType));
		wellDeck.Set(Napi::String::New(env, "terminal"), Napi::String::New(env, InputDeckRow.terminal));
		wellDeck.Set(Napi::String::New(env, "resourceClass"), Napi::String::New(env, InputDeckRow.Resource_Class));
		wellDeck.Set(Napi::String::New(env, "oilUR1P1C"), Napi::Number::New(env, InputDeckRow.URo_1P_1C));
		wellDeck.Set(Napi::String::New(env, "oilUR2P2C"), Napi::Number::New(env, InputDeckRow.URo_2P_2C));
		wellDeck.Set(Napi::String::New(env, "oilUR3P3C"), Napi::Number::New(env, InputDeckRow.URo_3P_3C));
		wellDeck.Set(Napi::String::New(env, "Np"), Napi::Number::New(env, InputDeckRow.Np));
		wellDeck.Set(Napi::String::New(env, "gasUR1P1C"), Napi::Number::New(env, InputDeckRow.URg_1P_1C));
		wellDeck.Set(Napi::String::New(env, "gasUR2P2C"), Napi::Number::New(env, InputDeckRow.URg_2P_2C));
		wellDeck.Set(Napi::String::New(env, "gasUR3P3C"), Napi::Number::New(env, InputDeckRow.URg_3P_3C));
		wellDeck.Set(Napi::String::New(env, "Gp"), Napi::Number::New(env, InputDeckRow.Gp));
		wellDeck.Set(Napi::String::New(env, "initOilGasRate1P1C"), Napi::Number::New(env, InputDeckRow.Init_Liquid_Gas_Rate_1P_1C));
		wellDeck.Set(Napi::String::New(env, "initOilGasRate2P2C"), Napi::Number::New(env, InputDeckRow.Init_Liquid_Gas_Rate_2P_2C));
		wellDeck.Set(Napi::String::New(env, "initOilGasRate3P3C"), Napi::Number::New(env, InputDeckRow.Init_Liquid_Gas_Rate_3P_3C));
		wellDeck.Set(Napi::String::New(env, "abandOilGasRate1P1C"), Napi::Number::New(env, InputDeckRow.Aband_Liquid_Gas_Rate_1P_1C));
		wellDeck.Set(Napi::String::New(env, "abandOilGasRate2P2C"), Napi::Number::New(env, InputDeckRow.Aband_Liquid_Gas_Rate_2P_2C));
		wellDeck.Set(Napi::String::New(env, "abandOilGasRate3P3C"), Napi::Number::New(env, InputDeckRow.Aband_Liquid_Gas_Rate_3P_3C));
		wellDeck.Set(Napi::String::New(env, "initBSWWGR"), Napi::Number::New(env, InputDeckRow.Init_BSW_WGR));
		wellDeck.Set(Napi::String::New(env, "abandBSWWGR1P1C"), Napi::Number::New(env, InputDeckRow.Aband_BSW_WGR_1P_1C));
		wellDeck.Set(Napi::String::New(env, "abandBSWWGR2P2C"), Napi::Number::New(env, InputDeckRow.Aband_BSW_WGR_2P_2C));
		wellDeck.Set(Napi::String::New(env, "abandBSWWGR3P3C"), Napi::Number::New(env, InputDeckRow.Aband_BSW_WGR_3P_3C));
		wellDeck.Set(Napi::String::New(env, "initGORCGR"), Napi::Number::New(env, InputDeckRow.Init_GOR_CGR));
		wellDeck.Set(Napi::String::New(env, "abandGORCGR1P1C"), Napi::Number::New(env, InputDeckRow.Aband_GOR_CGR_1P_1C));
		wellDeck.Set(Napi::String::New(env, "abandGORCGR2P2C"), Napi::Number::New(env, InputDeckRow.Aband_GOR_CGR_2P_2C));
		wellDeck.Set(Napi::String::New(env, "abandGORCGR3P3C"), Napi::Number::New(env, InputDeckRow.Aband_GOR_CGR_3P_3C));
		wellDeck.Set(Napi::String::New(env, "plateauPeriod"), Napi::Number::New(env, InputDeckRow.Plateau_Oil_Gas));
		wellDeck.Set(Napi::String::New(env, "optimizationWeight"), Napi::Number::New(env, InputDeckRow.optimizationWeight));
		double zro = 0.0;
		wellDeck.Set(Napi::String::New(env, "onStreamDate1P1C"), Napi::String::New(env, InputDeckRow.On_stream_Date_1P_1C));
		wellDeck.Set(Napi::String::New(env, "onStreamDate2P2C"), Napi::String::New(env, InputDeckRow.On_stream_Date_2P_2C));
		wellDeck.Set(Napi::String::New(env, "onStreamDate3P3C"), Napi::String::New(env, InputDeckRow.On_stream_Date_3P_3C));

		wellDeck.Set(Napi::String::New(env, "day1P1C"), Napi::Number::New(env, InputDeckRow.day_1P_1C));
		wellDeck.Set(Napi::String::New(env, "day2P2C"), Napi::Number::New(env, InputDeckRow.day_2P_2C));
		wellDeck.Set(Napi::String::New(env, "day3P3C"), Napi::Number::New(env, InputDeckRow.day_3P_3C));

		wellDeck.Set(Napi::String::New(env, "month1P1C"), Napi::Number::New(env, InputDeckRow.month_1P_1C));
		wellDeck.Set(Napi::String::New(env, "month2P2C"), Napi::Number::New(env, InputDeckRow.month_2P_2C));
		wellDeck.Set(Napi::String::New(env, "month3P3C"), Napi::Number::New(env, InputDeckRow.month_3P_3C));

		wellDeck.Set(Napi::String::New(env, "year1P1C"), Napi::Number::New(env, InputDeckRow.year_1P_1C));
		wellDeck.Set(Napi::String::New(env, "year2P2C"), Napi::Number::New(env, InputDeckRow.year_2P_2C));
		wellDeck.Set(Napi::String::New(env, "year3P3C"), Napi::Number::New(env, InputDeckRow.year_3P_3C));

		/* std::cout << "year1P1C after"  << InputDeckRow.year_1P_1C << std::endl;
		std::cout << "year2P2C after"  << InputDeckRow.year_2P_2C << std::endl;
		std::cout << "year3P3C after"  << InputDeckRow.year_3P_3C << std::endl; */

		wellDeck.Set(Napi::String::New(env, "remarks"), Napi::String::New(env, InputDeckRow.Remarks));
		wellDeck.Set(Napi::String::New(env, "developmentTranche"), Napi::String::New(env, InputDeckRow.TRANCHE));

		//------------Calculated Variable-------------------------------------------
		wellDeck.Set(Napi::String::New(env, "description"), Napi::String::New(env, InputDeckRow.Description));
		wellDeck.Set(Napi::String::New(env, "rateOfChangeGORCGR1P1C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_GOR_CGR_1P1C));
		wellDeck.Set(Napi::String::New(env, "rateOfChangeGORCGR2P2C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_GOR_CGR_2P2C));
		wellDeck.Set(Napi::String::New(env, "rateOfChangeGORCGR3P3C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_GOR_CGR_3P3C));
		wellDeck.Set(Napi::String::New(env, "rateOfChangeBSWWGR1P1C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_BSW_WGR_1P1C));
		wellDeck.Set(Napi::String::New(env, "rateOfChangeBSWWGR2P2C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_BSW_WGR_2P2C));
		wellDeck.Set(Napi::String::New(env, "rateOfChangeBSWWGR3P3C"), Napi::Number::New(env, InputDeckRow.Rate_Of_Rate_BSW_WGR_3P3C));
		wellDeck.Set(Napi::String::New(env, "rateofChangeRate1P1C"), Napi::Number::New(env, InputDeckRow.Rate_of_Change_Rate_1P_1C));
		wellDeck.Set(Napi::String::New(env, "rateofChangeRate2P2C"), Napi::Number::New(env, InputDeckRow.Rate_of_Change_Rate_2P_2C));
		wellDeck.Set(Napi::String::New(env, "rateofChangeRate3P3C"), Napi::Number::New(env, InputDeckRow.Rate_of_Change_Rate_3P_3C));
		wellDeck.Set(Napi::String::New(env, "declineExponent1P1C"), Napi::Number::New(env, zro));
		wellDeck.Set(Napi::String::New(env, "declineExponent2P2C"), Napi::Number::New(env, zro));
		wellDeck.Set(Napi::String::New(env, "declineExponent3P3C"), Napi::Number::New(env, zro));
		wellDeck.Set(Napi::String::New(env, "plateauUR1P1C"), Napi::Number::New(env, InputDeckRow.PlateauUR_1P_1C));
		wellDeck.Set(Napi::String::New(env, "plateauUR2P2C"), Napi::Number::New(env, InputDeckRow.PlateauUR_2P_2C));
		wellDeck.Set(Napi::String::New(env, "plateauUR3P3C"), Napi::Number::New(env, InputDeckRow.PlateauUR_3P_3C));

		string declineMethod = "exponential";
		if (InputDeckRow.DeclineMethod == 1)
		{
			declineMethod = "exponential";
		}
		else if (InputDeckRow.DeclineMethod == 2)
		{
			declineMethod = "hyperbolic";
		}
		else
		{
			declineMethod = "harmonic";
		}

		wellDeck.Set(Napi::String::New(env, "declineMethod"), Napi::String::New(env, declineMethod));

		//--------------------------------------------------------------

		wellDeckList.Set(Napi::Number::New(env, i), wellDeck);
	}

	return wellDeckList;
}

vector<InputDeckStruct> ReportJSON::getUpdatedInputDecks2(Napi::Array &wrappedDecks, Napi::Env &env,
														  int nWrappedDecks)
{

	vector<InputDeckStruct> InputDecks;

	int nSize = nWrappedDecks;

	for (int i = 0; i < nSize; i++)
	{
		// std::cout << "Seen 1111 " << std::endl;
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();
		InputDeckStruct deck;
		deck.Version_Name = (wrappedDeck.Get(Napi::String::New(env, "forecastVersion"))).As<Napi::String>();
		deck.Asset_Team = (wrappedDeck.Get(Napi::String::New(env, "asset"))).As<Napi::String>();
		deck.Field = (wrappedDeck.Get(Napi::String::New(env, "field"))).As<Napi::String>();
		deck.Reservoir = (wrappedDeck.Get(Napi::String::New(env, "reservoir"))).As<Napi::String>();
		deck.Drainage_Point = (wrappedDeck.Get(Napi::String::New(env, "drainagePoint"))).As<Napi::String>();
		deck.Production_String = (wrappedDeck.Get(Napi::String::New(env, "string"))).As<Napi::String>();
		deck.Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		deck.PEEP_Project = (wrappedDeck.Get(Napi::String::New(env, "projectCode"))).As<Napi::String>();
		deck.Flow_station = (wrappedDeck.Get(Napi::String::New(env, "facilities"))).As<Napi::String>();
		deck.Hydrocarbon_Stream = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonStream"))).As<Napi::String>();
		deck.hydrocarbonType = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonType"))).As<Napi::String>();
		deck.terminal = (wrappedDeck.Get(Napi::String::New(env, "terminal"))).As<Napi::String>();
		deck.URo_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "oilUR1P1C"))).As<Napi::Number>();
		deck.URo_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "oilUR2P2C"))).As<Napi::Number>();
		deck.URo_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "oilUR3P3C"))).As<Napi::Number>();
		deck.Np = (wrappedDeck.Get(Napi::String::New(env, "Np"))).As<Napi::Number>();
		deck.URg_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "gasUR1P1C"))).As<Napi::Number>();
		deck.URg_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "gasUR2P2C"))).As<Napi::Number>();
		deck.URg_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "gasUR3P3C"))).As<Napi::Number>();
		deck.Gp = (wrappedDeck.Get(Napi::String::New(env, "Gp"))).As<Napi::Number>();
		deck.Init_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate1P1C"))).As<Napi::Number>();
		deck.Init_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate2P2C"))).As<Napi::Number>();
		deck.Init_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate3P3C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate1P1C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate2P2C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate3P3C"))).As<Napi::Number>();
		deck.Init_BSW_WGR = (wrappedDeck.Get(Napi::String::New(env, "initBSWWGR"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR1P1C"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR2P2C"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR3P3C"))).As<Napi::Number>();
		deck.Init_GOR_CGR = (wrappedDeck.Get(Napi::String::New(env, "initGORCGR"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR1P1C"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR2P2C"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR3P3C"))).As<Napi::Number>();
		deck.Plateau_Oil_Gas = (wrappedDeck.Get(Napi::String::New(env, "plateauPeriod"))).As<Napi::Number>();
		deck.DeclineMethod = 1;
		string declineMethod = (wrappedDeck.Get(Napi::String::New(env, "declineMethod"))).As<Napi::String>();

		if (declineMethod == "exponential")
		{
			deck.DeclineMethod = 1;
		}
		else if (declineMethod == "hyperbolic")
		{
			deck.DeclineMethod = 2;
		}
		else
		{
			deck.DeclineMethod = 3;
		}

		InputDecks.push_back(deck);
	}

	return InputDecks;
}

vector<ForecastResult> ReportJSON::GetYearlyForcastResultModuleLevel(Napi::Object &wrappedSelectedModule, Napi::Env &env)
{
	vector<ForecastResult> ForcastResultsModuleLevel;
	Napi::Array wellForecastResults = (wrappedSelectedModule.Get(Napi::String::New(env, "resultWells"))).As<Napi::Array>();

	int lent = (int)wellForecastResults.Length();

	// std::cout << "GetYearlyForcastResultModuleLevel Started" << "\n";

	for (int i = 0; i < lent; i++)
	{
		Napi::Object wellForecastResult = ((Napi::Value)wellForecastResults[i]).As<Napi::Object>();

		ForecastResult forecastResult;

		forecastResult.Day = (wellForecastResult.Get(Napi::String::New(env, "day"))).As<Napi::Number>();
		forecastResult.Month = (wellForecastResult.Get(Napi::String::New(env, "month"))).As<Napi::Number>();
		forecastResult.Year = (wellForecastResult.Get(Napi::String::New(env, "year"))).As<Napi::Number>();
		forecastResult.Oil_rate = (wellForecastResult.Get(Napi::String::New(env, "oilRate"))).As<Napi::Number>();
		forecastResult.Condensate_Rate = (wellForecastResult.Get(Napi::String::New(env, "condensateRate"))).As<Napi::Number>();
		forecastResult.Gas_Rate = (wellForecastResult.Get(Napi::String::New(env, "gasRate"))).As<Napi::Number>();
		forecastResult.Water_Rate = (wellForecastResult.Get(Napi::String::New(env, "waterRate"))).As<Napi::Number>();
		forecastResult.Liquid_Rate = (wellForecastResult.Get(Napi::String::New(env, "liquidRate"))).As<Napi::Number>();
		forecastResult.Cum_Oil_Prod = (wellForecastResult.Get(Napi::String::New(env, "cumOilProd"))).As<Napi::Number>();
		forecastResult.Cum_Gas_Prod = (wellForecastResult.Get(Napi::String::New(env, "cumGasProd"))).As<Napi::Number>();
		forecastResult.Cum_Water_Prod = (wellForecastResult.Get(Napi::String::New(env, "cumWaterProd"))).As<Napi::Number>();
		forecastResult.GOR = (wellForecastResult.Get(Napi::String::New(env, "gOR"))).As<Napi::Number>();
		forecastResult.BSW = (wellForecastResult.Get(Napi::String::New(env, "bSW"))).As<Napi::Number>();
		forecastResult.CGR = (wellForecastResult.Get(Napi::String::New(env, "cGR"))).As<Napi::Number>();
		forecastResult.WGR = (wellForecastResult.Get(Napi::String::New(env, "wGR"))).As<Napi::Number>();
		forecastResult.CutBack = (wellForecastResult.Get(Napi::String::New(env, "cutBack"))).As<Napi::Number>();
		forecastResult.HyrocarbonStream = (wellForecastResult.Get(Napi::String::New(env, "hydrocarbonStream"))).As<Napi::String>();
		forecastResult.hydrocarbonType = (wellForecastResult.Get(Napi::String::New(env, "hydrocarbonType"))).As<Napi::String>();
		forecastResult.terminal = (wellForecastResult.Get(Napi::String::New(env, "terminal"))).As<Napi::String>();
		forecastResult.URo = (wellForecastResult.Get(Napi::String::New(env, "uRo"))).As<Napi::Number>();
		forecastResult.URg = (wellForecastResult.Get(Napi::String::New(env, "uRg"))).As<Napi::Number>();
		forecastResult.Gas_Own_Use = (wellForecastResult.Get(Napi::String::New(env, "ownUseGas"))).As<Napi::Number>();
		forecastResult.Gas_Demand = (wellForecastResult.Get(Napi::String::New(env, "gasDemand"))).As<Napi::Number>();
		forecastResult.Gas_Flared = (wellForecastResult.Get(Napi::String::New(env, "flareGas"))).As<Napi::Number>();
		forecastResult.Crude_Oil_Lossess = (wellForecastResult.Get(Napi::String::New(env, "crudeOilLossess"))).As<Napi::Number>();
		forecastResult.DeclineRate = 0; //(wellForecastResult.Get(Napi::String::New(env, "declineRate"))).As<Napi::Number>();

		forecastResult.moduleName = (wellForecastResult.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		forecastResult.Version_Name = (wellForecastResult.Get(Napi::String::New(env, "forecastVersion"))).As<Napi::String>();
		forecastResult.Field = (wellForecastResult.Get(Napi::String::New(env, "field"))).As<Napi::String>();
		forecastResult.Reservoir = (wellForecastResult.Get(Napi::String::New(env, "reservoir"))).As<Napi::String>();
		forecastResult.Drainage_Point = (wellForecastResult.Get(Napi::String::New(env, "drainagePoint"))).As<Napi::String>();
		forecastResult.Production_String = (wellForecastResult.Get(Napi::String::New(env, "string"))).As<Napi::String>();
		forecastResult.TRANCHE = (wellForecastResult.Get(Napi::String::New(env, "developmentTranche"))).As<Napi::String>();
		forecastResult.Asset_Team = (wellForecastResult.Get(Napi::String::New(env, "asset"))).As<Napi::String>();
		forecastResult.Flow_station = (wellForecastResult.Get(Napi::String::New(env, "facilities"))).As<Napi::String>();
		forecastResult.projectCode = (wellForecastResult.Get(Napi::String::New(env, "projectCode"))).As<Napi::String>();
		forecastResult.projectName = (wellForecastResult.Get(Napi::String::New(env, "projectName"))).As<Napi::String>();
		forecastResult.resourceClass = (wellForecastResult.Get(Napi::String::New(env, "resourceClass"))).As<Napi::String>();

		ForcastResultsModuleLevel.push_back(forecastResult);
	}

	// std::cout << "GetYearlyForcastResultModuleLevel Completed" << "\n";
	return ForcastResultsModuleLevel;
}

vector<ForecastResultForChart> ReportJSON::GetYearlyForcastResultModuleLevelChart(Napi::Object &wrappedSelectedModule, Napi::Env &env)
{
	vector<ForecastResultForChart> ForcastResultsModuleLevel;
	Napi::Array wellForecastResults = (wrappedSelectedModule.Get(Napi::String::New(env, "resultWells"))).As<Napi::Array>();

	int lent = (int)wellForecastResults.Length();

	for (int i = 0; i < lent; i++)
	{
		Napi::Object wellForecastResult = ((Napi::Value)wellForecastResults[i]).As<Napi::Object>();

		ForecastResultForChart forecastResult;

		forecastResult.data = (wellForecastResult.Get(Napi::String::New(env, "value"))).As<Napi::Number>();

		ForcastResultsModuleLevel.push_back(forecastResult);
	}

	return ForcastResultsModuleLevel;
}

vector<vector<ForecastResult>> ReportJSON::GetYearlyForcastResultModules(Napi::Array &wellsForecastResults,
																		 Napi::Env &env, int nWells)
{

	vector<vector<ForecastResult>> wells;

	int i = 0;

	for (i = 0; i < nWells; i++)
	{

		Napi::Object moduleObject = ((Napi::Value)wellsForecastResults[i]).As<Napi::Object>();

		vector<ForecastResult> results = GetYearlyForcastResultModuleLevel(moduleObject, env);

		wells.push_back(results);
	}

	return wells;
}

vector<vector<ForecastResultForChart>> ReportJSON::GetYearlyForcastResultModulesForChart(Napi::Array &wellsForecastResults, Napi::Env &env)
{

	vector<vector<ForecastResultForChart>> wells;

	int i = 0;

	int nWells = (int)wellsForecastResults.Length();

	for (i = 0; i < nWells; i++)
	{

		Napi::Object moduleObject = ((Napi::Value)wellsForecastResults[i]).As<Napi::Object>();

		vector<ForecastResultForChart> results = GetYearlyForcastResultModuleLevelChart(moduleObject, env);

		wells.push_back(results);
	}

	return wells;
}

Napi::Object ReportJSON::SetRowResult(ForecastResult &r, Napi::Env &env)
{

	Napi::Object resultWell = Napi::Object::New(env);
	resultWell.Set(Napi::String::New(env, "day"), Napi::Number::New(env, r.Day));
	resultWell.Set(Napi::String::New(env, "month"), Napi::Number::New(env, r.Month));
	resultWell.Set(Napi::String::New(env, "year"), Napi::Number::New(env, r.Year));
	resultWell.Set(Napi::String::New(env, "oilRate"), Napi::Number::New(env, r.Oil_rate));
	resultWell.Set(Napi::String::New(env, "gasRate"), Napi::Number::New(env, r.Gas_Rate));
	resultWell.Set(Napi::String::New(env, "waterRate"), Napi::Number::New(env, r.Water_Rate));
	resultWell.Set(Napi::String::New(env, "liquidRate"), Napi::Number::New(env, r.Liquid_Rate));
	resultWell.Set(Napi::String::New(env, "cumOilProd"), Napi::Number::New(env, r.Cum_Oil_Prod));
	resultWell.Set(Napi::String::New(env, "cumGasProd"), Napi::Number::New(env, r.Cum_Gas_Prod));
	resultWell.Set(Napi::String::New(env, "cumWaterProd"), Napi::Number::New(env, r.Cum_Water_Prod));

	resultWell.Set(Napi::String::New(env, "gOR"), Napi::Number::New(env, r.GOR));
	resultWell.Set(Napi::String::New(env, "bSW"), Napi::Number::New(env, r.BSW));
	resultWell.Set(Napi::String::New(env, "cGR"), Napi::Number::New(env, r.CGR));
	resultWell.Set(Napi::String::New(env, "wGR"), Napi::Number::New(env, r.WGR));
	resultWell.Set(Napi::String::New(env, "cutBack"), Napi::Number::New(env, r.CutBack));
	resultWell.Set(Napi::String::New(env, "hydrocarbonStream"), Napi::String::New(env, r.HyrocarbonStream));
	resultWell.Set(Napi::String::New(env, "hydrocarbonType"), Napi::String::New(env, r.hydrocarbonType));
	resultWell.Set(Napi::String::New(env, "terminal"), Napi::String::New(env, r.terminal));
	resultWell.Set(Napi::String::New(env, "uRo"), Napi::Number::New(env, r.URo));
	resultWell.Set(Napi::String::New(env, "uRg"), Napi::Number::New(env, r.URg));
	resultWell.Set(Napi::String::New(env, "ownUseGas"), Napi::Number::New(env, r.Gas_Own_Use));
	resultWell.Set(Napi::String::New(env, "gasDemand"), Napi::Number::New(env, r.Gas_Demand));
	resultWell.Set(Napi::String::New(env, "crudeOilLossess"), Napi::Number::New(env, r.Crude_Oil_Lossess));
	resultWell.Set(Napi::String::New(env, "cutBackRatio"), Napi::Number::New(env, r.CutBack));
	resultWell.Set(Napi::String::New(env, "declineRate"), Napi::Number::New(env, r.DeclineRate));

	resultWell.Set(Napi::String::New(env, "module"), Napi::String::New(env, r.moduleName));
	resultWell.Set(Napi::String::New(env, "forecastVersion"), Napi::String::New(env, r.Version_Name));
	resultWell.Set(Napi::String::New(env, "field"), Napi::String::New(env, r.Field));
	resultWell.Set(Napi::String::New(env, "reservoir"), Napi::String::New(env, r.Reservoir));
	resultWell.Set(Napi::String::New(env, "drainagePoint"), Napi::String::New(env, r.Drainage_Point));
	resultWell.Set(Napi::String::New(env, "string"), Napi::String::New(env, r.Production_String));
	resultWell.Set(Napi::String::New(env, "developmentTranche"), Napi::String::New(env, r.TRANCHE));
	resultWell.Set(Napi::String::New(env, "asset"), Napi::String::New(env, r.Asset_Team));
	resultWell.Set(Napi::String::New(env, "facilities"), Napi::String::New(env, r.Flow_station));
	resultWell.Set(Napi::String::New(env, "projectCode"), Napi::String::New(env, r.Flow_station));
	resultWell.Set(Napi::String::New(env, "projectName"), Napi::String::New(env, r.Flow_station));
	resultWell.Set(Napi::String::New(env, "resourceClass"), Napi::String::New(env, r.Flow_station));

	// std::cout << "Seen 3" << std::endl;
	return resultWell;
}

Napi::Object ReportJSON::SetRowResultForChart(ForecastResultForChart &r, Napi::Env &env)
{

	Napi::Object resultWell = Napi::Object::New(env);
	resultWell.Set(Napi::String::New(env, "day"), Napi::Number::New(env, r.Day));
	resultWell.Set(Napi::String::New(env, "month"), Napi::Number::New(env, r.Month));
	resultWell.Set(Napi::String::New(env, "year"), Napi::Number::New(env, r.Year));
	resultWell.Set(Napi::String::New(env, "value"), Napi::Number::New(env, r.data));

	return resultWell;
}

Napi::Object ReportJSON::GetForecastOutput(Napi::Env &env, vector<ForecastResult> &results)
{

	int nResults = results.size();

	Napi::Object moduleResult = Napi::Object::New(env);
	// Napi::Array resultsWellObject = Napi::Array::New(env);
	// std::cout << "Seen 2" << std::endl;
	string table = "";
	int i = 1;
	bool isLastRow = false;
	for (int ii = 0; ii < nResults; ii++)
	{

		ForecastResult r = results[ii];

		// Napi::Object resultWell = SetRowResult(r, env);
		if (ii == nResults - 1)
		{
			isLastRow = true;
		}
		// resultsWellObject.Set(Napi::Number::New(env, ii), resultWell);

		table = table + reportJSON2.GetRow(r, i, ii, isLastRow);
	}

	moduleResult.Set(Napi::String::New(env, "resultWells"), Napi::String::New(env, table));

	return moduleResult;
}

Napi::Object ReportJSON::GetForecastOutputForChart(Napi::Env &env, vector<ForecastResultForChart> &results)
{

	int nResults = results.size();

	Napi::Object moduleResult = Napi::Object::New(env);
	Napi::Array resultsWellObject = Napi::Array::New(env);
	// std::cout << "Seen 2" << std::endl;
	for (int ii = 0; ii < nResults; ii++)
	{

		ForecastResultForChart r = results[ii];

		Napi::Object resultWell = SetRowResultForChart(r, env);

		resultsWellObject.Set(Napi::Number::New(env, ii), resultWell);
	}

	moduleResult.Set(Napi::String::New(env, "resultWells"), resultsWellObject);

	return moduleResult;
}

Napi::Array ReportJSON::GetForecastOutputWWells(Napi::Env &env, vector<vector<ForecastResult>> &results)
{
	int nWells = results.size();

	Napi::Array decksPerFacility = Napi::Array::New(env);
	int i = 0;
	for (i = 0; i < nWells; i++)
	{
		// std::cout << "Seen 1" << std::endl;
		Napi::Object deckObject = GetForecastOutput(env, results[i]);
		int wellNo = i;
		decksPerFacility.Set(Napi::Number::New(env, wellNo), deckObject);
	}

	// std::cout << "Seen 2" << std::endl;
	return decksPerFacility;
}

Napi::Array ReportJSON::GetForecastOutputWWellsNEW(Napi::Env &env, vector<vector<ForecastResult>> &results)
{
	int nWells = results.size();

	Napi::Array decksPerFacility = Napi::Array::New(env);
	int i = 0;
	for (i = 0; i < nWells; i++)
	{
		// std::cout << "Seen 1" << std::endl;
		Napi::Object deckObject = GetForecastOutput(env, results[i]);
		int wellNo = i;
		decksPerFacility.Set(Napi::Number::New(env, wellNo), deckObject);
	}

	// std::cout << "Seen 2" << std::endl;
	return decksPerFacility;
}

Napi::Array ReportJSON::GetForecastOutputWWellsForChart(Napi::Env &env, vector<vector<ForecastResultForChart>> &results)
{
	int nWells = results.size();

	Napi::Array decksPerFacility = Napi::Array::New(env);
	int i = 0;
	for (i = 0; i < nWells; i++)
	{
		// std::cout << "Seen 1" << std::endl;
		Napi::Object deckObject = GetForecastOutputForChart(env, results[i]);
		int wellNo = i;
		decksPerFacility.Set(Napi::Number::New(env, wellNo), deckObject);
	}

	// std::cout << "Seen 2" << std::endl;
	return decksPerFacility;
}

vector<vector<vector<ForecastResult>>> ReportJSON::GetYearlyForcastResultFacilitiesLevel(
	Napi::Array &wellsForecastResults, Napi::Env &env, int nFacilities)
{

	vector<vector<vector<ForecastResult>>> facilities;

	int i = 0;

	for (i = 0; i < nFacilities; i++)
	{
		// innerWells: scenarios[key].facilities[facilitykey].wells,
		// nInnerWells: scenarios[key].facilities[facilitykey].wells.length

		Napi::Object _innerWellsObject = ((Napi::Value)wellsForecastResults[i]).As<Napi::Object>();
		// Napi::Array moduleObject = ((Napi::Value)wellsForecastResults[i]).As<Napi::Array>();
		Napi::Array innerWells = (_innerWellsObject.Get(Napi::String::New(env, "innerWells"))).As<Napi::Array>();
		Napi::Number nInnerWells = (_innerWellsObject.Get(Napi::String::New(env, "nInnerWells"))).As<Napi::Number>();

		vector<vector<ForecastResult>> results = GetYearlyForcastResultModules(innerWells, env, nInnerWells);

		facilities.push_back(results);
	}

	return facilities;
}

InterpParams ReportJSON::GetInterpParams(Napi::Object &wrappedInterpParams, Napi::Env &env)
{
	Napi::Array x1 = (wrappedInterpParams.Get(Napi::String::New(env, "x1"))).As<Napi::Array>();
	Napi::Array y1 = (wrappedInterpParams.Get(Napi::String::New(env, "y1"))).As<Napi::Array>();
	Napi::Array x2 = (wrappedInterpParams.Get(Napi::String::New(env, "x2"))).As<Napi::Array>();
	Napi::Array y2 = (wrappedInterpParams.Get(Napi::String::New(env, "y2"))).As<Napi::Array>();

	int lent1 = (int)x1.Length();
	int i = 0;
	InterpParams interpParams;

	for (i = 0; i < lent1; i++)
	{
		double xn1 = ((Napi::Value)x1[i]).As<Napi::Number>();
		double yn1 = ((Napi::Value)y1[i]).As<Napi::Number>();
		double xn2 = ((Napi::Value)x2[i]).As<Napi::Number>();
		double yn2 = ((Napi::Value)y2[i]).As<Napi::Number>();

		interpParams.Xs1.push_back(xn1);
		interpParams.Ys1.push_back(yn1);
		interpParams.Xs2.push_back(xn2);
		interpParams.Ys2.push_back(yn2);
	}

	return interpParams;
}

Napi::Object ReportJSON::GetInterpResult(Napi::Env &env, vector<double> &result)
{
	Napi::Object resultObject = Napi::Object::New(env);
	resultObject.Set(Napi::String::New(env, "x"), Napi::Number::New(env, result[0]));
	resultObject.Set(Napi::String::New(env, "y"), Napi::Number::New(env, result[1]));

	return resultObject;
}

vector<WellRampUp> ReportJSON::getWellRampUpDecks(Napi::Array &wrappedDecks,
												  int nWellRampUpDecks, Napi::Env &env)
{

	vector<WellRampUp> InputDecks;

	for (int i = 0; i < nWellRampUpDecks; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		WellRampUp deck;
		deck.Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		deck.maximumPotential = (wrappedDeck.Get(Napi::String::New(env, "maximumPotential"))).As<Napi::Number>();
		deck.dcaStrategy = (wrappedDeck.Get(Napi::String::New(env, "dcaStrategy"))).As<Napi::String>();
		inputdeck.ToLower(deck.dcaStrategy);
		deck.declineType = (wrappedDeck.Get(Napi::String::New(env, "declineType"))).As<Napi::String>();
		inputdeck.ToLower(deck.declineType);
		string startDate = (wrappedDeck.Get(Napi::String::New(env, "startDate"))).As<Napi::String>();
		deck.percentOfMaximumPotential = (wrappedDeck.Get(Napi::String::New(env, "percentOfMaximumPotential"))).As<Napi::Number>();
		deck.startupRatePlateau = (wrappedDeck.Get(Napi::String::New(env, "startupRatePlateau"))).As<Napi::Number>();
		deck.declineRate = (wrappedDeck.Get(Napi::String::New(env, "declineExponent"))).As<Napi::Number>();
		deck.hyperbolicExponent = (wrappedDeck.Get(Napi::String::New(env, "hyperbolicExponent"))).As<Napi::Number>();

		tm tm1;
		sscanf(startDate.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		deck.rampUpDate_1P_1C.day = tm1.tm_mday;
		deck.rampUpDate_1P_1C.month = tm1.tm_mon;
		deck.rampUpDate_1P_1C.year = tm1.tm_year;

		deck.rampUpDate_2P_2C.day = tm1.tm_mday;
		deck.rampUpDate_2P_2C.month = tm1.tm_mon;
		deck.rampUpDate_2P_2C.year = tm1.tm_year;

		deck.rampUpDate_3P_3C.day = tm1.tm_mday;
		deck.rampUpDate_3P_3C.month = tm1.tm_mon;
		deck.rampUpDate_3P_3C.year = tm1.tm_year;
	}

	return InputDecks;
}

vector<ShutInOpenUp> ReportJSON::getWellShutInOpenUpDecks(Napi::Array &wrappedDecks,
														  int nWellShutInOpenUpDecks, Napi::Env &env)
{

	vector<ShutInOpenUp> InputDecks;

	for (int i = 0; i < nWellShutInOpenUpDecks; i++)
	{
		Napi::Object wrappedDeck = ((Napi::Value)wrappedDecks[i]).As<Napi::Object>();

		ShutInOpenUp deck;
		deck.Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		string shutInDate = (wrappedDeck.Get(Napi::String::New(env, "shutInDate"))).As<Napi::String>();
		deck.event = (wrappedDeck.Get(Napi::String::New(env, "event"))).As<Napi::String>();
		deck.dcaStrategy = (wrappedDeck.Get(Napi::String::New(env, "dcaStrategy"))).As<Napi::String>();
		inputdeck.ToLower(deck.dcaStrategy);
		deck.declineType = (wrappedDeck.Get(Napi::String::New(env, "declineType"))).As<Napi::String>();
		inputdeck.ToLower(deck.declineType);
		deck.startupRate = (wrappedDeck.Get(Napi::String::New(env, "startupRate"))).As<Napi::Number>();
		deck.startupRatePlateau = (wrappedDeck.Get(Napi::String::New(env, "startupRatePlateau"))).As<Napi::Number>();
		deck.declineRate = (wrappedDeck.Get(Napi::String::New(env, "declineExponent"))).As<Napi::Number>();
		deck.hyperbolicExponent = (wrappedDeck.Get(Napi::String::New(env, "hyperbolicExponent"))).As<Napi::Number>();

		tm tm1, tm2;
		sscanf(shutInDate.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		deck.eventDate_1P_1C.day = tm1.tm_mday;
		deck.eventDate_1P_1C.month = tm1.tm_mon;
		deck.eventDate_1P_1C.year = tm1.tm_year;

		deck.eventDate_2P_2C.day = tm1.tm_mday;
		deck.eventDate_2P_2C.month = tm1.tm_mon;
		deck.eventDate_2P_2C.year = tm1.tm_year;

		deck.eventDate_3P_3C.day = tm1.tm_mday;
		deck.eventDate_3P_3C.month = tm1.tm_mon;
		deck.eventDate_3P_3C.year = tm1.tm_year;
	}

	return InputDecks;
}