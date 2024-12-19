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
  vector<Priotization> SetUpPrioritization(vector<FacilityStructExternal> &FacilityTable, Date &startDate, Date &stopDate,
                                           Priotization &priotization, vector<Priotization> &nodalPriotizations);
  vector<Priotization> SetUpDefaultPrioritization(vector<FacilityStructExternal> &FacilityTable, Date &startDate, Date &stopDate);
  void SetWellPrioritization(Priotization &priotization, Priotization &assestPriotization);
  void SetStreamPrioritization(Priotization &priotization, Priotization &assestPriotization);
  void SetResourceClassPrioritization(Priotization &priotization, Priotization &assestPriotization);
  void SetProjectPrioritization(Priotization &priotization, Priotization &assestPriotization);
};

ConfigurePrioritization::ConfigurePrioritization()
{
}

ConfigurePrioritization::~ConfigurePrioritization()
{
}

vector<Priotization> ConfigurePrioritization::SetUpDefaultPrioritization(vector<FacilityStructExternal> &FacilityTable, Date &startDate, Date &stopDate)
{
  vector<Priotization> priotizations;

  vector<string> parameterNames = vector<string>{High, Normal, Low};
  vector<double> parameterWeights = vector<double>{90, 50, 10}; // Create Ratios from this

  int i = 0, j = 0;
  for (i = 0; i < FacilityTable.size(); i++)
  {

    Priotization priotization;
    priotization.FromDate = startDate;

    priotization.ToDate = stopDate;

    priotization.FacilityName = FacilityTable[i].Primary_Facility;
    priotization.typeOfPrioritization = wellPrioritization;
    priotization.methodOfPrioritization = sequential;
    if (FacilityTable[i].equipmentType == gas_plant)
    {
      priotization.targetFluid = gas;
    }

    if (FacilityTable[i].equipmentType == gas_asset)
    {
      priotization.targetFluid = gas;
    }

    if (FacilityTable[i].equipmentType == flow_station)
    {
      priotization.targetFluid = oil;
    }

    if (FacilityTable[i].equipmentType == oil_asset)
    {
      priotization.targetFluid = oil;
    }

    if (FacilityTable[i].equipmentType == ag_asset)
    {
      priotization.targetFluid = ag;
    }

    if (FacilityTable[i].equipmentType == nag_asset)
    {
      priotization.targetFluid = nag;
    }

    if (FacilityTable[i].equipmentType == condensate_asset)
    {
      priotization.targetFluid = condensate;
    }

    double sum = 0;
    for (j = 0; j < parameterWeights.size(); j++)
    {
      sum = sum + parameterWeights[j];
    }

    for (j = 0; j < parameterNames.size(); j++)
    {
      priotization.prioritizationModel.ParameterNames.push_back(parameterNames[j]);
      priotization.prioritizationModel.ParameterWeights.push_back(parameterWeights[j] / sum);
    }

    priotizations.push_back(priotization);
  }

  return priotizations;
}

void ConfigurePrioritization::SetWellPrioritization(Priotization &priotization, Priotization &assestPriotization)
{

  assestPriotization.targetFluid = priotization.targetFluid;

  PrioritizationModel prioritizationModel;
  double sum = 0;
  if (priotization.methodOfPrioritization == weighted)
  {
    for (int j = 0; j < priotization.prioritizationModel.ParameterNames.size(); j++)
    {
      sum = sum + priotization.prioritizationModel.ParameterWeights[j];
    }
  }

  prioritizationModel.ParameterNames.clear();
  prioritizationModel.ParameterWeights.clear();
  for (int j = 0; j < priotization.prioritizationModel.ParameterNames.size(); j++)
  {
    string parameterName = priotization.prioritizationModel.ParameterNames[j];
    inputdeck.ToLower(parameterName);
    prioritizationModel.ParameterNames.push_back(parameterName);
    if (priotization.methodOfPrioritization == weighted)
    {
      prioritizationModel.ParameterWeights.push_back(priotization.prioritizationModel.ParameterWeights[j] / sum);
    }
  }

  assestPriotization.prioritizationModel.ParameterNames = prioritizationModel.ParameterNames;
  assestPriotization.prioritizationModel.ParameterWeights = prioritizationModel.ParameterWeights;
  assestPriotization.typeOfPrioritization = priotization.typeOfPrioritization;
}

void ConfigurePrioritization::SetStreamPrioritization(Priotization &priotization,
                                                      Priotization &assestPriotization)
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
    if (priotization.typeOfStream == "gas")
    {
      parameterNames.push_back(streamsGasPrioritized[i]);
    }

    if (priotization.typeOfStream == "oil")
    {
      parameterNames.push_back(streamsOilPrioritized[i]);
    }

    if (priotization.typeOfStream == "condensate")
    {
      parameterNames.push_back(streamsCondensatePrioritized[i]);
    }
  }

  PrioritizationModel prioritizationModel;
  double sum = 0;
  if (priotization.methodOfPrioritization == weighted)
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
    if (priotization.methodOfPrioritization == weighted)
    {
      prioritizationModel.ParameterWeights.push_back(parameterWeights[j] / sum);
    }
  }

  assestPriotization.prioritizationModel.ParameterNames = prioritizationModel.ParameterNames;
  assestPriotization.prioritizationModel.ParameterWeights = prioritizationModel.ParameterWeights;
  assestPriotization.typeOfPrioritization = priotization.typeOfPrioritization;
  assestPriotization.ochestrationVariable = priotization.ochestrationVariable;
  assestPriotization.ochestrationMethod = priotization.ochestrationMethod;
}

void ConfigurePrioritization::SetResourceClassPrioritization(Priotization &priotization,
                                                             Priotization &assestPriotization)
{
  assestPriotization.targetFluid = priotization.targetFluid;

  PrioritizationModel prioritizationModel;
  double sum = 0;
  if (priotization.methodOfPrioritization == weighted)
  {
    for (int j = 0; j < priotization.prioritizationModel.ParameterNames.size(); j++)
    {
      sum = sum + priotization.prioritizationModel.ParameterWeights[j];
    }
  }

  prioritizationModel.ParameterNames.clear();
  prioritizationModel.ParameterWeights.clear();
  for (int j = 0; j < priotization.prioritizationModel.ParameterNames.size(); j++)
  {
    string parameterName = priotization.prioritizationModel.ParameterNames[j];
    inputdeck.ToLower(parameterName);
    prioritizationModel.ParameterNames.push_back(parameterName);
    if (priotization.methodOfPrioritization == weighted)
    {
      prioritizationModel.ParameterWeights.push_back(priotization.prioritizationModel.ParameterWeights[j] / sum);
    }
  }

  assestPriotization.prioritizationModel.ParameterNames = prioritizationModel.ParameterNames;
  assestPriotization.prioritizationModel.ParameterWeights = prioritizationModel.ParameterWeights;
  assestPriotization.typeOfPrioritization = priotization.typeOfPrioritization;
}

void ConfigurePrioritization::SetProjectPrioritization(Priotization &priotization,
                                                       Priotization &assestPriotization)
{

  vector<string> streams1 = {"OIL", "GAS", "CONDENSATE", "AG", "NAG"}; // when streamPrioritization.type is oil or ag
  vector<string> streams2 = {"GAS", "CONDENSATE", "OIL", "NAG", "AG"}; // when streamPrioritization.type is gas or nag
  int lent = streams1.size();
  vector<string> parameterNames;
  vector<double> parameterWeights;
  for (int i = 0; i < lent; i++)
  {
    parameterWeights.push_back(1.0);
    if (priotization.typeOfStream == "NAGProjects")
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
  if (priotization.methodOfPrioritization == weighted)
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
    if (priotization.methodOfPrioritization == weighted)
    {
      prioritizationModel.ParameterWeights.push_back(parameterWeights[j] / sum);
    }
  }

  assestPriotization.prioritizationModel.ParameterNames = prioritizationModel.ParameterNames;
  assestPriotization.prioritizationModel.ParameterWeights = prioritizationModel.ParameterWeights;
  assestPriotization.typeOfPrioritization = priotization.typeOfPrioritization;
}

vector<Priotization> ConfigurePrioritization::SetUpPrioritization(vector<FacilityStructExternal> &FacilityTable, Date &startDate, Date &stopDate,
                                                                  Priotization &priotization, vector<Priotization> &nodalPriotizations)
{

  vector<Priotization> priotizations = SetUpDefaultPrioritization(FacilityTable, startDate, stopDate);

  if (priotization.typeOfPrioritization == wellPrioritization)
  {
    for (int i = 0; i < priotizations.size(); i++)
    {
      SetWellPrioritization(priotization, priotizations[i]);
    }
  }

  if (priotization.typeOfPrioritization == streamPrioritization &&
          priotization.typeOfStream == "oil" ||
      priotization.typeOfStream == "gas" ||
      priotization.typeOfStream == "condensate")
  {

    for (int i = 0; i < priotizations.size(); i++)
    {
      SetStreamPrioritization(priotization, priotizations[i]);
    }
  }

  if (priotization.typeOfPrioritization == resourceClassPrioritization)
  {
    for (int i = 0; i < priotizations.size(); i++)
    {
      SetResourceClassPrioritization(priotization, priotizations[i]);
    }
  }

  if (priotization.typeOfPrioritization == projectPrioritization)
  {
    for (int i = 0; i < priotizations.size(); i++)
    {
      SetProjectPrioritization(priotization, priotizations[i]);
    }
  }

  if (priotization.typeOfPrioritization == nodalPrioritization)
  {
    for (int i = 0; i < priotizations.size(); i++)
    {
      for (int j = 0; j < nodalPriotizations.size(); j++)
      {
        string actualTypeOfPrioritization = nodalPriotizations[j].typeOfPrioritization;

        if (priotizations[i].FacilityName == nodalPriotizations[j].FacilityName)
        {
          if (nodalPriotizations[j].typeOfPrioritization == wellPrioritization)
          {
            SetWellPrioritization(nodalPriotizations[j], priotizations[i]);
          }
          if (nodalPriotizations[j].typeOfPrioritization == streamPrioritization)
          {
            SetStreamPrioritization(nodalPriotizations[j], priotizations[i]);
          }
          if (nodalPriotizations[j].typeOfPrioritization == resourceClassPrioritization)
          {
            SetResourceClassPrioritization(nodalPriotizations[j], priotizations[i]);
          }
          if (nodalPriotizations[j].typeOfPrioritization == projectPrioritization)
          {
            SetProjectPrioritization(nodalPriotizations[j], priotizations[i]);
          }

          nodalPriotizations[j].typeOfPrioritization = actualTypeOfPrioritization;
          break;
        }
      }
    }
  }
  return priotizations;
}