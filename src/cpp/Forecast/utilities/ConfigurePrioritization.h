#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <algorithm>
#include <time.h>
#include <functional>
#include <exception>
#include <iostream>
#include <string>
#include <sys/stat.h> // stat
#include <errno.h>    // errno, ENOENT, EEXIST
// #include <filesystem>
#include "../ProductionForecast/Forecast.h"
#include "../ProductionForecast/Inputdeck.h"

using namespace std;
using namespace std::placeholders;

class ConfigurePrioritization
{

private:
  Inputdeck inputdeck;

public:
  ConfigurePrioritization();
  ~ConfigurePrioritization();
  vector<Prioritization> SetUpPrioritization(vector<FacilityStructExternal> &FacilityTable, Date &startDate, Date &stopDate,
                                           Prioritization &prioritization, vector<Prioritization> &nodalPrioritizations);
  vector<Prioritization> SetUpDefaultPrioritization(vector<FacilityStructExternal> &FacilityTable, Date &startDate, Date &stopDate);
  void SetWellPrioritization(Prioritization &prioritization, Prioritization &assestPrioritization);
  void SetStreamPrioritization(Prioritization &prioritization, Prioritization &assestPrioritization);
  void SetResourceClassPrioritization(Prioritization &prioritization, Prioritization &assestPrioritization);
  void SetProjectPrioritization(Prioritization &prioritization, Prioritization &assestPrioritization);
};

ConfigurePrioritization::ConfigurePrioritization()
{
}

ConfigurePrioritization::~ConfigurePrioritization()
{
}

vector<Prioritization> ConfigurePrioritization::SetUpDefaultPrioritization(vector<FacilityStructExternal> &FacilityTable, Date &startDate, Date &stopDate)
{
  vector<Prioritization> prioritizations;

  vector<string> parameterNames = vector<string>{High, Normal, Low};
  vector<double> parameterWeights = vector<double>{90, 50, 10}; // Create Ratios from this

  int i = 0, j = 0;
  for (i = 0; i < FacilityTable.size(); i++)
  {

    Prioritization prioritization;
    prioritization.FromDate = startDate;

    prioritization.ToDate = stopDate;

    prioritization.FacilityName = FacilityTable[i].Primary_Facility;
    prioritization.typeOfPrioritization = wellPrioritization;
    prioritization.methodOfPrioritization = sequential;
    if (FacilityTable[i].equipmentType == gas_plant)
    {
      prioritization.targetFluid = gas;
    }

    if (FacilityTable[i].equipmentType == gas_asset)
    {
      prioritization.targetFluid = gas;
    }

    if (FacilityTable[i].equipmentType == flow_station)
    {
      prioritization.targetFluid = oil;
    }

    if (FacilityTable[i].equipmentType == oil_asset)
    {
      prioritization.targetFluid = oil;
    }

    if (FacilityTable[i].equipmentType == ag_asset)
    {
      prioritization.targetFluid = ag;
    }

    if (FacilityTable[i].equipmentType == nag_asset)
    {
      prioritization.targetFluid = nag;
    }

    if (FacilityTable[i].equipmentType == condensate_asset)
    {
      prioritization.targetFluid = condensate;
    }

    double sum = 0;
    for (j = 0; j < parameterWeights.size(); j++)
    {
      sum = sum + parameterWeights[j];
    }

    for (j = 0; j < parameterNames.size(); j++)
    {
      prioritization.prioritizationModel.ParameterNames.push_back(parameterNames[j]);
      prioritization.prioritizationModel.ParameterWeights.push_back(parameterWeights[j] / sum);
    }

    prioritizations.push_back(prioritization);
  }

  return prioritizations;
}

void ConfigurePrioritization::SetWellPrioritization(Prioritization &prioritization, Prioritization &assestPrioritization)
{

  assestPrioritization.targetFluid = prioritization.targetFluid;

  PrioritizationModel prioritizationModel;
  double sum = 0;
  if (prioritization.methodOfPrioritization == weighted)
  {
    for (int j = 0; j < prioritization.prioritizationModel.ParameterNames.size(); j++)
    {
      sum = sum + prioritization.prioritizationModel.ParameterWeights[j];
    }
  }

  prioritizationModel.ParameterNames.clear();
  prioritizationModel.ParameterWeights.clear();
  for (int j = 0; j < prioritization.prioritizationModel.ParameterNames.size(); j++)
  {
    string parameterName = prioritization.prioritizationModel.ParameterNames[j];
    inputdeck.ToLower(parameterName);
    prioritizationModel.ParameterNames.push_back(parameterName);
    if (prioritization.methodOfPrioritization == weighted)
    {
      prioritizationModel.ParameterWeights.push_back(prioritization.prioritizationModel.ParameterWeights[j] / sum);
    }
  }

  assestPrioritization.prioritizationModel.ParameterNames = prioritizationModel.ParameterNames;
  assestPrioritization.prioritizationModel.ParameterWeights = prioritizationModel.ParameterWeights;
  assestPrioritization.typeOfPrioritization = prioritization.typeOfPrioritization;
}

void ConfigurePrioritization::SetStreamPrioritization(Prioritization &prioritization,
                                                      Prioritization &assestPrioritization)
{

  vector<string> streamsOilPrioritized = {"OIL", "CONDENSATE", "GAS", "AG", "NAG"};        // when streamPrioritization.type is oil or ag
  vector<string> streamsGasPrioritized = {"GAS", "CONDENSATE", "OIL", "NAG", "AG"};        // when streamPrioritization.type is gas or nag
  vector<string> streamsCondensatePrioritized = {"CONDENSATE", "OIL", "GAS", "NAG", "AG"}; // when streamPrioritization.type is oil or ag
  int lent = streamsOilPrioritized.size();
  vector<string> parameterNames;
  vector<double> parameterWeights;
  for (int i = 0; i < lent; i++)
  {
    parameterWeights.push_back(1.0);
    if (prioritization.typeOfStream == "gas")
    {
      parameterNames.push_back(streamsGasPrioritized[i]);
    }

    if (prioritization.typeOfStream == "oil")
    {
      parameterNames.push_back(streamsOilPrioritized[i]);
    }

    if (prioritization.typeOfStream == "condensate")
    {
      parameterNames.push_back(streamsCondensatePrioritized[i]);
    }
  }

  PrioritizationModel prioritizationModel;
  double sum = 0;
  if (prioritization.methodOfPrioritization == weighted)
  {
    for (int j = 0; j < parameterNames.size(); j++)
    {
      sum = sum + parameterWeights[j];
    }
  }

  prioritizationModel.ParameterNames.clear();
  prioritizationModel.ParameterWeights.clear();
  for (int j = 0; j < parameterNames.size(); j++)
  {
    string parameterName = parameterNames[j];
    inputdeck.ToLower(parameterName);
    prioritizationModel.ParameterNames.push_back(parameterName);
    if (prioritization.methodOfPrioritization == weighted)
    {
      prioritizationModel.ParameterWeights.push_back(parameterWeights[j] / sum);
    }
  }

  assestPrioritization.prioritizationModel.ParameterNames = prioritizationModel.ParameterNames;
  assestPrioritization.prioritizationModel.ParameterWeights = prioritizationModel.ParameterWeights;
  assestPrioritization.typeOfPrioritization = prioritization.typeOfPrioritization;
  assestPrioritization.ochestrationVariable = prioritization.ochestrationVariable;
  assestPrioritization.ochestrationMethod = prioritization.ochestrationMethod;
}

void ConfigurePrioritization::SetResourceClassPrioritization(Prioritization &prioritization,
                                                             Prioritization &assestPrioritization)
{
  assestPrioritization.targetFluid = prioritization.targetFluid;

  PrioritizationModel prioritizationModel;
  double sum = 0;
  if (prioritization.methodOfPrioritization == weighted)
  {
    for (int j = 0; j < prioritization.prioritizationModel.ParameterNames.size(); j++)
    {
      sum = sum + prioritization.prioritizationModel.ParameterWeights[j];
    }
  }

  prioritizationModel.ParameterNames.clear();
  prioritizationModel.ParameterWeights.clear();
  for (int j = 0; j < prioritization.prioritizationModel.ParameterNames.size(); j++)
  {
    string parameterName = prioritization.prioritizationModel.ParameterNames[j];
    inputdeck.ToLower(parameterName);
    prioritizationModel.ParameterNames.push_back(parameterName);
    if (prioritization.methodOfPrioritization == weighted)
    {
      prioritizationModel.ParameterWeights.push_back(prioritization.prioritizationModel.ParameterWeights[j] / sum);
    }
  }

  assestPrioritization.prioritizationModel.ParameterNames = prioritizationModel.ParameterNames;
  assestPrioritization.prioritizationModel.ParameterWeights = prioritizationModel.ParameterWeights;
  assestPrioritization.typeOfPrioritization = prioritization.typeOfPrioritization;
}

void ConfigurePrioritization::SetProjectPrioritization(Prioritization &prioritization,
                                                       Prioritization &assestPrioritization)
{

  vector<string> streams1 = {"OIL", "GAS", "CONDENSATE", "AG", "NAG"}; // when streamPrioritization.type is oil or ag
  vector<string> streams2 = {"GAS", "CONDENSATE", "OIL", "NAG", "AG"}; // when streamPrioritization.type is gas or nag
  int lent = streams1.size();
  vector<string> parameterNames;
  vector<double> parameterWeights;
  for (int i = 0; i < lent; i++)
  {
    parameterWeights.push_back(1.0);
    if (prioritization.typeOfStream == "NAGProjects")
    {
      parameterNames.push_back(streams2[i]);
    }
    else
    {
      parameterNames.push_back(streams1[i]);
    }
  }

  PrioritizationModel prioritizationModel;
  double sum = 0;
  if (prioritization.methodOfPrioritization == weighted)
  {
    for (int j = 0; j < parameterNames.size(); j++)
    {
      sum = sum + parameterWeights[j];
    }
  }

  prioritizationModel.ParameterNames.clear();
  prioritizationModel.ParameterWeights.clear();
  for (int j = 0; j < parameterNames.size(); j++)
  {
    string parameterName = parameterNames[j];
    inputdeck.ToLower(parameterName);
    prioritizationModel.ParameterNames.push_back(parameterName);
    if (prioritization.methodOfPrioritization == weighted)
    {
      prioritizationModel.ParameterWeights.push_back(parameterWeights[j] / sum);
    }
  }

  assestPrioritization.prioritizationModel.ParameterNames = prioritizationModel.ParameterNames;
  assestPrioritization.prioritizationModel.ParameterWeights = prioritizationModel.ParameterWeights;
  assestPrioritization.typeOfPrioritization = prioritization.typeOfPrioritization;
}

vector<Prioritization> ConfigurePrioritization::SetUpPrioritization(vector<FacilityStructExternal> &FacilityTable, Date &startDate, Date &stopDate,
                                                                  Prioritization &prioritization, vector<Prioritization> &nodalPrioritizations)
{

  vector<Prioritization> prioritizations = SetUpDefaultPrioritization(FacilityTable, startDate, stopDate);

  if (prioritization.typeOfPrioritization == wellPrioritization)
  {
    for (int i = 0; i < prioritizations.size(); i++)
    {
      SetWellPrioritization(prioritization, prioritizations[i]);
    }
  }

  if (prioritization.typeOfPrioritization == streamPrioritization &&
          prioritization.typeOfStream == "oil" ||
      prioritization.typeOfStream == "gas" ||
      prioritization.typeOfStream == "condensate")
  {

    for (int i = 0; i < prioritizations.size(); i++)
    {
      SetStreamPrioritization(prioritization, prioritizations[i]);
    }
  }

  if (prioritization.typeOfPrioritization == resourceClassPrioritization)
  {
    for (int i = 0; i < prioritizations.size(); i++)
    {
      SetResourceClassPrioritization(prioritization, prioritizations[i]);
    }
  }

  if (prioritization.typeOfPrioritization == projectPrioritization)
  {
    for (int i = 0; i < prioritizations.size(); i++)
    {
      SetProjectPrioritization(prioritization, prioritizations[i]);
    }
  }

  if (prioritization.typeOfPrioritization == nodalPrioritization)
  {
    for (int i = 0; i < prioritizations.size(); i++)
    {
      for (int j = 0; j < nodalPrioritizations.size(); j++)
      {
        string actualTypeOfPrioritization = nodalPrioritizations[j].typeOfPrioritization;

        if (prioritizations[i].FacilityName == nodalPrioritizations[j].FacilityName)
        {
          if (nodalPrioritizations[j].typeOfPrioritization == wellPrioritization)
          {
            SetWellPrioritization(nodalPrioritizations[j], prioritizations[i]);
          }
          if (nodalPrioritizations[j].typeOfPrioritization == streamPrioritization)
          {
            SetStreamPrioritization(nodalPrioritizations[j], prioritizations[i]);
          }
          if (nodalPrioritizations[j].typeOfPrioritization == resourceClassPrioritization)
          {
            SetResourceClassPrioritization(nodalPrioritizations[j], prioritizations[i]);
          }
          if (nodalPrioritizations[j].typeOfPrioritization == projectPrioritization)
          {
            SetProjectPrioritization(nodalPrioritizations[j], prioritizations[i]);
          }

          nodalPrioritizations[j].typeOfPrioritization = actualTypeOfPrioritization;
          break;
        }
      }
    }
  }
  return prioritizations;
}